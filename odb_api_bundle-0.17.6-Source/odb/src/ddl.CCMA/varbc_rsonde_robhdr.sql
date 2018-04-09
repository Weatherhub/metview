//
//-- ODB/SQL file 'varbc_rsonde_robhdr.sql'
//
//   For setting VarBC group indices

READONLY;

CREATE VIEW varbc_rsonde_robhdr AS
  SELECT seqno,
         body.len,
         reportype,
         statid,
         sonde_type
  FROM   index, hdr, conv
  WHERE  obstype = $temp

;

// Note:
//    if the elements in the SELE.CT are changed, remember to update varbc_rsonde.F90

