//
//-- ODB/SQL file 'sathdr_screen_atovs.sql'
//
//   Last updated:  17-May-2001
//

UPDATED;
SET $kset = 0;

CREATE VIEW sathdr_screen_atovs AS
  SELECT seqno  READONLY,                  // r/o; MUST BECOME FIRST
         scanpos@radiance  READONLY,       // r/o
         zenith@sat  READONLY,             // r/o
         azimuth  READONLY,                // r/o
         t2m,                              // possibly updated
         surface_class,                    // possibly updated
         skintemper,                       // possibly updated
         skintemp[1:($NMXUPD+1)]@radiance, // possibly updated
         cldptop[1:3],                     // possibly updated
         cldne[1:3],                       // possibly updated
         cldcover,
         solar_zenith@sat   READONLY,      // r/o
         solar_azimuth@sat  READONLY,      // r/o
         scatterindex_89_157 UPDATED,
         scatterindex_23_89 UPDATED,
         scatterindex_23_165 UPDATED,
         lwp_obs UPDATED,
         typesurf UPDATED,
         asr_pcloudy_high,                 // updated
         asr_pcloudy_middle  READONLY,     // r/o
         avhrr_stddev_ir    READONLY,    // r/o
         avhrr_stddev_ir2    READONLY,    // r/o
         avhrr_frac_cl1      READONLY,    // r/o
         avhrr_frac_cl2      READONLY,    // r/o
         avhrr_frac_cl3      READONLY,    // r/o
         avhrr_frac_cl4      READONLY,    // r/o
         avhrr_frac_cl5      READONLY,    // r/o
         avhrr_frac_cl6      READONLY,    // r/o
         avhrr_frac_cl7      READONLY,    // r/o
         avhrr_m_ir1_cl1     READONLY,    // r/o
         avhrr_m_ir1_cl2     READONLY,    // r/o
         avhrr_m_ir1_cl3     READONLY,    // r/o
         avhrr_m_ir1_cl4     READONLY,    // r/o
         avhrr_m_ir1_cl5     READONLY,    // r/o
         avhrr_m_ir1_cl6     READONLY,    // r/o
         avhrr_m_ir1_cl7     READONLY,    // r/o
         avhrr_m_ir2_cl1     READONLY,    // r/o
         avhrr_m_ir2_cl2     READONLY,    // r/o
         avhrr_m_ir2_cl3     READONLY,    // r/o
         avhrr_m_ir2_cl4     READONLY,    // r/o
         avhrr_m_ir2_cl5     READONLY,    // r/o
         avhrr_m_ir2_cl6     READONLY,    // r/o
         avhrr_m_ir2_cl7     READONLY,    // r/o
         avhrr_fg_ir1,                    // updated
         avhrr_fg_ir2,                    // updated
         avhrr_cloud_flag,                // updated
    FROM index, hdr, sat, radiance, modsurf, collocated_imager_information
   WHERE kset = $kset
     AND obstype = $satem 
     AND codetype = $atovs
;
