//
//  PSBIAS hierarchy:
//
//      1  desc
//      2  +---> hdr
//      3  +---> body

SET $mdi = 2147483647;

SET $synop = 1;
SET $manual_synop = 11;
SET $automatic_synop = 14;
SET $manual_ship = 21;
SET $abbreviated_ship = 22;
SET $reduced_ship = 23;
SET $automatic_ship = 24;
SET $metar = 140;
SET $dribu = 4;
SET $buoy = 165;
SET $bathy = 63;
SET $tesac = 64;

SET $bufr_land_surface = 0;
SET $bufr_land_manual = 1;
SET $bufr_land_automatic = 3;
SET $bufr_land_abbreviated = 9;
SET $bufr_land_metar = 140;
SET $bufr_sea_surface = 1;
SET $bufr_sea_manual_1 = 11;
SET $bufr_sea_manual_2 = 9;
SET $bufr_sea_reduced = 19;
SET $bufr_sea_automatic = 13;
SET $bufr_sea_dribu = 21;
SET $bufr_sea_bathy = 22;
SET $bufr_sea_tesac = 23;

SET $psvarno = 110;

SET $max_body_len = 756;

SET $reduced_press_code = 0;
SET $station_level_press_code = 1;


CREATE TYPE status_t AS (
  active bit1,                          // ACTIVE FLAG
  passive bit1,                         // PASSIVE FLAG
  rejected bit1,                        // REJECTED FLAG
  blacklisted bit1,                     // BLACKLISTED
// BLACKLIST FAILCODE BITS
  monthly bit1,
  constant bit1,
  experimental bit1,
  whitelist bit1,
);

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

CREATE TYPE datum_rdbflag_t AS (
  press_humon bit1,
  press_QCsub bit1,
  press_override bit1,
  press_flag bit2,
  press_HQC_flag bit1,
  press_judged_prev_an bit2,
  press_used_prev_an bit1,
  _press_unused_6 bit6,
  varno_humon bit1,
  varno_QCsub bit1,
  varno_override bit1,
  varno_flag bit2,
  varno_HQC_flag bit1,
  varno_judged_prev_an bit2,
  varno_used_prev_an bit1,
//  _varno_unused_6 bit6,
);

CREATE TYPE datum_flag_t AS (
  final bit4,           // FINAL FLAG
  fg bit4,              // FIRST GUESS FLAG
  depar bit4,           // DEPARTURE FLAG
  varQC bit4,           // VARIATIONAL QUALITY FLAG
  blacklist bit4,       // BLACKLIST FLAG
  ups bit1,             // d'utilisation par analyse de pression de surface
  uvt bit1,             // d'utilisation par analyse de vent et temperature
  uhu bit1,             // d'utilisation par analyse d'humidite
  ut2 bit1,             // d'utilisation par analyse de temperature a 2m
  uh2 bit1,             // d'utilisation par analyse d'humidite a 2m
  uv1 bit1,             // d'utilisation par analyse de vent a 10m
  urr bit1,             // d'utilisation par analyse de precipitations
  usn bit1,             // d'utilisation par analyse de neige
  usst bit1,            // d'utilisation par analyse de temperature de surface de la mer
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
);

CREATE TYPE datum_event2_t = pk1int;

CREATE TYPE report_blacklist_t AS (
  obstype bit1,
  statid bit1,
  codetype bit1,
  instype bit1,
  date bit1,
  time bit1,
  lat bit1,
  lon bit1,
  stalt bit1,
  scanpos bit1,
  retrtype bit1,
  QI_1 bit1,
  QI_2 bit1,
  QI_3 bit1,
  modoro bit1,
  lsmask bit1,
  rlsmask bit1,
  modPS bit1,
  modTS bit1,
  modT2M bit1,
  modtop bit1,
  sensor bit1,
  fov bit1,
  satza bit1,
  andate bit1,
  antime bit1,
);

CREATE TYPE datum_blacklist_t AS (
  varno bit1,
  vertco_type bit1,
  press bit1,
  press_rl bit1,
  ppcode bit1,
  obsvalue bit1,
  fg_depar bit1,
  obs_error bit1,
  fg_error bit1,
  winchan_dep bit1,
  obs_t bit1,
);

CREATE TYPE bc_info_t AS (
  cold_start bit1,
  duplicate_report bit1,
  quasiduplicate_report bit1,
  code_type_switch_over bit1,
  instrument_change bit1,
  ps_code_change bit1,
  kalman_method_flag bit1,
  oi_method_flag bit1,
  auxiliary bit1,
);

