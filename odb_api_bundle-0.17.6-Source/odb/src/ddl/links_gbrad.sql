//
//-- ODB/SQL file 'links_gbrad.sql'
//
//   Last updated:  22-Jul-2010
//

UPDATED;

CREATE VIEW links_gbrad AS
  SELECT gbrad
    FROM hdr
  WHERE obstype=$gbrad and codetype=$radrr
;
