#include <archiver.h>

int write_archive_header(struct archive *archive)
{
	check_io_errors(write(archive->fd, archive->file_descriptors, archive->files_count * sizeof(struct descr)), "write()");

	check_io_errors(write(archive->fd, &archive->files_count, sizeof(archive->files_count)), "write()");
	
	return 0;
}

/* TODO: тут нужно обработать новый файл: seek и read не отработают на нём */
int read_archive_header(struct archive *archive)
{

	size_t descriptors_size = sizeof(struct descr) * archive->append_files_count;

	int result;
	if (COM_APPEND == archive->command || COM_LIST == archive->command) {
		result = lseek(archive->fd, -sizeof(archive->files_count), SEEK_END);
		check_io_errors(result, "lseek()");	


		result = read(archive->fd, &archive->files_count, sizeof(archive->files_count));
		if (!check_io_errors(result, "read()")) {
			fprintf(stderr, "read 0 bytes from %s. Exiting.\n", archive->file_name);
			exit(1);
		}

		archive->headers_offset = sizeof(struct descr) * archive->files_count;
		archive->headers_offset += sizeof(archive->files_count);

		descriptors_size += sizeof(struct descr) * archive->files_count;
	}

	archive->file_descriptors = malloc(descriptors_size);
	if (!archive->file_descriptors)
	{
		printf("Cannot allocate memory for %d file descriptors\n",
		       (int)archive->files_count);
		exit(1);
	}


	if (COM_APPEND == archive->command || COM_LIST == archive->command) {
		result = lseek(archive->fd, -archive->headers_offset, SEEK_END);
		check_io_errors(result, "lseek()");


		result = read(archive->fd, archive->file_descriptors, archive->headers_offset - sizeof(archive->files_count));
		check_io_errors(result, "read()");
	}

	return result;
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
