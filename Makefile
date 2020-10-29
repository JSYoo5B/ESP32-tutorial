#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := app-template

include $(IDF_PATH)/make/project.mk

FIND_IDF_HEADERS=`find ${IDF_PATH}/components	\
	-path "${IDF_PATH}/components/esptool_py*"	-prune -o	\
	-path "${IDF_PATH}/components/unity*"		-prune -o	\
	-path "*/esp32s2beta*"						-prune -o	\
	-path "*/third-party*"						-prune -o	\
	-path "*/test*"								-prune -o	\
	-path "*/fuzz*"								-prune -o	\
	-path "*example*"							-prune -o	\
	-type f													\
	-name "*.[h]"`

FIND_PROJECT_SRCS=`find ${PWD}/main	\
	-type f							\
	-name "*.[cChHsS]"`

cscope_files:
	rm -f cscope.files
	realpath -es --relative-to=. ./build/config/sdkconfig.h > cscope.files
	realpath -es --relative-to=. ${FIND_IDF_HEADERS} >> cscope.files
	realpath -es --relative-to=. ${FIND_PROJECT_SRCS} >> cscope.files

cscope: cscope_files
	cscope -b -q -k > /dev/null 2>&1

ctags: cscope_files
	ctags -L cscope.files

