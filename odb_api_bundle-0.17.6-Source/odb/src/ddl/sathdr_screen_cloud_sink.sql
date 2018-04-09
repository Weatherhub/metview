//
//-- ODB/SQL file 'sathdr_screen_cloud_sink.sql'
//
//   Last updated:  17-May-2001
//

SET $kset = 0;

CREATE VIEW sathdr_screen_cloud_sink AS
  SELECT seqno  READONLY,                   // r/o; MUST BECOME FIRST
         ctopbg,
         ctoper,
         ctopinc,
         ctop[1:$NMXUPD],
         camtbg,
         camter,
         camtinc,
         camt[1:$NMXUPD],
    FROM index, hdr, sat, radiance, cloud_sink
   WHERE kset = $kset
     AND obstype = $satem 
     AND codetype = $atovs
;
