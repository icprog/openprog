#include "libPgmUsbIsp.h"
#include <stdio.h>

#define VID 0x03EB
#define PID 0xC8B4

#define INIT_CMD 0x80
#define EXIT_CMD 0x81
#define SPI_CMD 0x82
#define READ_FLASH_CMD 0x83
#define WRITE_FLASH_CMD 0x84

uint32_t PgmUsbIsp::Init() {
	if(myUsb.FindDevice(VID, PID)) {
		//found programmer
		
		buff[0]=0x01;
		buff[1]=0x0F;
		buff[2]=buff[3]=buff[4]=buff[5]=buff[6]=buff[7]=0x00;
		if(myUsb.hid_send_feature_report(8, buff)) {
			//printf("Loi report\n");
			return 1;
		}
		
		//return 0;
		buff[0]=0x01;
		buff[1]=0x0D;
		buff[2]=0x00;//chan RST muc 0, chip AVR
		buff[3]=0x04;//toc do 16KHz
		if(myUsb.hid_send_feature_report(8, buff)) {
			return 1;
		}

		buff[0]=0x01;
		buff[1]=0x0D;
		buff[2]=0x01;//chan RST muc 1, chip 89S
		buff[3]=0x04;//toc do 16KHz
		if(myUsb.hid_send_feature_report(8, buff)) {
			return 1;
		}

		return 0;
	}

	return 2;//not found
}
uint32_t PgmUsbIsp::Exit() {
	buff[0]=0x01;
	buff[1]=0x0D;
	buff[2]=0x01;//chan RST muc 1, chip 89S
	buff[3]=0x04;//toc do 16KHz
	if(myUsb.hid_send_feature_report(8, buff)) {
		myUsb.CloseDevice();
		return 1;
	}

	buff[0]=0x01;
	buff[1]=0x0D;
	buff[2]=0x00;//chan RST muc 0, chip AVR
	buff[3]=0x04;//toc do 16KHz
	if(myUsb.hid_send_feature_report(8, buff)) {
		myUsb.CloseDevice();
		return 1;
	}

	buff[0]=0x01;
	buff[1]=0x0B;//cac chan SPI giai phong
	buff[2]=0x00;//
	buff[3]=0x04;//
	if(myUsb.hid_send_feature_report(8, buff)) {
		myUsb.CloseDevice();
		return 1;
	}

	myUsb.CloseDevice();
	return 0;
}
uint32_t PgmUsbIsp::Spi(uint8_t u8Len, uint8_t *pu8Buff) {
	buff[0]=0x01;
	buff[1]=0x0E;
	buff[7]=u8Len;

	uint8_t i;
	for(i=0; i<u8Len; ++i) {
		buff[2+i]=pu8Buff[i];
	}

	if(myUsb.hid_send_feature_report(8, buff)) {
		myUsb.CloseDevice();
		return 1;
	}

	return 0;
}
uint32_t PgmUsbIsp::ReadFlashAT89S(uint16_t u16Addr, uint8_t u8Len, uint8_t *pu8Buff) {
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
uint32_t PgmUsbIsp::WriteFlashAT89S(uint16_t u16Addr, uint8_t u8Len, uint8_t *pu8Buff) {
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
