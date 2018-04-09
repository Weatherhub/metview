//
//-- ODB/SQL file 'ecmwf_matchup_body.sql'
//
//   updated     :  22-Jun-2005
//   Last updated:  22-Apr-2009
//   revert back to what we had in CY31R2 i.e.
//   paral($pe, procid - $hdr_min + 1)
//   and NOT paral($pe, target - $hdr_min + 1)
//   It was wrong from CY32R2
//
//

SET $tslot = -1;
SET $pe = 0;
SET $hdr_min = 1; // Here: the smallest procid (=global poolno) of the obs.grp. (ECMA)
SET $hdr_max = 0; // Here: the number of pools in (output) ECMA-database

CREATE VIEW ecmwf_matchup_body AS
  SELECT seqno  READONLY,            // r/o
         entryno  READONLY,          // r/o
         datum_anflag@body UPDATED,
         datum_status@body UPDATED,
         datum_event1@body UPDATED,
         an_sens_obs@body UPDATED,
         qc_pge@body UPDATED,
         final_obs_error@errstat UPDATED,
    FROM timeslot_index, index, hdr, body, errstat
   WHERE target > 0
     AND 1 <= procid - $hdr_min + 1 <= $hdr_max
     AND (($tslot == -1 AND timeslot@timeslot_index > 0) OR (timeslot@timeslot_index == $tslot))
     AND report_status.active@hdr
     AND datum_status.active@body
     AND paral($pe, procid - $hdr_min + 1)
;

