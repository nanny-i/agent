include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = ManageEvtMon.cpp ManageFileDown.cpp ManageLogicTimer.cpp ManageSysDrive.cpp ManageWinSession.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	rm -f ./*.o
