#include <archiver.h>



int write_archive_data(struct archive *archive, int option_index, int argc, char **argv)
{

	check_io_errors(lseek(archive->fd, -archive->headers_offset, SEEK_END), "lseek()");

	int index;

	for (index = option_index; index < argc; index++) {
		char *cur_file_name = argv[index];
		printf("Archive %s: writing file %s\n", archive->file_name, cur_file_name);
		append_file(archive, cur_file_name);
	}
	
	return 0;
}



struct archive archive = { 0 };

int main(int argc, char **argv)
{

	if (!process_command_line(&archive, argc, argv)) {
		usage(argc, argv);
		return -1;
	}


	!open_archive_file(&archive);


	switch (archive.command) {
	case COM_APPEND:
	case COM_CREATE:
		read_archive_header(&archive);
		write_archive_data(&archive, option_index, argc, argv);
		write_archive_header(&archive);
		break;

	case COM_LIST:
		read_archive_header(&archive);
		list_archive_content(&archive);
		break;

	case COM_UNKNOWN:
	default:
		cleanup(&archive);
		return(usage(argc, argv));
	}

	cleanup(&archive);
	return 0;

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
