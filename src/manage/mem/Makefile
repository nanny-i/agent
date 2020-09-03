include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = ManageChkExistInterval.cpp ManageDevOInfo.cpp ManageDeviceMedia.cpp ManageEvtMon.cpp ManageFileDown.cpp ManageLinkEnv.cpp ManageLogicTimer.cpp ManagePMSWork.cpp ManagePatchFile.cpp ManageSysDrive.cpp ManageVulnFileProtect.cpp ManageVulnRegProtect.cpp ManageWinSession.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

clean:
	rm -f $(OBJ)
