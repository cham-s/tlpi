#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include "tlpi_hdr.h" 

int
main(int ac, char **av)
{
	size_t	len;
	off_t	offset;
	int		fd;
	int 	ap;
	int		j;
	char	*buf;
	ssize_t	ret_read;
	ssize_t	ret_write;

	if (ac < 3 || strcmp(av[1], "--help") == 0)
		usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", av[0]);

	fd = open(av[1], O_RDWR | O_CREAT|
					 S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
		errExit("open");

	for (ap = 2; ap < ac ; ap++)
	{
		switch (av[ap][0])
		{
			case 'r':
			case 'R':
				len = getLong(&av[ap][1], GN_ANY_BASE, av[ap]);
				buf = malloc(len);
				if (buf ==  NULL)
					errExit("malloc");
				ret_read = read(fd, buf, len);
				if (ret_read == -1)
					errExit("read");
				if (ret_read == 0)
					printf("%s: end-of-file\n", av[ap]);
				else 
				{
					printf("%s: ", av[ap]);
					for (j = 0; j < ret_read; j++)
					{
						if (av[ap][0] == 'r')
							printf("%c", isprint((unsigned char)buf[j]) ? buf[j] : '?');
						else
							printf("%02x ", (unsigned int) buf[j]);
					}
					printf("\n");
				}
				free(buf);
				break;
			case 'w': /* write string at the current offset */
				ret_write = write(fd, &av[ap][1], strlen(&av[ap][1]));
				if (ret_write == -1)
					errExit("write");
				printf("%s: wrote %ld bytes\n", av[ap], (long) ret_write);
				break;
			case 's': /* change file offset */
				offset = getLong(&av[ap][1], GN_ANY_BASE, av[ap]);
				if (lseek(fd, offset, SEEK_SET) == -1)
					errExit("lseek");
				printf("%s: seek succeeded\n", av[ap]);
				break;
			default:
				cmdLineErr("Argument must start with [rRws]: %s\n", av[ap]);
		}
	}
	return (EXIT_SUCCESS);
}

