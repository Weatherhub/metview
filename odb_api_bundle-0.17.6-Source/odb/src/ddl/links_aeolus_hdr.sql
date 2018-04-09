//
//-- ODB/SQL file 'links_aeolus_hdr.sql'
//
//   Last updated:  14-Jun-2012
//

UPDATED;

CREATE VIEW links_aeolus_hdr AS
  SELECT aeolus_l2c, aeolus_auxmet
    FROM aeolus_hdr
;
