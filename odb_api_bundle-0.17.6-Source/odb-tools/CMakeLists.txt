##
# This package exists to contain odb_api tools that make use of ODB1, to break the circular
# dependency when building with IFS.

cmake_minimum_required( VERSION 2.8.11 FATAL_ERROR )

project( odb_tools CXX Fortran )

set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../ecbuild/cmake")

include( ecbuild_system NO_POLICY_SCOPE )

ecbuild_requires_macro_version( 2.0 )

###############################################################################
# local project

ecbuild_declare_project()

ecbuild_use_package( PROJECT eckit   VERSION 0.9 REQUIRED )
ecbuild_use_package( PROJECT odb_api VERSION ${odb_tools_VERSION_STR} REQUIRED )
ecbuild_use_package( PROJECT odb     VERSION 1.0.5 REQUIRED )

###############################################################################
# some variables/options of this project

ecbuild_add_option( FEATURE MIGRATOR
                    DESCRIPTION "whether or not to build the ODB migrator tool"
                    DEFAULT ON
                    REQUIRED_PACKAGES "PROJECT odb VERSION 1.0 QUIET" )

#ecbuild_add_option( FEATURE FORTRAN
#                    DESCRIPTION "whether or not to build the Fortran interface"
#                    DEFAULT OFF )
set( HAVE_FORTRAN ON )

if( HAVE_FORTRAN OR HAVE_MIGRATOR )

    set( Fortran Fortran )
    ecbuild_enable_fortran( REQUIRED MODULE_DIRECTORY ${CMAKE_BINARY_DIR}/module )
    ecbuild_find_fortranlibs( REQUIRED )
    message( "Fortran libraries: [${FORTRAN_LIBRARIES}]" )

endif()

if(CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
  ecbuild_add_fortran_flags("-fPIC -ffree-line-length-none")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  ecbuild_add_cxx_flags("-fPIC -Wl,--as-needed")
endif()

ecbuild_add_option( FEATURE OMP
                    DESCRIPTION "Support for OpenMP threaded parallelism"
                    REQUIRED_PACKAGES "OMP COMPONENTS CXX ${Fortran}" )

if( HAVE_OMP )
  ecbuild_enable_omp()
else()
  ecbuild_enable_ompstubs()
endif()

ecbuild_add_option( FEATURE PYTHON
                    DESCRIPTION "whether or not to build the Python interface"
                    DEFAULT OFF
                    REQUIRED_PACKAGES "Python VERSION 2.7 NO_LIBS" SWIG )

###############################################################################
# contents

set_directory_properties( PROPERTIES COMPILE_DEFINITIONS "${ECKIT_DEFINITIONS}" )

get_directory_property( ODB_API_DEFINITIONS COMPILE_DEFINITIONS )

set( ODB_TOOLS_INCLUDE_DIRS   ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/src )

#if( HAVE_FORTRAN )
  list( APPEND ODB_API_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/module )
  list( INSERT ODB_API_LIBRARIES 0 Odb_fortran )
#endif()

include_directories( ${ODB_API_INCLUDE_DIRS} ${ODB_TOOLS_INCLUDE_DIRS} )

add_subdirectory( src )

############################################################################################
# finalize

ecbuild_install_project( NAME OdbTools )

ecbuild_print_summary()

