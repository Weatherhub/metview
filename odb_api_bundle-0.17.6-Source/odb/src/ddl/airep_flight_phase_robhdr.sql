//
//-- ODB/SQL file 'airep_flight_phase_robhdr.sql'
//
//   Last updated:  30-Mar-2011

//

READONLY;

CREATE VIEW airep_flight_phase_robhdr AS
     SELECT seqno,
            body.len,
            statid, obstype, codetype, date,
            time,
            flight_phase, 
            flight_dp_o_dt UPDATED,
            varno, obsvalue,
            vertco_type,
            vertco_reference_1,
      FROM index, hdr, conv, body
      WHERE obstype==$airep and varno==2
      ORDERBY codetype, statid, date, time, vertco_reference_1
;
