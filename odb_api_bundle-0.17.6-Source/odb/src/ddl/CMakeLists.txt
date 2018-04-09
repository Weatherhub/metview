install(FILES odb98.flags DESTINATION share/odb)
install(FILES odb98.flags DESTINATION include) # TODO: until Xavi installs new odb module template

configure_file(odb98.flags ${CMAKE_BINARY_DIR}/share/odb/odb98.flags COPYONLY)
