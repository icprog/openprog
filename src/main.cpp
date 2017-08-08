#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

#include "global.h"

int main(int argc, char **argv)
{
	
	int c;
	char *pValue, *rValue, *wValue, *fValue;
	uint8_t pFlag=0, rFlag=0, wFlag=0, fFlag=0;
	
	if(argc!=7) {
		printf("1\n");
		printf("Use same as: openprog -p AT89S52 -r FLASH -f blink.bin\n");
		return 1;
	}

	while(1) {
		c=getopt(argc, argv, "p:r:w:f:");
		if(c==-1) {
			break;
		}
		switch(c) {
			case 'p':
				pFlag=1;
				pValue=optarg;
			break;
			case 'r':
				rFlag=1;
				rValue=optarg;
			break;
			case 'w':
				wFlag=1;
				wValue=optarg;
			break;
			case 'f':
				fFlag=1;
				fValue=optarg;
			break;
		}
	}

	at89s.prog=&vnpro;

	if( (0==pFlag) || (0==fFlag) ) {
		printf("2\n");
		printf("Use same as: openprog -p AT89S52 -r FLASH -f blink.bin\n");
		return 1;
	}

	if((0==rFlag) && (0==wFlag)) {
		printf("3\n");
		printf("Use same as: openprog -p AT89S52 -r FLASH -f blink.bin\n");
		return 1;
	}

	if(rFlag) {
		//read
		at89s.ReadFlash(pValue, fValue);
	}

	if(wFlag) {
		//write
		at89s.WriteFlash(pValue, fValue);
	}
	

	//at89s.prog=&vnpro;
	//at89s.WriteFlash("AT89S52", "write.bin");
	//at89s.ReadFlash("AT89S52", "read.bin");
	return 0;
}

