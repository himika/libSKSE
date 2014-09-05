#if NUM_PARAMS > 10
#error GamePapyrusFunctionsDef: too many params
#endif

#if GLOBAL_SPEC
#define CLASS_NAME __MACRO_JOIN__(NativeGlobalFunction, NUM_PARAMS)
#else
#define CLASS_NAME __MACRO_JOIN__(NativeNonGlobalFunction, NUM_PARAMS)
#endif

template <
#if !VOID_SPEC
typename T_Result
#endif

#if !GLOBAL_SPEC
#if !VOID_SPEC
,
#endif
typename T_Base
#endif

#if NUM_PARAMS > 0
#if !VOID_SPEC || !GLOBAL_SPEC
,
#endif
typename T_Arg0
#endif
#if NUM_PARAMS > 1
,typename T_Arg1
#endif
#if NUM_PARAMS > 2
,typename T_Arg2
#endif
#if NUM_PARAMS > 3
,typename T_Arg3
#endif
#if NUM_PARAMS > 4
,typename T_Arg4
#endif
#if NUM_PARAMS > 5
,typename T_Arg5
#endif
#if NUM_PARAMS > 6
,typename T_Arg6
#endif
#if NUM_PARAMS > 7
,typename T_Arg7
#endif
#if NUM_PARAMS > 8
,typename T_Arg8
#endif
#if NUM_PARAMS > 9
,typename T_Arg9
#endif
>

class CLASS_NAME
#if VOID_SPEC
	<void
#if !GLOBAL_SPEC
	,T_Base
#endif
#if NUM_PARAMS > 0
	,T_Arg0
#endif
#if NUM_PARAMS > 1
	,T_Arg1
#endif
#if NUM_PARAMS > 2
	,T_Arg2
#endif
#if NUM_PARAMS > 3
	,T_Arg3
#endif
#if NUM_PARAMS > 4
	,T_Arg4
#endif
#if NUM_PARAMS > 5
	,T_Arg5
#endif
#if NUM_PARAMS > 6
	,T_Arg6
#endif
#if NUM_PARAMS > 7
	,T_Arg7
#endif
#if NUM_PARAMS > 8
	,T_Arg8
#endif
#if NUM_PARAMS > 9
	,T_Arg9
#endif
	>
