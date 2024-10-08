cmake_minimum_required(VERSION 3.22)

project(
  files_photo-gallery
  VERSION 0.1.6
  DESCRIPTION
    "QT6 CXX20 console app to convert photos, collect Exif/IPTC and add metadata to DB"
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

find_package(Qt6 REQUIRED COMPONENTS Core Sql)
find_package(cxxopts REQUIRED)
find_package(plog REQUIRED)

add_library(inicpp includes/inicpp.h)
#add_library(aesencrypt includes/qaesencryption.h)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeFiles")

# no need to list header files, but helpful for IDE
add_executable(
  files_photo-gallery
  main.cpp
  includes/rz_inifile.cpp
  includes/rz_inifile.h
  includes/rz_pg_db.cpp
  includes/rz_pg_db.h
  includes/rz_sqlite3_db.cpp
  includes/rz_sqlite3_db.h
  includes/rz_readdir.cpp
  includes/rz_readdir.h
  includes/rz_datetime.h
  includes/rz_datetime.cpp
  includes/rz_aes.h
  includes/rz_aes.cpp
  includes/qaesencryption.h
  includes/qaesencryption.cpp
)

set(PROG_NAME "${PROJECT_NAME}")
set(PROG_VERSION "${PROJECT_VERSION}")
set(PROG_HOMEPAGE "${PROJECT_HOMEPAGE_URL}")
configure_file(configure/rz_config.h.in configured/rz_config.h)

target_compile_features(files_photo-gallery PUBLIC cxx_std_20)

target_include_directories(files_photo-gallery
                           PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(
  files_photo-gallery Qt6::Core Qt6::Sql
  cxxopts::cxxopts plog::plog inicpp)

# are we compliant?
#include(ClangTidy)
#addclangtidy(files_photo-gallery)

target_compile_definitions(
  files_photo-gallery
  PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang>:CXX_CLANG>
          $<$<COMPILE_LANG_AND_ID:CXX,Intel>:CXX_INTEL>
          $<$<COMPILE_LANG_AND_ID:C,Clang,Clang>:C_CLANG>)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message(STATUS "building SHA256sum on Linux ${CMAKE_SYSTEM_VERSION}")
  add_custom_command(
    TARGET files_photo-gallery
    POST_BUILD
    COMMAND sha256sum ARGS "files_photo-gallery" >
            "files_photo-gallery.sha256sum")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  message(STATUS "building SHA256sum on MacOS ${CMAKE_SYSTEM_VERSION}")
  add_custom_command(
    TARGET files_photo-gallery
    POST_BUILD
    COMMAND shasum ARGS "-a 256 files_photo-gallery" >
            "files_photo-gallery.sha256sum")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "building SHA256sum on Windows ${CMAKE_SYSTEM_VERSION}")
  # Powershell
  add_custom_command(
    TARGET files_photo-gallery
    POST_BUILD
    COMMAND Get-Filehash ARGS "$<TARGET_FILE_NAME:files_photo-gallery.exe>"
            > "qt_files_photo-gallery.sha256sum")
endif()

include(Doxygen)
doxygen(. docs)

include(GNUInstallDirs)
install(
  TARGETS files_photo-gallery
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS files_photo-gallery RUNTIME_DEPENDENCY_SET libDeps)
install(RUNTIME_DEPENDENCY_SET libDeps)


# IFW needs to set external export QTIFWDIR=...
# set(QTIFWDIR "${GLOBAL}/Qt/Tools/QtInstallerFramework/4.8/bin")
include(InstallRequiredSystemLibraries)
set(CPACK_IFW_ROOT "$ENV{HOME}/Qt/Tools/QtInstallerFramework/4.8")
set(CPACK_RESOURCE_FILE_LICENSE  ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE)
set(CPACK_PACKAGE_VENDOR "ZHENG Robert")
set(CPACK_PACKAGE_CONTACT "https://www.robert.hase-zheng.net")
set(CPACK_PACKAGE_DESCRIPTION "QT6 CXX20 console app to convert photos, collect Exif/IPTC and add metadata to DB")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "convert photos and add Metadata to Database")
set(CPACK_THREADS "${N}")
set(CPACK_PACKAGE_CHECKSUM SHA256)
set(CPACK_GENERATOR "IFW;DEB;ZIP;TBZ2;RPM")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Packaging")

include(CPack)
