include ../../build.config

CFLAGS = $(DEFINES) $(INCLUDES)

define make_sub_dir
set -e;										\
	for subdir in $(SUBDIR); do						\
		if [ -d "$${subdir}" ]; then					\
			$(MAKE) $(@) --directory="$${subdir}"; \
		fi								\
	done
endef


SUBDIR := source_server source_client

.PHONY: all

all:
	@$(make_sub_dir)
	$(CC) -shared -o asi_svrsock.so ../common_util/*.o source_server/*.o ../../lib/as_lib/src/libascomm.a -L$(OPENSSL_PATH)/lib -lssl -lcrypto
	$(CC) -shared -o asi_cltsock.so ../common_util/*.o source_client/*.o ../../lib/as_lib/src/libascomm.a -L$(OPENSSL_PATH)/lib -lssl -lcrypto

install:
	cp -f asi_svrsock.so /usr/local/ashin/nanny/dll
	cp -f asi_svrsock.so $(AS_PKG_HOME)/nanny/dll
	cp -f asi_cltsock.so /usr/local/ashin/nanny/dll
	cp -f asi_cltsock.so $(AS_PKG_HOME)/nanny/dll	

clean:
	@$(make_sub_dir)
	rm -f asi_svrsock.so
	rm -f asi_cltsock.so
