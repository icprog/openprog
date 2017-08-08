#ifndef PGM_VNPRO_H_
#define PGM_VNPRO_H_
#include <stdint.h>

#include "libProgrammer.h"

#include "libUSBHID.h"

#define VID 0x1986
#define PID 0x0030

#define INIT_CMD 0x80
#define EXIT_CMD 0x81
#define SPI_CMD 0x82
#define READ_FLASH_CMD 0x83
#define WRITE_FLASH_CMD 0x84

class PgmVnpro: public myProgrammer {
private:
	myUSBHID myUsb;
public:
	virtual uint32_t Init();
	virtual uint32_t Exit();
	virtual uint32_t Spi(uint8_t u8Len, uint8_t *pu8Buff);
	virtual uint32_t ReadFlashAT89S(uint16_t u16Addr, uint8_t u8Len, uint8_t *pu8Buff);
	virtual uint32_t WriteFlashAT89S(uint16_t u16Addr, uint8_t u8Len, uint8_t *pu8Buff);
};

#endif
