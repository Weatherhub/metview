set(sources

    MTOCOMP.ddl

    alloc.h
    bits.h
    cdrhook.h
    cma.h
    dca.h
    ecstdlib.h
    funcs.h
    idx.h
    info.h
    magicwords.h
    mdi.h
    namecfg.h
    obstype.h
    odb.h
    odb98.flags
    odb_macros.h
    odbcrc.h
    odbmd5.h
    pcma_extern.h
    ppcode.h
    privpub.h
    sensor.h
    swapbytes.h
    varno.h
    vertco_type.h
)

set(views)

odb_add_schema(TARGET MTOCOMP SOURCES ${sources} VIEWS ${views} CONDITION ODB_HAVE_MTOCOMP TYPE ${ODB_LIBS_TYPE})
