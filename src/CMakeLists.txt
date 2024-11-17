cmake_minimum_required(VERSION 3.23)

# -DCMAKE_BUILD_TYPE=Release
# -DCMAKE_BUILD_TYPE=Debug

project(
  files_photo-gallery
  VERSION 0.1.10
  DESCRIPTION
    "QT6 CXX23 SCS to add photos to photo-gallery"
  HOMEPAGE_URL "https://github.com/Zheng-Bote/qt_files_photo-gallery"
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_CLANG_TIDY clang-tidy;  -header-filter=.; -checks=cppcoreguidelines-*)

set(CXX_FLAGS_ALL "-m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -pthread")
set(CXX_FLAGS_DEBUG "-g3 -O0")
set(CXX_FLAGS_RELEASE "-O3")

set(PROG_NAME "${PROJECT_NAME}")
set(PROG_VERSION "${PROJECT_VERSION}")
set(PROG_HOMEPAGE "${PROJECT_HOMEPAGE_URL}")
set(PROG_DESCRIPTION "${PROJECT_DESCRIPTION}")

configure_file("${CMAKE_SOURCE_DIR}/configure/rz_config.h.in" configured/rz_config.h)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14)
            message(WARNING "!!!! GCC versions must be at least 14 !!!!")
        message(WARNING "!!!! Adust the makefile to build with a different compiler. !!!!")
    endif()
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18)
        message(WARNING "!!!! Clang version must be at least 18 !!!!")
                message(WARNING "!!!! Adust the makefile to build with a different compiler. !!!!")
    endif()
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_CXX_FLAGS "/Ox /EHsc")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.15)
        message(WARNING "!!!! MSVC version must be at least 19.15 !!!!")
    endif()
else()
    message(WARNING "!!! You are using an unsupported compiler! Compilation has only been tested with GCC >= 8, Clang >= 5, or MSVC >= 19.15. !!!")
endif()

set(SRC_LIST   main.cpp
    includes/rz_photo-gallery_plugins.hpp
    includes/rz_webserver.hpp
    includes/rz_snippets.hpp
    includes/rz_snippets.cpp
    includes/rz_qt_snippets.hpp
    includes/rz_qt_snippets.cpp
    includes/rz_do_thread.hpp
    includes/rz_do_thread.cpp
     includes/rz_options.hpp
    includes/rz_filesystem.cpp
    includes/rz_filesystem.hpp
    includes/rz_output.cpp
    includes/rz_output.hpp
    includes/rz_inifile.cpp
    includes/rz_inifile.hpp
    includes/rz_string_lib.hpp
    includes/rz_pg_db.cpp
    includes/rz_pg_db.hpp
    includes/rz_sqlite3_db.cpp
    includes/rz_sqlite3_db.hpp
    includes/rz_readdir.cpp
    includes/rz_readdir.hpp
    includes/rz_datetime.hpp
    includes/rz_datetime.cpp
    includes/rz_aes.h
    includes/rz_aes.cpp
    includes/qaesencryption.h
    includes/qaesencryption.cpp)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CXX_FLAGS_DEBUG} ${CXX_FLAGS_ALL}")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CXX_FLAGS_RELEASE} ${CXX_FLAGS_ALL}")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/configure")

find_package(Qt6 REQUIRED COMPONENTS Core Sql)
find_package(cxxopts REQUIRED)
find_package(plog REQUIRED)

add_library(inicpp includes/inicpp.h)

# no need to list header files, but helpful for IDE
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Sql cxxopts::cxxopts plog::plog inicpp)

# are we compliant?
#include(ClangTidy)
#addclangtidy(files_photo-gallery)

include(Doxygen)
doxygen(. docs)

IF(CMAKE_BUILD_TYPE MATCHES Release)
  message("RELEASE mode")


  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "building SHA256sum on Linux ${CMAKE_SYSTEM_VERSION}")
    add_custom_command(
      TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND sha256sum ARGS "${PROJECT_NAME}" >
              "${PROJECT_NAME}.sha256sum")
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "building SHA256sum on MacOS ${CMAKE_SYSTEM_VERSION}")
    add_custom_command(
      TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND shasum ARGS "-a 256 ${PROJECT_NAME}" >
              "${PROJECT_NAME}.sha256sum")
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "building SHA256sum on Windows ${CMAKE_SYSTEM_VERSION}")
    # Powershell
    add_custom_command(
      TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND Get-Filehash ARGS "$<TARGET_FILE_NAME:t${PROJECT_NAME}.exe>"
              > "${PROJECT_NAME}.sha256sum")
  endif()
ENDIF()

include(GNUInstallDirs)
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS ${PROJECT_NAME} RUNTIME_DEPENDENCY_SET libDeps)
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

# the end
message("Build with CMake version: ${CMAKE_VERSION} and ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} c++${CMAKE_CXX_STANDARD}")
include(ProcessorCount)
ProcessorCount(N)
message("number of processors: " ${N})
message("cmake --build . --parallel ${N}")
