include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)
CPPFILES = update.cpp 
OBJ = $(CPPFILES:.cpp=.o)

all:
	rm -f $(OBJ)
	rm -f update
	$(CC) $(CFLAGS) -c $(CPPFILES)
	make build
clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f update

install:
	/usr/bin/cp -f update /usr/local/ashin/.tools
	/usr/bin/cp -f update /home/share/install/media/tool	

build:
	$(CC) $(CFLAGS) -g -o update update.o ../../lib/as_lib/src/libascomm.a -lz -ldl