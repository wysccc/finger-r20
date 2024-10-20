LIB_SRC_DIR += ${TOP_DIR}/src

LIB_SRC += \
		   ${LIB_SRC_DIR}/zz_finger.c \

INCLUDE_DIR = ${TOP_DIR}/inc

#编译参数中的头文件路径
INCLUDE_DIRS += \
			   ${INCLUDE_DIR} \

#对外的头文件
EXPORT_INCLUDE_FILES += \
						${INCLUDE_DIR}/zz_finger.h \

LIB_CFLAGS += $(addprefix -I, $(INCLUDE_DIRS))
