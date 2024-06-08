#include "Context.h"
#include "FunctionList.h"
#include <pthread.h>

void CreateThread(ThreadParam* parameters)
{
	pthread_t thread;
	printf("Creating thread with function: %p\n", parameters->function);
	printf("_execProgWithThread address    %p\n", _execProgWithThread);
	pthread_create(&thread, NULL, parameters->function, parameters->stack);
}
