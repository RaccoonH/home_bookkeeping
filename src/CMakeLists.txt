cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(home_bookkeeping LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

set(project_headers
	about_window.h
	day_info.h
	instruction_window.h
	clickable_label.h
	dayinfo_window.h
    main_window.h)

set(project_sources 
    main.cpp
	about_window.cpp
	day_info.cpp
	dayinfo_window.cpp
	clickable_label.cpp
	instruction_window.cpp
    main_window.cpp)

qt5_wrap_cpp(project_sources_moc ${project_headers})

add_executable(${PROJECT_NAME} ${project_headers} ${project_sources} 
    ${project_sources_moc} ${project_headers_wrapped})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets)