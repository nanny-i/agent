include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = LogicAuth.cpp LogicEnvNotifyInfo.cpp LogicInitLink.cpp LogicInitLink_Policy.cpp LogicLogDeployFile.cpp LogicLogDoc.cpp LogicLogDocDScan.cpp LogicLogEvent.cpp LogicLogSecu.cpp LogicLogStatus.cpp LogicPoFaClear.cpp LogicPoInPtnSPRule.cpp LogicSiteFile.cpp LogicSiteVuln.cpp LogicSiteVulnLock.cpp LogicSiteVulnRepair.cpp LogicSiteVulnScan.cpp LogicUser.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

clean:
	rm -f $(OBJ)
