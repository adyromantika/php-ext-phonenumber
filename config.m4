dnl $Id$
dnl config.m4 for extension phonenumber

PHP_ARG_WITH(phonenumber, for phonenumber support,
[  --with-phonenumber             Include phonenumber support])

if test "$PHP_PHONENUMBER" != "no"; then
  # --with-phonenumber -> check with-path
  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  SEARCH_FOR="/include/phonenumbers/phonenumberutil.h"  # you most likely want to change this
  if test -r $PHP_PHONENUMBER/$SEARCH_FOR; then # path given as parameter
    PHONENUMBER_DIR=$PHP_PHONENUMBER
  else # search default path list
    AC_MSG_CHECKING([for phonenumber files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        PHONENUMBER_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  
  if test -z "$PHONENUMBER_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the phonenumber distribution])
  fi

  # --with-phonenumber -> add include path
  PHP_ADD_INCLUDE($PHONENUMBER_DIR/include)

  # --with-phonenumber -> check for lib and symbol presence
  LIBNAME=phonenumber # you may want to change this
  LIBSYMBOL=phonenumber # you most likely want to change this 

  AC_DEFINE(HAVE_PHONENUMBERLIB, 1, [Whether you have phonenumber support])
  PHP_REQUIRE_CXX()
  PHP_ADD_LIBRARY(phonenumber, 1, PHONENUMBER_SHARED_LIBADD)
  
  PHP_SUBST(PHONENUMBER_SHARED_LIBADD)
  PHP_NEW_EXTENSION(phonenumber, phonenumber.cc, $ext_shared)
fi
