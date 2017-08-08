#include "libUPDATE.h"

#define FLASH_SIZE 64*1024

uint32_t libUpdate::Update(char *szFileName) {
	FILE *f;
	uint8_t *pBuffReadFromFile, *pBuffReadFromMcu;

	pBuffReadFromFile = (uint8_t*)malloc(FLASH_SIZE);
	if(pBuffReadFromFile==NULL) {
		return 0;
	}

	pBuffReadFromMcu = (uint8_t*)malloc(FLASH_SIZE);
	if(pBuffReadFromMcu==NULL) {
		return 0;
	}

	f = fopen(szFileName, "rb");

	if(NULL == f) {
		free(pBuffReadFromFile);
		free(pBuffReadFromMcu);
		return 0;
	}

	

	fclose(f);

	free(pBuffReadFromFile);
	free(pBuffReadFromMcu);
	return 1;
}