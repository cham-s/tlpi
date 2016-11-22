#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h> 
#include "tlpi_hdr.h"
#include <getopt.h>

#define  BUF_SIZE 1024

int
main(int ac, char **av)
{
	char	buf[BUF_SIZE + 1];
	int		fd;
	int		flags;
	int		perm_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	int		opt;
	int		fname_position = 0;
	ssize_t	ret_read;
	ssize_t	ret_write;

	flags = O_WRONLY | O_CREAT;
	if (ac < 2 || strcmp(av[1], "--help") == 0)
		usageErr("%s [-a] newfile\n", av[0]);

	while ((opt = getopt(ac, av, "a")) != -1)
	{
		switch(opt)
		{
			case 'a': /* append to file if option a appears */
				flags = O_WRONLY | O_CREAT | O_APPEND;
				fname_position = 2;
			default:
				flags = O_WRONLY | O_CREAT;
				fname_position = 1;
		}
	}
	
	fd = open(av[1], flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
		errExit("open");
	while((ret_read = read(0, buf, BUF_SIZE)) > 0)
	{
		if (write(fd, buf, ret_read) != ret_read)
			fatal("couldn't write the whole buffer");
		if (ret_read == -1)
			errExit("close");
		buf[ret_read] = '\0';
		printf("%s", buf);
	}
}
