#include <stdio.h>
#include "libBinFile.h"

DWORD libBinFile::InitBuffer() {
	//HGLOBAL gRead, gWrite;
	gRead=GlobalAlloc(GPTR, dwMemSize);
	if(gRead==NULL) {
		return 0;
	}
	pReadBuff=(unsigned char*)GlobalLock(gRead);//malloc(dwMemSize);
	if(!pReadBuff)
		return 0;
	FillMemory(pReadBuff, dwMemSize, 0xff);
	//===================
	gWrite=GlobalAlloc(GPTR, dwMemSize);
	if(gWrite==NULL) {
		return 0;
	}
	pWriteBuff=(unsigned char*)GlobalLock(gWrite);//malloc(dwMemSize);
	if(!pWriteBuff)
		return 0;
	FillMemory(pWriteBuff, dwMemSize, 0xff);
	
	return 1;
}

void libBinFile::FreeBuffer() {
	GlobalFree(gWrite);
	GlobalFree(gRead);
}


DWORD libBinFile::Write() {
	//CreateFileW()
	hWrite=CreateFile(szWriteFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(!hWrite)
		return 0;
	//ghi du lieu
	DWORD dwWrite;
	if(!WriteFile(hWrite, pWriteBuff, dwMemSize, &dwWrite, NULL)) {
		CloseHandle(hWrite);
		return 0;
	}

	CloseHandle(hWrite);
	return 1;
}

DWORD libBinFile::Read() {
	hRead=CreateFile(szReadFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(!hRead)
		return 0;
	//lay ve size
	dwReadSize=GetFileSize(hRead, NULL);
	if(dwReadSize>dwMemSize) {
		CloseHandle(hRead);
		return 0;
	}
	DWORD dwRead;
	if(!ReadFile(hRead, pReadBuff, dwReadSize, &dwRead, NULL)) {
		CloseHandle(hRead);
		return 0;
	}
	CloseHandle(hRead);
	return 1;
}