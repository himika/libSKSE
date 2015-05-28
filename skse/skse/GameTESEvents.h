#pragma once

#include "GameEvents.h"

//===========================================================================
// TES Events
//===========================================================================

class Actor;
class TESObjectREFR;
class TESForm;
class ActiveEffect;
class TESObjectCELL;

enum
{
	kTESEvent_Unk00 = 0,
	kTESEvent_Activate,
	kTESEvent_ActiveEffectApplyRemove,
	kTESEvent_ActorLocationChange,
	kTESEvent_BookRead,
	kTESEvent_CellAttachDetach,
	kTESEvent_CellFullyLoaded,
	kTESEvent_CellReadyToApplyDecals,
	kTESEvent_Combat,
	kTESEvent_ContainerChanged,
	kTESEvent_Death,
	kTESEvent_DestructionStageChanged,
	kTESEvent_EnterBleedout,
	kTESEvent_Equip,
	kTESEvent_FormDelete,
	kTESEvent_Furniture,
	kTESEvent_GrabRelease,
	kTESEvent_Hit,
	kTESEvent_InitScript,
	kTESEvent_LoadGame,
	kTESEvent_LockChanged,
	kTESEvent_MagicEffectApply,
	kTESEvent_MagicWardHit,
	kTESEvent_MoveAttachDetach,
	kTESEvent_ObjectLoaded,
	kTESEvent_ObjectREFRTranslation,
	kTESEvent_OpenClose,
	kTESEvent_Package,
	kTESEvent_PerkEntryRun,
	kTESEvent_QuestInit,
	kTESEvent_QuestStage,
	kTESEvent_QuestStageItemDone,
	kTESEvent_QuestStartStop,
	kTESEvent_Reset,
	kTESEvent_ResolveNPCTemplates,
	kTESEvent_Scene,
	kTESEvent_SceneAction,
	kTESEvent_ScenePhase,
	kTESEvent_Sell,
	kTESEvent_SleepStart,
	kTESEvent_SleepStop,
	kTESEvent_SpellCast,
	kTESEvent_PlayerBowShot,
	kTESEvent_TopicInfo,
	kTESEvent_TrackedStats,
	kTESEvent_TrapHit,
	kTESEvent_Trigger,
	kTESEvent_TriggerEnter,
	kTESEvent_TriggerLeave,
	kTESEvent_UniqueIDChange,
	kTESEvent_WaitStart,
	kTESEvent_WaitStop,
	kTESEvent_SwitchRaceComplete
};

// 8
struct TESActivateEvent
{
	TESObjectREFR* target;
	TESObjectREFR* caster;
};

struct TESActiveEffectApplyRemoveEvent
{
	TESObjectREFR	* caster;
	TESObjectREFR	* target;
	UInt32			unk08;
	UInt32			unk0C;
	UInt32			unk10;
	UInt32			unk14;
	UInt32			unk18; // Flags?
	UInt32			unk1C; // Use effect2 if this is 1
	TESForm			* source; // Not really sure what this is, probably the extra form
	ActiveEffect	* effect1;
	ActiveEffect	* effect2;
};

// 0C
struct TESActorLocationChangeEvent
{
	UInt32 unk00;
	UInt32 unk01;
	UInt32 unk02;
};

struct TESBookReadEvent
{
};

struct TESCellAttachDetachEvent
{
	// SendEvent: 004CEB5F
	TESObjectREFR*	ref;
	bool			bAttach;
	UInt8			pad[3];
};

struct TESCellReadyToApplyDecalsEvent
{
};

// 04
struct TESCellFullyLoadedEvent
{
	// SendEvent: 00437663 <= 4CDD8E
	TESObjectCELL*	cell;
};

// 0C
struct TESCombatEvent
{
	Actor*  caster;
	Actor*  target;
	UInt32  state;
};

// 18
struct TESContainerChangedEvent
{
	UInt32	fromFormId;
	UInt32	toFormId;
	UInt32	itemFormId;
	UInt32	count;
	UInt32	toReference;
	UInt32	unk14;
};

