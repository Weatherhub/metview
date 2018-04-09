//
//-- ODB/SQL file 'links_raingg.sql'
//
//   Last updated:  22-Aug-2012
//

UPDATED;

CREATE VIEW links_raingg AS
  SELECT raingg
    FROM hdr
  WHERE reportype >= $synop_rg6h AND reportype <= $synop_rg24h
;
