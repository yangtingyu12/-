# 目标平台配置 select build target
set(TARGET_PLATFORM "pc")		# "arm" or "pc"

# 第三方库配置 select link libraries
set(LIB_QT5_PATH /usr/local/Qt-5.12.8)			# QT库路径 set your qt-lib path here
set(COMPILER_PATH /usr/bin)		#编译工具链路径 set your cross toolschain path here

message("********** TARGET_PLATFORM: ${TARGET_PLATFORM} **********")
message("********** LIB_QT5_PATH: ${LIB_QT5_PATH} **********")
message("********** COMPILER_PATH: ${COMPILER_PATH} **********")

# project private setting
set(PROJECT_NAME foreground_app)

# cmake needs this line
cmake_minimum_required(VERSION 2.8)

# this is foreground_app
add_definitions(-D FOREGROUND_APP)

if(TARGET_PLATFORM STREQUAL "arm")
	set(CMAKE_SYSTEM_NAME Linux)
	set(CMAKE_SYSTEM_PROCESSOR arm)
	set(CMAKE_C_COMPILER ${COMPILER_PATH}/arm-linux-gcc)
	set(CMAKE_CXX_COMPILER ${COMPILER_PATH}/arm-linux-g++)
	# use as user, only face recognize
	add_definitions(-D USER_CLIENT_ENABLE)
else()
	set(CMAKE_C_COMPILER ${COMPILER_PATH}/gcc)
	set(CMAKE_CXX_COMPILER ${COMPILER_PATH}/g++)
	# use as manager, can add & del user
	add_definitions(-D MANAGER_CLIENT_ENABLE)
endif()

	add_definitions(-D USER_CLIENT_ENABLE)
	add_definitions(-D MANAGER_CLIENT_ENABLE)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# 设置自动生成moc文件，一定要设置
# QObject派生的C++类需要通过moc进行处理(Q_OBJECT)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

# 指定编译参数	-fPIC: Qt request
#set(CMAKE_CXX_FLAGS -fPIC)
add_compile_options(-Wall -fPIC)

# Define project name
project(${PROJECT_NAME})

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

# 工程H头文件路径
set(HEAD_FILE_PATH ${HEAD_FILE_PATH} ${PROJECT_SOURCE_DIR}/include)
set(HEAD_FILE_PATH ${HEAD_FILE_PATH} ${PROJECT_SOURCE_DIR}/../common/include)
set(QT_HEAD_FILE_LIST ${QT_HEAD_FILE_LIST} ${PROJECT_SOURCE_DIR}/include/mainwindow.h)

# 工程C/C++源文件 --- globbing-通配
file(GLOB SRC_LIST_C ${SRC_LIST_C} ${PROJECT_SOURCE_DIR}/*.c)
file(GLOB SRC_LIST_C ${SRC_LIST_C} ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB SRC_LIST_C ${SRC_LIST_C} ${PROJECT_SOURCE_DIR}/../common/src/*.c)
file(GLOB SRC_LIST_CPP ${SRC_LIST_CPP} ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_LIST_CPP ${SRC_LIST_CPP} ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB SRC_LIST_CPP ${SRC_LIST_CPP} ${PROJECT_SOURCE_DIR}/../common/src/*.cpp)

#指定头文件目录
include_directories(${LIB_QT5_INC} ${HEAD_FILE_PATH})

#指定链接库文件目录
link_libraries(${QT5_LIB_FILE})

# Declare the executable target built from your sources
add_executable(${PROJECT_NAME} ${SRC_LIST_CPP} ${SRC_LIST_C} ${QT_HEAD_FILE_LIST})

# Link your application with 3rd libraries
set(OTHER_3RD_LIBS ${OTHER_3RD_LIBS} -lpthread -lrt)
target_link_libraries(${PROJECT_NAME} ${OTHER_3RD_LIBS})
