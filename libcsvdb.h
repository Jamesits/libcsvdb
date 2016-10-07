#pragma once
#ifndef __LIBCSVDB_H__
#define __LIBCSVDB_H__

struct csvdbhandle {
	FILE *file;
};

typedef struct csvhandle* CSVDBHANDLE;
typedef int CSVDBLINEHANDLE;


CSVHANDLE CSVDBOpen(char *file, char *mode);
int CSVDBClose(CSVHANDLE handle);
void CSVDBInsertRecord(CSVHANDLE handle, const char *fmt, ...);
void CSVDBSearchRecord(CSVHANDLE handle, int field, const char *content);


#endif