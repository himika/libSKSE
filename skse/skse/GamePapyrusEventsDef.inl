#if NUM_PARAMS > 10
#error GamePapyrusFunctionsDef: too many params
#endif

#define CLASS_NAME __MACRO_JOIN__(PapyrusEventArguments, NUM_PARAMS)


#if NUM_PARAMS > 0
template <
	typename T_Arg0
#if NUM_PARAMS > 1
	, typename T_Arg1
#endif
#if NUM_PARAMS > 2
	, typename T_Arg2
#endif
#if NUM_PARAMS > 3
	, typename T_Arg3
#endif
#if NUM_PARAMS > 4
	, typename T_Arg4
#endif
#if NUM_PARAMS > 5
	, typename T_Arg5
#endif
#if NUM_PARAMS > 6
	, typename T_Arg6
#endif
#if NUM_PARAMS > 7
	, typename T_Arg7
#endif
#if NUM_PARAMS > 8
	, typename T_Arg8
#endif
#if NUM_PARAMS > 9
	, typename T_Arg9
#endif
>
#endif
class CLASS_NAME : public PapyrusEventArguments
{
public:
	CLASS_NAME(
#if NUM_PARAMS > 0
		T_Arg0 arg0
#endif
#if NUM_PARAMS > 1
		, T_Arg1 arg1
#endif
#if NUM_PARAMS > 2
		, T_Arg2 arg2
#endif
#if NUM_PARAMS > 3
		, T_Arg3 arg3
#endif
#if NUM_PARAMS > 4
		, T_Arg4 arg4
#endif
#if NUM_PARAMS > 5
		, T_Arg5 arg5
#endif
#if NUM_PARAMS > 6
		, T_Arg6 arg6
#endif
#if NUM_PARAMS > 7
		, T_Arg7 arg7
#endif
#if NUM_PARAMS > 8
		, T_Arg8 arg8
#endif
#if NUM_PARAMS > 9
		, T_Arg9 arg9
#endif
	) {
#if NUM_PARAMS > 0
		m_arg0 = arg0;
#endif
#if NUM_PARAMS > 1
		m_arg1 = arg1;
#endif
#if NUM_PARAMS > 2
		m_arg2 = arg2;
#endif
#if NUM_PARAMS > 3
		m_arg3 = arg3;
#endif
#if NUM_PARAMS > 4
		m_arg4 = arg4;
#endif
#if NUM_PARAMS > 5
		m_arg5 = arg5;
#endif
#if NUM_PARAMS > 6
		m_arg6 = arg6;
#endif
#if NUM_PARAMS > 7
		m_arg7 = arg7;
#endif
#if NUM_PARAMS > 8
		m_arg8 = arg8;
#endif
#if NUM_PARAMS > 9
		m_arg9 = arg9;
#endif
	}

	virtual ~CLASS_NAME() { }

	virtual bool Copy(Output* dst)
	{
		dst->Resize(NUM_PARAMS);
#if NUM_PARAMS > 0
		PackValue(dst->Get(0), &m_arg0, m_registry);
#endif
#if NUM_PARAMS > 1
		PackValue(dst->Get(1), &m_arg1, m_registry);
#endif
#if NUM_PARAMS > 2
		PackValue(dst->Get(2), &m_arg2, m_registry);
#endif
#if NUM_PARAMS > 3
		PackValue(dst->Get(3), &m_arg3, m_registry);
#endif
#if NUM_PARAMS > 4
		PackValue(dst->Get(4), &m_arg4, m_registry);
#endif
#if NUM_PARAMS > 5
		PackValue(dst->Get(5), &m_arg5, m_registry);
#endif
#if NUM_PARAMS > 6
		PackValue(dst->Get(6), &m_arg6, m_registry);
#endif
#if NUM_PARAMS > 7
		PackValue(dst->Get(7), &m_arg7, m_registry);
#endif
#if NUM_PARAMS > 8
		PackValue(dst->Get(8), &m_arg8, m_registry);
#endif
#if NUM_PARAMS > 9
		PackValue(dst->Get(9), &m_arg9, m_registry);
#endif
		return true;
	}

private:
#if NUM_PARAMS > 0
	T_Arg0	m_arg0;
#endif
#if NUM_PARAMS > 1
	T_Arg1	m_arg1;
#endif
#if NUM_PARAMS > 2
	T_Arg2	m_arg2;
#endif
#if NUM_PARAMS > 3
	T_Arg3	m_arg3;
#endif
#if NUM_PARAMS > 4
	T_Arg4	m_arg4;
#endif
#if NUM_PARAMS > 5
	T_Arg5	m_arg5;
#endif
#if NUM_PARAMS > 6
	T_Arg6	m_arg6;
#endif
#if NUM_PARAMS > 7
	T_Arg7	m_arg7;
#endif
#if NUM_PARAMS > 8
	T_Arg8	m_arg8;
#endif
#if NUM_PARAMS > 9
	T_Arg9	m_arg9;
#endif
};

	template <typename T_Base
#if NUM_PARAMS > 0
		, typename T_Arg0
#endif
#if NUM_PARAMS > 1
		, typename T_Arg1
#endif
#if NUM_PARAMS > 2
		, typename T_Arg2
#endif
#if NUM_PARAMS > 3
		, typename T_Arg3
#endif
#if NUM_PARAMS > 4
		, typename T_Arg4
#endif
#if NUM_PARAMS > 5
		, typename T_Arg5
#endif
#if NUM_PARAMS > 6
		, typename T_Arg6
#endif
#if NUM_PARAMS > 7
		, typename T_Arg7
#endif
#if NUM_PARAMS > 8
		, typename T_Arg8
