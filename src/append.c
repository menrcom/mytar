#include <archiver.h>

/* file offset must be set properly before call. */
int append_file(struct archive *archive, char *file_name)
{
	struct descr *new_descr = archive->file_descriptors + archive->files_count;

	/* Взять последний дескриптор, посчитать смещение для данных нового файла */
	if (archive->files_count) {
		struct descr *last_descr = new_descr - 1;
		new_descr->data_start = last_descr->data_start + last_descr->data_length;
	} else
		new_descr->data_start = 0;

	
	/* Получили размер очередного файла в архиве */
	struct stat stat_data;
	if (-1 == stat(file_name, &stat_data)) {
		fprintf(stderr, "Cannot stat(%s): %s\n", file_name, strerror(errno));
		return 0;
	}
	new_descr->data_length = stat_data.st_size;


	int fd = open(file_name, O_RDONLY);
	if (-1 == fd) {
		fprintf(stderr, "Cannot open(%s): %s\n", file_name, strerror(errno));
		return 0;
	}
	void *file_data = mmap(NULL, new_descr->data_length, PROT_READ, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == file_data) {
		fprintf(stderr, "Cannot mmap(%s): %s\n", file_name, strerror(errno));
		close(fd); 	/* TODO: check return status here. */
		return 0;
	}


	check_io_errors(write(archive->fd, file_data, new_descr->data_length), "write()");
	munmap(file_data, new_descr->data_length); /* TODO: check return status here. */
	close(fd); /* TODO: check return status here. */

	
	strncpy(new_descr->file_name, file_name, 255);
	/* Если до сюда не дошли - невалидный дескриптор просто потеряется */
	return ++archive->files_count;
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
