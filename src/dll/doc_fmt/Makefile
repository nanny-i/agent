include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -fPIC

CPPFILES = DocFileFmt.cpp DocFileFmtUtil.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	$(CC) -shared $(CFLAGS) -o asi_dff.so $(OBJ) ../../extension/LogUtil.o ../../extension/MutexExt.o ../../lib/as_lib/src/libascomm.a

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

install:
	cp -f asi_dff.so /usr/local/ashin/nanny/dll
	cp -f asi_dff.so $(AS_PKG_HOME)/nanny/dll

clean:
	rm -f $(OBJ)
	rm -f asi_dff.so
