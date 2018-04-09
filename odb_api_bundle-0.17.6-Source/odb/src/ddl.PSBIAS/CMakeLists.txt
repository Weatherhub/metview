set(views

    psbias_compress_method_0.sql
    psbias_compress_method_1a.sql
    psbias_compress_method_1b.sql
    psbiasbody.sql
    psbiasbody_maintenance.sql
    psbiashdr.sql
    psbiashdr_maintenance.sql
)

odb_add_schema(TARGET PSBIAS SOURCES PSBIAS.ddl VIEWS ${views} CONDITION ODB_HAVE_PSBIAS TYPE ${ODB_LIBS_TYPE})
