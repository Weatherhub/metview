## check if all sources are used

ecbuild_find_project_files()

### include directories


### libs

if( HAVE_MIGRATOR )
    add_subdirectory( migrator )
endif()

add_subdirectory( odb2_to_odb1 )

add_subdirectory( tests )
