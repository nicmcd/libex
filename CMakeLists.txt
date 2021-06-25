cmake_minimum_required(VERSION 3.20)
project(libex)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FindPkgConfig)

add_library(
  ex
  SHARED
  ${PROJECT_SOURCE_DIR}/src/ex/Exception.cc
  ${PROJECT_SOURCE_DIR}/src/ex/Exception.h
  )

set_target_properties(
  ex
  PROPERTIES
  LINKER_LANGUAGE
  CXX
  POSITION_INDEPENDENT_CODE
  ON
  )

target_include_directories(
  ex
  PUBLIC
  ${PROJECT_SOURCE_DIR}/src
  )

include(GNUInstallDirs)

install(
  FILES
  ${PROJECT_SOURCE_DIR}/src/ex/Exception.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/ex/
  )

install(
  TARGETS
  ex
  )

configure_file(
  ${PROJECT_SOURCE_DIR}/libex.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/libex.pc
  @ONLY
  )
install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/libex.pc
  DESTINATION
  ${CMAKE_INSTALL_LIBDIR}/pkgconfig/
  )
