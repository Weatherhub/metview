//
//-- ODB/SQL file 'update_links_auxiliary.sql'
//
//   Last updated:  01-May-2010
//

UPDATED;

CREATE VIEW update_links_auxiliary AS
  SELECT body, auxiliary_body, 
    FROM hdr, auxiliary
;