struct TESDeathEvent
{
	TESObjectREFR	* source;	// 00
};


struct TESDestructionStageChangedEvent
{
};

struct TESEnterBleedoutEvent
{
};

// 10
struct TESEquipEvent
{
	UInt32 unk_00;
	UInt32 unk_01;
	UInt32 unk_02;
	UInt32 unk_03;
};

struct TESFormDeleteEvent
{
};

struct TESFurnitureEvent
{
};

struct TESGrabReleaseEvent
{
};

struct TESHitEvent
{
	TESObjectREFR	* target;			// 00
	TESObjectREFR	* caster;			// 04
	UInt32			sourceFormID;		// 08
	UInt32			projectileFormID;	// 0C

	enum
	{
		kFlag_PowerAttack = (1 << 0),
		kFlag_SneakAttack = (1 << 1),
		kFlag_Bash		  = (1 << 2),
		kFlag_Blocked	  = (1 << 3)
	};

	UInt32			flags;				// 10
	void			* unk14[7];			// 14
};

struct TESInitScriptEvent
{
	TESObjectREFR * reference;
	UInt32			unk04;
};


struct TESLoadGameEvent
{
};

struct TESLockChangedEvent
{
};

// 0C
struct TESMagicEffectApplyEvent
{
	TESObjectREFR*  target;
	TESObjectREFR*  caster;
	UInt32          unk08;
};

struct TESMagicWardHitEvent
{
};

struct TESMoveAttachDetachEvent
{
	TESObjectREFR*	ref;
	bool			bAttach;
};

struct TESObjectLoadedEvent
{
	UInt32 formId;
};

struct TESObjectREFRTranslationEvent
{
};

struct TESOpenCloseEvent
{
};

struct TESPackageEvent
{
};

struct TESPerkEntryRunEvent
{
};

struct TESQuestInitEvent
{
	UInt32	formId;
};

struct TESQuestStageEvent
{
	void			* finishedCallback;
	UInt32			formId;
	UInt32			stage;
};

struct TESQuestStageItemDoneEvent
{
};

struct TESQuestStartStopEvent
{
};

struct TESResetEvent
{
};

struct TESResolveNPCTemplatesEvent
{
};

struct TESSceneEvent
{
};

struct TESSceneActionEvent
{
};

struct TESScenePhaseEvent
{
};

struct TESSellEvent
{
};

// 08
struct TESSleepStartEvent
{
	float startTime;	// 00
	float endTime;		// 04
};

struct TESSleepStopEvent
{
};

struct TESSpellCastEvent
{
};

struct TESPlayerBowShotEvent
{
};

struct TESTrackedStatsEvent
{
};

struct TESTrapHitEvent
{
};

struct TESTopicInfoEvent
{
	Actor*	speaker;
	UInt32  unk04;
	UInt32  topicInfoID;
	UInt32  flag;
};

struct TESTriggerEvent
{
};

struct TESTriggerLeaveEvent
{
};

struct TESTriggerEnterEvent
{
};

struct TESUniqueIDChangeEvent
{
	UInt32	oldOwnerFormId;
	UInt32	newOwnerFormId;
	UInt32	formId;
	UInt16	oldUniqueId;
	UInt16	newUniqueId;
};

struct TESWaitStartEvent
{
};

struct TESWaitStopEvent
{
};

struct TESSwitchRaceCompleteEvent
{
	Actor * actor;
};



struct TESEventSourceHolder
{
	BSTEventSource<void*> eventSources[53];
	
	BSTEventSource<void*>* GetEventSource(UInt32 id) {
		return &eventSources[id];
	}

	template <class T>
	BSTEventSource<T>* GetEventSource();

	static TESEventSourceHolder* GetSingleton(void);
};
STATIC_ASSERT(sizeof(TESEventSourceHolder) == 0x9F0);



