#设置cmake最低版本要求
cmake_minimum_required(VERSION 3.26)

project(webserver
        VERSION 0.1
        DESCRIPTION "webserver"
        LANGUAGES C CXX
        )


#设置c,c++标准

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#启用当前头文件目录
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#clangd要求的
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



#生成debug版本程序
set(CMAKE_BUILD_TYPE "Debug")

#生成库为共享库
set(BUILD_SHARED_LIBS ON)

#判断cmake运行时候有没有新建一个build文件夹，并且有没有在里面新建
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)
if (EXISTS "${PATH_TO_CMAKELISTS_TXT}")
    message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake .. \" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif ()

set(TOOL_BUILD_SUPPORT_DIR "${CMAKE_SOURCE_DIR}/tools")




#########################################################################################################################
#qt
#########################################################################################################################

#qt dir
set(CMAKE_PREFIX_PATH  "/opt/Qt/5.15.2/gcc_64/lib/cmake")

#find qt library
find_package(Qt5 COMPONENTS
				Widgets 
				Gui 
				Core
				LinguistTools
				Network
				OpenGL
				Xml
				Svg
				Multimedia
				Sql
				REQUIRED)










##############################################################################################################################
#tools
##############################################################################################################################



# clang-format
if (NOT DEFINED CLANG_FORMAT_BIN)
    # attempt to find the binary if user did not specify
    find_program(CLANG_FORMAT_BIN
            NAMES clang-format clang-format-8)
endif ()
if ("${CLANG_FORMAT_BIN}" STREQUAL "CLANG_FORMAT_BIN-NOTFOUND")
    message(WARNING "couldn't find clang-format.")
else ()
    message(STATUS "found clang-format at ${CLANG_FORMAT_BIN}")
endif ()

# clang-tidy
if (NOT DEFINED CLANG_TIDY_BIN)
    # attempt to find the binary if user did not specify
    find_program(CLANG_TIDY_BIN
            NAMES clang-tidy clang-fidy-8)
endif ()
if ("${CLANG_TIDY_BIN}" STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
    message(WARNING "couldn't find clang-tidy.")
else ()
    # Output compile_commands.json
    set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
    message(STATUS "found clang-fidy at ${CLANG_TIDY_BIN}")
endif ()

# cpplint
find_program(CPPLINT_BIN
        NAMES cpplint cpplint.py
		HINTS ${TOOL_BUILD_SUPPORT_DIR})
if ("${CPPLINT_BIN}" STREQUAL "CPPLINT_BIN-NOTFOUND")
    message(WARNING "couldn't find cpplint.")
else ()
    message(STATUS "found cpplint at ${CPPLINT_BIN}")
endif ()


###################################################################################################################################
# COMPILER SETUP
###################################################################################################################################

# Compiler flags.
#编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -std=c++17 -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-attributes") #TODO: remove
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fPIC")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fPIC")
set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -fPIC")

set(GCC_COVERAGE_LINK_FLAGS "-fPIC")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")

# Output directory.
#动态库，静态库，可执行文件生成目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Includes.
set(SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/**/include)
set(TEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/test/include)

#添加子项目
add_subdirectory(src)
add_subdirectory(test)



######################################################################################################################
# MAKE TARGETS
######################################################################################################################

##########################################
# "make format"
# "make check-format"
##########################################
string(CONCAT FORMAT_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**,"
        "${CMAKE_CURRENT_SOURCE_DIR}/test,"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/**/include"
        )



# runs clang format and updates files in place.
add_custom_target(format ${TOOL_BUILD_SUPPORT_DIR}/run_clang_format.py
        ${CLANG_FORMAT_BIN}
        ${TOOL_BUILD_SUPPORT_DIR}/clang_format_exclusions.txt
        --source_dirs
        ${FORMAT_DIRS}
        --fix
        --quiet
        )

# runs clang format and exits with a non-zero exit code if any files need to be reformatted
add_custom_target(check-format ${TOOL_BUILD_SUPPORT_DIR}/run_clang_format.py
        ${CLANG_FORMAT_BIN}
        ${TOOL_BUILD_SUPPORT_DIR}/clang_format_exclusions.txt
        --source_dirs
        ${FORMAT_DIRS}
        --quiet
        )

##########################################
# "make cpplint"
##########################################

file(GLOB_RECURSE LINT_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/**/include/*.h"
        )

# Balancing act: cpplint.py takes a non-trivial time to launch,
# so process 12 files per invocation, while still ensuring parallelism
add_custom_target(cpplint echo '${LINT_FILES}' | xargs -n12 -P8
        ${CPPLINT_BIN}
        --verbose=2 --quiet
        --linelength=120
        --filter=-legal/copyright,-build/include_subdir,-readability/casting,-build/c++11
		--counting=detailed
        )

###########################################################
# "make clang-tidy" target
###########################################################
# runs clang-tidy and exits with a non-zero exit code if any errors are found.
# note that clang-tidy automatically looks for a .clang-tidy file in parent directories
add_custom_target(clang-tidy
        ${TOOL_BUILD_SUPPORT_DIR}/run_clang_tidy.py                     # run LLVM's clang-tidy script
        -clang-tidy-binary ${CLANG_TIDY_BIN}                              # using our clang-tidy binary
        -p ${CMAKE_BINARY_DIR}                                            # using cmake's generated compile commands
        )


add_dependencies(clang-tidy pine)   # needs gtest headers, compile_commands.json