CREATE TABLE desc AS (
  // creation date, time and created by whom (username)
  creadate YYYYMMDD,
  creatime HHMMSS,
  creaby   string,

  // modification date, time and modified by whom (username)
  moddate YYYYMMDD,
  modtime HHMMSS,
  modby   string,
);

CREATE TABLE hdr AS (
  seqno pk1int,                                //  1 OBSERVATION SEQUENCE
  obstype pk1int,                              //  2 OBSERVATION TYPE
  code_type pk1int,                            //  3 OBSERVATION CODE TYPE
  instrument_type pk1int,                      //  4 OBSERVATION INSTRUMENT TYPE
  date YYYYMMDD,                               //  5 OBS. DATE
  time HHMMSS,                                 //  6 OBS. EXACT TIME
  source string,                               //  7 Source ID of obs. (CHARACTER*8): ERA
  statid string,                               //  8 STATION ID (CHARACTER*8)
  lat pk9real,                                 //  9 LATITUDE
  lon pk9real,                                 // 10 LONGITUDE
  stalt pk9real,                               // 11 ALTITUDE
  modoro pk9real,                              // 12 MODEL'S OROGRAPHY
  anemoht pk9real,                             // 13 HEIGHT OF ANEMOMETER
  baroht pk9real,                              // 14 HEIGHT OF BAROMETRE
  numlev pk1int,		   	                   // 15 No. of levels
  subtype pk1int,                              // 16 BUFR subtype for reference
  bufrtype pk1int,                             // 17 BUFR-type
  station_type pk1int,                         // 18 SYNOP/SHIPs (needed to find out if DRIBU)
//bias_correction_on pk1int,                   // 19 bias correction on (0/1=bias correction off/on)
  reserved_0 pk9real,                          // 19 reserved 
  bc_info BC_INFO_t,                           // 20 station info 
//
  variable_no pk1int,                          // 21 variable no
  vertical_coordin_type pk1int,                // 22 vertical coordinate type 
  order_no pk1int,                             // 23 order/entry no.
  vertical_coordin pk9real,                    // 24 vertical coordinate
  observed_value pk9real,                      // 25 observed value
  biascorr_ind pk1int,                         // 26 current BIAS CORRECTION INDICATOR:
//                                                   00=no bias/decision
//                                                   11=long term bias
//                                                   21=KALMAN current bias
//                                                   22=KALMAN long term bias
//                                                   31=OI current bias
//                                                   32=OI long term bias
  biascorr pk9real,                            // 27 BIAS CORRECTION
//
  pressure_code pk1int,                        // 28 PRESSURE CODE
  departure pk9real,                           // 29 current OBSERVED MINUS FIRST GUESS VALUE
  previous_departure pk9real,                  // 30 PREVIOUS OBSERVED MINUS FIRST GUESS VALUE
//
  kl_weight pk9real,                           // 31 KALMAN METHOD WEIGHT
  kl_current_bias_estimate pk9real,            // 32 CURRERNT KALMAN METHOD BIAS ESTIMATE
  kl_previous_bias_estimate pk9real,           // 33 PREVIOUS KALMAN METHOD BIAS ESTIMATE
  kl_current_variance pk9real,                 // 34 CURRERNT KALMAN METHOD BIAS VARIANCE
  kl_previous_variance pk9real,                // 35 PREVIOUS KALMAN METHOD BIAS VARIANCE
  kl_current_obserr pk9real,                   // 36 CURRERNT KALMAN METHOD BIAS OBS ERROR
  kl_previous_obserr pk9real,                  // 37 PREVIOUS KALMAN METHOD BIAS OBS ERROR
  kl_c_parameter pk9real,                      // 38 KALMAN METHOD BIAS ESTIMATE C (confidence) 
  kl_long_term_bias pk9real,                   // 39 Kalman method long term bias estimate
  reserved_1 pk9real,                          // 40 reserved 
//
  oi_weight pk9real,                           // 41 OI METHOD WEIGHT
  oi_current_bias_estimate pk9real,            // 42 CURRERNT OI METHOD BIAS ESTIMATE
  oi_previous_bias_estimate pk9real,           // 43 PREVIOUS OI METHOD BIAS ESTIMATE
  oi_current_variance pk9real,                 // 44 CURRERNT OI METHOD BIAS VARIANCE
  oi_previous_variance pk9real,                // 45 PREVIOUS OI METHOD BIAS VARIANCE
  oi_current_obserr pk9real,                   // 46 CURRERNT OI METHOD BIAS OBS ERROR
  oi_previous_obserr pk9real,                  // 47 PREVIOUS OI METHOD BIAS OBS ERROR
  oi_q_varance pk9real,                        // 48 OI METHOD QUALITY
  oi_bias_err_estimate pk9real,                // 49 OI METHOD BIAS ERROR ESTIMATE
  oi_long_term_bias pk9real,                   // 50 OI method long term bias estimate
//
  long_term_sample_size pk1int,                // 51 long term sample size
  long_term_mean_departure pk9real,            // 52 long term mean
  long_term_bias pk9real,                      // 53 long term bias
  long_term_std  pk9real,                      // 54 long term std
  long_term_rms  pk9real,                      // 55 long term rms
//
  biascorr_applied pk9real,                    // 56 BIAS CORRECTION
//
  report_status STATUS_t,                      // 57 REPORT'S STATUS
  report_event_1 REPORT_EVENT1_t,              // 58 REPORT'S EVENTS (PART 1)
  report_event_2 REPORT_EVENT2_t,              // 59 REPORT'S EVENTS (PART 2)
  report_rdb_flag REPORT_RDBFLAG_T,            // 60 REPORT'S RDB FLAG
  report_blacklist REPORT_BLACKLIST_T,         // 61 REPORT'S BLACKLIST EVENTS
//
  ps_status STATUS_t,                          // 62 Ps STATUS
  ps_event_1 DATUM_EVENT1_t,                   // 63 Ps EVENTS (PART 1)
  ps_event_2 DATUM_EVENT2_t,                   // 64 Ps EVENTS (PART 2)
  ps_blacklist DATUM_BLACKLIST_T,              // 65 Ps BLACKLIST EVENTS
  ps_flag DATUM_FLAG_T,                        // 66 Ps FLAG
  ps_rdb_flag DATUM_RDBFLAG_T,                 // 67 Ps RDB FLAG
//
  body @LINK,                                  // 68-69 offset and length
);

