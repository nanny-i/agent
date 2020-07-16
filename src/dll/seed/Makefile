include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -I../common_util -fPIC

CPPFILES = seed.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	$(CC) -shared $(CFLAGS) -o asi_seed.so $(OBJ) ../common_util/Seedx.o ../common_util/SeedUtil.o

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

install:
	/usr/bin/cp -f asi_seed.so /usr/local/ashin/nanny/dll
	/usr/bin/cp -f asi_seed.so /home/share/install/media/nanny/dll
	
clean:
	/bin/rm -f $(OBJ)
	rm -f asi_seed.so
