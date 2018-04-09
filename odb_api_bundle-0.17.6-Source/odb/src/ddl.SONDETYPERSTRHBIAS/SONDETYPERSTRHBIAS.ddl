//
//  SONDETYPERSTRHBIAS hierarchy:
//
//      1  desc
//      2  +---> hdr
//      2  +--------> body
//

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
  seqno pk1int,                      //     1 SEQUENCE NO
  sonde_type_code pk1int,            //     2 SONDE TYPE CODE
  sonde_name[8] string,              //  3-10 SONDE TYPE NAME
  body @LINK,                        // 11-12 Offset, len
);

CREATE TABLE body AS (
  press pk9real,                     //  1 VERTICAL COORDINATE (PRESSURE)

  T_N_m75 pk1int,                    //  2 No. of T data FOR ANGLEs up TO -7.5
  T_N_m75_75 pk1int,                 //  3 No. of T data FOR ANGLEs -7.5 to 7.5
  T_N_75_225 pk1int,                 //  4 No. of T data FOR ANGLEs 7.5 to 22.5
  T_N_225 pk1int,                    //  5 No. of T data FOR ANGLEs above 22.5
  T_N_mean pk1int,                   //  6 No. of T data FOR MEAN

  T_D_m75 pk9real,                   //  7 T Uncorrected Departures FOR ANGLEs up TO -7.5
  T_D_m75_75 pk9real,                //  8 T Uncorrected Departures FOR ANGLEs -7.5 to 7.5
  T_D_75_225 pk9real,                //  9 T Uncorrected Departures FOR ANGLEs 7.5 to 22.5
  T_D_225 pk9real,                   // 10 T Uncorrected Departures FOR ANGLEs above 22.5
  T_D_mean pk9real,                  // 11 T Uncorrected Departures FOR MEAN

  T_C_m75 pk9real,                   // 12 T Corrected Departures FOR ANGLEs up TO -7.5
  T_C_m75_75 pk9real,                // 13 T Corrected Departures FOR ANGLEs -7.5 to 7.5
  T_C_75_225 pk9real,                // 14 T Corrected Departures FOR ANGLEs 7.5 to 22.5
  T_C_225 pk9real,                   // 15 T Corrected Departures FOR ANGLEs above 22.5
  T_C_mean pk9real,                  // 16 T Corrected Departures FOR MEAN

  T_B_m75_vs_all_mean pk9real,       // 17 T SOLAR BIAS FOR ANGLEs up TO -7.5 vs ALL MEAN
  T_B_m75_75_vs_all_mean pk9real,    // 18 T SOLAR BIAS FOR ANGLEs -7.5 to 7.5 vs ALL MEAN
  T_B_75_225_vs_all_mean pk9real,    // 19 T SOLAR BIAS FOR ANGLEs 7.5 to 22.5 vs ALL MEAN
  T_B_225_vs_all_mean pk9real,       // 20 T SOLAR BIAS FOR ANGLEs above 22.5 vs ALL MEAN
  T_B_all_mean pk9real,              // 21 T MEAN BIAS ALL MEAN

  T_B_m75_vs_night_mean pk9real,     // 22 T SOLAR BIAS FOR ANGLEs up TO -7.5 vs NIGHT MEAN
  T_B_m75_75_vs_night_mean pk9real,  // 23 T SOLAR BIAS FOR ANGLEs -7.5 to 7.5 vs NIGHT MEAN
  T_B_75_225_vs_night_mean pk9real,  // 24 T SOLAR BIAS FOR ANGLEs 7.5 to 22.5 vs NIGHT MEAN
  T_B_225_vs_night_mean pk9real,     // 25 T SOLAR BIAS FOR ANGLEs above 22.5 vs NIGHT MEAN
  T_B_night_mean pk9real,            // 26 T MEAN BIAS NIGHT MEAN

  T_B_m75_vs_day_mean pk9real,       // 27 T SOLAR BIAS FOR ANGLEs up TO -7.5 vs DAY MEAN
  T_B_m75_75_vs_day_mean pk9real,    // 28 T SOLAR BIAS FOR ANGLEs -7.5 to 7.5 vs DAY MEAN
  T_B_75_225_vs_day_mean pk9real,    // 29 T SOLAR BIAS FOR ANGLEs 7.5 to 22.5 vs DAY MEAN
  T_B_225_vs_day_mean pk9real,       // 30 T SOLAR BIAS FOR ANGLEs above 22.5 vs DAY MEAN
  T_B_day_mean pk9real,              // 31 T MEAN BIAS DAY MEAN

  RH_N_m75 pk1int,                   // 32 No. of RH data FOR ANGLEs up TO -7.5
  RH_N_m75_75 pk1int,                // 33 No. of RH data FOR ANGLEs -7.5 to 7.5
  RH_N_75_225 pk1int,                // 34 No. of RH data FOR ANGLEs 7.5 to 22.5
  RH_N_225 pk1int,                   // 35 No. of RH data FOR ANGLEs above 22.5
  RH_N_mean pk1int,                  // 36 No. of RH data FOR MEAN

  RH_D_m75 pk9real,                  // 37 RH Uncorrected Departures FOR ANGLEs up TO -7.5
  RH_D_m75_75 pk9real,               // 38 RH Uncorrected Departures FOR ANGLEs -7.5 to 7.5
  RH_D_75_225 pk9real,               // 39 RH Uncorrected Departures FOR ANGLEs 7.5 to 22.5
  RH_D_225 pk9real,                  // 40 RH Uncorrected Departures FOR ANGLEs above 22.5
  RH_D_mean pk9real,                 // 41 RH Uncorrected Departures FOR MEAN

  RH_C_m75 pk9real,                  // 42 RH Corrected Departures FOR ANGLEs up TO -7.5 vs ALL MEAN
  RH_C_m75_75 pk9real,               // 43 RH Corrected Departures FOR ANGLEs -7.5 to 7.5 vs ALL MEAN
  RH_C_75_225 pk9real,               // 44 RH Corrected Departures FOR ANGLEs 7.5 to 22.5 vs ALL MEAN
  RH_C_225 pk9real,                  // 45 RH Corrected Departures FOR ANGLEs above 22.5 vs ALL MEAN
  RH_C_mean pk9real,                 // 46 RH Corrected Departures FOR MEAN

  RH_B_m75_vs_all_mean pk9real,      // 47 RH SOLAR BIAS FOR ANGLEs up TO -7.5 vs ALL MEAN
  RH_B_m75_75_vs_all_mean pk9real,   // 48 RH SOLAR BIAS FOR ANGLEs -7.5 to 7.5 vs ALL MEAN
  RH_B_75_225_vs_all_mean pk9real,   // 49 RH SOLAR BIAS FOR ANGLEs 7.5 to 22.5 vs ALL MEAN
  RH_B_225_vs_all_mean pk9real,      // 50 RH SOLAR BIAS FOR ANGLEs above 22.5 vs ALL MEAN
  RH_B_all_mean pk9real,             // 51 RH MEAN BIAS  FOR ALL MEAN

  RH_B_m75_vs_night_mean pk9real,    // 52 RH SOLAR BIAS FOR ANGLEs up TO -7.5 vs NIGHT MEAN
  RH_B_m75_75_vs_night_mean pk9real, // 53 RH SOLAR BIAS FOR ANGLEs -7.5 to 7.5 vs NIGHT MEAN
  RH_B_75_225_vs_night_mean pk9real, // 54 RH SOLAR BIAS FOR ANGLEs 7.5 to 22.5 vs NIGHT MEAN
  RH_B_225_vs_night_mean pk9real,    // 55 RH SOLAR BIAS FOR ANGLEs above 22.5 vs NIGHT MEAN
  RH_B_night_mean pk9real,           // 56 RH MEAN BIAS FOR NIGHT MEAN

  RH_B_m75_vs_day_mean pk9real,      // 57 RH SOLAR BIAS FOR ANGLEs up TO -7.5 vs DAY MEAN
  RH_B_m75_75_vs_day_mean pk9real,   // 58 RH SOLAR BIAS FOR ANGLEs -7.5 to 7.5 vs DAY MEAN
  RH_B_75_225_vs_day_mean pk9real,   // 59 RH SOLAR BIAS FOR ANGLEs 7.5 to 22.5 vs DAY MEAN
  RH_B_225_vs_day_mean pk9real,      // 60 RH SOLAR BIAS FOR ANGLEs above 22.5 vs DAY MEAN
  RH_B_day_mean pk9real,             // 61 RH MEAN BIAS FOR DAY MEAN
);
