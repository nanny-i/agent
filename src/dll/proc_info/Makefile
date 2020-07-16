include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -fPIC

CPPFILES = NetworkInfo.cpp ProcessInfo.cpp ResInfo.cpp ResInfoUtil.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	$(CC) -shared $(CFLAGS) -o asi_procinfo.so $(OBJ)  ../../lib/as_lib/src/libascomm.a

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

install:
	/usr/bin/cp -f asi_procinfo.so /usr/local/ashin/nanny/dll
	/usr/bin/cp -f asi_procinfo.so /home/share/install/media/nanny/dll
	
clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f asi_procinfo.so
