//
// Data layout for TOVS & SSM/I PRESCREEN-jobs
//
// The present TABLE hierarchy
// ===========================
//
//                   +--> body
//                   |
//             hdr --+--> bufr
//
//

//--------------------------//
//  #    #  #####   #####   //
//  #    #  #    #  #    #  //
//  ######  #    #  #    #  //
//  #    #  #    #  #####   //
//  #    #  #    #  #   #   //
//  #    #  #####   #    #  //
//--------------------------//

CREATE TABLE hdr AS (
	seqno		int,		// Unique sequence no. (>0) across PE-ids
	duplseqno[1]	pk9int,		// Seqno of master, if duplicate

	sortbox		pk9int,		// Sorting box to be formed
	thinbox		pk9int,		// Equal to sorting box if NOT thinned

	date		YYYYMMDD,	// Date
	time		HHMMSS,		// Time
	msec		pk9int,		// Milliseconds

	satid		pk5int,		// Satellite id
	sensor		pk5int,		// Sensor id

	orbit		pk9int,		// Orbit no.
	fov		pk9int,		// Spot no.
	scanline	pk9int,		// Scanline no.

	lat		real4,		// LATITUDE (in degrees: -90..+90)
	lon		real4,		// LONGITUDE (in degrees: -180..+180)
	stalt		pk9int,		// Height of station

	zenith		real4,		// Zenith angle

	body		@LINK,		// Link to body	(brightness temperatures)
	bufr		@LINK,		// Link to the originating BUFR-message (if required)
)
;

//----------------------------------//
//  #####    ####   #####    #   #  //
//  #    #  #    #  #    #    # #   //
//  #####   #    #  #    #     #    //
//  #    #  #    #  #    #     #    //
//  #    #  #    #  #    #     #    //
//  #####    ####   #####      #    //
//----------------------------------//


CREATE TABLE body AS (
	varno		pk9int,		// Variable number (e.g. varno%rad=119)
	obsvalue	real4,		// Observed value (e.g. BRIGHTNESS TEMPERATURE)
);


//----------------------------------//
//  #####   #    #  ######  #####   //
//  #    #  #    #  #       #    #  //
//  #####   #    #  #####   #    #  //
//  #    #  #    #  #       #####   //
//  #    #  #    #  #       #   #   //
//  #####    ####   #       #    #  //
//----------------------------------//


CREATE TABLE bufr AS (
	msg		bufr,
);
