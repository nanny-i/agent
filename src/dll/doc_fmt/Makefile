include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -fPIC

CPPFILES = DocFileFmt.cpp DocFileFmtUtil.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	$(CC) -shared $(CFLAGS) -o asi_dff.so $(OBJ) ../../extension/LogUtil.o ../../extension/MutexExt.o ../../lib/as_lib/src/libascomm.a

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

install:
	/usr/bin/cp -f asi_dff.so /usr/local/ashin/nanny/dll
	/usr/bin/cp -f asi_dff.so /home/share/install/media/nanny/dll

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f asi_dff.so
