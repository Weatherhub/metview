//
// === TYPE and TABLE definitions for the BUFRBASE ===
//
// As of 17-Jun-1999 : by Sami Saarinen for MAKECMA/FEEDBACK
//
//
// The present TABLE hierarchy
// ===========================
//
//
//    hdr --> bufr
//         
//         

// 
// === Global $-variables ===
//

SET  $MDI = 2147483647; // Absolute value of the Missing Data Indicator

SET  $SYNOP = 1;
SET  $AIREP = 2;
SET  $SATOB = 3;
SET  $DRIBU = 4;
SET  $TEMP = 5;
SET  $PILOT = 6;
SET  $SATEM = 7;
SET  $PAOB = 8;
SET  $SCATT = 9;
SET  $ALLSKY = 16;

TYPEDEF obschar_t = (
  codetype bit9,                        // OBS. CODE TYPE 
  instype bit10,                        // INS. TYPE 
  retrtype bit6,                        // RETRIEVAL TYPE 
  datagroup bit6,                       // DATA PROCESSING GROUP
);

//
// === TABLE definitions ===
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
  seqno int,                            // OBSERVATION SEQUENCE NUMBER (CMA)

  obstype pk2int,                       // OBSERVATION TYPE (CMA)
  obschar OBSCHAR_t,                    // OBSERVATION CHARACTERISTICS (CMA)

  RDBtype pk5int,                       // RDB-type (BUFR)
  subtype pk5int,                       // Sub-type (BUFR)
  bufrtype pk5int,                      // BUFR-type (BUFR)

// Links
  bufr		@LINK,
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


