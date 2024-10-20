################################################################################################
#
#	func.mk for Makefile
#
#		build in 2024年 09月 05日 星期四 14:47:43 CST
#		by ZHEJIANG SHUNYU OPTICAL INTELLIGENCE TECHNOLOGY CO;LTD
#
################################################################################################
#normal
define m_log
	printf "$1\n"
endef

#green
define m_info
	printf "\033[32m$1\033[0m\n"
endef

#blue
define m_dbg
	printf "\033[34m$1\033[0m\n"
endef

#yellow
define m_warn 	
	printf "\033[33m$1\033[0m\n"
endef

#red
define m_err
	printf "\033[31m$1\033[0m\n"
endef

define get_jobs
	_jobs=`grep -c ^processor /proc/cpuinfo`;let jobs=$${_jobs}/2;printf $${jobs}
endef
