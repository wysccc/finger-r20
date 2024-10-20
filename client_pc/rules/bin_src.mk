BIN_SRC_DIR += ${TOP_DIR}/bin

# PC端测试程序源码
BIN_SRC += \
		   ${BIN_SRC_DIR}/main.c \

BIN_INC_DIR = ${BIN_SRC_DIR}

BIN_CFLAGS += $(addprefix -I, $(BIN_INC_DIR))
# 将编译仓库后_install 目录中的内容作为编译bin文件的依赖
BIN_CFLAGS += $(addprefix -I, $(DIR_TARGET_INCLUDE))
# 链接_install 中的静态库
LD_FLAGS += -L${DIR_TARGET_LIB} -l$(shell echo ${CONFIG_LIBRARY_NAME})

