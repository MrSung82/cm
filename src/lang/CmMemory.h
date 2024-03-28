#ifndef CM_LANG_MEMORY_H
#define CM_LANG_MEMORY_H

#include "lang/CmInt.h"
#include <memory>

namespace cm
{
	namespace lang
	{
		template<typename T, typename... TArgs>
		constexpr T* construct_at(T* p, TArgs&&... args)
		{
			return ::new (static_cast<void*>(p)) T(std::forward<TArgs>(args)...);
		}

	} // end of lang

} // end of cm
#endif // CM_LANG_MEMORY_H


