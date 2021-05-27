# 目标平台配置 select build target
set(TARGET_PLATFORM "pc")		# "arm" or "pc"

# 第三方库配置 select link libraries
set(LIB_OPENCV_PATH /usr/local/opencv4)	# opencv库路径 set your opencv-lib path here
set(LIB_QT5_PATH /usr/local/Qt-5.12.8)			# QT库路径 set your qt-lib path here
set(LIB_SQLITE3_PATH /usr/local/sqlite3)		# SQLITE3库路径 set your sqlite3-lib here
set(COMPILER_PATH /usr/bin)		#编译工具链路径 set your cross toolschain path here
set(OPENCV_VER_IS_3XX 0)	# set 0 or 1, OPENCV版本是否为3.x.x 因3与4部分函数不同，因此要加以区分

message("********** TARGET_PLATFORM: ${TARGET_PLATFORM} **********")
message("********** LIB_OPENCV_PATH: ${LIB_OPENCV_PATH} **********")
message("********** LIB_QT5_PATH: ${LIB_QT5_PATH} **********")
message("********** LIB_SQLITE3_PATH: ${LIB_SQLITE3_PATH} **********")
message("********** COMPILER_PATH: ${COMPILER_PATH} **********")

# project private setting
set(PROJECT_NAME background_app)

# cmake needs this line
cmake_minimum_required(VERSION 2.8)

# this is background_app
add_definitions(-D BACKGROUND_APP)

	set(CMAKE_SYSTEM_NAME Linux)
if(TARGET_PLATFORM STREQUAL "arm")
	set(CMAKE_SYSTEM_PROCESSOR arm)
	set(CMAKE_C_COMPILER ${COMPILER_PATH}/arm-linux-gcc)
	set(CMAKE_CXX_COMPILER ${COMPILER_PATH}/arm-linux-g++)
else()
	set(CMAKE_C_COMPILER ${COMPILER_PATH}/gcc)
	set(CMAKE_CXX_COMPILER ${COMPILER_PATH}/g++)
endif()

#define OPENCV_VER_3_X_X, use in C/C++
if(OPENCV_VER_IS_3XX EQUAL 1)
	add_definitions(-D OPENCV_VER_3_X_X)
endif()

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# 指定编译参数	-fPIC: Qt request
#set(CMAKE_CXX_FLAGS -fPIC)
add_compile_options(-Wall -fPIC)

# Define project name
project(${PROJECT_NAME})

# opencv库路径及文件
#find_package(OpenCV REQUIRED)
set(LIB_OPENCV_INC ${LIB_OPENCV_PATH}/include ${LIB_OPENCV_PATH}/include/opencv4)
set(LIB_OPENCV_LIB ${LIB_OPENCV_PATH}/lib)
file(GLOB OPENCV_LIB_FILE ${LIB_OPENCV_LIB}/libopencv_*.so*)

# QT5库路径及文件
#set xxx_DIR to xxx/lib/cmake/xxxConfig.cmake, for find_package(xxx)
set(Qt5Widgets_DIR ${LIB_QT5_PATH}/lib/cmake/Qt5Widgets/)
set(Qt5Gui_DIR ${LIB_QT5_PATH}/lib/cmake/Qt5Qt5Gui/)
set(Qt5Core_DIR ${LIB_QT5_PATH}/lib/cmake/Qt5Core/)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)
set(LIB_QT5_INC ${LIB_QT5_PATH}/include ${LIB_QT5_PATH}/include/QtWidgets ${LIB_QT5_PATH}/include/QtGui ${LIB_QT5_PATH}/include/QtCore)
set(LIB_QT5_LIB ${LIB_QT5_PATH}/lib)
file(GLOB QT5_LIB_FILE ${LIB_QT5_LIB}/libQt5*.so*)

# SQLITE3库路径及文件
set(LIB_SQLITE3_INC ${LIB_SQLITE3_PATH}/include)
set(LIB_SQLITE3_LIB ${LIB_SQLITE3_PATH}/lib)
file(GLOB SQLITE3_LIB_FILE ${LIB_SQLITE3_LIB}/libsqlite3*.so*)

# 工程H头文件路径
set(HEAD_FILE_PATH ${HEAD_FILE_PATH} ${PROJECT_SOURCE_DIR}/include)
set(HEAD_FILE_PATH ${HEAD_FILE_PATH} ${PROJECT_SOURCE_DIR}/../common/include)

# 工程C/C++源文件 --- globbing-通配
file(GLOB SRC_LIST_C ${SRC_LIST_C} ${PROJECT_SOURCE_DIR}/*.c)
file(GLOB SRC_LIST_C ${SRC_LIST_C} ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB SRC_LIST_C ${SRC_LIST_C} ${PROJECT_SOURCE_DIR}/../common/src/*.c)
file(GLOB SRC_LIST_CPP ${SRC_LIST_CPP} ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_LIST_CPP ${SRC_LIST_CPP} ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB SRC_LIST_CPP ${SRC_LIST_CPP} ${PROJECT_SOURCE_DIR}/../common/src/*.cpp)

#指定头文件目录
include_directories(${LIB_OPENCV_INC} ${LIB_QT5_INC} ${LIB_SQLITE3_INC} ${HEAD_FILE_PATH})

#指定链接库文件目录
link_libraries(${OPENCV_LIB_FILE} ${QT5_LIB_FILE} ${SQLITE3_LIB_FILE})

# Declare the executable target built from your sources
add_executable(${PROJECT_NAME} ${SRC_LIST_CPP} ${SRC_LIST_C})

# Link your application with 3rd libraries
set(OTHER_3RD_LIBS ${OTHER_3RD_LIBS} -lpthread -lrt)
target_link_libraries(${PROJECT_NAME} ${OTHER_3RD_LIBS})
