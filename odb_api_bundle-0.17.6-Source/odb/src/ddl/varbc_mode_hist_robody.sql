//
//-- ODB/SQL file 'varbc_mode_hist_robody.sql'
//

READONLY;

CREATE VIEW varbc_mode_hist_robody AS
  SELECT seqno,
         varbc_ix@body, 
         fg_depar,
         biascorr,
  FROM   index, hdr, body
  WHERE  datum_status@body = 3
;
