cmake_minimum_required(VERSION 3.20)
project(DebugBoy VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES src/main.cpp
    src/UICreation.cpp
    src/utils.cpp
)

find_package(imgui CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(tinyfiledialogs REQUIRED)


add_executable(DebugBoy ${SOURCES})

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(DebugBoy PUBLIC SDL2::SDL2main)
endif()
target_link_libraries(DebugBoy PUBLIC SDL2::SDL2)
target_link_libraries(DebugBoy PUBLIC OpenGL::GL)
target_link_libraries(DebugBoy PRIVATE imgui::imgui)
target_link_libraries(DebugBoy PRIVATE tinyfiledialogs::tinyfiledialogs)
