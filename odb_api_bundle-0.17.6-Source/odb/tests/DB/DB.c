#define ODB_MAINCODE 1

#include "DB.h"

PUBLIC void 
DB_print_flags_file(void)
{
  int rc = 0, io = -1;
  FILE *fp = NULL;
  cma_open_(&io, "DB.flags", "w", &rc, strlen("DB.flags"), strlen("w"));
  if (rc != 1) return; /* multi-bin file ==> forget flags-file */
  fp = CMA_get_fp(&io);
  if (!fp) return; /* pointer NULL ==> forget the flags-file ;-( */
  fprintf(fp,"%s\n","-Abody=(update,errstat,allsky_body,scatt_body,ssmi_body,radar_body, resat_averaging_kernel,update_1,update_2,update_3,update_4)");
  fprintf(fp,"%s\n","-Aatovs=atovs_pred");
  fprintf(fp,"%s\n","-1index=hdr");
  fprintf(fp,"%s\n","-1hdr=sat");
  fprintf(fp,"%s\n","-1sat=(resat,atovs,ssmi,scatt,satob,satem,radar_station,radar)");
  fprintf(fp,"-1index=hdr\n");
  cma_close_(&io, &rc);
}

PRIVATE int 
Create_Funcs(ODB_Pool *pool, int is_new, int io_method, int it)
{
  int nfuncs = 0;
  static int first_time = 1;
  static int IsConsidered[2];
  DRHOOK_START(Create_Funcs);
  if (first_time) {
    ODBMAC_INIT_IsConsidered(hdr, 0);
    ODBMAC_INIT_IsConsidered(body, 1);
    first_time = 0;
  } /* if (first_time) */
  ODBMAC_CREATE_TABLE(DB, hdr, 0, 1);
  ODBMAC_CREATE_TABLE(DB, body, 1, 1);
  DRHOOK_END(0);
  return nfuncs;
}

PRIVATE int
Load_Pool(ODB_Pool *P, int io_method)
{
  int rc = 0;
  int Nbytes = 0;
  ODB_Funcs *pf = P->funcs;
  if (io_method != 5) {
    Call_TABLE_Load(hdr, pf, 1);
    Call_TABLE_Load(body, pf, 1);
  } /* if (io_method != 5) */
  return (rc < 0) ? rc : Nbytes;
}

PRIVATE int
Store_Pool(const ODB_Pool *P, int io_method)
{
  int rc = 0;
  int Nbytes = 0;
  ODB_Funcs *pf = P->funcs;
  if (io_method != 5) {
    Call_TABLE_Store(hdr, pf, 1);
    Call_TABLE_Store(body, pf, 1);
  } /* if (io_method != 5) */
  return (rc < 0) ? rc : Nbytes;
}

PUBLIC ODB_Funcs *
Anchor2DB(void *V, ODB_Pool *pool, int *ntables, int it, int add_vars)
{
  ODB_Anchor_Funcs *func = V;
  ODB_Pool *p = pool;
  DRHOOK_START(Anchor2DB);
  /* A special case : ntables not a NULL => return no. of tables */
  if (ntables) {
    *ntables = 2;
    goto finish;
  }
  func->create_funcs = Create_Funcs;
  func->load         = Load_Pool;
  func->store        = Store_Pool;
  if (add_vars) {
    p->add_var(p->dbname, "$mdi", NULL, it, USD_mdi_DB);
  } /* if (add_vars) */
  finish:
  DRHOOK_END(0);
  return NULL;
}
