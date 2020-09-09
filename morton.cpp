#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

extern "C" {
#include "php.h"
#include "ext/standard/info.h"
#include "php_morton.h"
}


/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(morton)
{
#if defined(ZTS) && defined(COMPILE_DL_MORTON)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(morton)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "morton support", "enabled");
	php_info_print_table_end();
}
/* }}} */

static const zend_function_entry morton_functions[] = {
	PHP_FE_END
};

/* {{{ morton_module_entry
 */
zend_module_entry morton_module_entry = {
	STANDARD_MODULE_HEADER,
	"morton",
	morton_functions,
	NULL, /* MINIT */
	NULL, /* MSHUTDOWN */
	NULL, /* RINIT */
	NULL, /* PHP_RSHUTDOWN */
	PHP_MINFO(morton),
	PHP_MORTON_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MORTON
extern "C" {
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(morton)
}
#endif
