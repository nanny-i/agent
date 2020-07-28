include ../../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = DBMgrPoInVulnOp.cpp DBMgrPoInVulnOpPkg.cpp DBMgrPoInVulnScan.cpp DBMgrPoInVulnScanPkg.cpp DBMgrPoInVulnScanUnit.cpp DBMgrPoInVulnScanUnitPkg.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	rm -f ./*.o
