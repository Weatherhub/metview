//
//  SONDETYPES hierarchy:
//
//      1  desc
//      2  +---> hdr
//RESET ALIGN;
//ALIGN(body[1:12]);

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

  seqno pk1int,                             //  1 SEQUENCE NO
  sonde_code pk1int,                        //  2 SONDE CODE
  sonde_name[8] string,                     //  3 SONDE NAME
);
