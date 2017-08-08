#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

#include "libBOOT.h"
#include "global.h"

int main() {

	at89s.prog=&vnpro;
	at89s.WriteFlash("AT89S52", "write.bin");
	at89s.ReadFlash("AT89S52", "read.bin");
	return 0;
}
