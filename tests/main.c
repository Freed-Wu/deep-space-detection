#if 0
gcc "$0" -oa && exec ./a "$@"
#endif
/*
 * Test program to simulate center board
 * Refer docs/resources/serial-transform-protocol.md
 */
#ifndef TTY
#define TTY "/dev/ttyUSB1"
#endif
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int fd = open(TTY, O_RDWR | O_NDELAY | O_NOCTTY);
	if (fd == -1) {
		perror(TTY);
		return EXIT_FAILURE;
	}
	else {
		fcntl(fd, F_SETFL, 0);
	}
	char str[20];
	ssize_t n = read(fd, str, 2);
	printf("%ld\n", n);
	n = write(fd, str, 4);
	return EXIT_SUCCESS;
}
