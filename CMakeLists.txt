cmake_minimum_required(VERSION 3.10)
project(ftxui-application)

# Ensure the compiler MUST support this version to continue
# Disable compiler-specific extensions (makes your code more portable)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the executable
add_executable(ftxui-application main.cpp ${SOURCES})
target_include_directories(ftxui-application PUBLIC include)

# Specific build for each CPU struction
# PROCESSING FOR LINUX
if(LINUX)
	if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
        set(ARCH "x86_64")
	elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
        set(ARCH "arm64")
	endif()

    # Add ftxui header
    target_include_directories(ftxui-application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/include)

    # Link to static FTXUI lib
    target_link_options(ftxui-application PRIVATE -static-libgcc -static-libstdc++)

    # Link to static FTXUI lib
    target_link_libraries(ftxui-application PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/static/libftxui-component.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/static/libftxui-dom.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/static/libftxui-screen.a
    )
elseif(WIN32 OR MINGW OR CYGWIN)
    set(ARCH "win32")

    # Add ftxui header
    target_include_directories(ftxui-application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/include)

    # Add target link build for Win
    target_link_options(ftxui-application PRIVATE -static -static-libgcc -static-libstdc++ -lncurses)

    # Link to static FTXUI lib
    target_link_libraries(ftxui-application PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/static/libftxui-component.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/static/libftxui-dom.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/static/libftxui-screen.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ncurses/libncurses.a
    )
endif()
