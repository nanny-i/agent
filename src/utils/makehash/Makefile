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
	/bin/rm -f $(OBJ)
	/bin/rm -f makehash

install:
	/usr/bin/cp -f makehash /usr/local/ashin/.tools
	/usr/bin/cp -f makehash /home/share/install/media/tool	

build:
	$(CC) $(CFLAGS) -L$(CURL_PATH)/lib -o makehash makehash.o ../../lib/as_lib/src/libascomm.a	