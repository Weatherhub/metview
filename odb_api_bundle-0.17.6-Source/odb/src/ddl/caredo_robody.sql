//
//-- ODB/SQL file 'caredo_robody.sql'
//
//   Last updated:  10-Aug-2009
//

UPDATED;

CREATE VIEW caredo_robody AS
  SELECT seqno READONLY,
         varno READONLY,
         datum_anflag,
  FROM   index, hdr, body
;
