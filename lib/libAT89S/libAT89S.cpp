#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libAT89S.h"

AT89S_Part partList[]={
	{"AT89S51", {0x1E, 0x51, 0x06}, 4*1024}, \
	{"AT89S52", {0x1E, 0x52, 0x06}, 8*1024}
};

void myAT89S::ReadFlash(char *szPartName, char *szFile) {
	//cap phat bo nho
	uint8_t i, partIndex;
	uint8_t n;
	uint16_t u16FlashSize;
	
	n=sizeof(partList)/sizeof(AT89S_Part);

	for(i=0; i<n; ++i) {
		if(strcmpi(szPartName, partList[i].szName)==0) {
			u16FlashSize=partList[i].u16FlashSize;
			partIndex=i;
			break;
		}
	}
	if(i==n) {
		printf("Error part\n");
		return;
	}

	//cap phat bo nho
	uint8_t *buff;
	buff=(uint8_t*)malloc(u16FlashSize);

	//khoi tao programmer
	if(prog->Init()) {
		printf("Init Programmer: Error\n");
		free(buff);
		return;
	}

	if(ChipEnable()) {
		printf("Chip Enable: ERROR\n");
		free(buff);
		return;
	}


	//kiem tra ID
	uint8_t u8ID[3];

	if(ReadID(u8ID)) {
		printf("Read ID: ERROR\n");
		free(buff);
		return;
	}

	for(i=0; i<3; ++i) {
		if(partList[partIndex].ID[i]!=u8ID[i]) {
			printf("Check ID: ERROR\n");
			free(buff);
			return;
		}
	}

	printf("Check ID: %02X %02X %02X: OKAY\n", u8ID[0], u8ID[1], u8ID[2]);
	
	//doc flash tu MCU
	if(prog->ReadFlashAT89S(0x0000, 64, buff)) {
		printf("Doc flash loi\n");
	} else {
		printf("%02X %02X %02X %02X\n", buff[0], buff[1], buff[2], buff[3]);
	}
	
}
void myAT89S::WriteFlash(char *szPartName, char *szFile) {

}
void myAT89S::ReadLock(char *szPartName, char *szFile) {

}
void myAT89S::WriteLock(char *szPartName, char *szFile) {

}

uint32_t myAT89S::ChipEnable() {
	//goi toi ham SPI
	uint8_t buff[64];
	buff[0]=0xAC;
	buff[1]=0x53;
	buff[2]=0x00;
	buff[3]=0x00;
	if(prog->Spi(4, buff)) {
		return 1;
	}
	if(buff[3]==0x69) {
		return 0;
	}
	return 1;
}

uint32_t myAT89S::ReadID(uint8_t *pu8ID) {
	uint8_t buff[64];

	buff[0]=0x28;
	buff[1]=0x00;
	buff[2]=0x00;
	buff[3]=0x00;
	if(prog->Spi(4, buff)) {
		return 1;
	}
	pu8ID[0]=buff[3];

	buff[0]=0x28;
	buff[1]=0x01;
	buff[2]=0x00;
	buff[3]=0x00;
	if(prog->Spi(4, buff)) {
		return 1;
	}
	pu8ID[1]=buff[3];

	buff[0]=0x28;
	buff[1]=0x02;
	buff[2]=0x00;
	buff[3]=0x00;
	if(prog->Spi(4, buff)) {
		return 1;
	}
	pu8ID[2]=buff[3];

	return 0;
}