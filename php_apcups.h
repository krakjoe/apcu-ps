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
  | Author: Joe Watkins <joe.watkins@live.co.uk                          |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_APCUPS_H
#define PHP_APCUPS_H

extern zend_module_entry apcups_module_entry;
#define phpext_apcups_ptr &apcups_module_entry

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(apcups);
PHP_MSHUTDOWN_FUNCTION(apcups);
PHP_RINIT_FUNCTION(apcups);
PHP_RSHUTDOWN_FUNCTION(apcups);
PHP_MINFO_FUNCTION(apcups);

#endif	/* PHP_APCUPS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
