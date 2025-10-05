cmake_minimum_required(VERSION 3.15...4.0)

project(
	tvrender
	VERSION 0.2
	LANGUAGES C
)

add_library(
	tvrender
	src/tvr_core.c
)

target_sources(
    tvrender
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libtvrender>
)

get_target_property(CQP_PUBLIC_HEADERS tvrender INTERFACE_SOURCES)

set_target_properties(tvrender PROPERTIES PUBLIC_HEADER "${CQP_PUBLIC_HEADERS}")

target_include_directories(
    tvrender
    INTERFACE include/libtvrender
)

include(CPack)
include(GNUInstallDirs)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libtvrender.pc.in ${CMAKE_CURRENT_BINARY_DIR}/libtvrender.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libtvrender.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

install(TARGETS tvrender)


