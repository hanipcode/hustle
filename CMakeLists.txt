cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
# Add the -g flag to CMAKE_C_FLAGS_DEBUG
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

# Add the -g flag to CMAKE_CXX_FLAGS_DEBUG
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
project(hustle)



# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Disable useless warnings

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
	cmake_policy(SET CMP0135 NEW)
endif()

# Disable usless compiler warnings
if (MSVC)
	add_compile_options(/wd4068) # Disable unknown pragma warning. https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4068
	add_compile_options(/wd4996) # Disable unsecure function warnings (e.g., sprintf()
endif()


# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(TILESON_VERSION "v1.3.0")
include(FetchContent)
FetchContent_Declare(
  tileson
  GIT_REPOSITORY https://github.com/SSBMTonberry/tileson.git
  GIT_TAG ${TILESON_VERSION}
)
FetchContent_GetProperties(tileson)
if (NOT tileson_POPULATED)
  set(FETCHCONTENT_QUIET NO)
  FetchContent_Populate(tileson)
endif()

# Our Project
set(SOURCE_FILES
	main.cpp
  player.cpp
  draw_physics.cpp
  constants.cpp
  tilemap.cpp
  level.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME} PUBLIC ${tileson_SOURCE_DIR}/include)


add_custom_target(copy-runtime-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)

set(BOX2D_BUILD_UNIT_TESTS OFF)
set(BOX2D_BUILD_TESTBED OFF)
add_subdirectory(vendor/box2d)
target_link_libraries(${PROJECT_NAME} box2d)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/box2d/include)


# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()