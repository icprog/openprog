#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libBOOT.h"

uint8_t KT_BOOT::Connect() {
    return ktHid.FindDevice(0x1986, 0x0030);
}
void KT_BOOT::Disconnect() {
	ktHid.CloseDevice();
}
void KT_BOOT::ResetToAPROM(void) {
	//dau tien doc ve DATA_FLASH
	//kiem tra xem gia tri la bao nhieu
	//neu gia tri la 0x00 tuc lan tiep theo se nhay vao LDROM
	//luc nay can xoa ve 0xFF de lan tiep theo mac dinh nhay vao APROM
	uint8_t u8Tmp[100];
	FlashRead(0x0001F000, u8Tmp);
    if((u8Tmp[0]==0)&&(u8Tmp[1]==0)&&(u8Tmp[2]==0)&&(u8Tmp[3]==0)) {
		FlashErasePage(0x0001F000);
    }
	u8Buff[0]=RESET_TO_AP;
	ktHid.Write(u8Buff);
}

uint32_t KT_BOOT::GetPartID(void) {
	u8Buff[0]=READ_PART_ID;
	ktHid.Write(u8Buff);
	if(!ktHid.Read(u8Buff)) {
		return 0;
	}
	uint32_t t;
	t=u8Buff[3];
	t<<=8;
	t+=u8Buff[2];
	t<<=8;
	t+=u8Buff[1];
	t<<=8;
	t+=u8Buff[0];
    return (t);
}
void KT_BOOT::IspEnable(void) {
}
uint8_t KT_BOOT::FlashErasePage(uint32_t u32Addr) {
    u8Buff[0]=FLASH_ERASE_PAGE;
    u8Buff[1]=(uint8_t)u32Addr;
    u32Addr>>=8;
    u8Buff[2]=(uint8_t)u32Addr;
    u32Addr>>=8;
    u8Buff[3]=(uint8_t)u32Addr;
    u32Addr>>=8;
    u8Buff[4]=(uint8_t)u32Addr;
    ktHid.Write(u8Buff);
    return ktHid.Read(u8Buff);
}
uint8_t KT_BOOT::FlashRead(uint32_t u32Addr, uint8_t *pData) {
    u8Buff[0]=FLASH_READ;
	u8Buff[1]=(uint8_t)u32Addr;
    u32Addr>>=8;
    u8Buff[2]=(uint8_t)u32Addr;
    u32Addr>>=8;
    u8Buff[3]=(uint8_t)u32Addr;
    u32Addr>>=8;
    u8Buff[4]=(uint8_t)u32Addr;
    ktHid.Write(u8Buff);
    return ktHid.Read(pData);
}
uint8_t KT_BOOT::FlashWrite(uint32_t u32Addr, uint8_t *pData) {
	u8Buff[0]=FLASH_WRITE;
	u8Buff[1]=(uint8_t)u32Addr;
    u32Addr>>=8;
    u8Buff[2]=(uint8_t)u32Addr;
    u32Addr>>=8;
    u8Buff[3]=(uint8_t)u32Addr;
    u32Addr>>=8;
    u8Buff[4]=(uint8_t)u32Addr;
    //cho nay them phan dao thu tu byte cao va byte thap la xong
    uint8_t i, t0, t1, t2, t3;
    uint8_t tmp[32];
    memmove(tmp, pData, 32);
    for(i=0; i<8; ++i) {
        t0=tmp[i*4+3];
        t1=tmp[i*4+2];
        t2=tmp[i*4+1];
        t3=tmp[i*4];
        tmp[i*4]=t0;
        tmp[i*4+1]=t1;
        tmp[i*4+2]=t2;
        tmp[i*4+3]=t3;
    }
    memmove(&u8Buff[5], tmp, 32);
    ktHid.Write(u8Buff);
    return ktHid.Read(u8Buff);
}
