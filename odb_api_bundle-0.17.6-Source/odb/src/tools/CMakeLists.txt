
ecbuild_add_library(TARGET odbmain
    TYPE STATIC # to allow extraction of objects using ar -x
    DEPENDS odbifsaux odb_lib # parkind1.mod, odb_mod.mod
    SOURCES Create_index.F90
            Odbcompress.F90
            Odbdiff.F90
            Odbgnuplot.F90
            Odbless.F90)

set(libs ${ODB_LIBRARIES})
include_directories(${ODB_INCLUDE_DIRS})

ecbuild_add_executable(TARGET odbsql.x SOURCES Fodbsql.F90
    LINKER_LANGUAGE Fortran LIBS ${libs})

ecbuild_add_executable(TARGET fscheduler.x SOURCES Fscheduler.F90
    LINKER_LANGUAGE Fortran LIBS ${libs})

ecbuild_add_executable(TARGET dcagen.x SOURCES dcagen.c LIBS ${libs})
ecbuild_add_executable(TARGET hcat     SOURCES hcat.c   LIBS ${libs})
ecbuild_add_executable(TARGET ioassign SOURCES ioassign.c LIBS ${libs})
ecbuild_add_executable(TARGET odb2rgg SOURCES odb2rgg.c LIBS ${libs})
ecbuild_add_executable(TARGET odbversion SOURCES odbversion.c LIBS ${libs})
ecbuild_add_executable(TARGET odbcksum SOURCES odbcksum.c LIBS ${libs})
ecbuild_add_executable(TARGET odbdump.x SOURCES odbdump_main.c LIBS ${libs})
ecbuild_add_executable(TARGET odbmd5sum SOURCES odbmd5sum.c LIBS ${libs})
ecbuild_add_executable(TARGET pcma SOURCES pcma_main.c LIBS ${libs})
ecbuild_add_executable(TARGET qtar SOURCES qtar.c LIBS ${libs})

set(_odb_mpi_targets odb98.x odbsql.x fscheduler.x dcagen.x hcat ioassign odb2rgg
  odbversion odbcksum odbdump.x odbmd5sum pcma qtar)

if(HAVE_ODB_MPI AND HAVE_ODB_MPI_SERIAL_WRAPPERS)
  foreach(_target ${_odb_mpi_targets})
    # For now we assume that target name and output name are the same
    get_filename_component(_name ${_target} NAME_WE)
    get_filename_component(_ext ${_target} EXT)
    set_target_properties(${_target} PROPERTIES OUTPUT_NAME "${_name}mp${_ext}")
    add_custom_target(serial${_target} ALL COMMAND ${CMAKE_COMMAND}
      -E create_symlink .odb_serial_wrapper.sh ${_target}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    install(PROGRAMS ${CMAKE_BINARY_DIR}/bin/${_target} DESTINATION bin)
  endforeach()
endif()

# Client/server tools

ecbuild_add_executable(TARGET odbi_client.x
    SOURCES odbi_client_main.c LIBS ${libs} CONDITION ODB_CLIENT_SERVER)
ecbuild_add_executable(TARGET odbi_server.x
    SOURCES odbi_server_main.c LIBS ${libs} CONDITION ODB_CLIENT_SERVER)
ecbuild_add_executable(TARGET odbi_direct.x
    SOURCES odbi_direct_main.c LIBS ${libs} CONDITION ODB_CLIENT_SERVER)
ecbuild_add_executable(TARGET odbi_host.x
    SOURCES odbi_host.c LIBS ${libs} CONDITION ODB_CLIENT_SERVER)

# Serial helper tools

ecbuild_add_executable(TARGET dd2ddl.x SOURCES dd2ddl.c)
ecbuild_add_executable(TARGET mysort SOURCES mysort.c)
ecbuild_add_executable(TARGET scheduler SOURCES scheduler.c)
ecbuild_add_executable(TARGET odbfiletime.x SOURCES odbfiletime.c)

ecbuild_add_executable(TARGET b4.x DEFINITIONS HAS_XMOTIF SOURCES b4.c
    LIBS ${libs} ${MOTIF_LIBRARIES}
    CONDITION MOTIF_FOUND AND ODB_DEPRECATED)

