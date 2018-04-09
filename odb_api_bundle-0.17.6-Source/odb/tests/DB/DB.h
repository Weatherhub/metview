#ifndef ODB_GENCODE
#define ODB_GENCODE 1
#endif


/* Software revision : CY43R0.000 (430000) */

#include "odb.h"
#include "odb_macros.h"
#include "cdrhook.h"

#define ODB_LABEL    "DB"


/* Compilation options used :

	 -V
	 -O3
	 -I/usr/local/include
	 -lDB
	 -DDB
	 -s
	 -S
	 -C
	 -lDB
	 -DDB
	 -1index=hdr

*/

/* ----- Table hierarchy (= the default scanning order) : # of tables = 2

       Rank#         Table :     Order#   Weight
       -----         ----- :     ------   ------
           0           hdr :          0   0.000000
           1          body :          1   1.000001

   ----- End of table hierarchy ----- */

PUBLIC void DB_print_flags_file(void);

#if defined(ODB_MAINCODE)

PUBLIC double USD_mdi_DB = 2147483647; /* $mdi */

#endif /* defined(ODB_MAINCODE) */

DefineDS(pk1int);
#define DB_pack_INT ODB_pack_INT
#define DB_unpack_INT ODB_unpack_INT
DS_Unpacking(DB, INT, pk1int)
DS_Packing(DB, INT, pk1int)

DefineDS(yyyymmdd);
DS_Unpacking(DB, INT, yyyymmdd)
DS_Packing(DB, INT, yyyymmdd)

DefineDS(hhmmss);
DS_Unpacking(DB, INT, hhmmss)
DS_Packing(DB, INT, hhmmss)

DefineDS(string);
#define DB_pack_DBL ODB_pack_DBL
#define DB_unpack_DBL ODB_unpack_DBL
DS_Unpacking(DB, DBL, string)
DS_Packing(DB, DBL, string)

DefineDS(pk9real);
DS_Unpacking(DB, DBL, pk9real)
DS_Packing(DB, DBL, pk9real)

DefineDS(linkoffset_t);
DS_Unpacking(DB, INT, linkoffset_t)
DS_Packing(DB, INT, linkoffset_t)

DefineDS(linklen_t);
DS_Unpacking(DB, INT, linklen_t)
DS_Packing(DB, INT, linklen_t)


#if defined(IS_a_TABLE_hdr) || defined(ODB_MAINCODE) || defined(IS_a_VIEW)

/* *************** TABLE "hdr" : appearance order#0, hierarchy rank# 0, weight = 0.000000 *************** */

typedef struct {
  int Handle;
  int PoolNo;
  ODB_Funcs *Funcs;
  boolean Is_loaded;
  boolean Is_new;
  boolean Swapped_out;
  boolean Byteswap;
  int IO_method;
  int Created[2];
  int LastUpdated[2];
  int Ncols;
  int Nrows;
  int Nalloc;
  int Numreqs;
  DeclareDS(pk1int,seqno);
  DeclareDS(yyyymmdd,date);
  DeclareDS(hhmmss,time);
  DeclareDS(string,statid);
  DeclareDS(pk9real,lat);
  DeclareDS(pk9real,lon);
  DeclareDS(linkoffset_t,LINKOFFSET(body));
  DeclareDS(linklen_t,LINKLEN(body));
} TABLE_hdr;

#endif /* defined(IS_a_TABLE_hdr) || defined(ODB_MAINCODE)  || defined(IS_a_VIEW) */

