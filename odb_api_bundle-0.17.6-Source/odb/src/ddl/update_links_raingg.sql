//
//-- ODB/SQL file 'update_links_raingg.sql'
//
//   Last updated:  22-Jul-2010
//

UPDATED;

CREATE VIEW update_links_raingg AS
  SELECT body, raingg_body, 
    FROM hdr, raingg
    WHERE obstype=$raingg and codetype=$radrr
;
