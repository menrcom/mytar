#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

/* Header:  <descr 1><descr 2>...<descr count>
 * Header length: descr_count*sizeof(struct descr) + sizeof(descr_count)
 */

/* Usage: mytar -a -f file.mytar file1 file2 file3 ... */
/* Usage: mytar -t -f file.mytar */	

/* TODO: for each file: get length, append data to archive, add 		descriptor to header. */


enum commands {
	COM_UNKNOWN = 0,
	COM_APPEND,
	COM_LIST,
	COM_CREATE
};

struct descr {
	char file_name[256];
	size_t data_length;
	size_t data_start;
} __attribute__ ((packed));


struct archive {
	enum commands command;
	char *file_name;
	int fmode;
	int fd;
	uint32_t files_count;
	size_t append_files_count;
	size_t headers_offset;
	struct descr *file_descriptors;
};


int usage(int argc, char **argv);
int process_command_line(struct archive *a, int argc, char **argv);

int cleanup(struct archive *a);
int check_io_errors(int ret_code, const char *operation);
int open_archive_file(struct archive *archive);

int append_file(struct archive *archive, char *file_name);
int write_archive_data(struct archive *archive, int argc, char **argv);

int list_archive_content(struct archive *archive);

int write_archive_header(struct archive *archive);
int read_archive_header(struct archive *archive);


/*
 * Local variables:
 *  c-file-style: "linux"
 *  indent-tabs-mode: t
 *  c-indent-level: 8
 *  c-basic-offset: 8
 *  tab-width: 8
 * End:
 */


