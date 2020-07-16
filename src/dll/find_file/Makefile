include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -fPIC

CPPFILES = DocFileFmtDLLUtil.cpp FileInfoDLLUtil.cpp FindFile.cpp FindFileUtil.cpp ThreadFinder.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	$(CC) -shared $(CFLAGS) -o asi_ff.so $(OBJ) ../../extension/MutexExt.o ../../extension/TokenString.o ../../extension/SemExt.o ../../extension/LogUtil.o ../../thread/ThreadBase.o ../../lib/as_lib/src/libascomm.a -lpthread

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

install:
	/usr/bin/cp -f asi_ff.so /usr/local/ashin/nanny/dll
	/usr/bin/cp -f asi_ff.so /home/share/install/media/nanny/dll

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f asi_ff.so