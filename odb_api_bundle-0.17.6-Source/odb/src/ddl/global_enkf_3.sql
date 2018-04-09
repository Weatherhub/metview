//
//-- ODB/SQL file 'global_enkf_3.sql'
//
//   Last updated:  
//   By          :  Anne Fouilloux

READONLY;

CREATE VIEW global_enkf_3 AS
  SELECT
    lat,
    lon,
    date,
    time,
    obstype,
    codetype,
    reportype,
    varno,
    seqno,
    vertco_reference_1,
    vertco_reference_2,
    stalt,
    orography,
    fg_depar,
    an_depar  UPDATED,
    biascorr_fg,
    biascorr,
    obs_error,
    final_obs_error,
    qc_a,
    qc_l,
    qc_pge  UPDATED,
    datum_anflag   UPDATED,
    datum_status   UPDATED,
    datum_event1   UPDATED,
    obsvalue,
    jacobian_peak,
    jacobian_hpeak,
    satellite_identifier,
    sensor,
    hprior@enkf[1:min($NMXENKF,3)],
   FROM hdr,body,sat,errstat,modsurf,ensemble, enkf[1:min($NMXENKF,3)]
   WHERE datum_status = 1
;

