
#include "GameAPI.h"
#include "GameTypes.h"
#include "GamePapyrusEvents.h"

static const UInt32 * g_TlsIndexPtr = (UInt32 *)0x01BBEB54;

struct TLSData
{
	// thread local storage

	UInt32	pad000[(0x4AC - 0x000) >> 2];   // 000
	volatile UInt32	state;                  // 4AC
};

static TLSData * GetTLSData(void)
{
	UInt32 TlsIndex = *g_TlsIndexPtr;
	TLSData * data = NULL;

	__asm {
		mov		ecx,	[TlsIndex]
		mov		edx,	fs:[2Ch]	// linear address of thread local storage array
		mov		eax,	[edx+ecx*4]
		mov		[data], eax
	}

	return data;
}




void PapyrusEventArguments::QueueEvent(UInt64 handle, BSFixedString* eventName, bool bBroadcast)
{
	// change thread state = 14h
	TLSData* tlsData = GetTLSData();
	UInt32 oldState = tlsData->state;
	tlsData->state = 0x14;
	
	m_registry->QueueEvent(handle, eventName, this);
	if (bBroadcast) {
		CALL_MEMBER_FN(*g_skyrimVM, QueueAliasEvent)(handle, eventName, this, 0);
	}

	tlsData->state = oldState;

	return;
}

