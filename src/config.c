#include <archiver.h>

int usage(int argc, char **argv)
{
	fprintf(stderr, "Usage: %s -c -f file.mytar file1 file2 file3 ... - to create new archive file\n", argv[0]);
	fprintf(stderr, "Usage: %s -a -f file.mytar file1 file2 file3 ... - to append to existing archive file\n", argv[0]);
	fprintf(stderr, "Usage: %s -t -f file.mytar                       - to list existing archive file contents\n", argv[0]);
	return 1;
}

static struct option long_options[] = {
	{"create", no_argument, 0, 'c'},
	{"list", no_argument, 0, 't'},
	{"append", no_argument, 0, 'a'},
	{"file", required_argument, 0, 'f'},
	{0,0,0,0}
};

int process_command_line(struct archive *a, int argc, char **argv)
{
	int c;
	int option_index = 1;

	do {

		c = getopt_long(argc, argv, "ctaf:", long_options, NULL);
		switch (c) {
		case 'c':
			archive.command = COM_CREATE;
			archive.fmode = O_RDWR|O_CREAT|O_EXCL;
			break;
		case 't':

			archive.command = COM_LIST;
			archive.fmode = O_RDONLY;

			break;

		case 'a':
			archive.command = COM_APPEND;
			archive.fmode = O_RDWR|O_APPEND;
			break;

		case 'f':
			archive.file_name = optarg;
			break;

		case -1:
			break;
		case '?':
		case ':':
		default:
			fprintf(stderr, "Unknown option: %c\n", c);
			return 0;
			break;
		} /* switch(c) */
		option_index++;
	} while(c && -1 != c);

	/* argv[option_index] == file1 */

	archive.append_files_count = argc - option_index;

	if (!archive.file_name)
		return 0;

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
