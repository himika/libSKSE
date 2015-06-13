#pragma once

#include "skse/Utilities.h"
#include "skse/PapyrusVM.h"

#include <type_traits>

class VMState;
class VMValue;
class VMClassRegistry;
struct StaticFunctionTag;

template <typename T>
class VMArray
{
public:
	VMValue::ArrayData	* arr;
	UInt32 Length() const				{ return arr ? arr->len : 0; }
	void Get(T * dst, const UInt32 idx)	{ UnpackValue(dst, arr->GetData()+idx); }
	void Set(T * src, const UInt32 idx)
	{
		VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
		PackValue(arr->GetData()+idx, src, registry);
	}
	// himika -->
	VMArray()						{ arr = NULL; }
	VMArray(const VMArray& a_array)	{ if (arr=a_array.arr) arr->AddRef(); }
	VMArray(VMArray&& a_array)		{ arr = a_array.arr; a_array.arr = nullptr; }
	~VMArray()						{ if (arr) arr->DecRef(); }

	explicit VMArray(std::size_t size) {
		arr = NULL;
		Allocate(size);
	}

	// STL container --> VMArray
	template <class ContainerT,
		class value_type = typename ContainerT::value_type,
		class size_type  = typename ContainerT::size_type,
		class iterator   = typename ContainerT::iterator,
		class reference  = typename ContainerT::reference,
		class enabler    = typename std::enable_if<std::is_same<T, value_type>::value>::type>
	VMArray(const ContainerT& cont) : arr(NULL) {
		(*this) = cont;
	}

	// language built-in arrays --> VMArray
	template <std::size_t SIZE>
	VMArray(const T(&a_array)[SIZE]) : ptr() {
		(*this) = a_array;
	}
	
	// VMArray --> STL container
	template <class ContainerT,
		class value_type = typename ContainerT::value_type,
		class size_type  = typename ContainerT::size_type,
		class iterator   = typename ContainerT::iterator,
		class reference  = typename ContainerT::reference,
		class enabler    = typename std::enable_if<std::is_same<T, value_type>::value>::type>
	operator ContainerT() {
		size_type size = GetSize();
		ContainerT cont(size);

		if (size > 0) {
			size_type idx = 0;
			ContainerT::iterator it = cont.begin();
			while (it != cont.end()) {
				*it++ = (*this)[idx++];
			}
		}
		return cont;
	}

	VMArray& operator=(const VMArray & a_arr) {
		if (arr != a_arr.arr) {
			if (arr)
				arr->DecRef();
			arr = a_arr.arr;
			if (arr)
				arr->AddRef();
		}
		return *this;
	}

	VMArray& operator=(VMArray && a_arr) {
		if (arr)
			arr->DecRef();
		arr = a_arr.arr;
		a_arr.arr = nullptr;
		return *this;
	}

	// STL container
	template <class ContainerT,
		class value_type = typename ContainerT::value_type,
		class size_type  = typename ContainerT::size_type,
		class iterator   = typename ContainerT::iterator,
		class reference  = typename ContainerT::reference,
		class enabler    = typename std::enable_if<std::is_same<T, value_type>::value>::type>
	VMArray& operator=(const ContainerT& cont) {
		const size_type size = cont.size();
		if (size != 0 && Allocate(size)) {
			size_type idx = 0;
			ContainerT::const_iterator it = cont.begin();
			while (it != cont.end()) {
				(*this)[idx++] = *it++;
			}
		}
		return *this;
	}

	// language built-in arrays
	template <std::size_t SIZE>
	VMArray& operator=(const T(&a_array)[SIZE]) {
		const size_type size = SIZE;
		if (size != 0 && Allocate(size)) {
			for (size_type i = 0; i < size; i++) {
				(*this)[i] = a_array[i];
			}
		}
		return *this;
	}

	class const_reference
	{
	public:
		operator T() const {
			T tmp;
			VMValue* src = (VMValue*)this;
			UnpackValue(&tmp, src);
			return tmp;
		}
		bool operator==(T rhs) {
			T lhs = *this;
			return lhs == rhs;
		}
		bool operator!=(T rhs) {
			return !(*this == rhs);
		}
	private:
		const_reference() {}
	};

	class reference : public const_reference
	{
	public:
		reference& operator=(T rhs) {
			VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
			VMValue* dst = (VMValue*)this;
			PackValue(dst, &rhs, registry);
			return *this;
		}
	private:
		reference() {}
	};

