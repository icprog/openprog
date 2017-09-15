#ifndef MY_USB_HID_H
#define MY_USB_HID_H
#include <stdint.h>
class myUSBHID {
private:
	uint8_t u8Buff[8*1024];
public:
	uint32_t FindDevice(uint32_t u32VID, uint32_t u32PID);
	uint32_t CloseDevice(void);
	uint32_t Read(void *pData);
	uint32_t Read(uint16_t len, void *pData);
	uint32_t Write(void *pData);
	uint32_t Write(uint16_t len, void *pData);
	uint32_t my_hid_send_feature_report(uint8_t u8Len, uint8_t *u8Buff);
	uint32_t my_hid_get_feature_report(uint8_t u8Len, uint8_t *u8Buff);
};
#endif
