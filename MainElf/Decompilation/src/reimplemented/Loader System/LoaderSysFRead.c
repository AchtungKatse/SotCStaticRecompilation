#include <stdio.h>
#include "Context.h"
#include "FunctionList.h"

int LoaderSysFRead(void *filePointer, void *output, int length)
{
	printf("Reading %d bytes from file %p to %p\n", length, filePointer, output);
	return fread(output, 1, length, filePointer);
}
