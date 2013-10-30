# PHP Extension: phonenumber

A PHP extension that utilizes Google's [libphonenumber](https://code.google.com/p/libphonenumber/).

## Install
Make sure that libphonenumber has been built and installed. I've created a vagrant machine that has the complete environment to build libphonenumber: [vagrant-libphonenumber-build](https://github.com/adyromantika/vagrant-libphonenumber-build)

Once succeeded in installing libphonenumber, you can simply add php5-dev package and start building the extension. Clone this repo or download as zip, then:

```
phpize
./configure --with-phonenumber
make
make test
```

## Status
This extension is far from being production grade. It currently has only two basic functions, but for the future I am ambitious to implement PhoneNumber class except maybe for a few functions. Let's see what happens.

Issue page is disabled since this project is expected to have tons of issues!
