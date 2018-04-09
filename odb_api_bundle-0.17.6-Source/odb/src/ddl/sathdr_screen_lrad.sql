//
//-- ODB/SQL file 'sathdr_screen_lrad.sql'
//
//   Last updated:  22-Nov-2004
//


UPDATED;

SET $kset = 0;

CREATE VIEW sathdr_screen_lrad AS
  SELECT seqno READONLY,                   // r/o; MUST COME FIRST
         satellite_identifier@sat READONLY,               // r/o
         ntan,                             // r/o
         ztan[1:$mx_limb_tan],             // r/o
         ptan[1:$mx_limb_tan],             // r/o
         window_rad[1:$mx_limb_tan],       // r/o
         cloud_index[1:$mx_limb_tan]       // r/o
    FROM index, hdr, sat, limb
   WHERE kset = $kset
     AND obstype = $limb AND codetype = $lrad
;
