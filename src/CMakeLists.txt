cmake_minimum_required(VERSION 3.22)

project(
  qt_files_photo-gallery
  VERSION 0.1.0
  DESCRIPTION "QT6 CXX20 console app to add photos to DB"
  LANGUAGES CXX)

message("Building with CMake version: ${CMAKE_VERSION}")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)
find_package(cxxopts REQUIRED)
find_package(plog REQUIRED)

add_executable(
  qt_files_photo-gallery
  main.cpp
  includes/inicpp.h
  includes/rz_inifile.cpp
  includes/rz_inifile.h
  includes/rz_pg_db.cpp
  includes/rz_pg_db.h
  includes/rz_readdir.cpp
  includes/rz_readdir.h)
target_link_libraries(qt_files_photo-gallery Qt${QT_VERSION_MAJOR}::Core
                      Qt${QT_VERSION_MAJOR}::Sql cxxopts::cxxopts plog::plog)

include(GNUInstallDirs)
install(
  TARGETS qt_files_photo-gallery
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