#if !defined(ODB_MAINCODE) && defined(IS_a_TABLE_hdr)
extern const ODB_Tags *DB_Set_T_hdr_TAG(int *ntag_out, int *nmem_out);
extern const ODB_PrepTags *DB_Set_T_hdr_PREPTAG(int *npreptag_out);
#elif defined(ODB_MAINCODE)
PRIVATE const ODB_Tags *DB_T_hdr_TAG = NULL;
PRIVATE const ODB_PrepTags *DB_T_hdr_PREPTAG = NULL;
PRIVATE int DB_nT_hdr_TAG = 0;
PRIVATE int DB_nT_hdr_PREPTAG = 0;
PRIVATE int DB_nT_hdr_MEM = 0;
PUBLIC const ODB_Tags *
DB_Set_T_hdr_TAG(int *ntag_out, int *nmem_out)
{
  if (!DB_T_hdr_TAG) {
    int ntag = 8;
    ODB_Tags *T = NULL;
    CALLOC(T, ntag);
    { static char s[] = "pk1int:seqno@hdr"; T[0].name = s; }
    { static char s[] = "yyyymmdd:date@hdr"; T[1].name = s; }
    { static char s[] = "hhmmss:time@hdr"; T[2].name = s; }
    { static char s[] = "string:statid@hdr"; T[3].name = s; }
    { static char s[] = "pk9real:lat@hdr"; T[4].name = s; }
    { static char s[] = "pk9real:lon@hdr"; T[5].name = s; }
    { static char s[] = "linkoffset_t:LINKOFFSET(body)@hdr"; T[6].name = s; }
    { static char s[] = "linklen_t:LINKLEN(body)@hdr"; T[7].name = s; }
    DB_T_hdr_TAG = T;
    DB_nT_hdr_TAG = ntag;
    DB_nT_hdr_MEM = 0;
  }
  if (ntag_out) *ntag_out = DB_nT_hdr_TAG;
  if (nmem_out) *nmem_out = DB_nT_hdr_MEM;
  return DB_T_hdr_TAG;
}
PUBLIC const ODB_PrepTags *
DB_Set_T_hdr_PREPTAG(int *npreptag_out)
{
  if (!DB_T_hdr_PREPTAG) {
    int npreptag = 2;
    ODB_PrepTags *T = NULL;
    ALLOC(T, npreptag);
    T[0].tagtype = (preptag_name | preptag_extname);
    T[0].longname_len = 95;
    { static char s[] =
      ";seqno@hdr;date@hdr;time@hdr;statid@hdr;lat@hdr;lon@hdr;"
      "LINKOFFSET(body)@hdr;LINKLEN(body)@hdr;";
      T[0].longname = s; }
    T[1].tagtype = (preptag_type | preptag_exttype);
    T[1].longname_len = 70;
    { static char s[] =
      ";pk1int;yyyymmdd;hhmmss;string;pk9real;pk9real;linkoffset_t;"
      "linklen_t;";
      T[1].longname = s; }
    DB_T_hdr_PREPTAG = T;
    DB_nT_hdr_PREPTAG = npreptag;
  }
  if (npreptag_out) *npreptag_out = DB_nT_hdr_PREPTAG;
  return DB_T_hdr_PREPTAG;
}
#endif

#if defined(ODB_MAINCODE)

extern int DB_Pack_T_hdr(void *T);
extern int DB_Unpack_T_hdr(void *T);
extern int DB_Sel_T_hdr(void *T, ODB_PE_Info *PEinfo, int phase, void *feedback);
PreGetTable(DB, d, double, hdr);
PrePutTable(DB, d, double, hdr);
PreLoadTable(DB, hdr);
PreStoreTable(DB, hdr);
extern void DB_Dim_T_hdr(void *T, int *Nrows, int *Ncols, int *Nrowoffset, int ProcID);
extern void DB_Swapout_T_hdr(void *T);
extern int DB_Sql_T_hdr(FILE *fp, int mode, const char *prefix, const char *postfix, char **sqlout);
extern void *DB_Init_T_hdr(void *T, ODB_Pool *Pool, int Is_new, int IO_method, int it, int dummy);

#endif /* defined(ODB_MAINCODE) */

#if defined(IS_a_TABLE_body) || defined(ODB_MAINCODE) || defined(IS_a_VIEW)

/* *************** TABLE "body" : appearance order#1, hierarchy rank# 1, weight = 1.000001 *************** */

typedef struct {
  int Handle;
  int PoolNo;
  ODB_Funcs *Funcs;
  boolean Is_loaded;
  boolean Is_new;
  boolean Swapped_out;
  boolean Byteswap;
  int IO_method;
  int Created[2];
  int LastUpdated[2];
  int Ncols;
  int Nrows;
  int Nalloc;
  int Numreqs;
  DeclareDS(pk1int,entryno);
  DeclareDS(pk1int,varno);
  DeclareDS(pk9real,press);
  DeclareDS(pk9real,obsvalue);
  DeclareDS(pk9real,depar);
  DeclareDS(pk9real,obs_error);
  DeclareDS(pk9real,bias);
} TABLE_body;

