#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <math.h> //libmorton bug
#include <morton.h>

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
	php_info_print_table_row(2, "morton intrinsics",
#if defined(__AVX512BITALG__)
			"AVX512",
#elif defined(__BMI2__) || defined(__AVX2__)
			"BMI2",
#else
			"not used"
#endif
	);
	php_info_print_table_end();
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_morton2d_encode, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(morton2d_encode) {
	zend_long x, y;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(static_cast<zend_long>(libmorton::morton2D_64_encode(x, y)));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_morton3d_encode, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(morton3d_encode) {
	zend_long x, y, z;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(z)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(static_cast<zend_long>(libmorton::morton3D_64_encode(x, y, z)));
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_morton2d_decode, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, morton, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(morton2d_decode) {
	const size_t SHIFT = (sizeof(zend_long) * 8) - 32;
	zend_long morton;
	uint_fast32_t x, y;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
		Z_PARAM_LONG(morton)
	ZEND_PARSE_PARAMETERS_END();

	libmorton::morton2D_64_decode(morton, x, y);

	array_init_size(return_value, 2);
	add_next_index_long(return_value, static_cast<zend_long>(x) << SHIFT >> SHIFT);
	add_next_index_long(return_value, static_cast<zend_long>(y) << SHIFT >> SHIFT);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_morton3d_decode, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, morton, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(morton3d_decode) {
	const size_t SHIFT = (sizeof(zend_long) * 8) - 21;
	zend_long morton;
	uint_fast32_t x, y, z;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
		Z_PARAM_LONG(morton)
	ZEND_PARSE_PARAMETERS_END();

	libmorton::morton3D_64_decode(morton, x, y, z);

	array_init_size(return_value, 3);
	add_next_index_long(return_value, static_cast<zend_long>(x) << SHIFT >> SHIFT);
	add_next_index_long(return_value, static_cast<zend_long>(y) << SHIFT >> SHIFT);
	add_next_index_long(return_value, static_cast<zend_long>(z) << SHIFT >> SHIFT);
}

static const zend_function_entry morton_functions[] = {
	PHP_FE(morton2d_encode, arginfo_morton2d_encode)
	PHP_FE(morton3d_encode, arginfo_morton3d_encode)
	PHP_FE(morton2d_decode, arginfo_morton2d_decode)
	PHP_FE(morton3d_decode, arginfo_morton3d_decode)
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
