odb_add_schema(TARGET DB SOURCES DB.ddl
  VIEWS querydata1.sql querydata2.sql CONDITION ENABLE_TESTS NOINSTALL)

ecbuild_add_executable(TARGET createdb.x
  SOURCES createdb.F90
  INCLUDES ${ODB_INCLUDE_DIRS}
  LIBS ${ODB_LIBRARIES}
  CONDITION ENABLE_TESTS NOINSTALL)

ecbuild_add_executable(TARGET populate.x
  SOURCES populate.F90
  INCLUDES ${ODB_INCLUDE_DIRS}
  LIBS ${ODB_LIBRARIES}
  CONDITION ENABLE_TESTS NOINSTALL)

ecbuild_add_executable(TARGET querydata.x
  SOURCES querydata.F90
  INCLUDES ${ODB_INCLUDE_DIRS}
  LIBS ${ODB_LIBRARIES}
  CONDITION ENABLE_TESTS NOINSTALL)

odb_link_schemas(createdb.x  DB)
odb_link_schemas(populate.x  DB)
odb_link_schemas(querydata.x DB)

if(HAVE_ODB_MPI)
  if(NOT MPIEXEC) # FIXME: MPIEXEC is not set on Cray, assuming mpiexec for now
    set(_MPIEXEC_CMD mpiexec\ -n\ 1)
  else()
    set(_MPIEXEC_CMD ${MPIEXEC}\ -n\ 1)
  endif()
endif()

ecbuild_add_test(TARGET test_createdb
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/createdb.sh
    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/createdb.F90
         ${CMAKE_CURRENT_SOURCE_DIR}/DB.ddl
         ${CMAKE_CURRENT_SOURCE_DIR}/createdb.out
    ENVIRONMENT
        ${ODB_ENVIRONMENT}
        PATH=${CMAKE_CURRENT_BINARY_DIR}:${CMAKE_BINARY_DIR}/bin:$ENV{PATH}
        MPIEXEC_CMD=${_MPIEXEC_CMD}
    TEST_DEPENDS createdb.x
)

ecbuild_add_test(TARGET test_populate
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/populate.sh
    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/populate.F90
         ${CMAKE_CURRENT_SOURCE_DIR}/populate.out
    ENVIRONMENT
        ${ODB_ENVIRONMENT}
        PATH=${CMAKE_CURRENT_BINARY_DIR}:${CMAKE_BINARY_DIR}/bin:$ENV{PATH}
        MPIEXEC_CMD=${_MPIEXEC_CMD}
    TEST_DEPENDS populate.x test_createdb
)
