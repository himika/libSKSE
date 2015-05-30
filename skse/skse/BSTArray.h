#pragma once

#include "Utilities.h"

// 04
class BSTArrayBase
{
public:
	BSTArrayBase() : _M_count(0) {}

	class IAllocatorFunctor
	{
	public:
		IAllocatorFunctor() {}
		virtual bool	Allocate(UInt32 num, UInt32 value_size) = 0;
		virtual bool	Resize(UInt32 needNum, UInt32 copyFrontNum, UInt32 copySkipNum, UInt32 copyTailNum, UInt32 value_size) = 0;
		virtual void	Free(void* ptr) = 0;
		virtual ~IAllocatorFunctor() {}		// 004016E0
		// member
		//void	** _vtbl	// 00 - 010775F0
	};

	UInt32 GetSize() const {
		return _M_count;
	}

protected:
	SInt32 _Push(IAllocatorFunctor& functor, UInt32 capacity, UInt32 value_size) {
		return CALL_MEMBER_FN(this, _Push)(functor, capacity, value_size);
	}
	void _Move(void * entries, UInt32 to, UInt32 from, UInt32 num, UInt32 value_size) {
		CALL_MEMBER_FN(this, _Move)(entries, to, from, num, value_size);
	}

	MEMBER_FN_PREFIX(BSTArrayBase);
	DEFINE_MEMBER_FN(_Push, SInt32, 0x00A49B80, IAllocatorFunctor& functor, UInt32 capacity, UInt32 value_size);
	DEFINE_MEMBER_FN(_Move, void, 0x00A4A070, void * entries, UInt32 to, UInt32 from, UInt32 num, UInt32 value_size);
	void _Pop(UInt32 num) {
		_M_count -= num;
	}

private:
	// member
	UInt32	_M_count;		// 00
};


/*---------------------------------------------------
/ Allocator
/----------------------------------------------------*/
template <class _TAlloc>
class BSTArrayAllocatorFunctor;

// 08
class BSTArrayHeapAllocator
{
public:
	typedef BSTArrayAllocatorFunctor<BSTArrayHeapAllocator> functor_type;

	BSTArrayHeapAllocator() : _M_entries(NULL), _M_capacity(0) {
	}
	~BSTArrayHeapAllocator() {
		if (_M_entries)
			_Free();
	}

	UInt32		GetCapacity() const	{ return _M_capacity; }

protected:
	void*		_GetFront()			{ return _M_entries; }
	const void* _GetFront() const	{ return _M_entries; }

	bool _Allocate(UInt32 num, UInt32 value_size) {
		return CALL_MEMBER_FN(this, _Allocate)(num, value_size);
	}
	bool _Resize(UInt32 needNum, UInt32 copyFrontNum, UInt32 copySkipNum, UInt32 copyTailNum, UInt32 value_size) {
		return CALL_MEMBER_FN(this, _Resize)(needNum, copyFrontNum, copySkipNum, copyTailNum, value_size);
	}
	void _Free() {
		CALL_MEMBER_FN(this, _Free)();
	}

	MEMBER_FN_PREFIX(BSTArrayHeapAllocator);
	DEFINE_MEMBER_FN(_Allocate, bool, 0x00A49C60, UInt32 num, UInt32 value_size);
	DEFINE_MEMBER_FN(_Resize, bool, 0x00A49CA0, UInt32 needNum, UInt32 copyFrontNum, UInt32 copySkipNum, UInt32 copyTailNum, UInt32 value_size);
	DEFINE_MEMBER_FN(_Free, void, 0x00A49D90);

	// members
	void*		_M_entries;		// 00
	std::size_t	_M_capacity;	// 04

	friend class functor_type;
};


template <int local_size>
class BSTSmallArrayHeapAllocator
{
public:
	typedef BSTArrayAllocatorFunctor<BSTSmallArrayHeapAllocator> functor_type;

	enum { kLocalAlloc = 0x80000000 };

	BSTSmallArrayHeapAllocator() : _M_capacity(local_size | kLocalAlloc) {
		//memset(entries.local, 0, sizeof(Entry));
	}
	~BSTSmallArrayHeapAllocator() {
		if (!_IsLocal() && _M_capacity)
			_Free();
	}

	UInt32		GetCapacity() const	{ return (_M_capacity & ~kLocalAlloc); }

protected:
	void*		_GetFront()			{ return _IsLocal() ? _M_entries.local : _M_entries.heap; }
	const void* _GetFront() const	{ return _IsLocal() ? _M_entries.local : _M_entries.heap; }

	bool _Allocate(UInt32 num, UInt32 value_size, UInt32 local_size) {
		return CALL_MEMBER_FN(this, _Allocate)(num, value_size, local_size);
	}
	bool _Resize(UInt32 needNum, UInt32 copyFrontNum, UInt32 copySkipNum, UInt32 copyTailNum, UInt32 value_size, UInt32 local_size) {
		return CALL_MEMBER_FN(this, _Resize)(needNum, copyFrontNum, copySkipNum, copyTailNum, value_size, local_size);
	}
	void _Free() {
		CALL_MEMBER_FN(this, _Free)();
	}

	MEMBER_FN_PREFIX(BSTSmallArrayHeapAllocator);
	DEFINE_MEMBER_FN(_Allocate, bool, 0x00A4A720, UInt32 num, UInt32 value_size, UInt32 local_size);
	DEFINE_MEMBER_FN(_Resize, bool, 0x00A4A7A0, UInt32 needNum, UInt32 copyFrontNum, UInt32 copySkipNum, UInt32 copyTailNum, UInt32 value_size, UInt32 local_size);
	DEFINE_MEMBER_FN(_Free, void, 0x00A4A8F0);

private:
	bool		_IsLocal() const	{ return (_M_capacity & kLocalAlloc) != 0; }