#endif
	: public NativeFunction
{
public:
	typedef
#if VOID_SPEC
	void 
#else
	T_Result 
#endif
	(
#if !GLOBAL_SPEC
	T_Base::
#endif
	*CallbackType)(

#if NUM_PARAMS > 0
		T_Arg0
#endif
#if NUM_PARAMS > 1
		,T_Arg1
#endif
#if NUM_PARAMS > 2
		,T_Arg2
#endif
#if NUM_PARAMS > 3
		,T_Arg3
#endif
#if NUM_PARAMS > 4
		,T_Arg4
#endif
#if NUM_PARAMS > 5
		,T_Arg5
#endif
#if NUM_PARAMS > 6
		,T_Arg6
#endif
#if NUM_PARAMS > 7
		,T_Arg7
#endif
#if NUM_PARAMS > 8
		,T_Arg8
#endif
#if NUM_PARAMS > 9
		,T_Arg9
#endif
		);

	CLASS_NAME(const char* funcName, const char* className, CallbackType callback, VMClassRegistry* registry)
		: NativeFunction(funcName, className,
#if GLOBAL_SPEC
		1,
#else
		0,
#endif
		NUM_PARAMS), m_registry(registry)
	{
#if GLOBAL_SPEC
		m_callback = (void *)callback;
#else
		m_callback = *(void**)((void*)&callback);
#endif
#if NUM_PARAMS > 0
		m_params.data[0].type = GetTypeID<T_Arg0>(registry);
#endif
#if NUM_PARAMS > 1
		m_params.data[1].type = GetTypeID<T_Arg1>(registry);
#endif
#if NUM_PARAMS > 2
		m_params.data[2].type = GetTypeID<T_Arg2>(registry);
#endif
#if NUM_PARAMS > 3
		m_params.data[3].type = GetTypeID<T_Arg3>(registry);
#endif
#if NUM_PARAMS > 4
		m_params.data[4].type = GetTypeID<T_Arg4>(registry);
#endif
#if NUM_PARAMS > 5
		m_params.data[5].type = GetTypeID<T_Arg5>(registry);
#endif
#if NUM_PARAMS > 6
		m_params.data[6].type = GetTypeID<T_Arg6>(registry);
#endif
#if NUM_PARAMS > 7
		m_params.data[7].type = GetTypeID<T_Arg7>(registry);
#endif
#if NUM_PARAMS > 8
		m_params.data[8].type = GetTypeID<T_Arg8>(registry);
#endif
#if NUM_PARAMS > 9
		m_params.data[9].type = GetTypeID<T_Arg9>(registry);
#endif

#if VOID_SPEC
		m_retnType = VMValue::kType_None;
#else
		m_retnType = GetTypeID<T_Result>(registry);
#endif
	}

	virtual bool Run(VMValue * baseValue, VMClassRegistry * registry, UInt32 unk2, VMValue * resultValue, VMState * state)
	{
		// get argument list
		UInt32	argOffset = CALL_MEMBER_FN(state->argList, GetOffset)(state);

		// extract parameters
#if GLOBAL_SPEC
		CallbackType callback = (CallbackType)m_callback;
#else
		T_Base* base = NULL;
		UnpackValue(&base, baseValue);
		if (!base) return false;

		CallbackType callback = *(CallbackType*)&m_callback;
#endif
#if NUM_PARAMS > 0
		T_Arg0	arg0;
		UnpackValue(&arg0, CALL_MEMBER_FN(state->argList, Get)(state, 0, argOffset));
#endif
#if NUM_PARAMS > 1
		T_Arg1	arg1;
		UnpackValue(&arg1, CALL_MEMBER_FN(state->argList, Get)(state, 1, argOffset));
#endif
#if NUM_PARAMS > 2
		T_Arg2	arg2;
		UnpackValue(&arg2, CALL_MEMBER_FN(state->argList, Get)(state, 2, argOffset));
#endif
#if NUM_PARAMS > 3
		T_Arg3	arg3;
		UnpackValue(&arg3, CALL_MEMBER_FN(state->argList, Get)(state, 3, argOffset));
#endif
#if NUM_PARAMS > 4
		T_Arg4	arg4;
		UnpackValue(&arg4, CALL_MEMBER_FN(state->argList, Get)(state, 4, argOffset));
#endif
#if NUM_PARAMS > 5
		T_Arg5	arg5;
		UnpackValue(&arg5, CALL_MEMBER_FN(state->argList, Get)(state, 5, argOffset));
#endif
#if NUM_PARAMS > 6
		T_Arg6	arg6;
		UnpackValue(&arg6, CALL_MEMBER_FN(state->argList, Get)(state, 6, argOffset));
#endif
#if NUM_PARAMS > 7
		T_Arg7	arg7;
		UnpackValue(&arg7, CALL_MEMBER_FN(state->argList, Get)(state, 7, argOffset));
#endif
#if NUM_PARAMS > 8
		T_Arg8	arg8;
		UnpackValue(&arg8, CALL_MEMBER_FN(state->argList, Get)(state, 8, argOffset));
#endif
#if NUM_PARAMS > 9
		T_Arg9	arg9;
		UnpackValue(&arg9, CALL_MEMBER_FN(state->argList, Get)(state, 9, argOffset));
#endif

		// call the callback
#if !VOID_SPEC
		T_Result result =
#endif
#if GLOBAL_SPEC
			(*callback)(
#else
			(base->*callback)(
#endif
#if NUM_PARAMS > 0
			arg0
#endif
#if NUM_PARAMS > 1
			,arg1
#endif
#if NUM_PARAMS > 2
			,arg2
#endif
#if NUM_PARAMS > 3
			,arg3
#endif
#if NUM_PARAMS > 4
			,arg4
#endif
#if NUM_PARAMS > 5
			,arg5
#endif
#if NUM_PARAMS > 6
			,arg6
#endif
#if NUM_PARAMS > 7
			,arg7
#endif
#if NUM_PARAMS > 8
			,arg8
#endif
#if NUM_PARAMS > 9
			,arg9
#endif
			);

		// pack the result
#if VOID_SPEC
		resultValue->SetNone();
#else
		PackValue(resultValue, &result, registry);
#endif
		return true;
	}

protected:
	VMClassRegistry* m_registry;

	// hide
	CLASS_NAME();
};


// ===============================


#if VOID_SPEC
template<typename T_Result
#if !GLOBAL_SPEC
	,typename T_Base
#endif
#if NUM_PARAMS > 0
	,typename T_Arg0
#endif
#if NUM_PARAMS > 1
	,typename T_Arg1
#endif
#if NUM_PARAMS > 2
	,typename T_Arg2
#endif
#if NUM_PARAMS > 3
	,typename T_Arg3
#endif
#if NUM_PARAMS > 4
	,typename T_Arg4
#endif
#if NUM_PARAMS > 5
	,typename T_Arg5
#endif
#if NUM_PARAMS > 6
	,typename T_Arg6
#endif
#if NUM_PARAMS > 7
	,typename T_Arg7
#endif
#if NUM_PARAMS > 8
	,typename T_Arg8
#endif
#if NUM_PARAMS > 9
	,typename T_Arg9
#endif
>
void RegisterFunction(const char* className, const char* funcName, T_Result (
#if !GLOBAL_SPEC
	T_Base::
#endif
	*func)(
#if NUM_PARAMS > 0
	T_Arg0
#endif
#if NUM_PARAMS > 1
	,T_Arg1
#endif
#if NUM_PARAMS > 2
	,T_Arg2
#endif
#if NUM_PARAMS > 3
	,T_Arg3
#endif
#if NUM_PARAMS > 4
	,T_Arg4
#endif
#if NUM_PARAMS > 5
	,T_Arg5
#endif
#if NUM_PARAMS > 6
	,T_Arg6
#endif
#if NUM_PARAMS > 7
	,T_Arg7
#endif
#if NUM_PARAMS > 8
	,T_Arg8
#endif
#if NUM_PARAMS > 9
	,T_Arg9
#endif
	), VMClassRegistry* registry, UInt32 flags=0)
{
	registry->RegisterFunction(
		new CLASS_NAME<T_Result
#if !GLOBAL_SPEC
			,T_Base
#endif
#if NUM_PARAMS > 0
			,T_Arg0
#endif
#if NUM_PARAMS > 1
			,T_Arg1
#endif
#if NUM_PARAMS > 2
			,T_Arg2
#endif
#if NUM_PARAMS > 3
			,T_Arg3
#endif
#if NUM_PARAMS > 4
			,T_Arg4
#endif
#if NUM_PARAMS > 5
			,T_Arg5
#endif
#if NUM_PARAMS > 6
			,T_Arg6
#endif
#if NUM_PARAMS > 7
			,T_Arg7
#endif
#if NUM_PARAMS > 8
			,T_Arg8
#endif
#if NUM_PARAMS > 9
			,T_Arg9
#endif
			>(funcName, className, func, registry));
		if (flags)
		{
			registry->SetFunctionFlags(className, funcName, flags);
		}
}

#endif

#undef CLASS_NAME
#undef GLOBAL_SPEC
#undef VOID_SPEC

