#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"

int main(int argc, char **argv)
{

#if 1	
	int c;
	char *prog, *pValue, *rValue, *wValue, *fValue;
	uint8_t cFlag=0, pFlag=0, rFlag=0, wFlag=0, fFlag=0;
	
	if(argc!=9) {
		printf("Use same as: openprog -c VNPRO -p AT89S52 -r FLASH -f blink.bin\n");
		return 1;
	}

	while(1) {
		c=getopt(argc, argv, "c:p:r:w:f:");
		if(c==-1) {
			break;
		}
		switch(c) {
			case 'c':
				cFlag=1;
				prog=optarg;
				break;
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

	if(cFlag==0) {
		printf("Use same as: openprog -c VNPRO -p AT89S52 -r FLASH -f blink.bin\n");
		return 1;
	}

	if(strcmp(prog, "USBISP")==0) {
		at89s.prog=&usbisp;
	} else if(strcmp(prog, "VNPRO")==0) {
		at89s.prog=&vnpro;
	} else if(strcmp(prog, "ISPV2")==0) {
		at89s.prog=&ispv2;
	}else {
		printf("Use same as: openprog -c VNPRO -p AT89S52 -r FLASH -f blink.bin\n");
		return 1;
	}
	

	if( (0==pFlag) || (0==fFlag) ) {
		printf("Use same as: openprog -c VNPRO -p AT89S52 -r FLASH -f blink.bin\n");
		return 1;
	}

	if((0==rFlag) && (0==wFlag)) {
		printf("Use same as: openprog -c VNPRO -p AT89S52 -r FLASH -f blink.bin\n");
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
#endif	
	return 0;
}

