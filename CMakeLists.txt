cmake_minimum_required(VERSION 2.8.12)
Project(AutoMail)


message(STATUS ${CMAKE_CURRENT_LIST_FILE})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

include_directories(${AutoMail_SOURCE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

if (NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif (NOT MSVC)

#set (BUILD_STATIC_LIBRARIES "1")
if (BUILD_STATIC_LIBRARIES)
	set(ODS_STATIC "1")
	set(QUAZIP_STATIC "1")
	set(ZLIB_STATIC "1")
endif (BUILD_STATIC_LIBRARIES)

SET(INSTALL_INCLUDE_DIRS ${CMAKE_INSTALL_INCLUDEDIR}/include/AutoMail)
SET(INSTALL_LIB_DIRS ${CMAKE_INSTALL_LIBDIR}/lib )

# add_subdirectory(zlib)
# add_subdirectory(quazip)
# add_subdirectory(ods)

 # Find includes in corresponding build directories
 set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Xml)

 # Add the include directories for the Qt 5 Widgets module to
 # the compile lines.
 include_directories(	${Qt5Widgets_INCLUDE_DIRS}
						${Qt5Xml_INCLUDE_DIRS})

 # Use the compile definitions defined in the Qt 5 Widgets module
 add_definitions(${Qt5Widgets_DEFINITIONS})

 # Add compiler flags for building executables (-fPIE)
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

file(	GLOB_RECURSE
	src_files
	src/*.cpp
)

file(	GLOB_RECURSE
	header_files
	include/*.h
	include/*.hxx
)

include_directories(	include
						${QT_USE_FILE}
						${Qt5Core_INCLUDE_DIRS})

ADD_DEFINITIONS(${QT_DEFINITIONS})

foreach(f IN LISTS src_files)
	get_filename_component(b ${f} NAME)
	set_source_files_properties(${f} PROPERTIES
		COMPILE_DEFINITIONS "SRC_FILE_NAME=\"${b}\"")
endforeach()

ADD_LIBRARY(	MailAuto SHARED
                ${src_files})
target_link_libraries(MailAuto ods quazip zlib Qt5::Core Qt5::Gui Qt5::Xml)


add_executable(	AutoMailCompletion
                "${CMAKE_CURRENT_SOURCE_DIR}/app/AutoMailCompletion.cpp")

target_link_libraries(	AutoMailCompletion
                        MailAuto	)

add_executable(		AutoMail ${GUI_TYPE} app/main.cpp)

target_link_libraries(  AutoMail
						MailAuto)


### installation of the files


install( FILES ${header_files} DESTINATION ${INSTALL_INCLUDE_DIRS})
install( FILES "app/AutoMailCompletion.sh" DESTINATION /etc/bash_completion.d/)

install( TARGETS AutoMailCompletion AutoMail  LIBRARY RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin  COMPONENT main)
install( TARGETS MailAuto LIBRARY DESTINATION ${INSTALL_LIB_DIRS}  COMPONENT main)


