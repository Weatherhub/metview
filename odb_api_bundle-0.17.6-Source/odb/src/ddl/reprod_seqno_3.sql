//
//-- ODB/SQL file 'reprod_seqno_3.sql'
//
//   Last updated:  05-Jul-2005
//

SET $tslot = -1;

READONLY;

CREATE VIEW reprod_seqno_3 AS
  SELECT seqno UPDATED, // The only time seqno is updated ?
         obstype, codetype, // These MUST be be in this order here
         sensor,
         timeslot@timeslot_index, date, time,
         lat, lon,
	 stalt, statid
    FROM timeslot_index, index, hdr
   WHERE (timeslot@timeslot_index = $tslot OR $tslot = -1)
   ORDER BY timeslot@timeslot_index, obstype, codetype, sensor, date, time, lat, lon, stalt, statid
;