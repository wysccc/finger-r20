################################################################################################
#
#	Makefile for lib version
#
#		build in 2024年 08月 28日 星期三 19:02:34 CST
#		by ZHEJIANG SHUNYU OPTICAL INTELLIGENCE TECHNOLOGY CO;LTD
#
################################################################################################

TOP_DIR := ${CURDIR}
# 获取当前的commit号
SHORT_COMMIT := $(shell LC_ALL=C git rev-parse --short HEAD)
# 获取当前的分支名称
BRANCH_NAME := $(shell LC_ALL=C git branch -r --contains ${SHORT_COMMIT} | sed 's|.*/||')
# 拼接一个字符串
RELEASE_NAME := $(basename ${CONFIG_LIBRARY_NAME})-${BRANCH_NAME}-${SHORT_COMMIT}

# 查看编译过程中是否存在代码和远程仓库存在差异	
GIT_STATUS :=$(shell LC_ALL=C git status --porcelain)

# 通过计数计算一个库的版本号出来 FIXME
GIT_COMMIT_CNTS :=$(shell LC_ALL=C git log --oneline ./ | wc -l)

RELEASE_VERSION_01 := $(shell echo $$((${GIT_COMMIT_CNTS}/256/256)))
RELEASE_VERSION_02 := $(shell echo $$((${GIT_COMMIT_CNTS}/256)))
RELEASE_VERSION_03 := $(shell echo $$((${GIT_COMMIT_CNTS}%256)))

ifeq (${GIT_STATUS},)
RELEASE_PLUS = 0
GIT_DIFF_ORIGIN :=$(shell LC_ALL=C git cherry -v origin/${BRANCH_NAME})
ifeq (${GIT_DIFF_ORIGIN},)
RELEASE_PLUS = 0
else
RELEASE_PLUS = 1
endif
else
RELEASE_PLUS = 1
endif

#去除时间字符串前面多余的0，防止编译器误认为8进制
RELEASE_DATE := $(shell date "+20%y%m%d" | sed -e 's/^0//')
RELEASE_TIME := $(shell date "+%H%M%S" | sed -e 's/^0//')

#$(warning RELEASE_VERSION_01 ${RELEASE_VERSION_01})
#$(warning RELEASE_VERSION_02 ${RELEASE_VERSION_02})
#$(warning RELEASE_VERSION_03 ${RELEASE_VERSION_03})
#$(warning RELEASE_PLUS ${RELEASE_PLUS})
#$(warning RELEASE_DATE ${RELEASE_DATE})
#$(warning RELEASE_TIME ${RELEASE_TIME})
#$(warning RELEASE_NAME ${RELEASE_NAME})

C_FLAGS += -DRELEASE_NAME=\"${RELEASE_NAME}\" 
C_FLAGS += -DRELEASE_VERSION_1="${RELEASE_VERSION_01}" 
C_FLAGS += -DRELEASE_VERSION_2="${RELEASE_VERSION_02}" 
C_FLAGS += -DRELEASE_VERSION_3="${RELEASE_VERSION_03}" 
C_FLAGS += -DRELEASE_DATE=\"${RELEASE_DATE}\"
C_FLAGS += -DRELEASE_TIME=\"${RELEASE_TIME}\"
C_FLAGS += -DRELEASE_PLUS=${RELEASE_PLUS} 
