PROJECT = openprog
CC = g++

OS_32_64 = OS_32_BIT

LIB = 
LIB += libUSBHID
LIB += libUSBBULK
LIB += libBOOT
LIB += libProgrammer
LIB += libAT89S
LIB += libPgmVnpro
LIB += libPgmUsbIsp
LIB += libHexFile

TINCS = 
TINCS += src
TINCS += lib
TINCS += $(foreach dir,$(LIB),lib/$(dir))
INCS = $(patsubst %,-I%,$(TINCS))

SRC =
SRC += $(wildcard src/*.cpp)
SRC += $(wildcard lib/*.cpp)
SRC += $(foreach dir,$(LIB),$(wildcard lib/$(dir)/*.cpp))

TSRC = $(notdir $(SRC))

TOBJ = $(subst .cpp,.o, $(TSRC))
OBJ = $(patsubst %.o,obj/%.o, $(TOBJ))

VPATH =
VPATH += src
VPATH += lib
VPATH += $(foreach dir,$(LIB),lib/$(dir))

all: $(OBJ)
ifeq ($(OS),Windows_NT)
ifeq ($(OS_32_64),OS_32_BIT)
	$(CC) -m32 $(OBJ) -L./lib/ -lusb-1.0_w32 -o $(PROJECT)
else
	$(CC) -m64 $(OBJ) -L./lib/ -lusb-1.0_w64 -o $(PROJECT)
endif	
else
	$(CC) $(OBJ) -lusb-1.0 -o $(PROJECT)
endif

obj/%.o: %.cpp
ifeq ($(OS),Windows_NT)
ifeq ($(OS_32_64),OS_32_BIT)
	$(CC) -m32 $(INCS) -c $< -o $@
else
	$(CC) -m64 $(INCS) -c $< -o $@
endif
else
	$(CC) -c $< $(INCS) -o $@
endif

clean:
	rm -f $(PROJECT)
	rm -f $(PROJECT).exe
	rm -f $(OBJ)
