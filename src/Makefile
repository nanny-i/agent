include ./build.config

CFLAGS = $(DEFINES) $(INCLUDES)

define make_sub_dir
set -e;										\
	for subdir in $(SUBDIR); do						\
		if [ -d "$${subdir}" ]; then					\
			$(MAKE) $(@) --directory="$${subdir}" $(MAKEFLAGS);	\
		fi								\
	done
endef

define inst_sub_dir
set -e;										\
	for instdir in $(INSTDIR); do						\
		if [ -d "$${instdir}" ]; then					\
			$(MAKE) $(@) --directory="$${instdir}" $(MAKEFLAGS) $(INST_PKG);	\
		fi								\
	done
endef

SUBDIR := lib extension manage thread dll dbms_manage manage logic utils

INSTDIR := dll utils

.PHONY: all

all:
	@$(make_sub_dir)
	make sys_all

install:
	@$(inst_sub_dir)
	make sys_install
	
clean:
	@$(make_sub_dir)
	make sys_clean

sys_clean:
	rm -f nannysvc
	rm -f nannysvc.debug
	rm -f *.o

sys_all:
	$(CC) $(CFLAGS) -c Environment.cpp EnvironmentOp.cpp MainDlg.cpp MainDlg_Class.cpp MainDlg_DBSync.cpp MainDlg_SockEvt.cpp MainDlg_Util.cpp MainDlg_WMEvt.cpp NannyAgent.cpp
	$(CC) $(CFLAGS) -o nannysvc *.o extension/*.o dll/*.o dbms_manage/env/*.o dbms_manage/etc/*.o dbms_manage/log/*.o dbms_manage/org/*.o dbms_manage/po_etc/*.o dbms_manage/po_fa/*.o dbms_manage/po_fe/*.o dbms_manage/po_in/devo/*.o dbms_manage/po_in/ptn/*.o dbms_manage/po_in/rs/*.o dbms_manage/po_in/vuln/*.o dbms_manage/po_pms/*.o dbms_manage/ptn/*.o dbms_manage/site/*.o dbms_manage/*.o manage/*.o manage/db/env/*.o manage/db/etc/*.o manage/db/log/*.o manage/db/org/*.o manage/db/po_etc/*.o manage/db/po_fa/*.o manage/db/po_fe/*.o manage/db/po_in/devo/*.o manage/db/po_in/ptn/*.o manage/db/po_in/rs/*.o manage/db/po_in/vuln/*.o manage/db/po_pms/*.o manage/db/ptn/*.o manage/db/site/*.o manage/mem/*.o logic/base/*.o logic/impl/*.o logic/lgn/*.o logic/link/*.o logic/mgr/ctrl/*.o logic/mgr/env/*.o logic/mgr/log/*.o logic/mgr/org/*.o logic/mgr/po_etc/*.o logic/mgr/po_fa/*.o logic/mgr/po_fe/*.o logic/mgr/po_in/devo/*.o logic/mgr/po_in/ptn/*.o logic/mgr/po_in/rs/*.o logic/mgr/po_in/vuln/*.o logic/mgr/po_pms/*.o logic/mgr/ptn/*.o logic/mgr/site/*.o logic/mgr/*.o logic/udt/*.o logic/util/*.o thread/*.o lib/as_lib/src/libascomm.a -luuid -lodbc -ldl -lpthread -lrt -static-libgcc -static-libstdc++
#	objcopy --only-keep-debug nannysvc nannysvc.debug
#	objcopy --strip-debug nannysvc

sys_install:
	cp -f nannysvc /usr/local/ashin/nanny/sbin
	cp -f nannysvc $(AS_PKG_HOME)/nanny/sbin
