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
	rm -f $(OBJ)
	rm -f editconf

install:
	cp -f editconf /usr/local/ashin/.tools
	cp -f editconf $(AS_PKG_HOME)/tool	

build:
	$(CC) $(CFLAGS) -g -o editconf editconf.o ../../lib/as_lib/src/libascomm.a -lodbc -luuid -ldl -static-libstdc++