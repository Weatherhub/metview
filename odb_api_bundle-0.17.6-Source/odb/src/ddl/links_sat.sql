//
//-- ODB/SQL file 'links_sat.sql'
//
//   Last updated:  01-May-2010
//

SET $codetype = -1;

UPDATED;

CREATE VIEW links_sat AS
  SELECT sat, body
    FROM hdr
  WHERE ((obstype=$satem) OR (obstype=$allsky))
    AND  (($codetype == -1) OR (codetype == $codetype))
;
