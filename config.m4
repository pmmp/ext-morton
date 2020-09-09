dnl $Id$
dnl config.m4 for extension morton

PHP_ARG_ENABLE(morton, whether to enable morton support,
[  --enable-morton                         Enable libmorton binding extension])

if test "$PHP_MORTON" != "no"; then
  PHP_REQUIRE_CXX()

  dnl the 6th parameter here is required for C++ shared extensions
  PHP_NEW_EXTENSION(morton, morton.cpp, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1, yes)
  PHP_SUBST(MORTON_SHARED_LIBADD)
  PHP_ADD_INCLUDE($ext_builddir)
  PHP_ADD_INCLUDE($ext_builddir/libmorton/libmorton/include)
fi
