dnl $Id$
dnl config.m4 for extension apcups

PHP_ARG_ENABLE(apcups, whether to enable APCu PS mod,
[  --enable-apcups           Enable APCu PS mod])

if test "$PHP_APCUPS" != "no"; then
  PHP_NEW_EXTENSION(apcups, apcups.c, $ext_shared)
fi
