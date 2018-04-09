#undef ODB_MAINCODE
#undef IS_a_VIEW
#define IS_a_TABLE_body 1
#include "DB.h"

extern double USD_mdi_DB; /* $mdi */


PUBLIC int
DB_Pack_T_body(void *T)
{
  int Nbytes = 0;
  TABLE_body *P = T;
  Packed_DS *PDS;
  if (P->Is_loaded) {
    PDS = PackDS(P, DB, pk1int, entryno); CHECK_PDS_ERROR(1);
    PDS = PackDS(P, DB, pk1int, varno); CHECK_PDS_ERROR(2);
    PDS = PackDS(P, DB, pk9real, press); CHECK_PDS_ERROR(3);
    PDS = PackDS(P, DB, pk9real, obsvalue); CHECK_PDS_ERROR(4);
    PDS = PackDS(P, DB, pk9real, depar); CHECK_PDS_ERROR(5);
    PDS = PackDS(P, DB, pk9real, obs_error); CHECK_PDS_ERROR(6);
    PDS = PackDS(P, DB, pk9real, bias); CHECK_PDS_ERROR(7);
  }
  return Nbytes;
}

PUBLIC int
DB_Unpack_T_body(void *T)
{
  int Nbytes = 0;
  TABLE_body *P = T;
  if (P->Is_loaded) {
    UseDS(P, DB, pk1int, entryno); Nbytes += BYTESIZE(P->entryno.d);
    UseDS(P, DB, pk1int, varno); Nbytes += BYTESIZE(P->varno.d);
    UseDS(P, DB, pk9real, press); Nbytes += BYTESIZE(P->press.d);
    UseDS(P, DB, pk9real, obsvalue); Nbytes += BYTESIZE(P->obsvalue.d);
    UseDS(P, DB, pk9real, depar); Nbytes += BYTESIZE(P->depar.d);
    UseDS(P, DB, pk9real, obs_error); Nbytes += BYTESIZE(P->obs_error.d);
    UseDS(P, DB, pk9real, bias); Nbytes += BYTESIZE(P->bias.d);
  }
  return Nbytes;
}

PUBLIC int
DB_Sel_T_body(void *T, ODB_PE_Info *PEinfo, int phase, void *feedback)
{
  TABLE_body *P = T;
  ODBMAC_TABLE_DELAYED_LOAD(body);
  return P->Nrows;
}


PreGetTable(DB, d, double, body)
  Call_CopyGet_TABLE(DB, d, 1, body, pk1int, D, entryno, Count, DATATYPE_INT4);
  Call_CopyGet_TABLE(DB, d, 2, body, pk1int, D, varno, Count, DATATYPE_INT4);
  Call_CopyGet_TABLE(DB, d, 3, body, pk9real, D, press, Count, DATATYPE_REAL8);
  Call_CopyGet_TABLE(DB, d, 4, body, pk9real, D, obsvalue, Count, DATATYPE_REAL8);
  Call_CopyGet_TABLE(DB, d, 5, body, pk9real, D, depar, Count, DATATYPE_REAL8);
  Call_CopyGet_TABLE(DB, d, 6, body, pk9real, D, obs_error, Count, DATATYPE_REAL8);
  Call_CopyGet_TABLE(DB, d, 7, body, pk9real, D, bias, Count, DATATYPE_REAL8);
PostGetTable(d, double, body)


PrePutTable(DB, d, double, body)
  Call_CopyPut_TABLE(DB, d, 1, body, pk1int, entryno, D, Count, DATATYPE_INT4);
  Call_CopyPut_TABLE(DB, d, 2, body, pk1int, varno, D, Count, DATATYPE_INT4);
  Call_CopyPut_TABLE(DB, d, 3, body, pk9real, press, D, Count, DATATYPE_REAL8);
  Call_CopyPut_TABLE(DB, d, 4, body, pk9real, obsvalue, D, Count, DATATYPE_REAL8);
  Call_CopyPut_TABLE(DB, d, 5, body, pk9real, depar, D, Count, DATATYPE_REAL8);
  Call_CopyPut_TABLE(DB, d, 6, body, pk9real, obs_error, D, Count, DATATYPE_REAL8);
  Call_CopyPut_TABLE(DB, d, 7, body, pk9real, bias, D, Count, DATATYPE_REAL8);
PostPutTable(d, double, body)

PreLoadTable(DB, body);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, pk1int, DATATYPE_INT4, entryno);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, pk1int, DATATYPE_INT4, varno);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, press);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, obsvalue);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, depar);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, obs_error);
  Call_Read_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, bias);
PostLoadTable(body)

PreStoreTable(DB, body);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, pk1int, DATATYPE_INT4, entryno);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, pk1int, DATATYPE_INT4, varno);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, press);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, obsvalue);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, depar);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, obs_error);
  Call_Write_DS(DB, fp_idx, filename, Nbytes, pk9real, DATATYPE_REAL8, bias);
