#pragma once

#include "GameTypes.h"
#include "GameAPI.h"
#include "PapyrusArgs.h"
#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

#define REGISTER_PAPYRUS_FUNCTION(className, funcName, ...)	PapyrusUtil::RegisterFunction(#className, #funcName, &className::funcName, __VA_ARGS__)

/* ===========================================================================
template<typename T_Result, typename T_Arg0, typename T_Arg1>
class NativeGlobalFunction2 : public NativeFunction
{
public:
	typedef T_Result (*CallbackType)(T_Arg0, T_Arg1);

	NativeGlobalFunction2(const char* funcName, const char* className, CallbackType callback, VMClassRegistry* registry)
		: NativeFunction(funcName, className, 1, 2), m_registry(registry)
	{
		m_callback = (void *)callback;
		m_params.data[0].type = IsArrayType <T_Arg0>::TypeID(registry);
		m_params.data[1].type = IsArrayType <T_Arg1>::TypeID(registry);
		m_retnType            = IsArrayType <T_Result>::TypeID(registry);
	}

	virtual bool Run(VMValue * baseValue, VMClassRegistry * registry, UInt32 arg2, VMValue * resultValue, VMState * state)
	{
		// get argument list
		UInt32	argOffset = CALL_MEMBER_FN(state->argList, GetOffset)(state);

		// extract parameters
		T_Arg0	arg0;
		IsArrayType <T_Arg0>::Unpack(&arg0, CALL_MEMBER_FN(state->argList, Get)(state, 0, argOffset));
		T_Arg1	arg1;
		IsArrayType <T_Arg1>::Unpack(&arg1, CALL_MEMBER_FN(state->argList, Get)(state, 1, argOffset));

		// call the callback
		T_Result result = ((CallbackType)m_callback)(arg0, arg1);

		// pack the result
		IsArrayType <T_Result>::Pack(resultValue, &result, registry);

		return true;
	}

protected:
	VMClassRegistry* m_registry;

	// hide
	NativeGlobalFunction2();
};

template<typename T_Result, typename T_Base, typename T_Arg0, typename T_Arg1>
class NativeNonGlobalFunction2 : public NativeFunction
{
public:
	typedef T_Result (T_Base::*CallbackType)(T_Arg0, T_Arg1);

	NativeNonGlobalFunction2(const char* funcName, const char* className, CallbackType callback, VMClassRegistry* registry)
		: NativeFunction(funcName, className, 0, 2), m_registry(registry)
	{
		m_callback = *(void**)((void*)&callback);
		m_params.data[0].type = IsArrayType <T_Arg0>::TypeID(registry);
		m_params.data[1].type = IsArrayType <T_Arg1>::TypeID(registry);
		m_retnType            = IsArrayType <T_Result>::TypeID(registry);
	}

	virtual bool Run(VMValue * baseValue, VMClassRegistry * registry, UInt32 arg2, VMValue * resultValue, VMState * state)
	{
		// get argument list
		UInt32	argOffset = CALL_MEMBER_FN(state->argList, GetOffset)(state);

		// extract base object pointer for non-static types
		T_Base	* base = NULL;
		UnpackValue(&base, baseValue);
		if (!base) return false;

		// extract parameters
		T_Arg0	arg0;
		IsArrayType <T_Arg0>::Unpack(&arg0, CALL_MEMBER_FN(state->argList, Get)(state, 0, argOffset));
		T_Arg1	arg1;
		IsArrayType <T_Arg1>::Unpack(&arg1, CALL_MEMBER_FN(state->argList, Get)(state, 1, argOffset));

		// call the callback
		CallbackType callback = *(CallbackType*)&m_callback;
		T_Result result = (base->*callback)(arg0, arg1);

		// pack the result
		IsArrayType <T_Result>::Pack(resultValue, &result, registry);

		return true;
	}

protected:
	VMClassRegistry* m_registry;

	// hide
	NativeNonGlobalFunction2();
};

namespace PapyrusUtil
{
	template<typename T_Result, typename T_Arg0, typename T_Arg1>
	void reg(const char* className, const char* funcName, T_Result (*func)(T_Arg0, T_Arg1), VMClassRegistry* registry)
	{
	 	registry->RegisterFunction(
	 		new NativeGlobalFunction2<T_Result, T_Arg0, T_Arg1>(funcName, className, func, registry));
	}

	template<typename T_Result, typename T_Base, typename T_Arg0, typename T_Arg1>
	void reg(const char* className, const char* funcName, T_Result (T_Base::*func)(T_Arg0, T_Arg1), VMClassRegistry* registry)
	{
	 	registry->RegisterFunction(
	 		new NativeNonGlobalFunction2<T_Result, T_Base, T_Arg0, T_Arg1>(funcName, className, func, registry));
	}
}
=========================================================================== */

namespace PapyrusUtil {

#define NUM_PARAMS 0
#include "GamePapyrusFunctionsDef.inl"

#define NUM_PARAMS 1
#include "GamePapyrusFunctionsDef.inl"

#define NUM_PARAMS 2
#include "GamePapyrusFunctionsDef.inl"

#define NUM_PARAMS 3
#include "GamePapyrusFunctionsDef.inl"

#define NUM_PARAMS 4
#include "GamePapyrusFunctionsDef.inl"

#define NUM_PARAMS 5
#include "GamePapyrusFunctionsDef.inl"

#define NUM_PARAMS 6
#include "GamePapyrusFunctionsDef.inl"

#define NUM_PARAMS 7
#include "GamePapyrusFunctionsDef.inl"

#define NUM_PARAMS 8
#include "GamePapyrusFunctionsDef.inl"

#define NUM_PARAMS 9
#include "GamePapyrusFunctionsDef.inl"

#define NUM_PARAMS 10
#include "GamePapyrusFunctionsDef.inl"

}
