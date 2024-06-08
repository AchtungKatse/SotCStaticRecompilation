#include <stdio.h>

#include "SceStatus.h"
#include "Context.h"
#include "FunctionList.h"

int LoaderSysGetstat(char *name, void *buffer)
{
	SceStatus* status = buffer;
	
	char realPath[0x200];
	printf("Getting file %p info.\n", name);
	int convertResult = ConvertCDToLocalPath(name, realPath, sizeof(realPath));
	printf("Trying to open file at path %s\n", realPath);

	FILE* file = fopen(realPath, "r");
	if (!file)
	{
		printf("Failed to open file at path %s\n", realPath);
		return -1;
	}
	fseek(file, 0L, SEEK_END);
	int length = ftell(file);

	fclose(file);

	status->length = length;
	


	return 0;
}
