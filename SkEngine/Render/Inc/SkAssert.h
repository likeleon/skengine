#pragma once

#include <cassert>

#ifdef NDEBUG
#	define	SK_REQUIRE(expr)	(0)
#	define	SK_ENSURE(expr)		(0)
#	define	SK_ASSERT(expr)		(0)
#else
#	define	SK_REQUIRE(expr)	assert(expr)
#	define	SK_ENSURE(expr)		assert(expr)
#	define	SK_ASSERT(expr)		assert(expr)
#endif

#define SK_COMPILE_ASSERT(expr) impl_COMPILE_ASSERT(expr, __LINE__, __FILE__)

#define impl_PASTE(a,b) a##b
#define impl_COMPILE_ASSERT(expr, line, file) \
    typedef char impl_PASTE(assertion_failed_##file##_, line)[2*!!(expr)-1];