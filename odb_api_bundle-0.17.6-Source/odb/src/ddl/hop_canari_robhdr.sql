//
//-- ODB/SQL file 'hop_canari_robhdr.sql'
//
//   Last updated:  09-Oct-2001
//

READONLY;

SET $kset = 0;

CREATE VIEW hop_canari_robhdr AS
  SELECT seqno,
         body.len,
         abnob, mapomm,
         codetype,
         lat,
         stalt,
  FROM   index, hdr
  WHERE  kset = $kset
;