	std::size_t GetSize() const {
		return arr ? arr->len : 0;
	}

	reference& operator[](std::size_t idx) {
		VMValue* value = arr->GetData() + idx;
		return *(reference*)value;
	}
	const_reference& operator[](std::size_t idx) const {
		VMValue* value = arr->GetData() + idx;
		return *(const_reference*)value;
	}

	void Swap(std::size_t i, std::size_t j) {
		if (arr) {
			VMValue tmp;
			VMValue* data = arr->GetData();
			CALL_MEMBER_FN(&tmp, Set)(&data[i]);
			data[i].SetNone();
			CALL_MEMBER_FN(&data[i], Set)(&data[j]);
			CALL_MEMBER_FN(&data[j], Set)(&tmp);
		}
	}

	bool Allocate(UInt32 size)
	{
		VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
		UInt32 typeID = GetTypeID<T>(registry);
		if (arr)
		{
			arr->DecRef();
			arr = NULL;
		}
		return CALL_MEMBER_FN(registry, AllocateArray)(&typeID, size, &arr);
	}

private:
	template <class ContainerT>
	void copy_from(const ContainerT& cont) {
		if (arr) arr->DecRef();
		arr = NULL;
		
		if (cont.size() == 0)
			return;

		if (Allocate(cont.size())) {
			std::size_t idx = 0;
			ContainerT::const_iterator it = cont.begin();
			while (it != cont.end()) {
				(*this)[idx++] = *it++;
			}
		}
	}

	template <class ContainerT>
	ContainerT convert() const {
		std::size_t size = GetSize();
		ContainerT cont(size);

		std::size_t idx = 0;
		ContainerT::iterator it = cont.begin();
		while (it != cont.end()) {
			*it++ = (*this)[idx++];
		}
		
		return cont;
	}
	// <-- himika
};

template <typename T>
void PackValue(VMValue * dst, T * src, VMClassRegistry * registry);

template <typename T>
void UnpackValue(T * dst, VMValue * src);

template <typename T>
UInt32 GetTypeID(VMClassRegistry * registry);

template <> void PackValue <void>(VMValue * dst, void * src, VMClassRegistry * registry);
template <> void PackValue <UInt32>(VMValue * dst, UInt32 * src, VMClassRegistry * registry);
template <> void PackValue <SInt32>(VMValue * dst, SInt32 * src, VMClassRegistry * registry);
template <> void PackValue <float>(VMValue * dst, float * src, VMClassRegistry * registry);
template <> void PackValue <bool>(VMValue * dst, bool * src, VMClassRegistry * registry);
template <> void PackValue <BSFixedString>(VMValue * dst, BSFixedString * src, VMClassRegistry * registry);

void PackHandle(VMValue * dst, void * src, UInt32 typeID, VMClassRegistry * registry);

template <typename T>
void PackValue(VMValue * dst, T ** src, VMClassRegistry * registry)
{
	typedef remove_pointer <T>::type	BaseType;
	PackHandle(dst, *src, BaseType::kTypeID, registry);
}

template <> void UnpackValue <float>(float * dst, VMValue * src);
template <> void UnpackValue <UInt32>(UInt32 * dst, VMValue * src);
template <> void UnpackValue <SInt32>(SInt32 * dst, VMValue * src);
template <> void UnpackValue <bool>(bool * dst, VMValue * src);
template <> void UnpackValue <BSFixedString>(BSFixedString * dst, VMValue * src);
template <> void UnpackValue <const char*>(const char ** dst, VMValue * src);

template <> void UnpackValue <VMArray<float>>(VMArray<float> * dst, VMValue * src);
template <> void UnpackValue <VMArray<UInt32>>(VMArray<UInt32> * dst, VMValue * src);
template <> void UnpackValue <VMArray<SInt32>>(VMArray<SInt32> * dst, VMValue * src);
template <> void UnpackValue <VMArray<bool>>(VMArray<bool> * dst, VMValue * src);
template <> void UnpackValue <VMArray<BSFixedString>>(VMArray<BSFixedString> * dst, VMValue * src);

void * UnpackHandle(VMValue * src, UInt32 typeID);

template <typename T>
void UnpackValue(T * dst, VMValue * src)
{
	typedef remove_pointer <T>::type	BaseType;
	*dst = (T)UnpackHandle(src, BaseType::kTypeID);
}

