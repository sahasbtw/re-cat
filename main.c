#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXBUFF 1024

int main(int argc, char **argv)
{
	if (argc == 1) {
		fprintf(stderr, "Usage: %s file.txt\n", argv[0]);
		exit(1);
	}

	for (int i = 1; i < argc; i++) {

		int fd = open(argv[i], O_RDONLY);
		if (fd < 0) {
			perror("open");
			exit(1);
		}

		long eof = lseek(fd, 0, SEEK_END);
		if (eof < 0) {
			perror("eof lseek");
			exit(1);
		}

		printf("[%s]\n", argv[i]);

		char buf[MAXBUFF];

		if (lseek(fd, 0, SEEK_SET) < 0) { /* seek back to the beginning of the file */
			perror("lseek");
			exit(1);
		}

		if (eof > MAXBUFF) {
			int parts = ((eof % MAXBUFF) == 0) ? eof / MAXBUFF : (eof / MAXBUFF) + 1;
			int n;
			long cur;
			ssize_t rc;

			for (n = 0; n < parts; n++) {

				if ((rc = read(fd, buf, MAXBUFF)) < 0) {
					perror("read");
					exit(1);
				}
				buf[rc] = '\0';
				printf("%s", buf);

				cur = (n + 1) * MAXBUFF;
				if (lseek(fd, cur, SEEK_SET) < 0) {
					perror("lseek");
					exit(1);
				}

			}

		} else {

			ssize_t rc;
			if ((rc = read(fd, buf, eof)) < 0) {
				perror("read");
				exit(1);
			}
			buf[eof-1] = '\0';
			printf("%s\n", buf);
		}
	}

	return 0;
}
