
//
//-- ODB/SQL file 'robody_traj.sql'
//
//   Last updated: 15/03/2011 A. Fouilloux Remove aux_*
//

READONLY;

SET $tslot = -1;
SET $kset = 0;

CREATE VIEW robody_traj AS    
  SELECT entryno, varno,               // r/o
         datum_anflag UPDATED,                           // possibly updated
         datum_event1@body UPDATED, datum_status@body UPDATED, // possibly updated
         an_depar UPDATED, fg_depar UPDATED,       // possibly updated
         actual_depar  UPDATED,                    // to pass actual departure from one subroutine to another (working ODB column)
         hires@update[1:$NMXUPD] UPDATED,          // possibly updated
         lores@update[1:$NMXUPD] UPDATED,          // possibly updated
         qc_a UPDATED,                    // possibly updated
         qc_l UPDATED,                    // possibly updated
         qc_pge UPDATED,                    // possibly updated
         final_obs_error UPDATED,                  // possibly updated
         obs_error@errstat UPDATED,                // possibly updated
         repres_error,                            // r/o
         fg_error,                                // r/o
         pers_error,                              // r/o
         obsvalue                   UPDATED,      // possibly updated (twin exp)
         vertco_reference_1, 
         vertco_reference_2,                      // r/o
         varbc_ix,                                // r/o
         biascorr                   UPDATED,      // possibly updated
         biascorr_fg                UPDATED,      // possibly updated
         jacobian_peak              UPDATED, // MDB_JACOBIAN_PEAK
         jacobian_hpeak             UPDATED, // MDB_JACOBIAN_HPEAK
  FROM   timeslot_index, index, hdr, body, update[1:$NMXUPD], errstat
  WHERE	 (($tslot == -1 AND timeslot@timeslot_index > 0) OR
           (timeslot@timeslot_index == $tslot))
    AND  kset = $kset
;
