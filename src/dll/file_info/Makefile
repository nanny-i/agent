include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -fPIC

CPPFILES = FileInfo.cpp ElfInfo.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	$(CC) -shared $(CFLAGS) -o asi_fi.so $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

install:
	/usr/bin/cp -f asi_fi.so /usr/local/ashin/nanny/dll
	/usr/bin/cp -f asi_fi.so /home/share/install/media/nanny/dll

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f asi_fi.so
