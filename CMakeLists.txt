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

# Load "include" to main
target_include_directories(ftxui-application PUBLIC include)

# Automatically detect architecture (e.g., amd64, arm64)
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(ARCH "amd64")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(ARCH "arm64")
endif()

# Link to static FTXUI lib
target_link_libraries(ftxui-application PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/libftxui-component.a
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/libftxui-dom.a
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH}/ftxui/libftxui-screen.a
)