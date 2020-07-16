include ../../../build.config

CFLAGS = $(DEFINES) $(INCLUDES) -I../../common_util

CPPFILES = TCP_Client.cpp Client_DLL.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ) 

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

clean:
	/bin/rm -f $(OBJ)

