cmake_minimum_required(VERSION 3.16)

project(qt_files_photo-gallery LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)

add_executable(
  qt_files_photo-gallery
  main.cpp
  /usr/local/include/plog/Appenders/ColorConsoleAppender.h
  /usr/local/include/plog/Appenders/RollingFileAppender.h
  /usr/local/include/plog/Formatters/TxtFormatter.h
  /usr/local/include/plog/Init.h
  /usr/local/include/plog/Initializers/RollingFileInitializer.h
  /usr/local/include/plog/Log.h
  includes/cxxopts.hpp
  includes/inicpp.h
  includes/rz_inifile.cpp
  includes/rz_inifile.h
  includes/rz_pg_db.cpp
  includes/rz_pg_db.h
  includes/rz_readdir.cpp
  includes/rz_readdir.h)
target_link_libraries(qt_files_photo-gallery Qt${QT_VERSION_MAJOR}::Core
                      Qt${QT_VERSION_MAJOR}::Sql)

include(GNUInstallDirs)
install(
  TARGETS qt_files_photo-gallery
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
