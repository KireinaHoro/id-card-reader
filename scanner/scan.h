#include <stdint.h>
#include <stdbool.h>

#ifndef SCANNER_H
#define SCANNER_H

#define ENOCARDPRESENT 0xffffffff

#ifdef __cplusplus
extern "C" {
#endif

extern bool exiting;

bool open_device();
void close_device();

uint32_t get_current_id();
uint32_t wait_new_id();

#ifdef __cplusplus
}
#endif

#endif /* SCANNER_H */
