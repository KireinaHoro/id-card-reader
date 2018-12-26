#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <nfc/nfc.h>

#include "common.h"
#include "scanner.h"

nfc_device *pnd;
nfc_target nt;
nfc_context *context;

bool device_initialized = false;

bool exiting = false;

bool open_device() {
	if (device_initialized)
		return true;
	// Initialize libnfc and set the nfc_context
	nfc_init(&context);
	if (context == NULL) {
		debug("failed to create device context\n");
		return false;
	}

	// Open, using the first available NFC device which can be in order of selection:
	//   - default device specified using environment variable or
	//   - first specified device in libnfc.conf (/etc/nfc) or
	//   - first specified device in device-configuration directory (/etc/nfc/devices.d) or
	//   - first auto-detected (if feature is not disabled in libnfc.conf) device
	pnd = nfc_open(context, NULL);

	if (pnd == NULL) {
		debug("failed to open device context\n");
		return false;
	}
	// Set opened NFC device to initiator mode
	if (nfc_initiator_init(pnd) < 0) {
		debug("failed to set device to initiator mode\n");
		return false;
	}

	debug("NFC reader: %s opened\n", nfc_device_get_name(pnd));
	device_initialized = true;
	return true;
}

void close_device() {
	if (!device_initialized) 
		return;
	// Close NFC device
	nfc_close(pnd);
	// Release the context
	nfc_exit(context);
	device_initialized = false;
}

uint32_t get_current_id() {
	if (!device_initialized && !open_device()) {
		debug("failed to open device\n");
		return ENOCARDPRESENT;
	}

	// Poll for a ISO14443A (MIFARE) tag
	const nfc_modulation nmMifare = {
		.nmt = NMT_ISO14443A,
		.nbr = NBR_106,
	};
	if (nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt) > 0) {
		// Mifare Classic cards should have a ID of 4 bytes
		if (nt.nti.nai.szUidLen != 4) {
			debug("tag id length = %d > 4 (expected)\n", nt.nti.nai.szUidLen);
			return ENOCARDPRESENT;
		}
		uint32_t mifare_id = *(uint32_t*)nt.nti.nai.abtUid;
		return mifare_id;
	} else {
		debug("no tags detected\n");
		return ENOCARDPRESENT;
	}
}

uint32_t wait_new_id() {
	static bool first_call = true;
	static uint32_t curr_id = ENOCARDPRESENT;
	if (first_call && curr_id == ENOCARDPRESENT) {
		while (curr_id == ENOCARDPRESENT) {
			curr_id = get_current_id();
			usleep(10 * 1000);
		}
		first_call = false;
		return curr_id;
	} else {
		while (true && !exiting) {
			uint32_t id = get_current_id();
			usleep(10 * 1000);
			if (id != ENOCARDPRESENT && id != curr_id) {
				curr_id = id;
				return id;
			}
		}
	}
}
