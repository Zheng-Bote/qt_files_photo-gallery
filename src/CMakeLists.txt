cmake_minimum_required(VERSION 3.22)

project(
  qt_files_photo-gallery
  VERSION 0.1.0
  DESCRIPTION "QT6 CXX20 console app to add photos to DB"
  HOMEPAGE_URL "https://github.com/Zheng-Bote/qt_files_photo-gallery"
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Building with CMake version: ${CMAKE_VERSION}")
include(ProcessorCount)
ProcessorCount(N)
message("number of processors: " ${N})

message("Prog: ${PROJECT_NAME} v${PROJECT_VERSION}")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message(STATUS "this is Linux ${CMAKE_SYSTEM_VERSION}")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  message(STATUS "this is MacOS")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "this is Windows")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)
find_package(cxxopts REQUIRED)
find_package(plog REQUIRED)

add_library(inicpp includes/inicpp.h)

# no need to list header files, but helpful for IDE
add_executable(
  qt_files_photo-gallery
  main.cpp
  includes/rz_inifile.cpp
  includes/rz_inifile.h
  includes/rz_pg_db.cpp
  includes/rz_pg_db.h
  includes/rz_sqlite3_db.cpp
  includes/rz_sqlite3_db.h
  includes/rz_readdir.cpp
  includes/rz_readdir.h)

set(PROG_NAME "${PROJECT_NAME}")
set(PROG_VERSION "${PROJECT_VERSION}")
set(PROG_HOMEPAGE "${PROJECT_HOMEPAGE_URL}")
configure_file(configure/rz_config.h.in configured/rz_config.h)
target_include_directories(qt_files_photo-gallery
                           PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(
  qt_files_photo-gallery Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql
  cxxopts::cxxopts plog::plog inicpp)

target_compile_definitions(
  qt_files_photo-gallery
  PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang>:CXX_CLANG>
          $<$<COMPILE_LANG_AND_ID:CXX,Intel>:CXX_INTEL>
          $<$<COMPILE_LANG_AND_ID:C,Clang,Clang>:C_CLANG>)

target_compile_features(qt_files_photo-gallery PUBLIC cxx_std_20)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message(STATUS "building SHA256sum on Linux ${CMAKE_SYSTEM_VERSION}")
  add_custom_command(
    TARGET qt_files_photo-gallery
    POST_BUILD
    COMMAND sha256sum ARGS "qt_files_photo-gallery" >
            "qt_files_photo-gallery.sha256sum")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  message(STATUS "building SHA256sum on MacOS ${CMAKE_SYSTEM_VERSION}")
  add_custom_command(
    TARGET qt_files_photo-gallery
    POST_BUILD
    COMMAND shasum ARGS "-a 256 qt_files_photo-gallery" >
            "qt_files_photo-gallery.sha256sum")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "building SHA256sum on Windows ${CMAKE_SYSTEM_VERSION}")
  # Powershell
  add_custom_command(
    TARGET qt_files_photo-gallery
    POST_BUILD
    COMMAND Get-Filehash ARGS "$<TARGET_FILE_NAME:qt_files_photo-gallery.exe>"
            > "qt_options.sha256sum")
endif()

include(GNUInstallDirs)
install(
  TARGETS qt_files_photo-gallery
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
