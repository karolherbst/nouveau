ifndef LINUXDIR
LINUXVER := $(shell uname -r)
LINUXDIR := $(shell if [ -e /lib/modules/$(LINUXVER)/source ]; \
		    then \
		    	echo /lib/modules/$(LINUXVER)/source; \
		    else \
		    	echo /lib/modules/$(LINUXVER)/build; \
		    fi \
	     )
endif

KBUILD_OPTS := M=$(CURDIR)
KBUILD_OPTS += KCPPFLAGS="$(shell cat nouveau.config)"

all: modules

modules:
	make -C $(LINUXDIR) $(KBUILD_OPTS) modules

install:
	make -C $(LINUXDIR) $(KBUILD_OPTS) modules_install

clean:
	make -C $(LINUXDIR) $(KBUILD_OPTS) clean
