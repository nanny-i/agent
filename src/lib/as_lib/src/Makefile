CC = g++

DEFINES = $(DFT_DEFINES) $(LARGE_FILE_SUPPORT) $(LICENSE_MAC_CHECK)

INCLUDES = -I. -I../h -I../../../com_header -I../../../extension -I$(SQLITE3_PATH)/include -I$(ZLIB_PATH)/include -Wall -fPIC -shared -g

CFLAGS = $(DEFINES) $(INCLUDES)

TARGET = libascomm.a

CPPFILES = $(wildcard *.cpp)

OBJ = $(CPPFILES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rscv $@ $(OBJ)
.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	/bin/rm -f $(TARGET) $(OBJ)

install:
	/bin/cp -f $(TARGET) ../../../libs
