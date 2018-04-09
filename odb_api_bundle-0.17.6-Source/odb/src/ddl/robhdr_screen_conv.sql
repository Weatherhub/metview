//
//-- ODB/SQL file 'robhdr_screen_conv.sql'
//
//   Last updated:  27-Mar-2011
//

READONLY; // All read/only except selected columns marked with  UPDATED

SET $kset = 0;

CREATE VIEW robhdr_screen_conv AS
  SELECT seqno,                        // r/o; MUST BECOME FIRST
         anemoht@conv,                 // r/o
  FROM   index, hdr, conv
  WHERE	 kset = $kset
;
