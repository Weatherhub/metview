//
//-- ODB/SQL file 'sathdr_screen_gpsro.sql'
//
//   Last updated:  17-Mar-2011
//

SET $kset = 0;

CREATE VIEW sathdr_screen_gpsro AS
  SELECT seqno  READONLY,                  // r/o; MUST BECOME FIRST
    radcurv,
    FROM index, hdr, gnssro
   WHERE kset = $kset
     AND obstype = $limb 
     AND codetype = $gpsro
;
