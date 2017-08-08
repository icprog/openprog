#include <stdio.h>
#include "libUSBHID.h"
#include "libusb.h"

libusb_device *dev;
libusb_device **devs;
libusb_device_handle *hUsb = NULL;

uint32_t myUSBHID::FindDevice(uint32_t u32VID, uint32_t u32PID) {
	
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
}

uint32_t myUSBHID::CloseDevice(void) {
	if(hUsb==NULL) {
		libusb_exit(NULL);
		return 0;
	}
	libusb_release_interface(hUsb, 0);
	libusb_close(hUsb);
	libusb_exit(NULL);
	return 0;
}

uint32_t myUSBHID::Read(void *pData) {
	int len;
	if(libusb_interrupt_transfer(hUsb, 0x81, (uint8_t*)pData, 64, &len, 5000) < 0) {
		return 0;
	}
	return 1;
}

uint32_t myUSBHID::Read(uint16_t len, void *pData) {
	int rlen;
	if(libusb_interrupt_transfer(hUsb, 0x81, (uint8_t*)pData, len, &rlen, 5000) < 0) {
		return 0;
	}
	return 1;
}

uint32_t myUSBHID::Write(void *pData) {
	int len;
	if(libusb_interrupt_transfer(hUsb, 0x01, (uint8_t*)pData, 64, &len, 5000) < 0) {
		return 0;
	}
	return 1;
}

uint32_t myUSBHID::Write(uint16_t len, void *pData) {
	int rlen;
	if(libusb_interrupt_transfer(hUsb, 0x01, (uint8_t*)pData, len, &rlen, 5000) < 0) {
		return 0;
	}
	return 1;
}
