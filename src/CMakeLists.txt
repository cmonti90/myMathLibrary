set(target mathlib)
set(exportedTarget mathlibTarget)

set(CMAKE_CXX_STANDARD 20)
set(version 1.0.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(HEADERS 
            myMathAngle.h
            myMathBasicFunctions.h
            myMathConstants.h
            myMathDCM.h
            myMathDistribution.h
            myMath.h
            myMathMatrix.h
            myMathMatrixFunctions.h
            myMathQuaternion.h
            myMathRotation.h
            myMathStat.h
            myMathVector.h
)

add_library(${target} INTERFACE ${SOURCES})

set_property(TARGET ${target} PROPERTY VERSION ${version})
set_property(TARGET ${target} PROPERTY SOVERSION 1)
set_property(TARGET ${target} PROPERTY
  INTERFACE_myMathLib_MAJOR_VERSION 1)
set_property(TARGET ${target} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING myMathLib_MAJOR_VERSION
)

target_compile_definitions(${target} INTERFACE DEBUG)

target_include_directories(${target} INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                                            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

install(TARGETS ${target}
        EXPORT ${exportedTarget}
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

configure_package_config_file( ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${target}
  )

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
  )

install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${target}
          )




