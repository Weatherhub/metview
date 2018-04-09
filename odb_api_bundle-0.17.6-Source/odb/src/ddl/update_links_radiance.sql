//
//-- ODB/SQL file 'update_links_radiance.sql'
//
//   Last updated:  01-May-2010
//

SET $codetype = -1;

UPDATED;

CREATE VIEW update_links_radiance AS
  SELECT "/LINK.*/"
    FROM radiance
;
