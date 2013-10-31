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
	PHP_PHONENUMBER_EXTNAME,
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

/* {{{ phonenumber_class_entry */
zend_class_entry *phonenumber_class_entry;
/* }}} */

static function_entry phonenumber_methods[] = {
	PHP_ME(PhoneNumber, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(PhoneNumber, formatOutOfCountryCallingNumber, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

void phonenumber_init(TSRMLS_D) {
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "PhoneNumber", phonenumber_methods);

	phonenumber_class_entry = zend_register_internal_class(&ce TSRMLS_CC);

	zend_declare_property_bool(phonenumber_class_entry, "valid", strlen("valid"), false, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_string(phonenumber_class_entry, "region", strlen("region"), PHONENUMBER_G(global_default_region), ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_string(phonenumber_class_entry, "raw_number", strlen("raw_number"), "", ZEND_ACC_PUBLIC TSRMLS_CC);
}

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

	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_FIXED_LINE", PHONENUMBER_NUMBERTYPE_FIXED_LINE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_MOBILE", PHONENUMBER_NUMBERTYPE_MOBILE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_FIXED_LINE_OR_MOBILE", PHONENUMBER_NUMBERTYPE_FIXED_LINE_OR_MOBILE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_TOLL_FREE", PHONENUMBER_NUMBERTYPE_TOLL_FREE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_PREMIUM_RATE", PHONENUMBER_NUMBERTYPE_PREMIUM_RATE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_SHARED_COST", PHONENUMBER_NUMBERTYPE_SHARED_COST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_VOIP", PHONENUMBER_NUMBERTYPE_VOIP, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_PERSONAL_NUMBER", PHONENUMBER_NUMBERTYPE_PERSONAL_NUMBER, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_PAGER", PHONENUMBER_NUMBERTYPE_PAGER, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_UAN", PHONENUMBER_NUMBERTYPE_UAN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_VOICEMAIL", PHONENUMBER_NUMBERTYPE_VOICEMAIL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("PHONENUMBER_NUMBERTYPE_UNKNOWN", PHONENUMBER_NUMBERTYPE_UNKNOWN, CONST_CS | CONST_PERSISTENT);

	// Initialize class
	phonenumber_init(TSRMLS_C);

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

/* {{{ proto object __construct(string num [, string region])
   Initiates object and populates the properties */
PHP_METHOD(PhoneNumber, __construct)
{
	char *num = NULL;
	char *region = NULL;
	int num_len = 0, region_len = 0;
	string e164_format, international_format, national_format, rfc3966_format;
	string national_significant_number;
	int number_type = 0;
	bool valid = false;
	zval *tmp1 = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &num, &num_len, &region, &region_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Phone number can't be empty.");
		RETURN_FALSE;
	}

	if (region_len == 0) // Use default region
		region = PHONENUMBER_G(global_default_region);

	const i18n::phonenumbers::PhoneNumberUtil& phone_util(*i18n::phonenumbers::PhoneNumberUtil::GetInstance());
	i18n::phonenumbers::PhoneNumber number;

	if (i18n::phonenumbers::PhoneNumberUtil::NO_PARSING_ERROR != phone_util.Parse(num, region, &number))
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Parse error!");
		RETURN_FALSE;
	}

	phone_util.Format(number, i18n::phonenumbers::PhoneNumberUtil::E164, &e164_format);
	zend_update_property_string(phonenumber_class_entry, getThis(), "E164", strlen("E164"), e164_format.c_str() TSRMLS_CC);

	phone_util.Format(number, i18n::phonenumbers::PhoneNumberUtil::INTERNATIONAL, &international_format);
	zend_update_property_string(phonenumber_class_entry, getThis(), "internationalFormat", strlen("internationalFormat"), international_format.c_str() TSRMLS_CC);

	phone_util.Format(number, i18n::phonenumbers::PhoneNumberUtil::NATIONAL, &national_format);
	zend_update_property_string(phonenumber_class_entry, getThis(), "nationalFormat", strlen("nationalFormat"), national_format.c_str() TSRMLS_CC);

	phone_util.Format(number, i18n::phonenumbers::PhoneNumberUtil::RFC3966, &rfc3966_format);
	zend_update_property_string(phonenumber_class_entry, getThis(), "RFC3966", strlen("RFC3966"), rfc3966_format.c_str() TSRMLS_CC);

	phone_util.GetNationalSignificantNumber(number, &national_significant_number);
	zend_update_property_string(phonenumber_class_entry, getThis(), "nationalSignificantNumber", strlen("nationalSignificantNumber"), national_significant_number.c_str() TSRMLS_CC);

	i18n::phonenumbers::PhoneNumberUtil::PhoneNumberType phone_number_type = phone_util.GetNumberType(number);

	switch(phone_number_type)
	{
		case i18n::phonenumbers::PhoneNumberUtil::FIXED_LINE:
			number_type = PHONENUMBER_NUMBERTYPE_FIXED_LINE;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::MOBILE:
			number_type = PHONENUMBER_NUMBERTYPE_MOBILE;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::FIXED_LINE_OR_MOBILE:
			number_type = PHONENUMBER_NUMBERTYPE_FIXED_LINE_OR_MOBILE;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::TOLL_FREE:
			number_type = PHONENUMBER_NUMBERTYPE_TOLL_FREE;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::PREMIUM_RATE:
			number_type = PHONENUMBER_NUMBERTYPE_PREMIUM_RATE;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::SHARED_COST:
			number_type = PHONENUMBER_NUMBERTYPE_SHARED_COST;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::VOIP:
			number_type = PHONENUMBER_NUMBERTYPE_VOIP;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::PERSONAL_NUMBER:
			number_type = PHONENUMBER_NUMBERTYPE_PERSONAL_NUMBER;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::PAGER:
			number_type = PHONENUMBER_NUMBERTYPE_PAGER;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::UAN:
			number_type = PHONENUMBER_NUMBERTYPE_UAN;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::VOICEMAIL:
			number_type = PHONENUMBER_NUMBERTYPE_VOICEMAIL;
			break;
		case i18n::phonenumbers::PhoneNumberUtil::UNKNOWN:
			number_type = PHONENUMBER_NUMBERTYPE_UNKNOWN;
			break;
	}

	zend_update_property_long(phonenumber_class_entry, getThis(), "type", strlen("type"), number_type TSRMLS_CC);

	valid = phone_util.IsValidNumberForRegion(number, region);

	if (false == valid)
	{
		php_error_docref(NULL TSRMLS_CC, E_NOTICE, "The number is invalid but it is processed anyway. Other properties should be considered invalid too.");
	}

	zend_update_property_bool(phonenumber_class_entry, getThis(), "valid", strlen("valid"), valid TSRMLS_CC);
	zend_update_property_string(phonenumber_class_entry, getThis(), "region", strlen("region"), region TSRMLS_CC);
	zend_update_property_string(phonenumber_class_entry, getThis(), "raw_number", strlen("raw_number"), num TSRMLS_CC);
}
/* }}} */

/* {{{ proto string formatOutOfCountryCallingNumber(string caller_region)
   Returns the formatted number from the calling region */
PHP_METHOD(PhoneNumber, formatOutOfCountryCallingNumber)
{
	char *raw_number = NULL;
	char *caller_region = NULL;
	char *region = NULL;
	int caller_region_len = 0;
	string formatted_number;
	zval *zregion, *znum, *zvalid;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &caller_region, &caller_region_len) == FAILURE)
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Parameter 1 (caller region) must not be empty.");
		RETURN_FALSE;
	}

	zvalid = zend_read_property(Z_OBJCE_P(getThis()), getThis(), "valid", strlen("valid"), 1 TSRMLS_CC);
	convert_to_boolean(zvalid);
	if (false == Z_BVAL_P(zvalid))
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Number is invalid.");
		RETURN_FALSE;
	}

	zregion = zend_read_property(Z_OBJCE_P(getThis()), getThis(), "region", strlen("region"), 1 TSRMLS_CC);
	convert_to_string(zregion);
	region = Z_STRVAL_P(zregion);
	znum = zend_read_property(Z_OBJCE_P(getThis()), getThis(), "raw_number", strlen("raw_number"), 1 TSRMLS_CC);
	convert_to_string(znum);
	raw_number = Z_STRVAL_P(znum);

	const i18n::phonenumbers::PhoneNumberUtil& phone_util(*i18n::phonenumbers::PhoneNumberUtil::GetInstance());
	i18n::phonenumbers::PhoneNumber phone_number;

	if (i18n::phonenumbers::PhoneNumberUtil::NO_PARSING_ERROR != phone_util.Parse(raw_number, region, &phone_number))
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Parse error!");
		RETURN_FALSE;
	}

	phone_util.FormatOutOfCountryCallingNumber(phone_number, caller_region, &formatted_number);
	RETURN_STRING(formatted_number.c_str(),1);
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
