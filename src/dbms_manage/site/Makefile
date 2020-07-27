include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = DBMgrSiteFile.cpp DBMgrSiteVuln.cpp DBMgrSiteVulnLock.cpp DBMgrSiteVulnRepair.cpp DBMgrSiteVulnScan.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	rm -f ./*.o
