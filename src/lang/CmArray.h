#ifndef CM_LANG_ARRAY_H
#define CM_LANG_ARRAY_H

#include "lang/CmInt.h"
#include "lang/CmMemory.h"

#include <assert.h>
#include <algorithm>

namespace cm
{
namespace lang
{


/** 
 * Simple dynamic array. 
 * @param T Type of array element.
 * @param N Statically allocated buffer size.
 * @author Jani Kajala (jani.kajala@helsinki.fi)
 * @author Marat Sungatullin (mrsung82)
 */
template <class T, size_t N = 1> 
class Array
{
public:
	/** Creates an empty array. */
	Array()
	{
		m_data = m_staticBuffer;
	}

	/** Creates an array of n elements. */
	explicit Array(size_t n)
	{
		m_data = m_staticBuffer;
		resize(n);
	}

	/** Copy by value. */
	Array(const Array<T,N>& other)
	{
		m_data = m_staticBuffer;
		*this = other;
	}

	///
	~Array()
	{
		releaseBuffer();
	}

	/** Copy by value. */
	Array& operator=(const Array<T,N>& other)
	{
		setSize(other.m_len);
		std::copy(other.begin(), other.end(), m_data);
		return *this;
	}

	/** Returns ith element from the array. */
	T& operator[](size_t index)
	{
		assert(index < m_len);
		return m_data[index];
	}

	/** Adds an element to the end of the array. */
	void push_back(const T& item)
	{
		if (m_len + 1 > m_cap)
			realloc(m_len + 1);
		construct_at(&m_data[m_len++], item);
	}

	/** Adds an element before specified index. */
	void insert(size_t index, const T& item)
	{
		assert(index <= size());

		resize(m_len + 1);
		std::copy_backward(m_data + index, m_data + m_len, m_data + m_len + 1);
		m_data[index] = item;
	}

	/** Sets number of elements in the array. */
	void resize(size_t nSize)
	{
		if (nSize == m_len)
			return;
		if (nSize < m_len)
		{
			std::destroy_n(&m_data[nSize], m_len - nSize);
		}
		else 
		{
			if (nSize > m_cap)
				realloc(nSize);
			std::uninitialized_fill_n(m_data[m_len], nSize - m_len, T());
		}

		m_len = nSize;
	}

	/** Tries to turn storage to static. */
	void tryTurnToStatic()
	{
		realloc(m_len, true);
	}

	/** Sets number of elements in the array to 0. */
	void clear()
	{
		resize(0);
	}

	/** Returns pointer to the beginning of the array (inclusive). */
	T* begin()
	{
		return m_data;
	}

	/** Returns pointer to the end of the array (exclusive). */
	T* end()
	{
		return m_data + m_len;
	}

	/** Returns ith element from the array. */
	const T& operator[](size_t index) const
	{
		assert(index < m_len);
		return m_data[index];
	}

	/** Returns number of elements in the array. */
	size_t size() const
	{
		return m_len;
	}

	/** Returns pointer to the beginning of the array (inclusive). */
	const T* begin() const
	{
		return m_data;
	}

	/** Returns pointer to the end of the array (exclusive). */
	const T* end() const
	{
		return m_data + m_len;
	}

	bool isDynamic() const
	{
		return m_data != &m_staticBuffer[0];
	}

private:
	T*		m_data{};
	size_t	m_len{};
	size_t	m_cap{N};
	T		m_staticBuffer[N];

	void releaseBuffer()
	{
		std::destroy_n(m_data, m_len);
		if (isDynamic())
		{
			byte_t* pRawBytes = reinterpret_cast<byte_t*>(m_data);
			delete[] pRawBytes;
			m_data = &m_staticBuffer[0];
			m_cap = N;
		}
	}

	void realloc(size_t nSize, bool bShrinkToStatic = false)
	{
		if (nSize > m_cap)
		{
			assert(nSize > N);
			size_t cap = m_cap;
			if (cap < 4)
				cap = 4;
			while (cap < nSize)
				cap = cap + (cap >> 1);
			
			std::unique_ptr<byte_t[]> pNewData(new byte_t[cap * sizeof(T)]);
			
			std::uninitialized_copy_n(m_data, m_len, reinterpret_cast<T*>(pNewData.get()));
			releaseBuffer();

			m_data = reinterpret_cast<T*>(pNewData.release());
			m_cap = cap;
		}
		else if (nSize <= N && isDynamic() && bShrinkToStatic)
		{
			assert(nSize < m_len);
			std::uninitialized_copy_n(m_data, nSize, m_staticBuffer);
			
			releaseBuffer();
		}
	}
};


} // end of lang

} // end of cm
#endif // CM_LANG_ARRAY_H
