# openprog
Phần mềm nạp chương trình cho VĐK.

* Hỗ trợ cả Windows và Linux:
	- Windows XP, Windows 7, Windows 8, Windows 10 cả 32 bit và 64 bit.
	- Linux.
* Phần mềm được cung cấp đầy đủ mã nguồn; schematic và mã nguồn Firmware
của mạch nạp.

* Biên dịch sử dụng GCC:
	+ Trên Windows sử dụng trình biên dịch MingW.
		- Để biên dịch trên Windows cần:
			- Cài trình biên dịch TDM-GCC MinGW
				https://sourceforge.net/projects/tdm-gcc/
			- Cài GNU Make:
			Cài luôn bộ công cụ WinAVR trong đó có cả GNU Make
				http://winavr.sourceforge.net/download.html
			- Mở cửa sổ CMD tại thư mục mã nguồn (chứa makefile)
				Gõ make
	- Trên Linux sử dụng GCC mặc định.
		- Để biên dịch:
			Mở cửa sổ Terminal tại thư mục mã nguồn (chứa makefile)
				Gõ make
