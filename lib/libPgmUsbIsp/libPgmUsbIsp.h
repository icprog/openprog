#ifndef PGM_USBISP_H_
#define PGM_USBISP_H_
#include <stdint.h>

#include "libProgrammer.h"

#include "hidapi.h"

class PgmUsbIsp: public myProgrammer {
private:
	hid_device *hHid;
	uint8_t buff[512];
public:
	virtual uint32_t Init();
	virtual uint32_t Exit();
	virtual uint32_t Spi(uint8_t u8Len, uint8_t *pu8Buff);
	virtual uint32_t ReadFlashAT89S(uint16_t u16Addr, uint8_t u8Len, uint8_t *pu8Buff);
	virtual uint32_t WriteFlashAT89S(uint16_t u16Addr, uint8_t u8Len, uint8_t *pu8Buff);
};

#endif
