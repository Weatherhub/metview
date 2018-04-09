
get_target_property( odb_bin odb LOCATION )

set( test_environment
  ODB_API_CODES=${PROJECT_SOURCE_DIR}/etc
  ODB_API_HOME=${PROJECT_SOURCE_DIR}
  ODB_API_TEST_DATA_PATH=${CMAKE_CURRENT_BINARY_DIR}
  PATH=${CMAKE_BINARY_DIR}/bin:$ENV{PATH}
  ODB_RTABLE_PATH=${PROJECT_SOURCE_DIR}/etc

  TEST_DHSHOME=${CMAKE_CURRENT_SOURCE_DIR}/dhshome/
  TEST_DATA_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}
)

### odb2_to_odb1 tests

ecbuild_get_test_multidata( TARGET get_odb2_to_odb1_data NAMES odb2_to_odb1.ECMA.conv.tar.gz NOCHECK )

ecbuild_add_test(

    TARGET test_odb2_to_odb1

    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test_odb2_to_odb1.sh

    ENVIRONMENT
        ${test_environment}
        ${ODB_ENVIRONMENT}
        PATH=${CMAKE_BINARY_DIR}/bin:${odb_BASE_DIR}/bin:$ENV{PATH}
        ODB_IO_METHOD=4
        ODB_IO_GRPSIZE=160

    TEST_DEPENDS get_odb2_to_odb1_data

    CONDITION HAVE_FORTRAN AND ODB_FOUND AND ODB_HAVE_ECMA )


if ( HAVE_FORTRAN AND ODB_FOUND AND ODB_HAVE_ECMA)
    set_tests_properties( test_odb2_to_odb1 PROPERTIES LABELS "odb_api;odb_api_migrator" )
endif()


### Migrator tests

if ( HAVE_MIGRATOR )

    list( APPEND test_migrator_data_files 2000010106.old.ECMA.tar.gz )

    ecbuild_get_test_multidata( TARGET get_migrator_test_data
                                NAMES ${test_migrator_data_files}
                                NOCHECK )

    list( APPEND migrator_tests
        import_odb
        import_odb_dispatching )

    foreach( _test ${migrator_tests} )

        ecbuild_add_test(

            TARGET test_${_test}
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test_${_test}.sh

            ENVIRONMENT
                ${test_environment}
                ${ODB_ENVIRONMENT}

            TEST_DEPENDS get_migrator_test_data
        )

        set_tests_properties( test_${_test} PROPERTIES LABELS "odb_api;odb_api_migrator" )

    endforeach()

endif()
