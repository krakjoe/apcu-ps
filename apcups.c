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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/apcu/apc_api.h"
#include "ext/session/php_session.h"
#include "php_apcups.h"

apc_cache_t* apc_ps_cache = NULL;

apc_sma_api_extern(apc_sma);

static inline PS_OPEN_FUNC(apcu) 
{   
    PS_SET_MOD_DATA(apc_ps_cache);
    
    return SUCCESS;
}

static inline PS_CLOSE_FUNC(apcu) 
{
    PS_SET_MOD_DATA(NULL);
    
    return SUCCESS;
}

static inline PS_READ_FUNC(apcu) 
{
    apc_cache_entry_t* entry;
    time_t now = sapi_get_request_time();
    
	if ((entry = apc_cache_find(apc_ps_cache, (char*)key, strlen(key)+1, now TSRMLS_CC))) {
	    *val = estrndup(
	        Z_STRVAL_P(entry->val),
	        *vallen = Z_STRLEN_P(entry->val)
	    );
	} else {
	    return FAILURE;
	}
    
    return SUCCESS;
}

static inline PS_WRITE_FUNC(apcu) 
{
    zval zcontent;
    
    ZVAL_STRINGL(&zcontent, val, vallen+1, 0);

    apc_cache_store(
        apc_ps_cache, (char*) key, strlen(key)+1, &zcontent, 0, 0 TSRMLS_CC);

    return SUCCESS;
}

static inline PS_DESTROY_FUNC(apcu) 
{
    apc_cache_delete(
        apc_ps_cache, (char*) key, strlen(key)+1 TSRMLS_CC);
    return SUCCESS;
}

static inline PS_GC_FUNC(apcu) 
{
    return SUCCESS;
}

/* PS Module */
ps_module ps_mod_apcu = 
{
    "apcu",
    ps_open_apcu,
    ps_close_apcu,
    ps_read_apcu,
    ps_write_apcu,
    ps_delete_apcu,
    ps_gc_apcu,
    php_session_create_id
};

/* {{{ apcups_deps [] */
const zend_module_dep apcups_deps[] = {
    ZEND_MOD_REQUIRED("apcu")
    ZEND_MOD_END
}; /* }}} */

/* {{{ apcups_module_entry
 */
zend_module_entry apcups_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER_EX,
#endif
    NULL,
    apcups_deps,
	"apcups",
	NULL,
	PHP_MINIT(apcups),
	PHP_MSHUTDOWN(apcups),
	NULL,
	NULL,
	PHP_MINFO(apcups),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_APCUPS
ZEND_GET_MODULE(apcups)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(apcups)
{
	/* create ps cache */
	if (!apc_ps_cache) {
	    apc_ps_cache = apc_cache_create(
		    &apc_sma, 
		    apc_find_serializer("php" TSRMLS_CC), 
		    2000, 
		    0, 0, 0, 0 TSRMLS_CC
	    );
	}
	
	/* register ps module */
	php_session_register_module(&ps_mod_apcu);
	
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(apcups)
{
	/* create ps cache */
	if (apc_ps_cache) {
	    apc_cache_destroy(
	        apc_ps_cache TSRMLS_CC);
	}
	
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(apcups)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "APCu PS mod", "enabled");
	php_info_print_table_end();
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
