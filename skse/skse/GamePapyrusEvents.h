#pragma once

#include "GameTypes.h"
#include "GameAPI.h"
#include "PapyrusArgs.h"
#include "PapyrusVM.h"


class PapyrusEventArguments : public IFunctionArguments
{
public:
	PapyrusEventArguments() {}
	~PapyrusEventArguments() {}

	template <typename T_Base>
	void operator()(T_Base* base, BSFixedString* eventName, VMClassRegistry* registry, bool bBroadcast=false)
	{
		m_registry = registry;
		IObjectHandlePolicy* policy = registry->GetHandlePolicy();
		UInt64 handle = policy->Create(base->kTypeID, base);

		if (bBroadcast && base->kTypeID != kFormType_Reference && base->kTypeID != kFormType_Character)
			bBroadcast = false;

		QueueEvent(handle, eventName, bBroadcast);
	}
protected:
	void QueueEvent(UInt64 handle, BSFixedString* eventName, bool bBroadcast);

	VMClassRegistry* m_registry;
};


/*

template <typename T_Arg0, typename T_Arg1, typename T_Arg2, typename T_Arg3, typename T_Arg4, typename T_Arg5, typename T_Arg6, typename T_Arg7, typename T_Arg8, typename T_Arg9>
class PapyrusEventArguments10 : public PapyrusEventArguments
{
public:

	PapyrusEventArguments10(T_Arg0 arg0, T_Arg1 arg1, T_Arg2 arg2, T_Arg3 arg3, T_Arg4 arg4, T_Arg5 arg5, T_Arg6 arg6, T_Arg7 arg7, T_Arg8 arg8, T_Arg9 arg9)
	{
		m_arg0 = arg0;
		m_arg1 = arg1;
		m_arg2 = arg2;
		m_arg3 = arg3;
		m_arg4 = arg4;
		m_arg5 = arg5;
		m_arg6 = arg6;
		m_arg7 = arg7;
		m_arg8 = arg8;
		m_arg9 = arg9;
	}

	virtual ~PapyrusEventArguments10()
	{
	}

	virtual bool Copy(Output* dst)
	{
		dst->Resize(10);
		PackValue(dst->Get(0), &m_arg0, m_registry);
		PackValue(dst->Get(1), &m_arg1, m_registry);
		PackValue(dst->Get(2), &m_arg2, m_registry);
		PackValue(dst->Get(3), &m_arg3, m_registry);
		PackValue(dst->Get(4), &m_arg4, m_registry);
		PackValue(dst->Get(5), &m_arg5, m_registry);
		PackValue(dst->Get(6), &m_arg6, m_registry);
		PackValue(dst->Get(7), &m_arg7, m_registry);
		PackValue(dst->Get(8), &m_arg8, m_registry);
		PackValue(dst->Get(9), &m_arg9, m_registry);
		return true;
	}

private:
	T_Arg0	m_arg0;
	T_Arg1	m_arg1;
	T_Arg2	m_arg2;
	T_Arg3	m_arg3;
	T_Arg4	m_arg4;
	T_Arg5	m_arg5;
	T_Arg6	m_arg6;
	T_Arg7	m_arg7;
	T_Arg8	m_arg8;
	T_Arg9	m_arg9;
};

namespace PapyrusUtil
{
	template <typename T_Base, typename T_Arg0, typename T_Arg1, typename T_Arg2, typename T_Arg3, typename T_Arg4, typename T_Arg5, typename T_Arg6, typename T_Arg7, typename T_Arg8, typename T_Arg9>
	void SendEvent(T_Base* base, BSFixedString* eventName, T_Arg0 arg0, T_Arg1 arg1, T_Arg2 arg2, T_Arg3 arg3, T_Arg4 arg4, T_Arg5 arg5, T_Arg5 arg6, T_Arg5 arg7, T_Arg5 arg8, T_Arg5 arg9)
	{
		VMClassRegistry* registry = (*g_skyrimVM)->GetClassRegistry();
		PapyrusEventArguments10<T_Arg0, T_Arg1, T_Arg2, T_Arg3, T_Arg4, T_Arg5, T_Arg6, T_Arg7, T_Arg8, T_Arg9> args(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		args(base, eventName, registry, false);
	}

	template <typename T_Base, typename T_Arg0, typename T_Arg1, typename T_Arg2, typename T_Arg3, typename T_Arg4, typename T_Arg5, typename T_Arg6, typename T_Arg7, typename T_Arg8, typename T_Arg9>
	void BroadcastEvent(T_Base* base, BSFixedString* eventName, T_Arg0 arg0, T_Arg1 arg1, T_Arg2 arg2, T_Arg3 arg3, T_Arg4 arg4, T_Arg5 arg5, T_Arg5 arg6, T_Arg5 arg7, T_Arg5 arg8, T_Arg5 arg9)
	{
		VMClassRegistry* registry = (*g_skyrimVM)->GetClassRegistry();
		PapyrusEventArguments10<T_Arg0, T_Arg1, T_Arg2, T_Arg3, T_Arg4, T_Arg5, T_Arg6, T_Arg7, T_Arg8, T_Arg9> args(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		args(base, eventName, registry, true);
	}
}
*/

namespace PapyrusUtil {

#define NUM_PARAMS 0
#include "GamePapyrusEventsDef.inl"

#define NUM_PARAMS 1
#include "GamePapyrusEventsDef.inl"

#define NUM_PARAMS 2
#include "GamePapyrusEventsDef.inl"

#define NUM_PARAMS 3
#include "GamePapyrusEventsDef.inl"

#define NUM_PARAMS 4
#include "GamePapyrusEventsDef.inl"

#define NUM_PARAMS 5
#include "GamePapyrusEventsDef.inl"

#define NUM_PARAMS 6
#include "GamePapyrusEventsDef.inl"

#define NUM_PARAMS 7
#include "GamePapyrusEventsDef.inl"

#define NUM_PARAMS 8
#include "GamePapyrusEventsDef.inl"

#define NUM_PARAMS 9
#include "GamePapyrusEventsDef.inl"

#define NUM_PARAMS 10
#include "GamePapyrusEventsDef.inl"

}

