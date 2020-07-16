include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -I../as_lib/h -I../as_lib/src/ -fPIC

CPPFILES = res_info.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	$(CC) -shared $(CFLAGS) -o asi_resinfo.so $(OBJ) ../../lib/as_lib/src/libascomm.a

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

install:
	/usr/bin/cp -f asi_resinfo.so /usr/local/ashin/nanny/dll
	/usr/bin/cp -f asi_resinfo.so /home/share/install/media/nanny/dll

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f asi_resinfo.so
