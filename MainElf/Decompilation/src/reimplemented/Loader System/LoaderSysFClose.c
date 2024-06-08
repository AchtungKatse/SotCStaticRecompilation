#include "Context.h"
#include "FunctionList.h"

void LoaderSysFClose(void* fileHandle){
	fclose(fileHandle);
}
