#include <stdio.h>
#include <dirent.h>
#include "memmem.h"

int indexOfBin(char *str, int len1, const char *substr, int len2)
{
	char *result = memmem(str, len1, substr, len2);
	if (result == NULL)
	{
		return -1;
	}
	return result - str;
}

int indexOf(const char *str, const char *substr)
{
	char *result = strstr(str, substr);
	if (result == NULL)
	{
		return -1;
	}
	return result - str;
}


void getMapName(char *mapName, char *fileName)
{
	char buff[65536];
	FILE *f = fopen(fileName, "rb");
	
	while (fread(buff, sizeof(char), 65536, f) > 0)
	{
		if (indexOfBin(buff, sizeof(buff), ".bsp", 4) != -1)
		{
			int start = indexOfBin(buff, sizeof(buff), "maps\\", 5) + 5;
			int end = indexOfBin(buff, sizeof(buff), ".bsp", 4);
			strncpy(mapName, buff + start, end - start);
			fclose(f);
		}
	}
	fclose(f);
}

int main(int argc, char *argv[])
{
	DIR *d = NULL;
	struct dirent *fileList;
	
	// Fail if run with arguments
	if (argc != 1)
	{
		return -1;
	}
	
	// Fetch all files in working directory
	d = opendir(".");
	if (d == NULL)
	{
		perror("Failed to open current directory.");
	}
	while ((fileList = readdir(d)) != NULL)
	{
		char newFileName[256];
		char mapName[256];
		char *fullFileName = fileList->d_name;
		strcpy(newFileName, fullFileName);
		
		if (indexOf(fullFileName, ".dem") != -1)
		{
			memset(mapName, 0, sizeof(mapName));
			getMapName(mapName, fullFileName);
			printf("Found file: %s with map name %s\n", fullFileName, mapName);
		}
	}
	closedir(d);

	return 0;
}
