//
//-- ODB/SQL file 'links_body.sql'
//
//   Last updated:  01-May-2010
//

SET $codetype = -1;

READONLY;

CREATE VIEW links_body AS
  SELECT body, auxiliary
    FROM hdr
    WHERE ((obstype=$satem) OR (obstype=$allsky))
    AND  (($codetype == -1) OR (codetype == $codetype))
;
