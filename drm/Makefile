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
	$(MAKE) -C $(LINUXDIR) $(KBUILD_OPTS) modules

install:
	$(MAKE) -C $(LINUXDIR) $(KBUILD_OPTS) modules_install

clean:
	$(MAKE) -C $(LINUXDIR) $(KBUILD_OPTS) clean
