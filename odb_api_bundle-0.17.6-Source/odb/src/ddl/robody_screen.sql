//
//-- ODB/SQL file 'robody_screen.sql'
//
//   Last updated:  16-Nov-2006
//

UPDATED; // the default: all updated (except those with  READONLY or  READONLY)

SET $kset = 0;

CREATE VIEW robody_screen AS
  SELECT seqno           READONLY,     // r/o; MUST BECOME FIRST
         entryno         READONLY,     // r/o
         datum_anflag, 
         varno,                        // possibly updated
         datum_event1,                 // possibly updated
    	 datum_event2, 
         datum_status,                 // possibly updated
         datum_blacklist,              // possibly updated
         datum_rdbflag,                // possibly updated
         vertco_type,                  // possibly updated
         final_obs_error,              // possibly updated
         obs_error,                    // possibly updated
         pers_error,                   // possibly updated
         repres_error,                 // possibly updated
         obsvalue,                     // possibly updated
         fg_depar,                     // possibly updated
         vertco_reference_1,           // possibly updated
         vertco_reference_2,           // possibly updated
         varbc_ix,                     // r/o
         biascorr,                     // possibly updated
         biascorr_fg,                     // possibly updated
	     lores,                        // possibly updated
 FROM   index, hdr, body, update[1], errstat
  WHERE	 kset = $kset
;
