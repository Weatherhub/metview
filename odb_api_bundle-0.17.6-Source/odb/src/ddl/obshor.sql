//
//-- ODB/SQL file 'obshor.sql'
//
//   Last updated:  02-Feb-2005
//

SET $tslot = -1;

READONLY;

CREATE VIEW obshor AS
  SELECT seqno, // for debugging purposes only
         timeslot@index, obstype, 
         codetype,       // for debugging purposes only
         instrument_type,       // for debugging purposes only
         retrtype,       // for debugging purposes only
         areatype,       // for debugging purposes only
         abnob, mapomm
    FROM timeslot_index, index, hdr
   WHERE ($tslot == -1 AND timeslot@timeslot_index > 0) OR
(timeslot@timeslot_index == $tslot)
 ORDERBY timeslot@index, seqno
;
