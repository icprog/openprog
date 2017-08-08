#include "libPgmVnpro.h"

uint32_t PgmVnpro::Init() {
	if(myUsb.FindDevice(VID, PID)) {
		//found programmer
		buff[0]=INIT_CMD;
		if(myUsb.Write(buff)) {
			return 0;
		} else {
			return 1;//write error
		}
	}

	return 2;//not found
}
uint32_t PgmVnpro::Exit() {
	buff[0]=EXIT_CMD;

	if(myUsb.Write(buff)) {
		myUsb.CloseDevice();
		return 0;
	}
	
	myUsb.CloseDevice();
	return 1;
}
uint32_t PgmVnpro::Spi(uint8_t u8Len, uint8_t *pu8Buff) {
	buff[0]=SPI_CMD;
	buff[1]=u8Len;
	uint8_t i;
	for(i=0; i<u8Len; ++i) {
		buff[2+i]=pu8Buff[i];
	}
	if(myUsb.Write(buff)) {
		if(myUsb.Read(buff)) {
			for(i=0; i<u8Len; ++i) {
				pu8Buff[i]=buff[i];
			}
			return 0;
		} else {
			return 1;//error
		}
	}
	return 1;
}
uint32_t PgmVnpro::ReadFlashAT89S(uint16_t u16Addr, uint8_t u8Len, uint8_t *pu8Buff) {
	buff[0]=READ_FLASH_CMD;
	buff[1]=u8Len;
	buff[2]=(uint8_t)(u16Addr>>8);
	buff[3]=(uint8_t)(u16Addr);
	if(myUsb.Write(buff)) {
		if(myUsb.Read(buff)) {
			uint8_t i;
			for(i=0; i<u8Len; ++i) {
				pu8Buff[i]=buff[i];
			}
			return 0;
		} else {
			return 1;
		}
	}

	return 1;
}
uint32_t PgmVnpro::WriteFlashAT89S(uint16_t u16Addr, uint8_t u8Len, uint8_t *pu8Buff) {
	buff[0]=WRITE_FLASH_CMD;
	buff[1]=u8Len;
	buff[2]=(uint8_t)(u16Addr>>8);
	buff[3]=(uint8_t)(u16Addr);
	uint8_t i;
	for(i=0; i<u8Len; ++i) {
		buff[4+i]=pu8Buff[i];
	}
	if(myUsb.Write(buff)) {
		if(myUsb.Read(buff)) {
			if(buff[0]) {
				return 1;
			}
			return 0;
		} else {
			return 1;
		}
	}
	return 1;
}
