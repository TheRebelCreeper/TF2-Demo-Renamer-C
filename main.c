#define PCRE2_STATIC
#define PCRE2_CODE_UNIT_WIDTH 8
#include <stdio.h>
#include <dirent.h>
#include "pcre2.h"
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

int isValidDemo(char *fileName)
{
	const char *pattern = "([a-zA-Z]*)(_?)(\\d{4}-\\d{2}-\\d{2})_(\\d{2}-\\d{2}-\\d{2})(\\.dem)";
	const unsigned char *src = (unsigned char*)fileName;
	int error_number;
	PCRE2_SIZE error_offset;
	pcre2_code *re = pcre2_compile_8((unsigned char*)pattern, PCRE2_ZERO_TERMINATED, 0, &error_number, &error_offset, NULL);
	if (re == NULL)
	{
		return -1;
	}
	pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
	int rc = pcre2_match(re, src, strlen(fileName), 0, 0, match_data, NULL);
	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return rc;
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
			snprintf(mapName, end - start + 1, "%s", buff + start);
			fclose(f);
			return;
		}
	}
	sprintf(mapName, "error");
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
		char mapName[128];
		char *fullFileName = fileList->d_name;
		int i;
		char c;
		
		if ((i = indexOf(fullFileName, ".dem")) != -1 && isValidDemo(fullFileName) == 6)
		{
			// Parse demo file for map name
			getMapName(mapName, fullFileName);
			
			// Add map name before file extension
			c = fullFileName[i];
			fullFileName[i] = '\0';
			sprintf(newFileName, "%s_%s.dem", fullFileName, mapName);
			fullFileName[i] = c;
			
			// Rename file
			//if (rename(fullFileName, newFileName) != 0)
			//{
			//	perror("Failed to rename file");
			//}	
			
			printf("Renaming %s to %s\n", fullFileName, newFileName);
		}
		else
		{
			printf("Skipping %s\n", fullFileName);
		}
	}
	closedir(d);

	return 0;
}
