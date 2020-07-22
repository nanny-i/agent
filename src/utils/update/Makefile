include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)
CPPFILES = mz_ioapi.cpp mz_unzip.cpp mz_zip.cpp zip.cpp update.cpp 
OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	$(CC) $(CFLAGS) -g -o update $(OBJ) ../../lib/as_lib/src/libascomm.a -lz -ldl

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f update

install:
	/usr/bin/cp -f update /usr/local/ashin/.tools
	/usr/bin/cp -f update /home/share/install/media/tool