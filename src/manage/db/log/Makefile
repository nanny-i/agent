include ../../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = ManageLogDeployFile.cpp ManageLogDoc.cpp ManageLogDocDScan.cpp ManageLogDocHost.cpp ManageLogEvent.cpp ManageLogSecu.cpp ManageLogStatus.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

clean:
	/bin/rm -f $(OBJ)