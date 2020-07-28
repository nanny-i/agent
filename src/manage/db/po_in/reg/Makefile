include ../../../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = ManagePoInRegSvc.cpp ManagePoInRegSvcObjUnit.cpp ManagePoInRegSvcPkg.cpp ManagePoInRegSvcSubUnit.cpp ManagePoInRegSvcUnit.cpp ManagePoInRegSvcUnitObjPkg.cpp ManagePoInRegSvcUnitSubPkg.cpp ManagePoInRegSW.cpp ManagePoInRegSWObjUnit.cpp ManagePoInRegSWPkg.cpp ManagePoInRegSWSubUnit.cpp ManagePoInRegSWUnit.cpp ManagePoInRegSWUnitObjPkg.cpp ManagePoInRegSWUnitSubPkg.cpp ManagePoInRegSys.cpp ManagePoInRegSysPkg.cpp ManagePoInRegSysUnit.cpp ManagePoInRegVuln.cpp ManagePoInRegVulnPkg.cpp ManagePoInRegVulnUnit.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	rm -f ./*.o
