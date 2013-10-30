dnl $Id$
dnl config.m4 for extension phonenumber

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(phonenumber, for phonenumber support,
dnl Make sure that the comment is aligned:
dnl [  --with-phonenumber             Include phonenumber support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(phonenumber, whether to enable phonenumber support,
dnl Make sure that the comment is aligned:
dnl [  --enable-phonenumber           Enable phonenumber support])

if test "$PHP_PHONENUMBER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-phonenumber -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/phonenumber.h"  # you most likely want to change this
  dnl if test -r $PHP_PHONENUMBER/$SEARCH_FOR; then # path given as parameter
  dnl   PHONENUMBER_DIR=$PHP_PHONENUMBER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for phonenumber files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHONENUMBER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHONENUMBER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the phonenumber distribution])
  dnl fi

  dnl # --with-phonenumber -> add include path
  dnl PHP_ADD_INCLUDE($PHONENUMBER_DIR/include)

  dnl # --with-phonenumber -> check for lib and symbol presence
  dnl LIBNAME=phonenumber # you may want to change this
  dnl LIBSYMBOL=phonenumber # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHONENUMBER_DIR/lib, PHONENUMBER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHONENUMBERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong phonenumber lib version or lib not found])
  dnl ],[
  dnl   -L$PHONENUMBER_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PHONENUMBER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(phonenumber, phonenumber.c, $ext_shared)
fi
