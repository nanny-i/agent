include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = DBMgrLogDeployFile.cpp DBMgrLogDoc.cpp DBMgrLogDocDScan.cpp DBMgrLogDocHost.cpp DBMgrLogEvent.cpp DBMgrLogSecu.cpp DBMgrLogStatus.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

clean:
	rm -f ./*.o
