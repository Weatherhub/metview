//
//-- ODB/SQL file 'update_links_gbrad.sql'
//
//   Last updated:  22-Jul-2010
//

UPDATED;

CREATE VIEW update_links_gbrad AS
  SELECT body, gbrad_body, 
    FROM hdr, gbrad
    WHERE obstype=$gbrad and codetype=$radrr
;
