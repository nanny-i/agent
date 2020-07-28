include ../../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = ManageHost.cpp ManageHostHw.cpp ManageHostKey.cpp ManageHostPolicy.cpp ManageHostStatusPo.cpp ManageHostSw.cpp ManageHostSys.cpp ManageUser.cpp ManageUserPolicy.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

clean:
	rm -f $(OBJ)
