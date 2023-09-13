#cmake最低版本要求
cmake_minimum_required(VERSION 3.3)

#指定项目名称
project(ChineseChess VERSION 1.0.0)

#设置c++标准
set(CXX_STANDARD 17)
set(C_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

#qt dir
set(CMAKE_PREFIX_PATH  "/opt/Qt/6.2.4/gcc_64/lib/cmake")
set(CMAKE_BUILD_TYPE "Debug")

#设置可执行文件生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

#启用当前头文件目录
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#指定cpp文件的头目录
include_directories("./include")


#find qt library
find_package(Qt6 COMPONENTS
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



#统计各种文件
file(GLOB_RECURSE HEADER_FILES "./include/*.h")
file(GLOB_RECURSE SRC_FILES "./src/*.cpp")
file(GLOB_RECURSE FORMS "./ui/*.ui")
file(GLOB_RECURSE RESOURCE_FILES "./resource/*.qrc")
file(GLOB_RECURSE MOC_FILES "./include/moc_*.cpp")

#定义一个所有源文件的变量
set(PROJECT_ALL_SOURCE ${HEADER_FILES} ${SRC_FILES} ${FORMS})

#将ui文件编译成ui*.h
IF(FORMS)
	qt6_wrap_ui(FORMS_UIC ${FORMS})
ENDIF()

#将包含Q_OBJECT的头文件编译成moc_*.cpp文件
qt6_wrap_cpp(MOC_FILES ${HEADER_FILES})

#启用资源qrc文件
#set(QT_RESOURCES_PREFIX "./resource")
qt6_add_resources(RES_FILES ${RESOURCE_FILES})


#[[


#设置ts文件名
set(TS_FILES
	${PROJECT_SOURCE_DIR}/lang/en_US.ts
	)

#自定义两个关于ts文件的目标
add_custom_target(update_all_ts_files ALL)
add_custom_target(create_all_qm_files ALL)

#找到两个相关ts可执行文件的路径
find_file(LUPDATE_PATH lupdate)
find_file(LRELEASE_PATH lrelease)

#处理ts文件
foreach(TS_FILE ${TS_FILES})

	# 把zh_CN.ts中的zh_CN提取出来
	get_filename_component(baseFileName ${TS_FILES} NAME_WE)
	set(TS_TARGET_NAME "update_ts_file_${baseFileName}")
	
	add_custom_target(${TS_TARGET_NAME} 
	COMMAND ${LUPDATE_PATH} ${PROJECT_ALL_SOURCE} -ts ${TS_FILE}
	VERBATIM)
	#将update_ts_file_<filename> 设置为 update_all_ts_files的依赖
	add_dependencies(update_all_ts_files ${TS_TARGET_NAME})

	set(QM_TARGET_NAME "create_qm_file_${baseFileName}")
	set(QM_FILE "${PROJECT_SOURCE_DIR}/lang/${baseFileName}.qm")

    add_custom_target(${QM_TARGET_NAME}
            COMMAND ${LRELEASE_PATH} ${TS_FILE} -qm ${QM_FILE}
            VERBATIM)
	
	# 因为得先有ts文件才能生成qm文件，所以把构建ts文件的目标作为自己的依赖
	add_dependencies(${QM_TARGET_NAME} ${TS_TARGET_NAME})
	add_dependencies(create_all_qm_files ${QM_TARGET_NAME})	
endforeach()



#qt_create_translation(QM_FILES ${TS_FILES} ${HEADER_FILES} ${SRC_FILES} ${FORMS_UIC})

#add_custom_target(translations ALL DEPENDS ${QM_FILES})


]]

add_executable(${PROJECT_NAME} main.cpp
				${HEADER_FILES}
				${SRC_FILES}
				${MOC_FILES}
				${FORMS_UIC}
				${RESOURCES_FILES}
				${RES_FILES}
				)

#add_dependencies(${CMAKE_PROJECT_NAME} create_all_qm_files)


#link qt library
target_link_libraries(${PROJECT_NAME} PUBLIC
Qt6::Core
Qt6::Gui
Qt6::Widgets
Qt6::OpenGL
Qt6::Network
Qt6::OpenGL
Qt6::Xml
Qt6::Svg
Qt6::Multimedia
Qt6::Sql
)
