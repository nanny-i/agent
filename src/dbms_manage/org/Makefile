include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = DBMgrHost.cpp DBMgrHostHw.cpp DBMgrHostKey.cpp DBMgrHostPolicy.cpp DBMgrHostStatusPo.cpp DBMgrHostSw.cpp DBMgrHostSys.cpp DBMgrUser.cpp DBMgrUserPolicy.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	/bin/rm -f ./*.o
