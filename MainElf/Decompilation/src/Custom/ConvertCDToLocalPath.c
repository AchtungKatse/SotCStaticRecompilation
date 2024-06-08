#include <string.h>

int ConvertCDToLocalPath(char *cdPath, char *localPathBuffer, int bufferSize)
{
	// Convert cd path to filesystem path
	const char *filesystemPath = "/home/achtung/Documents/RE/ShadowOfTheColossus/Files/";

	const char *cdBasePath = "cdrom0:\\";
	const int cdBasePathLength = sizeof(cdBasePath);
	
	printf("Converting cd path '%p' to new new path\n", cdPath);
	printf("Converting cd path '%s' to new new path\n", cdPath);

	if (strlen(cdPath) - cdBasePathLength + strlen(filesystemPath) < bufferSize)
	{
		if (strncmp("cdrom0:\\", cdPath, cdBasePathLength) == 0)
		{
			// It's meant to be a cd path
			strcpy(localPathBuffer, filesystemPath);
			strcat(localPathBuffer, cdPath + cdBasePathLength);

			int realPathLength = strlen(localPathBuffer);
			localPathBuffer[realPathLength - 2] = 0;

			printf("Trying to read '%s' as '%s'\n", cdPath, localPathBuffer);
			return 0;
		}
		else
		{
			printf("Trying to read file '%s': outsize of cd\n", cdPath);
		}
	}
	else
	{
		printf("Trying to find path that exceeds path buffer size\n");
	}

	return -1;
}