############################################################################
#
# Sub Makefile for build RTOS-Module_Upgrade lib
#
#		2024年 09月 05日 星期四 14:43:18 CST
#		build by ZheJiang ShunYu Optical Intelligence Technology CO;LTD
#
############################################################################
# RTOS-Module_Upgrade 仓库顶层目录
TOP_DIR = ${CURDIR}
# 编译规则路径
RULES_DIR = ${TOP_DIR}/rules
# 工具目录
TOOLS_DIR = ${TOP_DIR}/tools
# 配置路径，主要用来区分平台的差异
CONFS_DIR = ${TOP_DIR}/configs
# 依赖的第三方库目录
THIRD_PART_DIR = ${TOP_DIR}/third_part
# 编译成果路径
INSTALL_DIR = ${TOP_DIR}/_install

# 确认是否配置了要编译的平台 
ifndef PLATFORM
$(error PLATFORM is not defined!)
endif

# 通用函数
include ${RULES_DIR}/func.mk

# 配置选项
include ${TOP_DIR}/.config

# 库的版本管理
include ${RULES_DIR}/version.mk

# 库的版本管理
include ${THIRD_PART_DIR}/third_part.mk

# 配置需要拷贝的库文件目标路径
DIR_TARGET_LIB = ${TOP_DIR}/_install/${PLATFORM}/lib
DIR_TARGET_BIN = ${TOP_DIR}/_install/${PLATFORM}/bin

ifneq (${${PLATFORM}_COPY_LIBRARY_PATH},)
DIR_COPY_TARGET_LIB = $(shell echo ${${PLATFORM}_COPY_LIBRARY_PATH})
endif
# 配置需要拷贝的头文件目标路径
DIR_TARGET_INCLUDE = ${TOP_DIR}/_install/${PLATFORM}/include
ifneq (${${PLATFORM}_COPY_INCLUDE_PATH},)
DIR_COPY_TARGET_INCLUDE = $(shell echo ${${PLATFORM}_COPY_INCLUDE_PATH})
endif
# 配置.o文件路径
DIR_OBJ = ${TOP_DIR}/_install/${PLATFORM}/obj
# 库名称
LIBRARY_NAME = lib$(shell echo ${CONFIG_LIBRARY_NAME})
# 可执行程序名称
BINARY_NAME = $(shell echo ${CONFIG_BINARY_NAME})
# 编译工具链
CROSS = $(shell echo ${CONFIG_CROSS})
# 编译参数
PLATFORM_FLAGS = $(shell echo ${CONFIG_PLATFORM_FLAGS})
# 源文件
LIBRARY_RULES_FILE = $(shell echo ${CONFIG_LIBRARY_RULES_FILE})
# 可执行文件的源文件
BINARY_RULES_FILE = $(shell echo ${CONFIG_BINARY_RULES_FILE})
# 配置中的库文件路径 需提供：
# LIB_SRC ==》 库源码文件
# EXPORT_INCLUDE_FILES  ==》 归档到packshop中的头文件
# CFLAGS 中带上库自身的头文件路径
include ${RULES_DIR}/${LIBRARY_RULES_FILE}

ifdef CONFIG_BUILD_BIN
-include ${RULES_DIR}/${BINARY_RULES_FILE}
endif

ifndef LIB_SRC 
$(error LIB_SRC is undefined!)
endif

CC	= ${CROSS}gcc
CPP	= ${CROSS}g++
LD	= ${CROSS}ld
AR	= ${CROSS}ar
STRIP = ${CROSS}strip

CFLAGS += ${PLATFORM_FLAGS}
# 相关编译obj
LIB_COBJS = $(patsubst ${LIB_SRC_DIR}/%.c,${DIR_OBJ}/%.o,$(filter %.c,${LIB_SRC}))
LIB_COBJDS = $(patsubst %.o,%.d,${LIB_COBJS})
BIN_COBJS = $(patsubst ${BIN_SRC_DIR}/%.c,${DIR_OBJ}/%.o,$(filter %.c,${BIN_SRC}))
BIN_COBJDS = $(patsubst %.o,%.d,${BIN_COBJS})
LIB_CPPOBJS = $(patsubst ${LIB_SRC_DIR}/%.cpp,${DIR_OBJ}/%.o,$(filter %.cpp,${LIB_SRC}))
LIB_CPPOBJDS = $(patsubst %.o,%.d,${LIB_CPPOBJS})
BIN_CPPOBJS = $(patsubst ${BIN_SRC_DIR}/%.cpp,${DIR_OBJ}/%.o,$(filter %.cpp,${BIN_SRC}))
BIN_CPPOBJDS = $(patsubst %.o,%.d,${BIN_CPPOBJS})
LIB_OBJS = ${LIB_COBJS} ${LIB_CPPOBJS}
LIB_OBJDS = $(patsubst %.o,%.d,${LIB_OBJS})
BIN_OBJS = ${BIN_COBJS} ${BIN_CPPOBJS}
BIN_OBJDS = $(patsubst %.o,%.d,${BIN_OBJS})

