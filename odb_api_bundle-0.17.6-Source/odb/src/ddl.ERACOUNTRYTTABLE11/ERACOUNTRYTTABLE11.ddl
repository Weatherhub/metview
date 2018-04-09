//
//  ERACOUNTRYTTABLE11 hierarchy:
//
//      1  era_country_t_table11_desc
//      2  +---> era_country_t_table11_hdr
//
//RESET ALIGN;
//ALIGN(body[1:12]);

CREATE TABLE era_country_t_table11_desc AS (
// creation date, time and created by whom (username)
creadate YYYYMMDD,
creatime HHMMSS,
creaby   string,

// modification date, time and modified by whom (username)
moddate YYYYMMDD,
modtime HHMMSS,
modby   string,
);

CREATE TABLE era_country_t_table11_hdr AS (
  seqno pk1int,                        //     1 SEQUENCE NO
  active_line pk1int,                  //     2 ACTIVE LINE IND (=1)
  active_inactive_seqno pk1int,        //     3 ACTIVE LINE SEQUENCE NO
  country_group pk1int,                //     4 COUNTRY GROUP
  country_statid_from pk1int,          //     5 COUNTRY STAT ID FROM
  country_statid_to pk1int,            //     6 COUNTRY STAT ID TO
  country_lat_from pk1int,             //     7 COUNTRY LAT FROM
  country_lat_to pk1int,               //     8 COUNTRY LAT TO
  country_lon_from pk1int,             //     9 COUNTRY LON FROM
  country_lon_to pk1int,               //    10 COUNTRY LON TO
  country_name[8] string,              // 11-18 COUNTRY NAME
);
