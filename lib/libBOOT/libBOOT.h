#include <stdio.h>
#include <stdint.h>
#ifndef LIB_BOOT_H_
#define LIB_BOOT_H_
#define READ_PART_ID		0x00
#define ISP_EN				0x01
#define RESET_TO_AP 		0x02
#define FLASH_ERASE_PAGE 	0x03
#define FLASH_READ			0x04
#define FLASH_WRITE			0x05

#include "libUSBHID.h"

class KT_BOOT {
private:
	uint8_t u8Buff[100];
	myUSBHID ktHid;
public:
	uint8_t Connect();
	void Disconnect();
	void ResetToAPROM(void);
	void IspEnable(void);
	uint8_t FlashErasePage(uint32_t u32Addr);
	uint8_t FlashRead(uint32_t u32Addr, uint8_t *pData);
	uint8_t FlashWrite(uint32_t u32Addr, uint8_t *pData);
	uint32_t GetPartID(void);
};
#endif
