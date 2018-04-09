-- © Copyright 1996-2012 ECMWF.
-- 
-- This software is licensed under the terms of the Apache Licence Version 2.0
-- which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
-- In applying this licence, ECMWF does not waive the privileges and immunities 
-- granted to it by virtue of its status as an intergovernmental organisation nor
-- does it submit to any jurisdiction.

SELECT
	count(*),
	count(lat),
	sum(blacklist.fg_depar@body) as sumfg_depar,
	sum((blacklist.fg_depar@body) * (blacklist.fg_depar@body)) as s2umfg_depar,
	min(blacklist.fg_depar@body) as minfg_depar,
	max(blacklist.fg_depar@body) as maxfg_depar, 
	sum(biascorr@body) as sumbiascorr,
	sum((biascorr@body) * (biascorr@body)) as s2umbiascorr,
	min(biascorr@body) as minbiascorr,
	max(biascorr@body) as maxbiascorr,
	sum(blacklist.fg_depar@body + biascorr@body) as sumfgdp_unc,
	sum((blacklist.fg_depar@body + biascorr@body) * (blacklist.fg_depar@body + biascorr@body)) as s2umfgdp_unc,
	min(blacklist.fg_depar@body + biascorr@body) as minfgdp_unc,
	max(blacklist.fg_depar@body + biascorr@body) as maxfgdp_unc,

--obstype@hdr as obstype, varno@body as varno,  status@body as status, lldegrees(lat@hdr)<=-20 as latbin0, lldegrees(lat@hdr)<=20 AND lldegrees(lat@hdr)>-20 as latbin1, lldegrees(lat@hdr)>20 as latbin2 

FROM "2000010106/ECMA.odb" 

WHERE (biascorr@body is not NULL and biascorr@body <> 0)
	AND  not((obstype@hdr == 10 and obschar.codetype@hdr == 250))
	AND (obstype@hdr in (1,4,8,9) or (obstype@hdr == 7 and (obschar.codetype@hdr == 215 or obschar.codetype@hdr == 206)));

JUST_ONE_TEST(test, setUp, tearDown)
void test(){}
void setUp(){}
void tearDown(){}
JUST_ONE_TEST(test, setUp, tearDown)
