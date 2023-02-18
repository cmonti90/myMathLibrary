cmake_minimum_required(VERSION 3.10)

set(target mathlib)
set(exportedTarget mathlibTarget)

set(buildToDir "${CMAKE_CURRENT_SOURCE_DIR}/build/lib/")

set(version 1.0.0)

project(${target})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(SOURCES mathlib.cpp)

set(HEADERS mathlib.h)

add_library(${target} SHARED ${SOURCES})

target_include_directories(${target} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                                            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

set_property(TARGET ${target} PROPERTY VERSION ${version})
set_property(TARGET ${target} PROPERTY SOVERSION 1)
set_property(TARGET ${target} PROPERTY
  INTERFACE_myMathLib_MAJOR_VERSION 1)
set_property(TARGET ${target} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING myMathLib_MAJOR_VERSION
)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)


#############

install(TARGETS ${target}
        EXPORT ${exportedTarget}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${exportedTarget}
        FILE "${exportedTarget}.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${target}
)

# Create imported target ${exportedTarget}
add_library(${exportedTarget} SHARED IMPORTED)

set_target_properties(${exportedTarget} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
)

#############

configure_package_config_file( ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${target}
)

install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${target}
)




