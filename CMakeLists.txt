project( libdscpp C CXX )

cmake_minimum_required( VERSION 3.8 )

set( LIBDSCPP_STABLE_VERSION 0 )
set( LIBDSCPP_RELEASE 0 )
set( LIBDSCPP_PATCH_VERSION 5-pre )
set( LIBDSCPP_VERSION "${LIBDSCPP_STABLE_VERSION}.${LIBDSCPP_RELEASE}.${LIBDSCPP_PATCH_VERSION}" )

set ( PROJECT_NAME "${CMAKE_PROJECT_NAME}" )
set ( PROJECT_VERSION "${LIBDSCPP_VERSION}" )
set ( PROJECT_DESCRIPTION "A C++/C library for data design and processing in data science." )
set ( PROJECT_IMAGE "${PROJECT_SOURCE_DIR}/img/projectlogo.jpg" )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_C_STANDARD 17 )


if( DSCPP_DESTDIR )
else()
	set( DSCPP_DESTDIR "${CMAKE_INSTALL_PREFIX}" )
endif()


include_directories( ${PROJECT_SOURCE_DIR}/include )

file (GLOB LIBDSCPP_HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp )
file (GLOB LIBDSCPP_SOURCE_C ${PROJECT_SOURCE_DIR}/src/*.c )
file (GLOB LIBDSCPP_SOURCE ${PROJECT_SOURCE_DIR}/src/*.cpp )
file (GLOB LIDSCPP_EXPR_SOURCE ${PROJECT_SOURCE_DIR}/src/ds_*.cpp )

if( DSCPP_SHARED )
	add_library( dsc SHARED ${LIBDSCPP_SOURCE_C} )
	add_library( dscpp SHARED ${LIBDSCPP_SOURCE} ${LIBDSCPP_SOURCE_C} )
	add_library( dscpp_expr SHARED ${LIBDSCPP_EXPR_SOURCE} )
else()
	add_library( dsc STATIC ${LIBDSCPP_SOURCE_C} )
	add_library( dscpp STATIC ${LIBDSCPP_SOURCE} ${LIBDSCPP_SOURCE_C} )
	add_library( dscpp_expr STATIC ${LIBDSCPP_EXPR_SOURCE} )
endif()



if( BUILD_DSCPP_TEST )
	add_executable( dsc_test ${PROJECT_SOURCE_DIR}/examples/castcompat.c )
	target_link_libraries( dsc_test dsc )
	add_executable( dscpp_test ${PROJECT_SOURCE_DIR}/examples/main.cpp )
	target_link_libraries( dscpp_test dscpp )
endif()

if( DSCPP_HEADER_INSTALL_DIR )
else()
	set( DSCPP_HEADER_INSTALL_DIR ${DSCPP_DESTDIR}/include/libdscpp )
endif()

if ( DSCPP_LIB_INSTALL_DIR )
else()
	set ( DSCPP_LIB_INSTALL_DIR ${DSCPP_DESTDIR}/lib )
endif()

if( DSCPP_INSTALL_LIBS )
	install(TARGETS dscpp DESTINATION ${DSCPP_LIB_INSTALL_DIR} )
	install(FILES ${LIBDSCPP_HEADERS} DESTINATION ${DSCPP_HEADER_INSTALL_DIR} )
	install(FILES ${PROJECT_SOURCE_DIR}/lib/LIBDSCPPConfig.cmake DESTINATION "${DSCPP_LIB_INSTALL_DIR}/cmake/LIBDSCPP" )
	configure_file(${PROJECT_SOURCE_DIR}/lib/LIBDSCPP.pc.in ${CMAKE_CURRENT_BINARY_DIR}/LIBDSCPP.pc @ONLY)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/LIBDSCPP.pc DESTINATION "${DSCPP_LIB_INSTALL_DIR}/pkgconfig" )
endif()


find_package(Doxygen)
if(DOXYGEN_FOUND)
	message("-- Enabled doc_dscpp target for make")
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc_dscpp ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating documentation with Doxygen")
endif()
