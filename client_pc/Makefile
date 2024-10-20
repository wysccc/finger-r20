# 仓库顶层目录
TOP_DIR = ${CURDIR}
# 编译规则路径
RULES_DIR = ${TOP_DIR}/rules
# 工具目录
TOOLS_DIR = ${TOP_DIR}/tools
# 配置路径，主要用来区分平台的差异
CONFS_DIR = ${TOP_DIR}/configs
# 编译成果路径
INSTALL_DIR = ${TOP_DIR}/_install

include $(RULES_DIR)/func.mk

# 支持的配置文件
TARGET_DEFCONFIGS = $(shell cd ${TOP_DIR}/configs;ls *_defconfig)
TARGETS = $(patsubst %_defconfig,%,${TARGET_DEFCONFIGS})

#判断当前.config是否存在
DEF_CONFIG = $(shell [ -e ${TOP_DIR}/.config ] && echo y)

# 如果存在，默认编译当前配置所选择的平台库
ifeq (${DEF_CONFIG},y)
__all:
	@platform=`sed -n  "s/^CONFIG_PLATFORM=\"\(.*\)\"/\1/p" ${TOP_DIR}/.config`; \
		$(MAKE) -f ${RULES_DIR}/Makefile PLATFORM=$${platform}
endif

all:${TARGETS}

help: 
	@$(call m_warn, help)
	@$(call m_warn,     --> list cmds which supported)
	@$(call m_warn, make)
	@$(call m_warn,     --> build defult project {if .confg exist} or make all)
	@$(call m_warn, make menuconfig)
	@$(call m_warn,     --> config default .config file)
	@$(call m_warn, make format)
	@$(call m_warn,     --> format .c & .h file by rules/code_format/format.sh)
	@$(call m_warn, make [${TARGETS}])
	@$(call m_warn,     --> building by TARGET_DEFCONFIGS)
	@$(call m_warn, make [${TARGET_DEFCONFIGS}])
	@$(call m_warn,     --> use TARGET_DEFCONFIGS as default .config file)

MCONF := ${TOOLS_DIR}/mconf/mconf
${MCONF}:
	@cd $(@D); $(MAKE) -f Makefile.host menuconfig; cd -

${TARGET_DEFCONFIGS}:
	@cp -vf ${TOP_DIR}/configs/$@ ${TOP_DIR}/.config

${TARGETS}:%:%_defconfig
	@platform=`sed -n  "s/^CONFIG_PLATFORM=\"\(.*\)\"/\1/p" ${TOP_DIR}/.config`; \
		$(MAKE) -f ${RULES_DIR}/Makefile PLATFORM=$${platform}

menuconfig: ${MCONF}
	@$< $(CONFS_DIR)/syconfig
	@if [ -e ${TOP_DIR}/.config ];then \
		config_name=`sed -n "s/^CONFIG_PLATFORM=\"\(.*\)\"/\1/p" ${TOP_DIR}/.config`_defconfig; \
		if [ ! -e ${TOP_DIR}/configs/$${config_name} ];then \
			cp -vf ${TOP_DIR}/.config ${TOP_DIR}/configs/$${config_name}; \
		else \
			printf "You can run:\n\t\033[33mcp .config configs/$${config_name}\033[0m\n"; \
		fi; \
	fi

format: 
	@echo $(shell ${RULES_DIR}/code_format/format.sh); 

clean:
	@rm -rf ${INSTALL_DIR}

distclean:
	@rm -rf ${INSTALL_DIR}

.PHONY: all clean distclean ${TARGET_DEFCONFIGS} ${TARGETS} menuconfig
