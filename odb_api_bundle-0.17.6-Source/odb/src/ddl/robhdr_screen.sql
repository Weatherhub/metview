//
//-- ODB/SQL file 'robhdr_screen.sql'
//
//   Last updated:  13-Oct-2008
//

READONLY; // All read/only except selected columns marked with  UPDATED

SET $kset = 0;

CREATE VIEW robhdr_screen AS
  SELECT seqno,                        // r/o; MUST BECOME FIRST
         retrtype UPDATED,             // possibly updated, MUST BE SECOND for Aeolus
         sat.offset,                   // r/o for Aeolus processing
         timeslot,                        // r/o for Aeolus processing
         body.len,                     // r/o
         abnob, mapomm, maptovscv,      // r/o
         obstype,                      // r/o
         date, time,                   // r/o
         sensor,                       // r/o
         codetype UPDATED,             // possibly updated
         instrument_type UPDATED,      // possibly updated
         areatype UPDATED,             // possibly updated
         report_event1  UPDATED,       // possibly updated
         report_status  UPDATED,       // possibly updated
         stalt  UPDATED,               // possibly updated
         statid,                       // r/o
         lat,lon,                      // r/o
         zenith,
         lsm           UPDATED,                   
         seaice        UPDATED,                
         orography     UPDATED,                
         tsfc          UPDATED,            
         albedo        UPDATED,            
         windspeed10m  UPDATED,        
         u10m          UPDATED,        
         v10m          UPDATED,   
         t2m           UPDATED,   
         snow_depth    UPDATED,            
  FROM   index, hdr, sat, modsurf
  WHERE	 kset = $kset
;
