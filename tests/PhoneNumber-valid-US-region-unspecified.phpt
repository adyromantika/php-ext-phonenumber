--TEST--
Test PhoneNumber with valid US number, region unspecified.
--SKIPIF--
<?php if (!extension_loaded("phonenumber")) print "skip"; ?>
--FILE--
<?php 
$p = new PhoneNumber("19785932488");
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
string(2) "US"
string(12) "+19785932488"
string(15) "+1 978-593-2488"
string(14) "(978) 593-2488"
string(19) "tel:+1-978-593-2488"
string(10) "9785932488"
int(3)
string(11) "19785932488"
