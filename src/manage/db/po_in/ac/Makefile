include ../../../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = ManagePoInAcDoc.cpp ManagePoInAcDocObjUnit.cpp ManagePoInAcDocPkg.cpp ManagePoInAcDocSubUnit.cpp ManagePoInAcDocUnit.cpp ManagePoInAcDocUnitObjPkg.cpp ManagePoInAcDocUnitSubPkg.cpp ManagePoInAcFile.cpp ManagePoInAcFileObjUnit.cpp ManagePoInAcFilePkg.cpp ManagePoInAcFileSchUnit.cpp ManagePoInAcFileSubUnit.cpp ManagePoInAcFileUnit.cpp ManagePoInAcFileUnitObjPkg.cpp ManagePoInAcFileUnitRulPkg.cpp ManagePoInAcFileUnitSchPkg.cpp ManagePoInAcFileUnitSubPkg.cpp ManagePoInAcSf.cpp ManagePoInAcSfObjUnit.cpp ManagePoInAcSfPkg.cpp ManagePoInAcSfSubUnit.cpp ManagePoInAcSfUnit.cpp ManagePoInAcSfUnitObjPkg.cpp ManagePoInAcSfUnitSubPkg.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	rm -f ./*.o
