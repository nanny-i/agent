include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -I/usr/include -I$(SQLITE3_PATH)/include

CPPFILES = dbuse.cpp 
OBJ = $(CPPFILES:.cpp=.o)

all:
	rm -f $(OBJ)
	rm -f dbuse
	$(CC) $(CFLAGS) -c $(CPPFILES)
	make build
clean:
	rm -f $(OBJ)
	rm -f dbuse

install:
	cp -f dbuse /usr/local/ashin/.tools
	cp -f dbuse $(AS_PKG_HOME)/tool
	
build:
	$(CC) $(CFLAGS) -g -o dbuse dbuse.o ../../lib/as_lib/src/libascomm.a -lodbc -ldl