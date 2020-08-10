include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = makehash.cpp 
OBJ = $(CPPFILES:.cpp=.o)


all:
	rm -f $(OBJ)
	rm -f makehash
	$(CC) $(CFLAGS) -c $(CPPFILES)
	make build
clean:
	rm -f $(OBJ)
	rm -f makehash

install:
	cp -f makehash /usr/local/ashin/.tools
	cp -f makehash $(AS_PKG_HOME)/tool	

build:
	$(CC) $(CFLAGS) -L$(CURL_PATH)/lib -o makehash makehash.o ../../lib/as_lib/src/libascomm.a -static-libgcc -static-libstdc++