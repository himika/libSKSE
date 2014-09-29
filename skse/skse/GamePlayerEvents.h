#pragma once

#include "GameEvents.h"

class Actor;

struct Inventory
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct ActorItemEquipped
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct ActorKill
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct CriticalHit
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct SkillIncrease
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct Bounty
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct QuestStaus
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct ObjectiveState
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct LocationDiscovery
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct BookRead
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct Harvest
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct DaysPassed
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct AssaultCrime
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct MurderCrime
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct LocationCleared
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct SoulsTrapped
{
	// 08
	struct Event
	{
		Actor* trapper;
		Actor* target;
	};
	static BSTEventSource<Event>& eventSource;
};

struct LocksPicked
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct SoulGemsUsed
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct ChestsLooted
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};


struct LevelIncrease
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct HourPassed
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct TimesTrained
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct TimesBartered
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct ContractedDisease
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct PoisonedWeapon
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct Disarmed
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct WordLearned
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct WordUnlocked
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct SpellsLearned
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct DragonSoulGained
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct ShoutAttack
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct ShoutMastered
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct ItemCrafted
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct Pickpocket
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct Trespass
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct FinesPaid
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct DaysJailed
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct ItemsPickpocketed
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct ItemStolen
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct Jailing
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct JailEscape
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};

struct GrandTheftHorse
{
	struct Event
	{
	};
	static BSTEventSource<Event>& eventSource;
};


#define _EVENT_SINK(name)																		\
template <> class BSTEventSink <name::Event> {													\
public:																							\
	typedef name::Event EventT;																	\
	typedef BSTEventSource<name::Event> SourceT;												\
	virtual ~BSTEventSink() {}																	\
	virtual EventResult ReceiveEvent(EventT* evn, SourceT* source) = 0;							\
	SourceT*	GetSource(void)			{ return &name::eventSource; }							\
	BSTEventSink*	Register(void)		{ GetSource()->AddEventSink(this); return this; }		\
	BSTEventSink*	Unregister(void)	{ GetSource()->RemoveEventSink(this); return this; }	\
};
_EVENT_SINK(Inventory)
_EVENT_SINK(ActorItemEquipped)
_EVENT_SINK(ActorKill)
_EVENT_SINK(CriticalHit)
_EVENT_SINK(SkillIncrease)
_EVENT_SINK(Bounty)
_EVENT_SINK(QuestStaus)
_EVENT_SINK(ObjectiveState)
_EVENT_SINK(LocationDiscovery)
_EVENT_SINK(BookRead)
_EVENT_SINK(Harvest)
_EVENT_SINK(DaysPassed)
_EVENT_SINK(AssaultCrime)
_EVENT_SINK(MurderCrime)
_EVENT_SINK(LocationCleared)
_EVENT_SINK(SoulsTrapped)
_EVENT_SINK(LocksPicked)
_EVENT_SINK(SoulGemsUsed)
_EVENT_SINK(ChestsLooted)
_EVENT_SINK(LevelIncrease)
_EVENT_SINK(HourPassed)
_EVENT_SINK(TimesTrained)
_EVENT_SINK(TimesBartered)
_EVENT_SINK(ContractedDisease)
_EVENT_SINK(PoisonedWeapon)
_EVENT_SINK(Disarmed)
_EVENT_SINK(WordLearned)
_EVENT_SINK(WordUnlocked)
_EVENT_SINK(SpellsLearned)
_EVENT_SINK(DragonSoulGained)
_EVENT_SINK(ShoutAttack)
_EVENT_SINK(ShoutMastered)
_EVENT_SINK(ItemCrafted)
_EVENT_SINK(Pickpocket)
_EVENT_SINK(Trespass)
_EVENT_SINK(FinesPaid)
_EVENT_SINK(DaysJailed)
_EVENT_SINK(ItemsPickpocketed)
_EVENT_SINK(ItemStolen)
_EVENT_SINK(Jailing)
_EVENT_SINK(JailEscape)
_EVENT_SINK(GrandTheftHorse)
#undef _EVENT_SINK
