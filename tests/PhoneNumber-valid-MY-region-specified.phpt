--TEST--
Test PhoneNumber with valid MY number, region specified.
--SKIPIF--
<?php if (!extension_loaded("phonenumber")) print "skip"; ?>
--FILE--
<?php 
$p = new PhoneNumber("388859999","MY");
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
bool(true)
string(2) "MY"
string(12) "+60388859999"
string(15) "+60 3-8885 9999"
string(12) "03-8885 9999"
string(19) "tel:+60-3-8885-9999"
string(9) "388859999"
int(1)
string(9) "388859999"
