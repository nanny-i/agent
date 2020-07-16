include ../../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = ManageSiteFile.cpp ManageSiteVuln.cpp ManageSiteVulnLock.cpp ManageSiteVulnRepair.cpp ManageSiteVulnScan.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	/bin/rm -f ./*.o
