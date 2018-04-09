//
//  ERACOUNTRYTTABLE12 hierarchy:
//
//      1  country_t_table12_desc
//      2  +---> country_t_table12_hdr
//
//RESET ALIGN;
//ALIGN(body[1:12]);

CREATE TABLE era_country_t_table12_desc AS (
// creation date, time and created by whom (username)
creadate YYYYMMDD,
creatime HHMMSS,
creaby   string,

// modification date, time and modified by whom (username)
moddate YYYYMMDD,
modtime HHMMSS,
modby   string,
);

CREATE TABLE era_country_t_table12_hdr AS (
  seqno pk1int,                        //     1 SEQUENCE NO
  active_line pk1int,                  //     2 ACTIVE LINE IND
  active_inactive_seqno pk1int,        //     3 active/inactive line count
  country_group pk1int,                //     4 COUNTRY GROUP
  country_name[8] string,              //  5-12 COUNTRY name
);

