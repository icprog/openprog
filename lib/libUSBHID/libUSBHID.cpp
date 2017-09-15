#include <stdio.h>
#include "libUSBHID.h"
//#include "libusb.h"
#include "hidapi.h"

//libusb_device *dev;
//libusb_device **devs;
//libusb_device_handle *hUsb = NULL;
hid_device *hHid;

uint32_t myUSBHID::FindDevice(uint32_t u32VID, uint32_t u32PID) {
	/*
	int r;

	r = libusb_init(NULL);
	if (r < 0)
		return 0;

	hUsb = libusb_open_device_with_vid_pid(NULL, u32VID, u32PID);
	
	if(hUsb==NULL) {
		return 0;
	}
	
	libusb_detach_kernel_driver(hUsb, 0); 
	
	r = libusb_set_configuration(hUsb, 1);
	
	if(r<0) {
		return 0;
	}
	
	r = libusb_claim_interface(hUsb, 0);
	
	if(r<0) {
		return 0;
	}
	
	return 1;
	*/
	hHid=hid_open(u32VID, u32PID, NULL);
	if(hHid) {
		return 1;
	}
	return 0;
}

uint32_t myUSBHID::CloseDevice(void) {
	/*
	if(hUsb==NULL) {
		libusb_exit(NULL);
		return 0;
	}
	libusb_release_interface(hUsb, 0);
	libusb_close(hUsb);
	libusb_exit(NULL);
	return 0;
	*/
	if(hHid!=NULL) {
		hid_close(hHid);
	}
	hid_exit();
	return 0;
}

uint32_t myUSBHID::Read(void *pData) {
	//int len;
	/*
	if(libusb_interrupt_transfer(hUsb, 0x81, (uint8_t*)pData, 64, &len, 5000) < 0) {
		return 0;
	}
	return 1;
	*/
	if(hid_read_timeout(hHid, (uint8_t*)pData, 64, 5000)==-1) {
		return 0;
	}
	return 1;
}

uint32_t myUSBHID::Read(uint16_t len, void *pData) {
	/*
	int rlen;
	if(libusb_interrupt_transfer(hUsb, 0x81, (uint8_t*)pData, len, &rlen, 5000) < 0) {
		return 0;
	}
	return 1;
	*/
	if(hid_read_timeout(hHid, (uint8_t*)pData, len, 5000)==-1) {
		return 0;
	}
	return 1;
}

uint32_t myUSBHID::Write(void *pData) {
	/*
	int len;
	if(libusb_interrupt_transfer(hUsb, 0x01, (uint8_t*)pData, 64, &len, 5000) < 0) {
		return 0;
	}
	return 1;
	*/
	if(hid_write(hHid, (uint8_t*)pData, 64)==-1) {
		return 0;
	}
	return 1;
}

uint32_t myUSBHID::Write(uint16_t len, void *pData) {
	/*
	int rlen;
	if(libusb_interrupt_transfer(hUsb, 0x01, (uint8_t*)pData, len, &rlen, 5000) < 0) {
		return 0;
	}
	return 1;
	*/
	if(hid_write(hHid, (uint8_t*)pData, len)==-1) {
		return 0;
	}
	return 1;
}

uint32_t myUSBHID::my_hid_send_feature_report(uint8_t u8Len, uint8_t *u8Buff) {
#if 0
	int res;
	res = libusb_control_transfer(hUsb,
		LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT,
		0x09/*HID set_report*/,
		(3/*HID feature*/ << 8) | u8Buff[0],
		1,
		(unsigned char *)u8Buff, u8Len,
		5000/*timeout millis*/);
	if(res<0) {
		return 1;
	}
	return 0;
#endif
	if(hid_send_feature_report(hHid, u8Buff, u8Len)==-1) {
		return 0;
	}
	return 1;
}

uint32_t myUSBHID::my_hid_get_feature_report(uint8_t u8Len, uint8_t *u8Buff) {
#if 0
	int res;
	res = libusb_control_transfer(hUsb,
		LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_IN,
		0x01/*HID get_report*/,
		(3/*HID feature*/ << 8) | u8Buff[0],
		1,
		(unsigned char *)u8Buff, u8Len,
		5000/*timeout millis*/);
	
	if (res < 0)
		return 1;
	return 0;
#endif
	if(hid_get_feature_report(hHid, u8Buff, u8Len)==-1) {
		return 0;
	}
	return 1;
}