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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_phonenumber.h"

#include "phonenumbers/phonenumberutil.h"

using namespace std;

ZEND_DECLARE_MODULE_GLOBALS(phonenumber)

static int le_phonenumber;

/* {{{ phonenumber_functions[] */
const zend_function_entry phonenumber_functions[] = {
	PHP_FE(confirm_phonenumber_compiled, NULL)		/* For testing, remove later. */
	PHP_FE(get_international_number, NULL)
	PHP_FE(is_valid_number_for_region, NULL)
	PHP_FE_END	/* Must be the last line in phonenumber_functions[] */
};
/* }}} */

/* {{{ phonenumber_module_entry */
zend_module_entry phonenumber_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"phonenumber",
	phonenumber_functions,
	PHP_MINIT(phonenumber),
	PHP_MSHUTDOWN(phonenumber),
	PHP_RINIT(phonenumber),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(phonenumber),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(phonenumber),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_PHONENUMBER_VERSION, /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHONENUMBER
ZEND_GET_MODULE(phonenumber)
#endif

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("phonenumber.default_region", "US", PHP_INI_ALL, OnUpdateString, global_default_region, zend_phonenumber_globals, phonenumber_globals)
PHP_INI_END()
/* }}} */

/* {{{ php_phonenumber_init_globals
 */
static void php_phonenumber_init_globals(zend_phonenumber_globals *phonenumber_globals)
{
	phonenumber_globals->global_default_region = "US";
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(phonenumber)
{
	REGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(phonenumber)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(phonenumber)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(phonenumber)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(phonenumber)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "phonenumber support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_phonenumber_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_phonenumber_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "phonenumber", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */

/* {{{ proto string get_international_number(string num [, string region])
   Return an internationally formatted phone number */
/* TODO should also check for validity first */
PHP_FUNCTION(get_international_number)
{
	char *num = NULL;
	char *region = NULL;
	int num_len = 0, region_len = 0;
	string formatted_number;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &num, &num_len, &region, &region_len) == FAILURE)
		RETURN_NULL();

	if (region_len == 0) // Use default region
		region = PHONENUMBER_G(global_default_region);

	const i18n::phonenumbers::PhoneNumberUtil& phone_util(*i18n::phonenumbers::PhoneNumberUtil::GetInstance());
	i18n::phonenumbers::PhoneNumber number;

	if (i18n::phonenumbers::PhoneNumberUtil::NO_PARSING_ERROR != phone_util.Parse(num, region, &number))
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Parse Error");
		RETURN_FALSE;
	}

	phone_util.Format(number, i18n::phonenumbers::PhoneNumberUtil::INTERNATIONAL, &formatted_number);

	RETURN_STRINGL(formatted_number.c_str(), strlen(formatted_number.c_str()), 1);
}
/* }}} */

/* {{{ proto bool is_valid_number_for_region(string num [, string region])
   Returns whether a number is valid for the given region */
PHP_FUNCTION(is_valid_number_for_region)
{
	char *num = NULL;
	char *region = NULL;
	int num_len = 0, region_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &num, &num_len, &region, &region_len) == FAILURE)
		RETURN_NULL();

	if (region_len == 0) // Use default region
		region = PHONENUMBER_G(global_default_region);

	const i18n::phonenumbers::PhoneNumberUtil& phone_util(*i18n::phonenumbers::PhoneNumberUtil::GetInstance());
	i18n::phonenumbers::PhoneNumber number;

	if (i18n::phonenumbers::PhoneNumberUtil::NO_PARSING_ERROR != phone_util.Parse(num, region, &number))
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Parse Error");
		RETURN_FALSE;
	}

	RETURN_BOOL(phone_util.IsValidNumberForRegion(number, region));
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
