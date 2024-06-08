#include <stdio.h>
#include "Context.h"
#include "FunctionList.h"

void *LoaderSysFOpen(char *path, uint param_2, uint param_3)
{
	// CD Path
	char *cdPath = path;
	printf("Trying to open file %p\n", cdPath);
	printf("Trying to open file %s\n", cdPath);

	char realPathBuffer[0x200];
	int convertResult = ConvertCDToLocalPath(cdPath, realPathBuffer, sizeof(realPathBuffer));
	if (convertResult != 0)
		return -1;

	printf("Reading file '%s'\n", realPathBuffer);
	// printf("Loaded file at %p\n", file);
	return fopen(realPathBuffer, "rb");
}
