include ../../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = LogicMgrSiteFile.cpp LogicMgrSiteVuln.cpp LogicMgrSiteVulnLock.cpp LogicMgrSiteVulnRepair.cpp LogicMgrSiteVulnScan.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

clean:
	rm -f $(OBJ)
