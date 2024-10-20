menuconfig: $(obj)/mconf

check-lxdialog  := $(srctree)/$(src)/lxdialog/check-lxdialog.sh

HOST_EXTRACFLAGS += $(shell $(CONFIG_SHELL) $(check-lxdialog) -ccflags) \
                    -DLOCALE

lxdialog := lxdialog/checklist.o lxdialog/util.o lxdialog/inputbox.o
lxdialog += lxdialog/textbox.o lxdialog/yesno.o lxdialog/menubox.o

conf-objs	:= conf.o  zconf.tab.o
mconf-objs     := mconf.o zconf.tab.o $(lxdialog)

#hostprogs-y := conf

ifeq ($(MAKECMDGOALS),menuconfig)
	hostprogs-y += mconf
endif

clean-files     += mconf 

HOST_EXTRACFLAGS += $(shell $(CONFIG_SHELL) $(srctree)/$(src)/check.sh $(HOSTCC) $(HOSTCFLAGS))

HOSTLOADLIBES_mconf   = $(shell $(CONFIG_SHELL) $(check-lxdialog) -ldflags $(HOSTCC))

