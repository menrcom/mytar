#include <archiver.h>

int cleanup(struct archive *a)
{
	close(a->fd);
	free(a->file_descriptors);
	return 0;
}

int check_io_errors(int ret_code, const char *operation)
{
	if (-1 == ret_code) {
		fprintf(stderr, "Error executing %s: %s\n", operation, strerror(errno));
		exit(-1);
	}

	return ret_code;
}

int open_archive_file(struct archive *archive)
{
	if ('-' == archive.file_name[0])
		archive.fd = STDIN_FILENO;
	else {
		archive.fd = open(archive.file_name, archive.fmode, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
		check_io_errors(archive.fd, "open()");		
	}

	return 1;
}


/*
 * Local variables:
 *  c-file-style: "linux"
 *  indent-tabs-mode: t
 *  c-indent-level: 8
 *  c-basic-offset: 8
 *  tab-width: 8
 * End:
 */
