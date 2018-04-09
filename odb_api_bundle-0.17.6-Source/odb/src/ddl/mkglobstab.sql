//
//-- ODB/SQL file 'mkglobstab.sql'
//

CREATE VIEW mkglobstab AS
  SELECT seqno READONLY,
         timeslot READONLY,
         obstype READONLY,
         codetype READONLY,
         instrument_type READONLY,
         retrtype READONLY,
         areatype READONLY,
	       abnob READONLY, 
         mapomm,
         lat READONLY, 
         lon READONLY, 
         trlat READONLY,
         trlon READONLY,
    FROM index, hdr
 ORDERBY timeslot, seqno
;
