#include "GameTypes.h"

void SimpleLock::Lock(void)
{
	SInt32 myThreadID = GetCurrentThreadId();
	if (threadID == myThreadID) {
		lockCount++;
		return;
	}

	UInt32 spinCount = 0;
	while (InterlockedCompareExchange(&threadID, myThreadID, 0))
		Sleep(++spinCount > kFastSpinThreshold);

	lockCount = 1;
}

void SimpleLock::Release(void)
{
	if (--lockCount == 0)
		InterlockedCompareExchange(&threadID, 0, threadID);
}

SInt32 BSIntrusiveRefCounted::IncrementRefCount(void)
{
	return InterlockedIncrement(&m_refCount);
}

SInt32 BSIntrusiveRefCounted::DecrementRefCount(void)
{
	return InterlockedDecrement(&m_refCount);
}

StringCache * StringCache::GetSingleton(void)
{
	typedef StringCache * (* _GetSingleton)(void);

	return ((_GetSingleton)0x00A50B00)();
}

StringCache::Lock * StringCache::GetLock(UInt32 crc16)
{
	return &locks[crc16 & 0x1F];
}

StringCache::Ref::Ref(const char * rhs)
{
	CALL_MEMBER_FN(this, ctor)(rhs);
}

StringCache::Ref::Ref(const Ref &rhs)
{
	Entry* entry = (Entry*)((UInt32)rhs.data - sizeof(StringCache::Entry));
	entry->state.refCount += 1;
	data = rhs.data;
}

StringCache::Ref::Ref(Ref &&rhs)
{
	data = rhs.data;
	rhs.data = nullptr;
}

StringCache::Ref::~Ref()
{
	// fixed memory leak bug
	CALL_MEMBER_FN(this, Release)();
}

StringCache::Ref& StringCache::Ref::operator=(const char* buf)
{
	if (data && data[0])
		CALL_MEMBER_FN(this, Release)();

	return *CALL_MEMBER_FN(this, Set)(buf);
}

StringCache::Ref& StringCache::Ref::operator=(const StringCache::Ref& ref)
{
	if (data && data[0])
		CALL_MEMBER_FN(this, Release)();

	if (ref.data && ref.data[0])
	{
		data = ref.data;
		Entry* entry = (Entry*)((UInt32)data - sizeof(StringCache::Entry));
		entry->state.refCount++;
	}

	return *this;
}

StringCache::Ref& StringCache::Ref::operator=(StringCache::Ref&& ref)
{
	if (data && data[0])
		CALL_MEMBER_FN(this, Release)();

	data = ref.data;
	ref.data = nullptr;
	return *this;
}

BSString::~BSString()
{
	if(m_data)
	{
		FormHeap_Free(m_data);
		m_data = NULL;
	}
}

const char * BSString::Get(void)
{
	return m_data ? m_data : "";
}

const _CRC32_Calc4 CRC32_Calc4 = (_CRC32_Calc4)0x00A4A570;
const _CRC32_Calc8 CRC32_Calc8 = (_CRC32_Calc8)0x00A4A5D0;

void UpdateRegistrationHolder::Order(UInt32 index)
{
	UInt32 count = m_regs.count;
	UInt32 pivotIndex = count >> 1;

	if (index >= pivotIndex)
		return;

	Registration * pOldReg = m_regs[index];
	UInt32 startIndex = index;
	UInt32 cmpIndex;
	do
	{
		cmpIndex = 2*index + 1;

		if (cmpIndex < (count-1))
		{
			Registration * pCur = m_regs[cmpIndex];
			Registration * pSucc = m_regs[cmpIndex+1];
			if (!pCur || !pSucc || pCur->schedTime > pSucc->schedTime)
				cmpIndex++;
		}

		Registration * pCmpReg = m_regs[cmpIndex];
		if (!pCmpReg || !pOldReg || pCmpReg->schedTime > pOldReg->schedTime)
			break;

		m_regs[index] = pCmpReg;
		index = cmpIndex;

	}
	while (cmpIndex < pivotIndex);

	if (index != startIndex)
		m_regs[index] = pOldReg;

}

bool UpdateRegistrationHolder::Remove(UInt64 & handle)
{
	if (m_regs.count == 0)
		return false;

	for (UInt32 i=0; i<m_regs.count; i++)
	{
		Registration * pReg = m_regs[i];

		if (pReg && pReg->handle == handle)
		{
			UInt32 lastIndex = m_regs.count - 1;

			// Remove last entry => no reorganizing necessary
			if (i == lastIndex)
			{
				pReg->Release();
				m_regs.count--;
			}
			else
			{
				m_regs[i] = m_regs[lastIndex];
				m_regs[lastIndex] = pReg;	// seems pointless, but the original code does it

				pReg->Release();
				m_regs.count--;

				Order(i);
			}
			return true;
		}
	}
	return false;
}
