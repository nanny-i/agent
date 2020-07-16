include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -fPIC

CFILES = rm_log.cpp

OBJ = $(CFILES:.cpp=.o)

all: $(OBJ)
	$(CC) -shared $(CFLAGS) -o asi_rmlog.so $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CFILES)

install:
	/usr/bin/cp -f asi_rmlog.so /usr/local/ashin/nanny/dll
	/usr/bin/cp -f asi_rmlog.so /home/share/install/media/nanny/dll

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f asi_rmlog.so