	union Entry
	{
		void*		heap;
		UInt8		local[local_size];
	};

	// members
	UInt32	_M_capacity;	// 00
	Entry	_M_entries;		// 04

	friend class functor_type;
};



/// AllocatorFunctor
template <class _TAlloc>
class BSTArrayAllocatorFunctor : public BSTArrayBase::IAllocatorFunctor
{
public:
	typedef _TAlloc allocator_type;

	explicit BSTArrayAllocatorFunctor(allocator_type * a_allocator) : allocator(a_allocator) { }

	// BSTArrayHeapAllocator:		TESV.004016B0
	// BSTSmallArrayHeapAllocator:	TESV.005A7470
	virtual bool Allocate(UInt32 num, UInt32 value_size) override {
		return allocator->_Allocate(num, value_size);
	}
	// BSTArrayHeapAllocator:		TESV.004016C0
	// BSTSmallArrayHeapAllocator:	TESV.005A7490
	virtual bool Resize(UInt32 needNum, UInt32 copyFrontNum, UInt32 copySkipNum, UInt32 copyTailNum, UInt32 value_size) override {
		return allocator->_Resize(needNum, copyFrontNum, copySkipNum, copyTailNum, value_size);
	}
	// BSTArrayHeapAllocator:		TESV.004016D0
	// BSTSmallArrayHeapAllocator:	TESV.0040B750
	virtual void Free(void* ptr) override {
		allocator->_Free();
	}

private:
	// member
	//void			** _vtbl		// 00 - BSTArrayHeapAllocator:01077640, BSTSmallArrayHeapAllocator:010BE92C
	allocator_type	* allocator;	// 04
};

/*---------------------------------------------------
/ BSTArray
/----------------------------------------------------*/

// the same type as tArray
template <class _Ty, class _TAlloc = BSTArrayHeapAllocator>
class BSTArray : public _TAlloc, public BSTArrayBase
{
public:
	typedef _TAlloc allocator_type;
	typedef BSTArrayAllocatorFunctor<allocator_type> functor_type;
	typedef _Ty value_type;
	typedef _Ty *pointer;
	typedef const _Ty *const_pointer;
	typedef _Ty &reference;
	typedef const _Ty &const_reference;

	BSTArray() {}
	~BSTArray() {
		for (int i = 0; i < GetSize(); ++i) {
			(*this)[i].~value_type();
		}
	}

	reference Front() {
		return *reinterpret_cast<pointer>(_GetFront());
	}

	const_reference Front() const {
		return *reinterpret_cast<const_pointer>(_GetFront());
	}

	reference operator[] (UInt32 index) {
		return *(&Front() + index);
	}

	const_reference operator[] (UInt32 index) const {
		return *(&Front() + index);
	}

	SInt32 Find(const_reference ref) const {
		//return Find([&ref](const_reference a) -> bool { return (a == ref); });
		const_pointer entries = &Front();
		SInt32 index = -1;
		for (UInt32 i = 0; i < GetSize(); ++i) {
			if (entries[index] == ref) {
				index = i;
				break;
			}
		}
		return index;
	}

	template <class _F>
	SInt32 Find(_F functor) const {
		const_pointer entries = &Front();
		SInt32 index = -1;
		for (UInt32 i = 0; i < GetSize(); ++i) {
			if (functor(entries[index])) {
				index = i;
				break;
			}
		}
		return index;
	}

	// TESV.0043C670
	void Add(const_reference ref) {
		functor_type functor(this);
		SInt32 index = _Push(functor, GetCapacity(), sizeof(value_type));
		if (index != -1) {
			(*this)[index] = ref;
		}
	}

	// TESV.00C55770
	void Remove(UInt32 index, UInt32 num = 1) {
		pointer p = &Front() + index;
		for (std::size_t i = 0; i < num; i++) {
			(p++)->~value_type();
		}

		UInt32 size = GetSize();
		UInt32 tailNum = size - (index + num);
		if (tailNum > 0) {
			if (tailNum >= num)
				tailNum = num;
			UInt32 from = size - tailNum;
			UInt32 to = index;
			_Move(_GetFront(), to, from, tailNum, sizeof(value_type));
		}
		_Pop(num);
	}

	// near TESV.004FB4C3
	void Remove(const_reference ref) {
		SInt32 index = Find(ref);
		if (index != -1) {
			Remove(index, 1);
		}
	}

	void PopFront() {
		Remove(0, 1);
	}

	void PopBack() {
		std::size_t num = GetSize();
		if (num) {
			pointer p = &Front() + (num - 1);
			p->~value_type();
			_Pop(1);
		}
	}

	bool GetNthItem(UInt32 index, reference pT) const {
		return (index < GetSize()) ? (pT = (*this)[index], true) : false;
	}
};

#if _MSC_VER >= 1800
template<class _Ty, int num = 1>
using BSTSmallArray = BSTArray < _Ty, BSTSmallArrayHeapAllocator<sizeof(_Ty)*num> > ;
#else
template<class _Ty, int num = 1>
struct BSTSmallArray : public BSTArray<_Ty, BSTSmallArrayHeapAllocator<sizeof(_Ty)*num>>
{
};
#endif