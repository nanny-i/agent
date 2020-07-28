include ../../build.config

#CFLAGS = $(DEFINES) $(INCLUDES) -fPIC -O2 -fomit-frame-pointer
CFLAGS = $(DEFINES) $(INCLUDES) -fPIC -fomit-frame-pointer

CPPFILES = Compress.cpp CompSecuUtil.cpp CompUtil.cpp CompMemToken.cpp FileToken.cpp MiniLzo.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	$(CC) -shared $(CFLAGS) -o asi_comp.so $(OBJ) ../../extension/ComGlobalMethod.o ../../extension/FileUtil.o ../../extension/TokenString.o ../../lib/as_lib/src/libascomm.a

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

install:
	cp -f asi_comp.so /usr/local/ashin/nanny/dll
	cp -f asi_comp.so $(AS_PKG_HOME)/nanny/dll

clean:
	rm -f $(OBJ)
	rm -f asi_comp.so