#endif /* defined(IS_a_TABLE_body) || defined(ODB_MAINCODE)  || defined(IS_a_VIEW) */

#if !defined(ODB_MAINCODE) && defined(IS_a_TABLE_body)
extern const ODB_Tags *DB_Set_T_body_TAG(int *ntag_out, int *nmem_out);
extern const ODB_PrepTags *DB_Set_T_body_PREPTAG(int *npreptag_out);
#elif defined(ODB_MAINCODE)
PRIVATE const ODB_Tags *DB_T_body_TAG = NULL;
PRIVATE const ODB_PrepTags *DB_T_body_PREPTAG = NULL;
PRIVATE int DB_nT_body_TAG = 0;
PRIVATE int DB_nT_body_PREPTAG = 0;
PRIVATE int DB_nT_body_MEM = 0;
PUBLIC const ODB_Tags *
DB_Set_T_body_TAG(int *ntag_out, int *nmem_out)
{
  if (!DB_T_body_TAG) {
    int ntag = 7;
    ODB_Tags *T = NULL;
    CALLOC(T, ntag);
    { static char s[] = "pk1int:entryno@body"; T[0].name = s; }
    { static char s[] = "pk1int:varno@body"; T[1].name = s; }
    { static char s[] = "pk9real:press@body"; T[2].name = s; }
    { static char s[] = "pk9real:obsvalue@body"; T[3].name = s; }
    { static char s[] = "pk9real:depar@body"; T[4].name = s; }
    { static char s[] = "pk9real:obs_error@body"; T[5].name = s; }
    { static char s[] = "pk9real:bias@body"; T[6].name = s; }
    DB_T_body_TAG = T;
    DB_nT_body_TAG = ntag;
    DB_nT_body_MEM = 0;
  }
  if (ntag_out) *ntag_out = DB_nT_body_TAG;
  if (nmem_out) *nmem_out = DB_nT_body_MEM;
  return DB_T_body_TAG;
}
PUBLIC const ODB_PrepTags *
DB_Set_T_body_PREPTAG(int *npreptag_out)
{
  if (!DB_T_body_PREPTAG) {
    int npreptag = 2;
    ODB_PrepTags *T = NULL;
    ALLOC(T, npreptag);
    T[0].tagtype = (preptag_name | preptag_extname);
    T[0].longname_len = 86;
    { static char s[] =
      ";entryno@body;varno@body;press@body;obsvalue@body;"
      "depar@body;obs_error@body;bias@body;";
      T[0].longname = s; }
    T[1].tagtype = (preptag_type | preptag_exttype);
    T[1].longname_len = 55;
    { static char s[] =
      ";pk1int;pk1int;pk9real;pk9real;pk9real;pk9real;pk9real;";
      T[1].longname = s; }
    DB_T_body_PREPTAG = T;
    DB_nT_body_PREPTAG = npreptag;
  }
  if (npreptag_out) *npreptag_out = DB_nT_body_PREPTAG;
  return DB_T_body_PREPTAG;
}
#endif

#if defined(ODB_MAINCODE)

extern int DB_Pack_T_body(void *T);
extern int DB_Unpack_T_body(void *T);
extern int DB_Sel_T_body(void *T, ODB_PE_Info *PEinfo, int phase, void *feedback);
PreGetTable(DB, d, double, body);
PrePutTable(DB, d, double, body);
PreLoadTable(DB, body);
PreStoreTable(DB, body);
extern void DB_Dim_T_body(void *T, int *Nrows, int *Ncols, int *Nrowoffset, int ProcID);
extern void DB_Swapout_T_body(void *T);
extern int DB_Sql_T_body(FILE *fp, int mode, const char *prefix, const char *postfix, char **sqlout);
extern void *DB_Init_T_body(void *T, ODB_Pool *Pool, int Is_new, int IO_method, int it, int dummy);

#endif /* defined(ODB_MAINCODE) */

