include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = DBMgrErrorCode.cpp DBMgrLinkLicense.cpp DBMgrLocalEnvAuth.cpp DBMgrLocalEnvLog.cpp DBMgrOsType.cpp DBMgrSchemaInfo.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

clean:
	rm -f ./*.o
