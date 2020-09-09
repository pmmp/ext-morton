#ifndef PHP_MORTON_H
# define PHP_MORTON_H

extern zend_module_entry morton_module_entry;
# define phpext_morton_ptr &morton_module_entry

# define PHP_MORTON_VERSION "0.1.0"

#ifdef ZTS
#include "TSRM.h"
#endif

# if defined(ZTS) && defined(COMPILE_DL_MORTON)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_MORTON_H */