#define _EVENT_SINK(name)\
template <> inline BSTEventSource<TES##name##Event>* TESEventSourceHolder::GetEventSource<TES##name##Event>() {			\
	return(BSTEventSource<TES##name##Event>*)GetEventSource(kTESEvent_##name);											\
}																														\
template <> class BSTEventSink <TES##name##Event> {																		\
public:																													\
	typedef TES##name##Event EventT;																					\
	typedef BSTEventSource<TES##name##Event> SourceT;																	\
	virtual ~BSTEventSink() {}																							\
	virtual EventResult ReceiveEvent(EventT* evn, SourceT* dispatcher) = 0;												\
	static SourceT*	GetSource(void)		{ return TESEventSourceHolder::GetSingleton()->GetEventSource<EventT>(); }		\
	BSTEventSink*	Register(void)		{ GetSource()->AddEventSink(this); return this; }								\
	BSTEventSink*	Unregister(void)	{ GetSource()->RemoveEventSink(this); return this; }							\
};
_EVENT_SINK(Activate)
_EVENT_SINK(ActiveEffectApplyRemove)
_EVENT_SINK(ActorLocationChange)
_EVENT_SINK(BookRead)
_EVENT_SINK(CellAttachDetach)
_EVENT_SINK(CellFullyLoaded)
_EVENT_SINK(CellReadyToApplyDecals)
_EVENT_SINK(Combat)
_EVENT_SINK(ContainerChanged)
_EVENT_SINK(Death)
_EVENT_SINK(DestructionStageChanged)
_EVENT_SINK(EnterBleedout)
_EVENT_SINK(Equip)
_EVENT_SINK(FormDelete)
_EVENT_SINK(Furniture)
_EVENT_SINK(GrabRelease)
_EVENT_SINK(Hit)
_EVENT_SINK(InitScript)
_EVENT_SINK(LoadGame)
_EVENT_SINK(LockChanged)
_EVENT_SINK(MagicEffectApply)
_EVENT_SINK(MagicWardHit)
_EVENT_SINK(MoveAttachDetach)
_EVENT_SINK(ObjectLoaded)
_EVENT_SINK(ObjectREFRTranslation)
_EVENT_SINK(OpenClose)
_EVENT_SINK(Package)
_EVENT_SINK(PerkEntryRun)
_EVENT_SINK(QuestInit)
_EVENT_SINK(QuestStage)
_EVENT_SINK(QuestStageItemDone)
_EVENT_SINK(QuestStartStop)
_EVENT_SINK(Reset)
_EVENT_SINK(ResolveNPCTemplates)
_EVENT_SINK(Scene)
_EVENT_SINK(SceneAction)
_EVENT_SINK(ScenePhase)
_EVENT_SINK(Sell)
_EVENT_SINK(SleepStart)
_EVENT_SINK(SleepStop)
_EVENT_SINK(SpellCast)
_EVENT_SINK(PlayerBowShot)
_EVENT_SINK(TopicInfo)
_EVENT_SINK(TrackedStats)
_EVENT_SINK(TrapHit)
_EVENT_SINK(Trigger)
_EVENT_SINK(TriggerEnter)
_EVENT_SINK(TriggerLeave)
_EVENT_SINK(UniqueIDChange)
_EVENT_SINK(WaitStart)
_EVENT_SINK(WaitStop)
_EVENT_SINK(SwitchRaceComplete)
#undef _EVENT_SINK

