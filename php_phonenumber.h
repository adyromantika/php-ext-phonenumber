/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Ady Romantika <ady.romantika@gmail.com>                      |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_PHONENUMBER_H
#define PHP_PHONENUMBER_H

#define PHP_PHONENUMBER_VERSION   "0.1"
#define PHP_PHONENUMBER_EXTNAME   "phonenumber"

extern zend_module_entry phonenumber_module_entry;
#define phpext_phonenumber_ptr &phonenumber_module_entry

#ifdef PHP_WIN32
#	define PHP_PHONENUMBER_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_PHONENUMBER_API __attribute__ ((visibility("default")))
#else
#	define PHP_PHONENUMBER_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(phonenumber);
PHP_MSHUTDOWN_FUNCTION(phonenumber);
PHP_RINIT_FUNCTION(phonenumber);
PHP_RSHUTDOWN_FUNCTION(phonenumber);
PHP_MINFO_FUNCTION(phonenumber);

PHP_FUNCTION(confirm_phonenumber_compiled);	/* For testing, remove later. */
/* Declare the PHP functions provided by this extension */
PHP_FUNCTION(get_international_number);
PHP_FUNCTION(is_valid_number_for_region);

ZEND_BEGIN_MODULE_GLOBALS(phonenumber)
	char *global_default_region;
ZEND_END_MODULE_GLOBALS(phonenumber)

// Object related
#define PHONENUMBER_NUMBERTYPE_FIXED_LINE 1
#define PHONENUMBER_NUMBERTYPE_MOBILE 2
#define PHONENUMBER_NUMBERTYPE_FIXED_LINE_OR_MOBILE 3
#define PHONENUMBER_NUMBERTYPE_TOLL_FREE 4
#define PHONENUMBER_NUMBERTYPE_PREMIUM_RATE 5
#define PHONENUMBER_NUMBERTYPE_SHARED_COST 6
#define PHONENUMBER_NUMBERTYPE_VOIP 7
#define PHONENUMBER_NUMBERTYPE_PERSONAL_NUMBER 8
#define PHONENUMBER_NUMBERTYPE_PAGER 9
#define PHONENUMBER_NUMBERTYPE_UAN 10
#define PHONENUMBER_NUMBERTYPE_VOICEMAIL 11
#define PHONENUMBER_NUMBERTYPE_UNKNOWN 12

void phonenumber_init(TSRMLS_D);
PHP_METHOD(PhoneNumber, __construct);
PHP_METHOD(PhoneNumber, formatOutOfCountryCallingNumber);

/* In every utility function you add that needs to use variables 
   in php_phonenumber_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as PHONENUMBER_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define PHONENUMBER_G(v) TSRMG(phonenumber_globals_id, zend_phonenumber_globals *, v)
#else
#define PHONENUMBER_G(v) (phonenumber_globals.v)
#endif

#endif	/* PHP_PHONENUMBER_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
