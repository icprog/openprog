#include <stdio.h>
#include "libSPI.h"
#include "libUSBHID.h"

myUSBHID ktHid;

uint32_t mySPI::spiInit(uint8_t u8Mode) {
	if(ktHid.FindDevice(0x1986, 0x0030)) {
		u8Buff[0]=0x60;
		u8Buff[1]=u8Mode;
		if(ktHid.Write(u8Buff)) {
			return 0;
		} else {
			return 1;
		}
		return 0;
	}
	return 1;
}

uint32_t mySPI::spiSend(uint8_t u8NumOfBytes, uint8_t *u8BuffSend) {
	u8Buff[0]=0x64;
	u8Buff[1]=0x04;
	u8Buff[2]=0x19;
	u8Buff[3]=0x86;
	u8Buff[4]=0x14;
	u8Buff[5]=0x12;
	if(ktHid.Write(u8Buff)) {
		if(ktHid.Read(u8Buff)) {
			return 0;
		}
		return 1;
	}
	return 1;
}