extern BSTEventSource<TESActivateEvent>&				g_activateEventSource;
extern BSTEventSource<TESActiveEffectApplyRemoveEvent>&	g_activeEffectApplyRemoveEventSource;
extern BSTEventSource<TESActorLocationChangeEvent>&		g_actorLocationChangeEventSource;
extern BSTEventSource<TESBookReadEvent>&				g_bookReadEventSource;
extern BSTEventSource<TESCellAttachDetachEvent>&		g_cellAttachDetachEventSource;
extern BSTEventSource<TESCellFullyLoadedEvent>&			g_cellFullyLoadedEventSource;
extern BSTEventSource<TESCellReadyToApplyDecalsEvent>&	g_cellReadyToApplyDecalsEventSource;
extern BSTEventSource<TESCombatEvent>&					g_combatEventSource;
extern BSTEventSource<TESContainerChangedEvent>&		g_containerChangedEventSource;
extern BSTEventSource<TESDeathEvent>&					g_deathEventSource;
extern BSTEventSource<TESDestructionStageChangedEvent>&	g_destructionStageChangedEventSource;
extern BSTEventSource<TESEnterBleedoutEvent>&			g_enterBleedoutEventSource;
extern BSTEventSource<TESEquipEvent>&					g_equipEventSource;
extern BSTEventSource<TESFormDeleteEvent>&				g_formDeleteEventSource;
extern BSTEventSource<TESFurnitureEvent>&				g_furnitureEventSource;
extern BSTEventSource<TESGrabReleaseEvent>&				g_grabReleaseEventSource;
extern BSTEventSource<TESHitEvent>&						g_hitEventSource;
extern BSTEventSource<TESInitScriptEvent>&				g_initScriptEventSource;
extern BSTEventSource<TESLoadGameEvent>&				g_loadGameEventSource;
extern BSTEventSource<TESLockChangedEvent>&				g_lockChangedEventSource;
extern BSTEventSource<TESMagicEffectApplyEvent>&		g_magicEffectApplyEventSource;
extern BSTEventSource<TESMagicWardHitEvent>&			g_magicWardHitEventSource;
extern BSTEventSource<TESMoveAttachDetachEvent>&		g_moveAttachDetachEventSource;
extern BSTEventSource<TESObjectLoadedEvent>&			g_objectLoadedEventSource;
extern BSTEventSource<TESObjectREFRTranslationEvent>&	g_objectREFRTranslationEventSource;
extern BSTEventSource<TESOpenCloseEvent>&				g_openCloseEventSource;
extern BSTEventSource<TESPackageEvent>&					g_packageEventSource;
extern BSTEventSource<TESPerkEntryRunEvent>&			g_perkEntryRunEventSource;
extern BSTEventSource<TESQuestInitEvent>&				g_questInitEventSource;
extern BSTEventSource<TESQuestStageEvent>&				g_questStageEventSource;
extern BSTEventSource<TESQuestStageItemDoneEvent>&		g_questStageItemDoneEventSource;
extern BSTEventSource<TESQuestStartStopEvent>&			g_questStartStopEventSource;
extern BSTEventSource<TESResetEvent>&					g_resetEventSource;
extern BSTEventSource<TESResolveNPCTemplatesEvent>&		g_resolveNPCTemplatesEventSource;
extern BSTEventSource<TESSceneEvent>&					g_sceneEventSource;
extern BSTEventSource<TESSceneActionEvent>&				g_sceneActionEventSource;
extern BSTEventSource<TESScenePhaseEvent>&				g_scenePhaseEventSource;
extern BSTEventSource<TESSellEvent>&					g_sellEventSource;
extern BSTEventSource<TESSleepStartEvent>&				g_sleepStartEventSource;
extern BSTEventSource<TESSleepStopEvent>&				g_sleepStopEventSource;
extern BSTEventSource<TESSpellCastEvent>&				g_spellCastEventSource;
extern BSTEventSource<TESPlayerBowShotEvent>&			g_playerBowShotEventSource;
extern BSTEventSource<TESTopicInfoEvent>&				g_topicInfoEventSource;
extern BSTEventSource<TESTrackedStatsEvent>&			g_trackedStatsEventSource;
extern BSTEventSource<TESTrapHitEvent>&					g_trapHitEventSource;
extern BSTEventSource<TESTriggerEvent>&					g_triggerEventSource;
extern BSTEventSource<TESTriggerEnterEvent>&			g_triggerEnterEventSource;
extern BSTEventSource<TESTriggerLeaveEvent>&			g_triggerLeaveEventSource;
extern BSTEventSource<TESUniqueIDChangeEvent>&			g_uniqueIDChangeEventSource;
extern BSTEventSource<TESWaitStartEvent>&				g_waitStartEventSource;
extern BSTEventSource<TESWaitStopEvent>&				g_waitStopEventSource;
extern BSTEventSource<TESSwitchRaceCompleteEvent>&		g_switchRaceCompleteEventSource;

