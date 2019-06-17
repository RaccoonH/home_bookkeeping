cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(home_bookkeeping LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

set(project_headers
	src/about_window.h
	src/day_info.h
	src/instruction_window.h
	src/clickable_label.h
	src/dayinfo_window.h
    src/main_window.h)

set(project_sources 
    src/main.cpp
	src/about_window.cpp
	src/day_info.cpp
	src/dayinfo_window.cpp
	src/clickable_label.cpp
	src/instruction_window.cpp
    src/main_window.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${project_headers} ${project_sources})

add_executable(${PROJECT_NAME} ${project_headers} ${project_sources} 
    ${project_sources_moc} ${project_headers_wrapped})

target_include_directories(${PROJECT_NAME} PUBLIC
 ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
	
target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets)