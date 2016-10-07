#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __LIBCSVDB_DELIMETER ','
#define __LIBCSVDB_DELIMETER_STRING ","

CSVHANDLE CSVDBOpen(char *file, char *mode)
{
	struct csvhandle* handle = malloc(sizeof(struct csvhandle));
	handle.file = fopen(file, "a+");
	return handle;
}

int CSVDBClose(CSVHANDLE handle){
	fclose(handle.file);
	free(handle);
	return 0;
}

void CSVDBInsertRecord(CSVHANDLE handle, const char *fmt, ...) {
   va_list arg;
   int done;

   va_start (arg, format);
   done = vfprintf (handle.file, format, arg);
   fprintf(handle.file, __LIBCSVDB_DELIMETER_STRING);
   va_end (arg);

   return done;
}

CSVLINEHANDLE CSVDBSearchRecord(CSVHANDLE handle, int field, const char *content) {
	// simple and naive handling
	fseek(handle.file, 0, SEEK_SET);
	char buf[1024];
	int record_count = 0;
	while (!feof(myFile)) {
		++record_count;
		fscanf(handle.file, "%1023s", buf);
		int end_pos = 0;
		while (field--) while(buf[++end_pos] == __LIBCSVDB_DELIMETER);
		int start_pos = end_pos;
		while(start_pos && buf[--start_pos] == __LIBCSVDB_DELIMETER);
		int len = end_pos - start_pos + 1;
		char *cmpbuf = malloc((len + 1) * sizeof(char));
		memcpy(cmpbuf, buf + start_pos, len);
		cmpbuf[len + 1] = 0;
		if (!strcmp(cmpbuf, content)) return record_count;
	}
	return -1;
}