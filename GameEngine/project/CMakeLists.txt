cmake_minimum_required(VERSION 3.12.1)

if(UNIX)
    message(">>OS: Linux")
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_C_COMPILER_ID "Clang")
    set(CMAKE_CXX_COMPILER_ID "Clang")
else()  # TODO FIX, Windows only
    message(">>OS: Windows")
    set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang-cl.exe")
    set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang-cl.exe")
    set(CMAKE_C_COMPILER_ID "Clang")
    set(CMAKE_CXX_COMPILER_ID "Clang")
    set(CMAKE_SYSTEM_NAME "Generic")
endif()

project(MindBendingEngine)

file(
    GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.hpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/freetype-gl/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/freetype-gl/*.c"

)

add_executable(${PROJECT_NAME} ${SOURCES})

set(THIRD_PARTY "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
set(RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../resources")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "DEBUG")
endif()
add_definitions(-D${CMAKE_BUILD_TYPE})

message(">>Build type: " ${CMAKE_BUILD_TYPE})
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("Architecture: 64-bit")
else()
    message("Architecture: 32-bit")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -w")

set(GLAD_DIR "${THIRD_PARTY}/glad")
add_library(glad "${GLAD_DIR}/src/glad.c")
target_include_directories(glad PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")

target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}" -lfreeimage)

if(UNIX)
    find_package(SDL2 REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(Freetype REQUIRED)
    #find_package(FreeImage REQUIRED)
    #find_package(GTest REQUIRED)

    include_directories(
        ${OPENGL_INCLUDE_DIRS}  
        ${SDL2_INCLUDE_DIRS} 
        ${FREETYPE_INCLUDE_DIRS}
        #${FREEIMAGE_INCLUDE_DIRS}
        #${GTEST_INCLUDE_DIRS} 
    )
    target_link_libraries(${PROJECT_NAME} 
        ${OPENGL_LIBRARIES} 
        ${SDL2_LIBRARIES} 
        ${FREETYPE_LIBRARIES}
        #${FREEIMAGE_LIBRARIES}
        #${GTEST_LIBRARIES}
    )    
    set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../binaries/Linux/${CMAKE_BUILD_TYPE}")
else() # TODO FIX, windows only
#if(WIN32)
    file(GLOB INCLUDES "${THIRD_PARTY}/SDL2")
    include_directories(${INCLUDES})
    target_link_libraries(${PROJECT_NAME} "${THIRD_PARTY}/SDL2/lib/x64/SDL2.lib" 
    "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.16299.0/um/x64/OpenGL32.Lib")
    set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../binaries/Win/${CMAKE_BUILD_TYPE}")
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
if(WIN32)
    file(COPY "${THIRD_PARTY}/SDL2/lib/x64/SDL2.dll" DESTINATION "${CMAKE_BINARY_DIR}")
endif()
file(COPY "${RESOURCES}" DESTINATION "${CMAKE_BINARY_DIR}")
