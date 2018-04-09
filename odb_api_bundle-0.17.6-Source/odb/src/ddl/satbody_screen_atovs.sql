//
//-- ODB/SQL file 'satbody_screen_atovs.sql'
//
//   Last updated:  27-Aug-2014
//

UPDATED; // the default: all updated (except those with  READONLY or  READONLY)

SET $kset = 0;

CREATE VIEW satbody_screen_atovs AS
  SELECT seqno  READONLY,              // r/o; MUST BECOME FIRST
         emis_retr,                    // possibly updated
         emis_atlas,                   // possibly updated
         emis_atlas_error,             // possibly updated
         emis_rtin,                    // possibly updated
         skintemp_retr,                // possibly updated
         tausfc,                       // possibly updated
         cld_fg_depar,                 // possibly updated
         rank_cld,                     // possibly updated
         nobs_averaged READONLY,       // r/o
         stdev_averaged READONLY,      // r/o
         jacobian_peak,                // possibly updated
         jacobian_hpeak,               // possibly updated
         jacobian_peakl,               // possibly updated
         jacobian_hpeakl,              // possibly updated
         tbclear,                      // clear sky TB
 FROM   index, hdr, body, sat, radiance, radiance_body
  WHERE	 kset = $kset
     AND obstype = $satem
     AND codetype = $atovs
;