#endif
#if NUM_PARAMS > 9
		, typename T_Arg9
#endif
	> void SendEvent(T_Base* base, BSFixedString* eventName
#if NUM_PARAMS > 0
		, T_Arg0 arg0
#endif
#if NUM_PARAMS > 1
		, T_Arg1 arg1
#endif
#if NUM_PARAMS > 2
		, T_Arg2 arg2
#endif
#if NUM_PARAMS > 3
		, T_Arg3 arg3
#endif
#if NUM_PARAMS > 4
		, T_Arg4 arg4
#endif
#if NUM_PARAMS > 5
		, T_Arg5 arg5
#endif
#if NUM_PARAMS > 6
		, T_Arg5 arg6
#endif
#if NUM_PARAMS > 7
		, T_Arg5 arg7
#endif
#if NUM_PARAMS > 8
		, T_Arg5 arg8
#endif
#if NUM_PARAMS > 9
		, T_Arg5 arg9
#endif
	) {
		VMClassRegistry* registry = (*g_skyrimVM)->GetClassRegistry();
		CLASS_NAME<
#if NUM_PARAMS > 0
			T_Arg0
#endif
#if NUM_PARAMS > 1
			, T_Arg1
#endif
#if NUM_PARAMS > 2
			, T_Arg2
#endif
#if NUM_PARAMS > 3
			, T_Arg3
#endif
#if NUM_PARAMS > 4
			, T_Arg4
#endif
#if NUM_PARAMS > 5
			, T_Arg5
#endif
#if NUM_PARAMS > 6
			, T_Arg6
#endif
#if NUM_PARAMS > 7
			, T_Arg7
#endif
#if NUM_PARAMS > 8
			, T_Arg8
#endif
#if NUM_PARAMS > 9
			, T_Arg9
#endif
		> args(
#if NUM_PARAMS > 0
			arg0
#endif
#if NUM_PARAMS > 1
			, arg1
#endif
#if NUM_PARAMS > 2
			, arg2
#endif
#if NUM_PARAMS > 3
			, arg3
#endif
#if NUM_PARAMS > 4
			, arg4
#endif
#if NUM_PARAMS > 5
			, arg5
#endif
#if NUM_PARAMS > 6
			, arg6
#endif
#if NUM_PARAMS > 7
			, arg7
#endif
#if NUM_PARAMS > 8
			, arg8
#endif
#if NUM_PARAMS > 9
			, arg9
#endif
		);
		args(base, eventName, registry, false);
	}


	template <typename T_Base
#if NUM_PARAMS > 0
		, typename T_Arg0
#endif
#if NUM_PARAMS > 1
		, typename T_Arg1
#endif
#if NUM_PARAMS > 2
		, typename T_Arg2
#endif
#if NUM_PARAMS > 3
		, typename T_Arg3
#endif
#if NUM_PARAMS > 4
		, typename T_Arg4
#endif
#if NUM_PARAMS > 5
		, typename T_Arg5
#endif
#if NUM_PARAMS > 6
		, typename T_Arg6
#endif
#if NUM_PARAMS > 7
		, typename T_Arg7
#endif
#if NUM_PARAMS > 8
		, typename T_Arg8
#endif
#if NUM_PARAMS > 9
		, typename T_Arg9
#endif
	> void BroadcastEvent(T_Base* base, BSFixedString* eventName
#if NUM_PARAMS > 0
		, T_Arg0 arg0
#endif
#if NUM_PARAMS > 1
		, T_Arg1 arg1
#endif
#if NUM_PARAMS > 2
		, T_Arg2 arg2
#endif
#if NUM_PARAMS > 3
		, T_Arg3 arg3
#endif
#if NUM_PARAMS > 4
		, T_Arg4 arg4
#endif
#if NUM_PARAMS > 5
		, T_Arg5 arg5
#endif
#if NUM_PARAMS > 6
		, T_Arg5 arg6
#endif
#if NUM_PARAMS > 7
		, T_Arg5 arg7
#endif
#if NUM_PARAMS > 8
		, T_Arg5 arg8
#endif
#if NUM_PARAMS > 9
		, T_Arg5 arg9
#endif
	) {
		VMClassRegistry* registry = (*g_skyrimVM)->GetClassRegistry();
		CLASS_NAME<
#if NUM_PARAMS > 0
			T_Arg0
#endif
#if NUM_PARAMS > 1
			, T_Arg1
#endif
#if NUM_PARAMS > 2
			, T_Arg2
#endif
#if NUM_PARAMS > 3
			, T_Arg3
#endif
#if NUM_PARAMS > 4
			, T_Arg4
#endif
#if NUM_PARAMS > 5
			, T_Arg5
#endif
#if NUM_PARAMS > 6
			, T_Arg6
#endif
#if NUM_PARAMS > 7
			, T_Arg7
#endif
#if NUM_PARAMS > 8
			, T_Arg8
#endif
#if NUM_PARAMS > 9
			, T_Arg9
#endif
		> args(
#if NUM_PARAMS > 0
			arg0
#endif
#if NUM_PARAMS > 1
			, arg1
#endif
#if NUM_PARAMS > 2
			, arg2
#endif
#if NUM_PARAMS > 3
			, arg3
#endif
#if NUM_PARAMS > 4
			, arg4
#endif
#if NUM_PARAMS > 5
			, arg5
#endif
#if NUM_PARAMS > 6
			, arg6
#endif
#if NUM_PARAMS > 7
			, arg7
#endif
#if NUM_PARAMS > 8
			, arg8
#endif
#if NUM_PARAMS > 9
			, arg9
#endif
		);
		args(base, eventName, registry, true);
	}


#undef CLASS_NAME
#undef NUM_PARAMS