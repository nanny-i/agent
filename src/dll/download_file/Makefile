include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -fPIC

CPPFILES = DownLoadFile.cpp HttpFileGetUtil.cpp DownLoadUtil.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	$(CC) -shared $(CFLAGS) -o asi_fdl.so $(OBJ) ../../extension/LogUtil.o ../../extension/MutexExt.o ../../lib/as_lib/src/libascomm.a

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

install:
	/usr/bin/cp -f asi_fdl.so /usr/local/ashin/nanny/dll
	/usr/bin/cp -f asi_fdl.so /home/share/install/media/nanny/dll

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f asi_fdl.so
