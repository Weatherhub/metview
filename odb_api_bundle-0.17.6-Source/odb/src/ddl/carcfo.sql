//
//-- ODB/SQL file 'carcfo.sql'
//
//   Last updated:  10-Oct-2001
//

UPDATED;

CREATE VIEW carcfo AS
  SELECT  varno READONLY,
          vertco_reference_2,
          mf_log_p
  FROM    body
;
