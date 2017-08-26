#include "libPgmUsbIsp.h"
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

#define VID 0x03EB
#define PID 0xC8B4

#define INIT_CMD 0x80
#define EXIT_CMD 0x81
#define SPI_CMD 0x82
#define READ_FLASH_CMD 0x83
#define WRITE_FLASH_CMD 0x84

uint32_t PgmUsbIsp::Init() {
	hHid=hid_open(VID, PID, NULL);
	if(hHid) {
	/*if(myUsb.FindDevice(VID, PID)) {*/
		//found programmer
		
		buff[0]=0x01;
		buff[1]=0x0F;
		buff[2]=buff[3]=buff[4]=buff[5]=buff[6]=buff[7]=0x00;
		if(/*myUsb.*/hid_send_feature_report(hHid, buff, 8)==0) {
			//printf("Loi report\n");
			return 1;
		}
		
		//return 0;
		buff[0]=0x01;
		buff[1]=0x0D;
		buff[2]=0x00;//chan RST muc 0, chip AVR
		buff[3]=0x01;//toc do 16KHz
		buff[4]=0x20;//chu y cho nay phai la 0x20
		buff[5]=0xA0;
		buff[6]=0x40;
		buff[7]=0xC0;

		if(/*myUsb.*/hid_send_feature_report(hHid, buff, 8)==0) {
			return 1;
		}

		buff[0]=0x01;
		buff[1]=0x0D;
		buff[2]=0x01;//chan RST muc 1, chip 89S
		buff[3]=0x01;//toc do 16KHz
		buff[4]=0x20;//chu y cho nay phai la 0x20
		buff[5]=0xA0;
		buff[6]=0x40;
		buff[7]=0xC0;

		if(/*myUsb.*/hid_send_feature_report(hHid, buff, 8)==0) {
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
	if(/*myUsb.*/hid_send_feature_report(hHid, buff, 8)==0) {
		//myUsb.CloseDevice();
		hid_close(hHid);
		return 1;
	}

	buff[0]=0x01;
	buff[1]=0x0D;
	buff[2]=0x00;//chan RST muc 0, chip AVR
	buff[3]=0x04;//toc do 16KHz
	if(/*myUsb.*/hid_send_feature_report(hHid, buff, 8)==0) {
		//myUsb.CloseDevice();
		hid_close(hHid);
		return 1;
	}

	buff[0]=0x01;
	buff[1]=0x0B;//cac chan SPI giai phong
	buff[2]=0x00;//
	buff[3]=0x04;//
	if(/*myUsb.*/hid_send_feature_report(hHid, buff, 8)==0) {
		//myUsb.CloseDevice();
		hid_close(hHid);
		return 1;
	}

	//myUsb.CloseDevice();
	hid_close(hHid);
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

	if(/*myUsb.*/hid_send_feature_report(hHid, buff, 8)==0) {
		//myUsb.CloseDevice();
		hid_close(hHid);
		return 1;
	}

	//cho nay moi thuc su ra lenh ghi SPI tu duoi mach USBISP

	if(/*myUsb.*/hid_get_feature_report(hHid, buff, 8)==0) {
		//myUsb.CloseDevice();
		hid_close(hHid);
		return 1;
	}
	for(i=0; i<u8Len; ++i) {
		pu8Buff[i]=buff[i];
	}

	return 0;
}
uint32_t PgmUsbIsp::ReadFlashAT89S(uint16_t u16Addr, uint8_t u8Len, uint8_t *pu8Buff) {
	if((u16Addr%128)==0) {
		buff[0]=1;
		buff[1]=0x08;
		buff[2]=(uint8_t)u16Addr;
		buff[3]=(uint8_t)(u16Addr>>8);
		buff[4]=(uint8_t)(u16Addr>>16);
		buff[5]=0x00;
		buff[6]=0x00;
		buff[7]=0x00;
		if(/*myUsb.*/hid_send_feature_report(hHid, buff, 8)==0) {
			//myUsb.CloseDevice();
			hid_close(hHid);
			//printf("Send Feature: ERRORRRR\n");
			return 1;
		}

		buff[0]=0x03;
		buff[1]=0x00;
		buff[2]=0x00;
		buff[3]=0x00;
		buff[4]=0x00;
		buff[5]=0x00;
		buff[6]=0x00;
		buff[7]=0x00;
		
		//buff[2]=(uint8_t)u16Addr;
		//buff[3]=(uint8_t)(u16Addr>>8);
		//buff[4]=(uint8_t)(u16Addr>>16);

		if(/*myUsb.*/hid_get_feature_report(hHid, buff, 128)==0) {
			//myUsb.CloseDevice();
			hid_close(hHid);
			//printf("Get Feature: ERRORRRR\n");
			return 1;
		}
		
		//thu hien thi ra xem sao???


		memmove(pu8Buff, buff, 64);
		return 0;
	} else {
		memmove(pu8Buff, &buff[64], 64);
		return 0;
	}

	return 1;
}

static uint8_t num;

uint32_t PgmUsbIsp::WriteFlashAT89S(uint16_t u16Addr, uint8_t u8Len, uint8_t *pu8Buff) {
	if((u16Addr%128)==0) {
		buff[0]=2;
		buff[1]=(uint8_t)u16Addr;//dia chi thap
		buff[2]=(uint8_t)(u16Addr>>8);//dia chi cao
		buff[3]=0x00;
		buff[4]=0x00;
		buff[5]=0x80;
		buff[6]=0x00;
		buff[7]=0x01;
		num=1;
		//luu lai du lieu flash
		memmove(&buff[8+(num-1)*32], pu8Buff, 32);
		return 0;
	} else {
		//luu lai du lieu flash
		++num;
		memmove(&buff[8+(num-1)*32], pu8Buff, 32);
		if(num==4) {
			if(/*myUsb.*/hid_send_feature_report(hHid, buff, 136)==0) {
				//myUsb.CloseDevice();
				hid_close(hHid);
				//printf("Send Feature: ERRORRRR\n");
				return 1;
			}
		}
		return 0;
	}

	return 1;
}
