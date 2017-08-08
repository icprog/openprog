#ifndef LIB_BIN_FILE_H_
#define LIB_BIN_FILE_H_
class libBinFile {
public:
	char szReadFileName[260];
	char szWriteFileName[260];
	unsigned char *pReadBuff;
	unsigned char *pWriteBuff;
	void FreeBuffer();
	DWORD InitBuffer();
	DWORD dwMemSize;
	virtual DWORD Read();
	virtual DWORD Write();
	DWORD dwReadSize;
	DWORD dwNumAddr;
	HANDLE hRead, hWrite;
	DWORD dwPageSize;
	HGLOBAL gRead, gWrite;
};
#endif
