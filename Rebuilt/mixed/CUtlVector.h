#pragma once
#include <cassert>

// https://github.com/EternityX/DEADCELL-CSGO/blob/a3c781e8f5db6bd036441ca1e9e85f34bbabd5ef/csgo/sdk/valve%20utils/cutlvector.h

inline int UtlMemory_CalcNewAllocationcount(int nAllocationcount, int nGrowSize, int nNewSize, int nBytesItem) {
	if (nGrowSize) {
		nAllocationcount = ((1 + ((nNewSize - 1) / nGrowSize)) * nGrowSize);
	}
	else {
		if (!nAllocationcount) {
			// Compute an allocation which is at least as big as a cache line...
			nAllocationcount = (31 + nBytesItem) / nBytesItem;
		}

		while (nAllocationcount < nNewSize) {
			nAllocationcount *= 2;
		}
	}

	return nAllocationcount;
}

template< class T, class I = int >
class CUtlMemory {
public:
	bool IsValidIndex(I i) const {
		long x = i;
		return (x >= 0) && (x < m_alloc_count);
	}

	T& operator[](I i);
	const T& operator[](I i) const;

	T* Base() {
		return m_memory;
	}

	int NumAllocated() const {
		return m_alloc_count;
	}

	void Grow(int num) {
		assert(num > 0);

		auto old_alloc_count = m_alloc_count;
		// Make sure we have at least numallocated + num allocations.
		// Use the grow rules specified for this memory (in m_grow_size)
		int alloc_requested = m_alloc_count + num;

		int new_alloc_count = UtlMemory_CalcNewAllocationcount(m_alloc_count, m_grow_size, alloc_requested, sizeof(T));

		// if m_alloc_requested wraps index type I, recalculate
		if ((int)(I)new_alloc_count < alloc_requested) {
			if ((int)(I)new_alloc_count == 0 && (int)(I)(new_alloc_count - 1) >= alloc_requested) {
				--new_alloc_count; // deal w/ the common case of m_alloc_count == MAX_USHORT + 1
			}
			else {
				if ((int)(I)alloc_requested != alloc_requested) {
					// we've been asked to grow memory to a size s.t. the index type can't address the requested amount of memory
					assert(0);
					return;
				}
				while ((int)(I)new_alloc_count < alloc_requested) {
					new_alloc_count = (new_alloc_count + alloc_requested) / 2;
				}
			}
		}

		m_alloc_count = new_alloc_count;

		if (m_memory) {
			auto ptr = new unsigned char[m_alloc_count * sizeof(T)];

			memcpy(ptr, m_memory, old_alloc_count * sizeof(T));
			m_memory = (T*)ptr;
		}
		else {
			m_memory = (T*)new unsigned char[m_alloc_count * sizeof(T)];
		}
	}

protected:
	T* m_memory;
	int m_alloc_count;
	int m_grow_size;
};

template< class T, class I >
T& CUtlMemory< T, I >::operator[](I i) {
	assert(IsValidIndex(i));
	return m_memory[i];
}

template< class T, class I >
const T& CUtlMemory< T, I >::operator[](I i) const {
	assert(IsValidIndex(i));
	return m_memory[i];
}

template< class T >
void Destruct(T* memory) {
	memory->~T();
}

template< class T >
T* Construct(T* memory) {
	return ::new(memory) T;
}

template< class T >
T* CopyConstruct(T* memory, T const& src) {
	return ::new(memory) T(src);
}

template< class T, class A = CUtlMemory< T > >
class CUtlVector {
	typedef A c_allocator;

	typedef T* iterator;
	typedef const T* const_iterator;
public:
	T& operator[](int i);
	const T& operator[](int i) const;

	T& Element(int i) {
		return m_memory[i];
	}

	const T& Element(int i) const {
		assert(IsValidIndex(i));
		return m_memory[i];
	}

	T* Base() {
		return m_memory.base();
	}

	int Count() const {
		return m_size;
	}

	void RemoveAll() {
		for (int i = m_size; --i >= 0; )
			Destruct(&element(i));

		m_size = 0;
	}

	bool IsValidIndex(int i) const {
		return (i >= 0) && (i < m_size);
	}

	void ShiftElementsRight(int elem, int num = 1) {
		assert(IsValidIndex(elem) || (m_size == 0) || (num == 0));
		int num_to_move = m_size - elem - num;
		if ((num_to_move > 0) && (num > 0))
			memmove(&Element(elem + num), &Element(elem), num_to_move * sizeof(T));
	}

	void shift_elements_left(int elem, int num = 1) {
		assert(IsValidIndex(elem) || (m_size == 0) || (num == 0));
		int numToMove = m_size - elem - num;
		if ((numToMove > 0) && (num > 0))
			memmove(&Element(elem), &Element(elem + num), numToMove * sizeof(T));
	}

	void GrowVector(int num = 1) {
		if (m_size + num > m_memory.NumAllocated()) {
			m_memory.Grow(m_size + num - m_memory.NumAllocated());
		}

		m_size += num;
	}

	int InsertBefore(int elem) {
		// Can insert at the end
		assert((elem == Count()) || IsValidIndex(elem));

		GrowVector();
		ShiftElementsRight(elem);
		Construct(&Element(elem));
		return elem;
	}

	int AddToHead() {
		return InsertBefore(0);
	}

	int AddToTail() {
		return InsertBefore(m_size);
	}

	int InsertBefore(int elem, const T& src) {
		// Can't insert something that's in the list... reallocation may hose us
		assert((Base() == NULL) || (&src < Base()) || (&src >= (Base() + Count())));

		// Can insert at the end
		assert((elem == Count()) || IsValidIndex(elem));

		GrowVector();
		ShiftElementsRight(elem);
		CopyConstruct(&element(elem), src);
		return elem;
	}

	int AddToTail(const T& src) {
		// Can't insert something that's in the list... reallocation may hose us
		return InsertBefore(m_size, src);
	}

	int Find(const T& src) const {
		for (int i = 0; i < count(); ++i) {
			if (Element(i) == src)
				return i;
		}
		return -1;
	}

	void Remove(int elem) {
		Destruct(&Element(elem));
		ShiftElementsLeft(elem);
		--m_size;
	}

	bool FindAndRemove(const T& src) {
		int elem = Find(src);
		if (elem != -1) {
			remove(elem);
			return true;
		}
		return false;
	}

	iterator Begin() {
		return Base();
	}

	const_iterator Begin() const {
		return Base();
	}

	iterator End() {
		return Base() + Count();
	}

	const_iterator End() const {
		return Base() + Count();
	}

protected:
	c_allocator m_memory;
	int m_size;
	T* m_elements;
};

template< typename T, class A >
T& CUtlVector< T, A >::operator[](int i) {
	assert(i < m_size);
	return m_memory[i];
}

template< typename T, class A >
const T& CUtlVector< T, A >::operator[](int i) const {
	assert(i < m_size);
	return m_memory[i];
}