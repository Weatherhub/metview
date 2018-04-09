//
//-- ODB/SQL file 'varbc_mode_hist_robhdr.sql'
//

READONLY;

CREATE VIEW varbc_mode_hist_robhdr AS
  SELECT seqno,
         body.len,
         codetype@hdr,
  FROM   index, hdr
;
