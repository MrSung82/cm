#ifndef CM_LANG_INT_H
#define CM_LANG_INT_H


#include <assert.h>


using CmInt8 = signed char;
using CmInt16 = short;
using CmInt32 = int;

using CmInt8u = unsigned char;
using CmInt16u = unsigned short;
using CmInt32u = unsigned int;

namespace cm
{
	namespace lang
	{
		/**
		 * Compiler independent 8-bit signed int.
		 * @author Marat Sungatullin (mrsung82)
		 */
		using Int8 = CmInt8;

		/**
		 * Compiler independent 16-bit signed int.
		 * @author Marat Sungatullin (mrsung82)
		 */
		using Int16 = CmInt16;

		/**
		 * Compiler independent 32-bit signed int.
		 * @author Marat Sungatullin (mrsung82)
		 */
		using Int32 = CmInt32;

		/**
		 * Compiler independent 8-bit unsigned int.
		 * @author Marat Sungatullin (mrsung82)
		 */
		using Int8u = CmInt8u;

		/**
		 * Compiler independent 16-bit unsigned int.
		 * @author Marat Sungatullin (mrsung82)
		 */
		using Int16u = CmInt16u;

		/**
		 * Compiler independent 32-bit unsigned int.
		 * @author Marat Sungatullin (mrsung82)
		 */
		using Int32u = CmInt32u;

		/**
		 * Compiler independent integer type for storing size.
		 * @author Marat Sungatullin (mrsung82)
		 */
		using size_t = Int32u;


		/**
		 * Compiler independent integer type for storing byte.
		 * @author Marat Sungatullin (mrsung82)
		 */
		using byte_t = Int8u;
	} // end of lang

} // end of cm
#endif // CM_LANG_INT_H

