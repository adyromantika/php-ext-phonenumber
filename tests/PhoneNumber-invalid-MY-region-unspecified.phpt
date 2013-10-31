--TEST--
Test PhoneNumber with valid MY number (invalid US number), region unspecified.
--SKIPIF--
<?php if (!extension_loaded("phonenumber")) print "skip"; ?>
--FILE--
<?php 
ini_set('error_reporting',E_ERROR);
ini_set('phonenumber.default_region','US');
$p = new PhoneNumber("388859999");
var_dump($p->valid);
var_dump($p->region);
var_dump($p->E164);
var_dump($p->internationalFormat);
var_dump($p->nationalFormat);
var_dump($p->RFC3966);
var_dump($p->nationalSignificantNumber);
var_dump($p->type);
var_dump($p->raw_number);
?>
--EXPECT--
bool(false)
string(2) "US"
string(11) "+1388859999"
string(12) "+1 388859999"
string(9) "388859999"
string(16) "tel:+1-388859999"
string(9) "388859999"
int(12)
string(9) "388859999"