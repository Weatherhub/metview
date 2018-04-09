//
//-- ODB/SQL file 'caifc1.sql'
//
//   Last updated:  11-Oct-2001
//

READONLY;

CREATE VIEW caifc1 AS
  SELECT seqno,
	 body.len,
	 fg_depar,
         hires UPDATED
    FROM index, hdr, body, update[1]
;
