#include <iostream>
#include <poll.h>
#include <unistd.h>

int main(void) {
	char name[255];
	struct pollfd mypoll;
	int counter = 0;

	mypoll.fd = 1;
	mypoll.events = POLLIN;

	while (1) {
		poll(&mypoll, 1, 100);
		if (mypoll.revents & POLLIN) {
			read(0, name, sizeof(name));
			printf("Hello %s\n", name);
			break;
		}
		else {
			counter++;
		}
	}
	printf("It took you %d ms to type in your name.\n", counter * 100);
}