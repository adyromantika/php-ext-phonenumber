--TEST--
Check for get_international_number
--SKIPIF--
<?php if (!extension_loaded("phonenumber")) print "skip"; ?>
--FILE--
<?php 
var_dump( get_international_number( '19785932481' ) );
var_dump( get_international_number( '388859223', 'MY' ) );
var_dump( get_international_number( '446681800', 'CH' ) );
/*
	you can add regression tests for your extension here

  the output of your test code has to be equal to the
  text in the --EXPECT-- section below for the tests
  to pass, differences between the output and the
  expected text are interpreted as failure

	see php5/README.TESTING for further information on
  writing regression tests
*/
?>
--EXPECT--
string(15) "+1 978-593-2481"
string(15) "+60 3-8885 9223"
string(16) "+41 44 668 18 00"