SET  $NMXUPD = 3;

CREATE TYPE report_rdbflag_t AS (
  lat_humon bit1,  
  lat_QCsub bit1,  
  lat_override bit1,  
  lat_flag bit2,  
  lat_HQC_flag bit1,  
  lon_humon bit1,  
  lon_QCsub bit1,  
  lon_override bit1,  
  lon_flag bit2,  
  lon_HQC_flag bit1,  
  date_humon bit1,  
  date_QCsub bit1,  
  date_override bit1,  
  date_flag bit2,  
  date_HQC_flag bit1,  
  time_humon bit1,  
  time_QCsub bit1,  
  time_override bit1,  
  time_flag bit2,  
  time_HQC_flag bit1,  
  stalt_humon bit1,  
  stalt_QCsub bit1,  
  stalt_override bit1,  
  stalt_flag bit2,  
  stalt_HQC_flag bit1,  
);

CREATE TYPE status_t AS (
  active bit1,                          // ACTIVE FLAG
  passive bit1,                         // PASSIVE FLAG
  rejected bit1,                        // REJECTED FLAG
  blacklisted bit1,                     // BLACKLISTED
  monthly bit1,
  constant bit1,
  experimental bit1,
  whitelist bit1,
);

CREATE TYPE datum_flag_t AS (
  final bit4,                           // FINAL FLAG
  fg bit4,                              // FIRST GUESS FLAG
  depar bit4,                           // DEPARTURE FLAG
  varQC bit4,                           // VARIATIONAL QUALITY FLAG
  blacklist bit4,                       // BLACKLIST FLAG
  ups bit1,                             // d'utilisation par analyse de pression de surface
  uvt bit1,                             // d'utilisation par analyse de vent et temperature
  uhu bit1,                             // d'utilisation par analyse d'humidite
  ut2 bit1,                             // d'utilisation par analyse de temperat ure a 2m
  uh2 bit1,                             // d'utilisation par analyse d'humidite a 2m
  uv1 bit1,                             // d'utilisation par analyse de vent a 10m
  urr bit1,                             // d'utilisation par analyse de precipitations
  usn bit1,                             // d'utilisation par analyse de neige
  usst bit1,                            // d'utilisation par analyse de temperature de surface de la mer
);

CREATE TYPE report_event1_t AS (
  no_data bit1,  
  all_rejected bit1,  
  bad_practice bit1,  
  rdb_rejected bit1,  
  rdb_activated bit1,  
  whitelist_activated bit1,  
  horipos_outrange bit1,  
  vertpos_outrange bit1,  
  time_outrange bit1,  
  redundant bit1,  
  land bit1,  
  sea bit1,  
  stalt_missing bit1,  
  modsurf_stalt_distance bit1,  
  namelist_rejected bit1,  
  QC_failed bit1,  
);

CREATE TYPE report_event2_t = pk1int;

CREATE TYPE datum_event1_t AS (
  vertco_missing bit1,  
  obsvalue_missing bit1,  
  fg_missing bit1,  
  rdb_rejected bit1,  
  rdb_activated bit1,  
  whitelist_activated bit1,  
  bad_practice bit1,  
  vertpos_outrange bit1,  
  reflevel_outrange bit1,  
  fg2big bit1,  
  depar2big bit1,  
  obs_error2big bit1,  
  datum_redundant bit1,  
  level_redundant bit1,  
  land bit1,  
  sea bit1,  
  not_analysis_varno bit1,  
  duplicate bit1,  
  levels2many bit1,  
  multilevel_check bit1,  
  level_selection bit1,  
  vertco_consistency bit1,  
  vertco_type_changed bit1,  
  namelist_rejected bit1,  
  combined_flagging bit1,  
  report_rejected bit1,  
  varQC_performed bit1,
  contam_cld_flag bit1,  // cloud contamination
  contam_rain_flag bit1, // rain contamination
  contam_aerosol_flag bit1, // aerosol contamination
);

CREATE TABLE ddrs AS (
  ddrno pk1int,  
  wordno pk1int,  
  bulkdata pk9real,  
);

CREATE TABLE hdr AS (
  obstype pk1int,                       // OBSERVATION TYPE
  codetype pk1int,                      // OBSERVATION CODE TYPE
  insttype pk1int,                      // OBSERVATION INSTRUMENT TYPE
  date YYYYMMDD,                        // OBS. DATE
  time HHMMSS,                          // OBS. EXACT TIME
  status STATUS_t,                      // REPORT'S STATUS
  event1 REPORT_EVENT1_t,               // REPORT'S EVENTS (PART 1)
  statid string,                        // STATION ID (CHARACTER*8)
  ident pk1int,                         // Integer equivalent of STATION ID (or zero)
  lat pk9real,                          // LATITUDE
  lon pk9real,                          // LONGITUDE
  stalt pk9real,                        // ALTITUDE
  modoro pk9real,                       // MODEL'S OROGRAPHY
  sensor pk1int,                        // SATELLITE SENSOR INDICATOR
  sat @LINK,  
  body @LINK,  
  errstat @LINK,  
  update[1:$NMXUPD] @LINK,  
  rdbflag REPORT_RDBFLAG_t,             // REPORT'S FLAGS
  event2 REPORT_EVENT2_t,               // REPORT EVENTS (PART 2) WORD POS.
);

CREATE TABLE sat AS (
  satid pk1int,                        // Integer equivalent to statid@hdr or 0; same as ident@hdr
  atovs @LINK,  
  reo3  @LINK,  
  satob @LINK,  
  scatt @LINK,  
);

CREATE TABLE reo3 AS (
  solar_elevation pk9real,              // SOLAR ELEVATION
);

CREATE TABLE satob AS (
  comp_method pk1int,                   // CLOUD MOTION COMP. METHOD
);

CREATE TABLE atovs AS (
  scanline pk1int,                      // SCAN LINE NUMBER                   
  fov pk1int,                           // FIELD OF VIEW NUMBER               
  bearing_azimuth pk9real,              // BEARING OR AZIMUTH
  cldne[1:2] pk9real,                   // CLOUD EMISSIVITY FROM HIRS RADIANCES
);

CREATE TABLE atovs_pred AS (
  predictor[16] pk9real,  
);

CREATE TABLE scatt AS (
  cellno pk1int,                        // CELL NO.
);

CREATE TABLE body AS (
  varno pk1int,                         // VARIABLE NUMBER
  anflag DATUM_FLAG_t,                  // OBSERVATION FLAGS
  status STATUS_t,                      // OBSERVATION STATUS
  event1 DATUM_EVENT1_t,                // OBSERVATION EVENTS (PART 1)
  press pk9real,                        // VERTICAL COORDINATE REFERENCE 1
  press_rl pk9real,                     // VERTICAL COORDINATE REFERENCE 2
  obsvalue pk9real,                     // OBSERVED VARIABLE
  biascorr pk9real,                     // RADIANCE BIAS CORRECTION
  an_depar pk9real,                     // OBSERVED MINUS ANALYSED VALUE
  fg_depar pk9real,                     // OBSERVED MINUS FIRST GUESS VALUE
  fg_check[2] pk9real,  
);

CREATE TABLE errstat AS (
  obs_error pk9real,                    // OBSERVATION ERROR
  repres_error pk9real,                 // REPRESENTATIVENESS ERROR
  fg_error pk9real,                     // FIRST GUESS ERROR
);

CREATE TABLE update[1:$NMXUPD] AS (
  hires pk9real,               // OBS. MINUS UPD. U HIGH RES. VALUE
  lores pk9real,               // OBS. MINUS UPD. U LOW RES. VALUE
);