template <typename T>
void UnpackArray(VMArray<T> * dst, VMValue * src, const UInt32 type)
{
	VMValue::ArrayData * arrData;

	if (src->type != type || (arrData = src->data.arr, !arrData))
	{
		dst->arr = NULL;
		return;
	}

	dst->arr = arrData;
	arrData->AddRef();			// (himika)
}

UInt32 GetTypeIDFromFormTypeID(UInt32 formTypeID, VMClassRegistry * registry);

template <> UInt32 GetTypeID <void>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <UInt32>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <SInt32>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <int>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <float>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <bool>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <BSFixedString>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <const char*>(VMClassRegistry * registry);

template <> UInt32 GetTypeID <VMArray<UInt32>>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <VMArray<SInt32>>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <VMArray<int>>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <VMArray<float>>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <VMArray<bool>>(VMClassRegistry * registry);
template <> UInt32 GetTypeID <VMArray<BSFixedString>>(VMClassRegistry * registry);

template<typename T>
struct IsArrayType
{
	enum { value = 0 };
	typedef T TypedArg;
};

template<typename T>
struct IsArrayType<VMArray<T*>>
{
	enum { value = 1 };
	typedef T TypedArg;
};

template <typename T>
UInt32 GetTypeID <T *>(VMClassRegistry * registry)
{
	UInt32		result;

	typedef remove_pointer <IsArrayType<T>::TypedArg>::type	BaseType;
	if(!IsArrayType<T>::value) {
		result = GetTypeIDFromFormTypeID(BaseType::kTypeID, registry);
	} else { // Arrays are ClassInfo ptr + 1
		result = GetTypeIDFromFormTypeID(BaseType::kTypeID, registry) | VMValue::kType_Identifier;
	}

	return result;
}

template <class T>
struct IsStaticType
{
	enum { value = 0 };
};

template <>
struct IsStaticType <StaticFunctionTag>
{
	enum { value = 1 };
};


#ifdef _NATIVEDUMP
template <typename T>
const char * GetArgumentTypeName(VMClassRegistry * registry);

template <> const char * GetArgumentTypeName <void>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <UInt32>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <SInt32>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <int>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <float>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <bool>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <BSFixedString>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <VMArray<UInt32>>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <VMArray<SInt32>>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <VMArray<int>>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <VMArray<float>>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <VMArray<bool>>(VMClassRegistry * registry);
template <> const char * GetArgumentTypeName <VMArray<BSFixedString>>(VMClassRegistry * registry);

const char * GetTypeNameFromFormTypeID(UInt32 formTypeID, VMClassRegistry * registry);

template <typename T>
const char * GetArgumentTypeName <T *>(VMClassRegistry * registry)
{
	typedef remove_pointer <T>::type	BaseType;
	
	return GetTypeNameFromFormTypeID(BaseType::kTypeID, registry);
}
#endif

// =========== (himika) ============
template <> void PackValue <VMArray<UInt32>>(VMValue * dst, VMArray<UInt32> * src, VMClassRegistry * registry);
template <> void PackValue <VMArray<SInt32>>(VMValue * dst, VMArray<SInt32> * src, VMClassRegistry * registry);
template <> void PackValue <VMArray<float>>(VMValue * dst, VMArray<float> * src, VMClassRegistry * registry);
template <> void PackValue <VMArray<bool>>(VMValue * dst, VMArray<bool> * src, VMClassRegistry * registry);
template <> void PackValue <VMArray<BSFixedString>>(VMValue * dst, VMArray<BSFixedString> * src, VMClassRegistry * registry);

template <typename T>
void PackValue(VMValue * dst, VMArray<T*> * src, VMClassRegistry * registry)
{
	UInt32 type = GetTypeID<T*>(registry) | 0x00000001;
	PackArray(dst, src, type);
}

template <typename T>
void PackArray(VMValue * dst, VMArray<T> * src, const UInt32 type)
{
	dst->SetNone();
	if (src->arr && src->Length() > 0)
	{
		dst->type = type;
		dst->data.arr = src->arr;
		dst->data.arr->AddRef();
	}
}

template <typename T>
void UnpackValue(VMArray<T*> * dst, VMValue * src)
{
	VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
	UInt32 type = GetTypeID<T*>(registry) | 0x00000001;
	UnpackArray(dst, src, type);
}
