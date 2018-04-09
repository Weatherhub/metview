//
//-- ODB/SQL file 'hop_canari_robody.sql'
//
//   Last updated:  09-Oct-2001
//

READONLY;

SET $kset = 0;

CREATE VIEW hop_canari_robody AS
  SELECT seqno,
         varno,
         vertco_reference_1,
         vertco_reference_2,
         obsvalue,
         mf_log_p UPDATED,
         final_obs_error,
         an_depar UPDATED,
         fg_depar UPDATED,
         mf_stddev UPDATED,
         fg_error UPDATED
  FROM   index, hdr, body, errstat
  WHERE  kset = $kset
;
