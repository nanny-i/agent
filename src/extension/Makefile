include ../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

CPPFILES = BIniFile.cpp ComExternMethod.cpp ComGlobalMethod.cpp ComFuncUtil.cpp DateTime.cpp DeployPolicyUtil.cpp DocBackupUtil.cpp EncodeUtil.cpp ExecuteFileUtil.cpp FileDeleteUtil.cpp FileUtil.cpp HostToAddrUtil.cpp LogUtil.cpp MemoryFile.cpp MemToken.cpp MutexExt.cpp PowerUtil.cpp ProcInfo.cpp ProcUtil.cpp RegUtil.cpp ResUtil.cpp SecureDeleteUtil.cpp SemExt.cpp StlUtil.cpp SystemInfo.cpp TimerUtil.cpp TokenString.cpp UtilBase.cpp ValidTimeUtil.cpp DownLoadFile.cpp DownLoadUtil.cpp HttpFileGetUtil.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

clean:
	/bin/rm -f $(OBJ)
