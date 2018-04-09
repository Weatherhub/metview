//
//-- ODB/SQL file 'hretr_canari_satbody.sql'
//
//   Last updated:  16-Mar-2011
//
// AF: added this SQL query but cannot test anything (CANARI configuration)
//     may need to add something in getdb (same as hretr for IFS/ARPEGE)

READONLY;

SET $kset = 0;

CREATE VIEW hretr_canari_satbody AS
  SELECT seqno,
         entryno,
         bg_refractivity UPDATED,           // possibly updated
         bg_dndz UPDATED,          // possibly updated
         bg_layerno UPDATED             // possibly updated
  FROM   index, hdr, body, gnssro, gnssro_body
  WHERE  kset = $kset
  AND obstype = $satem AND codetype = $gpsro
;
