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
	/bin/rm -f $(OBJ)
	/bin/rm -f dbuse

install:
	/usr/bin/cp -f dbuse /usr/local/ashin/.tools
	/usr/bin/cp -f dbuse /home/share/install/media/tool
	
build:
	$(CC) $(CFLAGS) -g -o dbuse dbuse.o ../../lib/as_lib/src/libascomm.a -lodbc -ldl