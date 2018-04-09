//
//-- ODB/SQL file 'sathdr_screen_resat.sql'
//
//   Created:  6-May-2003
//

UPDATED;
SET $kset = 0;
CREATE VIEW sathdr_screen_resat AS
SELECT seqno READONLY,
       solar_elevation READONLY,
FROM index, hdr, sat, resat
WHERE kset = $kset
;
