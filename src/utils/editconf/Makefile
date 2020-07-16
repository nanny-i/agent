include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -I/usr/include/mysql
CPPFILES = editconf.cpp 
OBJ = $(CPPFILES:.cpp=.o)

all:
	rm -f $(OBJ)
	rm -f editconf
	$(CC) $(CFLAGS) -c $(CPPFILES)
	make build
clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f editconf

install:
	/usr/bin/cp -f editconf /usr/local/ashin/.tools
	/usr/bin/cp -f editconf /home/share/install/media/tool	

build:
	$(CC) $(CFLAGS) -g -o editconf editconf.o ../../lib/as_lib/src/libascomm.a -lodbc -luuid -ldl -static-libstdc++