PostStoreTable(body)

DefineLookupTable(body)

PUBLIC void
DB_Dim_T_body(void *T, int *Nrows, int *Ncols,
  int *Nrowoffset, int ProcID)
{
  TABLE_body *P = T;
  Call_LookupTable(body, P, Nrows, Ncols);
  if (Nrowoffset) *Nrowoffset = 0;
}

PUBLIC void
DB_Swapout_T_body(void *T)
{
  TABLE_body *P = T;
  int Nbytes = 0;
  int Count = 0;
  int PoolNo = P->PoolNo;
  FILE *do_trace = NULL;
  if (P->Swapped_out || !P->Is_loaded) return;
  do_trace = ODB_trace_fp();
  FreeDS(P, entryno, Nbytes, Count);
  FreeDS(P, varno, Nbytes, Count);
  FreeDS(P, press, Nbytes, Count);
  FreeDS(P, obsvalue, Nbytes, Count);
  FreeDS(P, depar, Nbytes, Count);
  FreeDS(P, obs_error, Nbytes, Count);
  FreeDS(P, bias, Nbytes, Count);
  P->Nrows = 0;
  P->Nalloc = 0;
  P->Is_loaded = 0;
  P->Swapped_out = P->Is_new ? 0 : 1;
  ODBMAC_TRACE_SWAPOUT(body,7);
}

DefineRemoveTable(DB, body)

PUBLIC int
DB_Sql_T_body(FILE *fp, int mode, const char *prefix, const char *postfix, char **sqlout) { ODBMAC_TABLESQL(); }

PUBLIC void *
DB_Init_T_body(void *T, ODB_Pool *Pool, int Is_new, int IO_method, int it, int dummy)
{
  TABLE_body *P = T;
  int PoolNo = Pool->poolno;
  ODB_Funcs *pf;
  static ODB_CommonFuncs *pfcom = NULL; /* Shared between pools & threads */
  DRHOOK_START(DB_Init_T_body);
  if (!P) ALLOC(P, 1);
  PreInitTable(P, 7);
  InitDS(pk1int, DATATYPE_INT4, entryno, body, 1);
  InitDS(pk1int, DATATYPE_INT4, varno, body, 1);
  InitDS(pk9real, DATATYPE_REAL8, press, body, 9);
  InitDS(pk9real, DATATYPE_REAL8, obsvalue, body, 9);
  InitDS(pk9real, DATATYPE_REAL8, depar, body, 9);
  InitDS(pk9real, DATATYPE_REAL8, obs_error, body, 9);
  InitDS(pk9real, DATATYPE_REAL8, bias, body, 9);
  if (!pfcom) { /* Initialize once only */
    CALLOC(pfcom,1);
    { static char s[] = "@body"; pfcom->name = s; }
    pfcom->is_table = 1;
    pfcom->is_considered = 0;
    pfcom->ntables = 0;
    pfcom->ncols = 7;
    pfcom->tableno = 1;
    pfcom->rank = 1;
    pfcom->wt = 1.000001;
    pfcom->tags = DB_Set_T_body_TAG(&pfcom->ntag, &pfcom->nmem);
    pfcom->preptags = DB_Set_T_body_PREPTAG(&pfcom->npreptag);
    pfcom->Info = NULL;
    pfcom->create_index = 0;
    pfcom->init = DB_Init_T_body;
    pfcom->swapout = DB_Swapout_T_body;
    pfcom->dim = DB_Dim_T_body;
    pfcom->sortkeys = NULL;
    pfcom->update_info = NULL;
    pfcom->aggr_info = NULL;
    pfcom->getindex = NULL; /* N/A */
    pfcom->putindex = NULL; /* N/A */
    pfcom->select = DB_Sel_T_body;
    pfcom->remove = DB_Remove_T_body;
    pfcom->peinfo = NULL; /* N/A */
    pfcom->cancel = NULL;
    pfcom->dget = DB_dGet_T_body; /* REAL(8) dbmgr */
    pfcom->dput = DB_dPut_T_body; /* REAL(8) dbmgr */
    pfcom->load = DB_Load_T_body;
    pfcom->store = DB_Store_T_body;
    pfcom->pack = DB_Pack_T_body;
    pfcom->unpack = DB_Unpack_T_body;
    pfcom->sql = DB_Sql_T_body;
    pfcom->ncols_aux = 0;
    pfcom->colaux = NULL;
    pfcom->has_select_distinct = 0;
    pfcom->has_usddothash = 0;
  } /* if (!pfcom) */
  ALLOC(pf, 1);
  pf->it = it;
  pf->data = P;
  pf->Res = NULL;
  pf->tmp = NULL;
  pf->pool = Pool;
  pf->common = pfcom;
  pf->next = NULL;
  P->Funcs = pf;
  P->Handle = P->Funcs->pool->handle;
  DRHOOK_END(0);
  return P;
}

/* *************** End of TABLE "body" *************** */
