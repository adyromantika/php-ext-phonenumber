--TEST--
Check for is_valid_number_for_region
--SKIPIF--
<?php if (!extension_loaded("phonenumber")) print "skip"; ?>
--FILE--
<?php 
var_dump( is_valid_number_for_region( '19785932481' ) );
var_dump( is_valid_number_for_region( '19785932481', 'US' ) );
var_dump( is_valid_number_for_region( '388859223', 'MY' ) );
var_dump( is_valid_number_for_region( '8388859223', 'MY' ) );
var_dump( is_valid_number_for_region( '19785932481889' ) );
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
bool(true)
bool(true)
bool(true)
bool(false)
bool(false)