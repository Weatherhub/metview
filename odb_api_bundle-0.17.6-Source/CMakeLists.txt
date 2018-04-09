cmake_minimum_required( VERSION 2.8.4 FATAL_ERROR )

set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_CURRENT_SOURCE_DIR}/ecbuild/cmake;${CMAKE_MODULE_PATH}" )
include( ecbuild_bundle )

project( odb_api_bundle C CXX )

ecbuild_bundle_initialize()
ecbuild_bundle( PROJECT ecbuild        STASH "ecsdk/ecbuild"      TAG  2.7.3 )
ecbuild_bundle( PROJECT eckit          STASH "ecsdk/eckit"        TAG  0.18.5 )
ecbuild_bundle( PROJECT metkit         STASH "ecsdk/metkit"       TAG  0.8.0 )
ecbuild_bundle( PROJECT odb_api        STASH "odb/odb_api"        TAG  0.17.6 )

if( ENABLE_ODB )
ecbuild_bundle( PROJECT odb            STASH "odb/odb"            TAG 1.0.8 )
ecbuild_bundle( PROJECT odb-tools      STASH "odb/odb-tools"      TAG 0.17.1 )
endif()

ecbuild_bundle_finalize()

