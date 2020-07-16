include ../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

define make_sub_dir
set -e;                                     \
    for subdir in $(SUBDIR); do                     \
        if [ -d "$${subdir}" ]; then                    \
            $(MAKE) $(@) --directory="$${subdir}"; \
        fi                              \
    done
endef

define inst_sub_dir
set -e;                                     \
    for instdir in $(INSTDIR); do                     \
        if [ -d "$${instdir}" ]; then                    \
            $(MAKE) $(@) --directory="$${instdir}"; \
        fi                              \
    done
endef


SUBDIR := common_util network res_info rm_log seed socket proc_info device_info doc_fmt file_info find_file compress

INSTDIR := network res_info rm_log seed socket proc_info device_info doc_fmt file_info find_file compress

.PHONY:	all

CPPFILES = ClientSocketDLLUtil.cpp CompDLLUtil.cpp DeviceInfoDLLUtil.cpp DownloadFileDLLUtil.cpp FindFileDLLUtil.cpp NetworkDLLUtil.cpp ProcInfoDLLUtil.cpp RemoveLogDLLUtil.cpp ResInfoDLLUtil.cpp SeedDLLUtil.cpp ServerSocketDLLUtil.cpp

OBJ = $(CPPFILES:.cpp=.o)

all: $(OBJ)
	@$(make_sub_dir)

.cpp.o:
	$(CC) $(CFLAGS) -c $(CPPFILES)

install:
	@$(inst_sub_dir)

clean:
	@$(make_sub_dir)
	/bin/rm -f $(OBJ)