CREATE TABLE body AS (
  history_date YYYYMMDD,                       //  1 DATE
  history_time HHMMSS,                         //  2 TIME
  history_departure pk9real,                   //  3 departure
//
  history_kl_bias pk9real,                     //  4 kalman method bias estimate
  history_kl_weight pk9real,                   //  5 KALMAN WEIGHT
  history_kl_variance pk9real,                 //  6 KALMAN variance
  history_kl_obserr  pk9real,                  //  7 KALMAN obs error
  history_kl_c_parameter pk9real,              //  8 KALMAN C param
//
  history_oi_bias pk9real,                     //  9 oi method bias estimate
  history_oi_weight pk9real,                   // 10 OI WEIGHT
  history_oi_variance pk9real,                 // 11 OI variance
  history_oi_obserr  pk9real,                  // 12 OI obs error
  history_oi_q_varance pk9real,                // 13 OI METHOD QUALITY
  history_oi_err_estimate  pk9real,            // 14 OI METHOD BIAS ERROR ESTIMATE
//
  history_bc_info BC_INFO_t,                   // 15 info
//
  history_report_status STATUS_t,              // 16 REPORT'S STATUS
  history_report_event_1 REPORT_EVENT1_t,      // 17 REPORT'S EVENTS (PART 1)
  history_report_event_2 REPORT_EVENT2_t,      // 18 REPORT'S EVENTS (PART 2)
  history_report_rdb_flag REPORT_RDBFLAG_T,    // 19 REPORT'S RDB FLAG
  history_report_blacklist REPORT_BLACKLIST_T, // 20 REPORT'S BLACKLIST EVENTS
//
  history_ps_status STATUS_t,                  // 21 Ps STATUS
  history_ps_event_1 DATUM_EVENT1_t,           // 22 Ps EVENTS (PART 1)
  history_ps_event_2 DATUM_EVENT2_t,           // 23 Ps EVENTS (PART 2)
  history_ps_blacklist DATUM_BLACKLIST_T,      // 24 Ps BLACKLIST EVENTS
  history_ps_flag DATUM_FLAG_T,                // 25 Ps FLAG
  history_ps_rdb_flag DATUM_RDBFLAG_T,         // 26 Ps RDB FLAG
//
  history_biascorr_ind pk1int,                 // 27 BIAS CORRECTION INDICATOR
  history_biascorr pk9real,                    // 28 NEW BIAS CORRECTION
  history_biascorr_applied pk9real,            // 29 APPLIED BIAS CORRECTION
);