# 目标头文件
TARGET_INCLUDE_FILES = $(patsubst ${INCLUDE_DIR}/%,${DIR_TARGET_INCLUDE}/%,${EXPORT_INCLUDE_FILES})
TARGETS = ${TARGET_INCLUDE_FILES}

# 目标库名称
ifeq (${CONFIG_BUILD_SHARED_LIBRARY}, y)
ifeq (${CONFIG_PLATFORM}, "WIN32")
TARGET_LIBRARY = ${DIR_TARGET_LIB}/${LIBRARY_NAME}.dll
else
TARGET_LIBRARY = ${DIR_TARGET_LIB}/${LIBRARY_NAME}.so
endif
else
TARGET_LIBRARY = ${DIR_TARGET_LIB}/${LIBRARY_NAME}.a
endif

TARGETS += copy_target_include

ifdef CONFIG_BUILD_BIN
TARGET_BINARY += ${DIR_TARGET_BIN}/${BINARY_NAME}
TARGETS += ${TARGET_BINARY}
endif

ifdef CONFIG_COMPILER_OPTIMIZE
CFLAGS += -O2
endif

ifdef CONFIG_COMPILER_DEBUG
CFLAGS += -g
endif

all: ${TARGETS} 
	@$(call m_info,${RELEASE_NAME}-${RELEASE_VERSION_01}.${RELEASE_VERSION_02}.${RELEASE_VERSION_03}.${RELEASE_PLUS} ${RELEASE_DATE} ${RELEASE_TIME})

# 编译win32 目标库
%.dll: ${LIB_OBJS}
	@mkdir -p $(dir $@)
	@${CC} -shared -o $@ $^ -Wl,--out-implib,$(subst .dll,.lib,$@) 

%.a: ${LIB_OBJS}
	@mkdir -p $(dir $@)
	@${AR} -rvD  $@ $^

copy_target_include:${TARGET_LIBRARY}
	@$(call m_info,$@ ok!)
	@if [ -d "${DIR_COPY_TARGET_LIB}" ] && [ "${DIR_COPY_TARGET_LIB}" != "${DIR_TARGET_LIB}" ];then \
		cp -vf $@ ${DIR_COPY_TARGET_LIB};fi

${DIR_TARGET_BIN}/${BINARY_NAME}:${BIN_OBJS} ${TARGET_LIBRARY} ${TARGET_INCLUDE_FILES}
	@mkdir -p $(dir $@)
	@$(call m_info,$@ ok!)
	@${CC} ${CFLAGS} ${BIN_CFLAGS} ${BIN_OBJS} ${LD_FLAGS} -o $@


ifneq (${BIN_COBJS},)
${BIN_COBJS}:${DIR_OBJ}/%.o:${BIN_SRC_DIR}/%.c ${DIR_OBJ}/%.d
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${BIN_CFLAGS} ${C_FLAGS} -c -o $@ $< && echo "${CC} $(notdir $@)"
	@$(call m_dbg,$@ ok!)
${BIN_COBJDS}:${DIR_OBJ}/%.d:${BIN_SRC_DIR}/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${BIN_CFLAGS} ${C_FLAGS} -MM $< -MQ "$@" -o $@
endif

ifneq (${LIB_COBJS},)
${LIB_COBJS}:${DIR_OBJ}/%.o:${LIB_SRC_DIR}/%.c ${DIR_OBJ}/%.d
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${LIB_CFLAGS} ${C_FLAGS} -c -o $@ $< && echo "${CC} $(notdir $@)"
	@$(call m_dbg,$@ ok!)
${LIB_COBJDS}:${DIR_OBJ}/%.d:${LIB_SRC_DIR}/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${LIB_CFLAGS} ${C_FLAGS} -MM $< -MQ "$@" -o $@
endif

ifneq (${LIB_CPPOBJS},)
${LIB_CPPOBJS}:${DIR_OBJ}/%.o:${LIB_SRC_DIR}/%.cpp ${DIR_OBJ}/%.d
	@mkdir -p $(dir $@)
	@${CPP} ${CFLAGS} ${LIB_CFLAGS} ${CC_FLAGS} -c -o $@ $< && echo "${CPP} $(notdir $@)" 
	@$(call m_dbg,$@ ok!)
${LIB_CPPOBJDS}:${DIR_OBJ}/%.d:${LIB_SRC_DIR}/%.cpp
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${LIB_CFLAGS} ${CC_FLAGS} -MM $< -MQ "$@" -o $@
endif

ifneq ($(wildcard ${LIB_OBJDS}),)
include ${LIB_OBJDS}
endif

${TARGET_INCLUDE_FILES}:${DIR_TARGET_INCLUDE}/%:${INCLUDE_DIR}/%
	@mkdir -p $(dir $@)
	@cp $< $@
	@if [ -d "${DIR_COPY_TARGET_INCLUDE}" ] && [ "${DIR_COPY_TARGET_INCLUDE}" != "${DIR_TARGET_INCLUDE}" ];then \
		cp -vf $@ ${DIR_COPY_TARGET_INCLUDE};fi

clean:
	@rm -rf ${TOP_DIR}/_install/ ${DIR_OBJ}

PHONY += all
.PHONY: ${PHONY}
