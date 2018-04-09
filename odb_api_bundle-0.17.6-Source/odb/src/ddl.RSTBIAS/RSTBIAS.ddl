//
//  RSTBIAS hierarchy:
//
//      1  desc
//      2  +---> hdr
//      3  +---> body

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
  seqno pk1int,                        //  1 SEQUENCE NO
  statid string,                       //  2 STATION ID (CHARACTER*8)
  lat pk9real,                         //  3 LATITUDE
  lon pk9real,                         //  4 LONGITUDE
  stalt pk9real,                       //  5 ALTITUDE
  sonde_name string,                   //  6 SONDE NAME
  sonde_code pk1int,                   //  7 SONDE CODE
  date_from YYYYMMDD,                  //  8 VALID DATE FROM
  time_from HHMMSS,                    //  9 VALID TIME FROM
  date_to YYYYMMDD,                    // 10 VALID DATE TO
  time_to HHMMSS,                      // 11 VALID TIME TO
  body @LINK,
);


CREATE TABLE body AS (
  press pk9real,                       //    1 VERTICAL COORDINATE (PRESSURE)
  bccf[13] pk9real,                    // 2-14 BIAS CORRECTIONS COEFFICINTS
);

