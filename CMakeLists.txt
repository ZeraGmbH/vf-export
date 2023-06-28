cmake_minimum_required(VERSION 3.1)

project(vf-export LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(VfExport_VERSION_MAJOR "0")
set(VfExport_VERSION_MINOR "0")
set(VfExport_VERSION_PATCH "1")
set(PROJECT_VERSION "${VfExport_VERSION_MAJOR}.${VfExport_VERSION_MINOR}.${VfExport_VERSION_PATCH}")

include(FeatureSummary)
include(GNUInstallDirs)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

find_package(Qt5 REQUIRED COMPONENTS Core CONFIG)
find_package(VeinFramework REQUIRED)
find_package(VfCpp REQUIRED)
find_package(PythonLibs 3.8 REQUIRED)
find_package(PythonScriptingInterface)

file(GLOB SOURCES
${PROJECT_SOURCE_DIR}/src/*.cpp
    )

file(GLOB HEADER
${PROJECT_SOURCE_DIR}/src/*.h
    )

include_directories(
    ${PYTHON_INCLUDE_DIRS}
    )

list(REMOVE_ITEM SOURCES "${PROJECT_SOURCE_DIR}/vl_postgresdatabase.cpp")

add_library(VfExport SHARED
    ${SOURCES}
    ${HEADER}
    )

target_link_libraries(VfExport 
    PUBLIC
    Qt5::Core
    ${PYTHON_LIBRARIES}
    Zera::VfHelpers
    Zera::VfEvent
    Zera::VfComponent
    Zera::VfStorageHash
    VeinMeta::VfCpp
    VeinMeta::PythonScriptingInterface
    )

set_target_properties(VfExport PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(VfExport PROPERTIES SOVERSION ${VfExport_VERSION_MAJOR})

generate_export_header(VfExport)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/vfexport_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VfExport
    )

target_include_directories(VfExport
    PUBLIC
    $<INSTALL_INTERFACE:include/VfExport>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

install(TARGETS VfExport
    EXPORT VfExportExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

write_basic_package_version_file(
    VfExportConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )

configure_file(VfExportConfig.cmake.in VfExportConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/VfExportConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/VfExportConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VfExport
    )

install(EXPORT VfExportExport
    FILE VfExportTargets.cmake
    NAMESPACE VeinMeta::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VfExport
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VfExport
    )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
