#include <iostream>
#include <set>
#include <signal.h>

#include "scanner.h"

using namespace std;

void sighandler(int sig) {
	if (sig == SIGINT) {
		exiting = true;
	}
}

int main() {
	struct sigaction sa;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sighandler;
	sigaction(SIGINT, &sa, nullptr);

	set<uint32_t> ids;

	open_device();

	cout << "Device opened." << endl;
	cout << "Press Ctrl-C to stop enrollment." << endl;
	cout << endl;

	uint32_t prev_id = 0;
	while (true && !exiting) {
		uint32_t id = wait_new_id();
		if (!exiting) {
			ids.insert(id);
			cout << "Tag swap detected." << endl;
		}
	}
	
	cout << "Enrollment completed." << endl;
	for (const auto &a : ids) {
		cout << a << endl;
	}
		
	close_device();
	return 0;
}
