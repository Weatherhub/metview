//
//-- ODB/SQL file 'obsortca_auxiliary.sql'
//
//   Last updated:  20-Jul-2006
//

READONLY;

SET $all = 1;
SET $pe = 0;

CREATE VIEW obsortca_auxiliary AS
  SELECT target, seqno, "*@auxiliary"
    FROM index, hdr, auxiliary, body
    WHERE ( ($all >= 1 OR report_status.active@hdr = 1)
     AND ($all >= 1 OR datum_status.active@body = 1)
     AND (timeslot = 4) AND (obstype NOT IN ($satem,$scatt))
     AND ($all = 2 OR obstype IN ($synop,$dribu,$temp,$pilot,$paob)) )
     AND  paral($pe, target)
     AND  auxiliary.len > 0
     AND  auxiliary.len == body.len
     ORDERBY seqno
;

