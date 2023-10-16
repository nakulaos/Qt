#统计各种文件
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui")
file(GLOB_RECURSE RESOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/resource/*.qrc")
file(GLOB_RECURSE MOC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/moc_*.cpp")


#定义一个所有源文件的变量
set(PROJECT_ALL_SOURCE ${HEADER_FILES} ${SRC_FILES} ${FORMS})


#将ui文件编译成ui*.h
IF(FORMS)
	qt5_wrap_ui(FORMS_UIC ${FORMS})
ENDIF()

#将包含Q_OBJECT的头文件编译成moc_*.cpp文件
qt5_wrap_cpp(MOC_FILES ${HEADER_FILES})

#启用资源qrc文件
#set(QT_RESOURCES_PREFIX "./resource")
qt5_add_resources(RES_FILES ${RESOURCE_FILES})

#设置ts文件名
set(TS_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/lang/en_US.ts
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
	set(QM_FILE "${CMAKE_CURRENT_SOURCE_DIR}/lang/${baseFileName}.qm")

    add_custom_target(${QM_TARGET_NAME}
            COMMAND ${LRELEASE_PATH} ${TS_FILE} -qm ${QM_FILE}
            VERBATIM)
	
	# 因为得先有ts文件才能生成qm文件，所以把构建ts文件的目标作为自己的依赖
	add_dependencies(${QM_TARGET_NAME} ${TS_TARGET_NAME})
	add_dependencies(create_all_qm_files ${QM_TARGET_NAME})	

endforeach()

add_library(pine  SHARED
		${HEADER_FILES}
		${SRC_FILES}
		${MOC_FILES}
		${FORMS_UIC}
		${RESOURCES_FILES}
		${RES_FILES}
		)




target_include_directories(pine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

target_link_libraries(pine PUBLIC
Qt5::Core
Qt5::Gui
Qt5::Widgets
Qt5::OpenGL
Qt5::Network
Qt5::OpenGL
Qt5::Xml
Qt5::Svg
Qt5::Multimedia
Qt5::Sql
)