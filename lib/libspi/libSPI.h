#ifndef LIB_SPI_H_
#define LIB_SPI_H_
#include <stdint.h>
class mySPI {
	uint8_t u8Buff[64];
public:
	virtual uint32_t spiInit(uint8_t u8Mode);
	virtual uint32_t spiSend(uint8_t u8NumOfBytes, uint8_t *u8BuffSend);
};
#endif
