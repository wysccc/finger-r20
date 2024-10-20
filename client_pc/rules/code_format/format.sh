#!/bin/bash

SCRIPT_DIR=$(dirname "${BASH_SOURCE[0]}")
cd ${SCRIPT_DIR};

src_file=../../src

c_files=$(find ${src_file} -name "*.c" -o  -name "*.h")
format_cmd=clang-format
echo code format files: ${c_files}

# 判断clang-format是否存在，对所有的c文件进行代码格式化
if type $format_cmd >/dev/null 2>&1;then
	$format_cmd -i ${c_files}
else 
	echo "please install clang-format"
fi

#linux 内核风格的校验, 
#for c_f in ${c_files}; do
#	./linux_format/checkpatch --no-tree --fix-inplace --file  ${c_f}
#done
