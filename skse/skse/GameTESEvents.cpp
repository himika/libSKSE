#include "GameTESEvents.h"

TESEventSourceHolder* TESEventSourceHolder::GetSingleton(void)
{
	// g_skyrimVM (0x012E568C) - 0x0A5C
	return (TESEventSourceHolder*)0x012E4C30;
}

BSTEventSource<TESActivateEvent>&					g_activateEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESActivateEvent>();
BSTEventSource<TESActiveEffectApplyRemoveEvent>&	g_activeEffectApplyRemoveEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESActiveEffectApplyRemoveEvent>();
BSTEventSource<TESActorLocationChangeEvent>&		g_actorLocationChangeEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESActorLocationChangeEvent>();
BSTEventSource<TESBookReadEvent>&					g_bookReadEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESBookReadEvent>();
BSTEventSource<TESCellAttachDetachEvent>&			g_cellAttachDetachEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESCellAttachDetachEvent>();
BSTEventSource<TESCellFullyLoadedEvent>&			g_cellFullyLoadedEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESCellFullyLoadedEvent>();
BSTEventSource<TESCellReadyToApplyDecalsEvent>&		g_cellReadyToApplyDecalsEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESCellReadyToApplyDecalsEvent>();
BSTEventSource<TESCombatEvent>&						g_combatEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESCombatEvent>();
BSTEventSource<TESContainerChangedEvent>&			g_containerChangedEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESContainerChangedEvent>();
BSTEventSource<TESDeathEvent>&						g_deathEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESDeathEvent>();
BSTEventSource<TESDestructionStageChangedEvent>&	g_destructionStageChangedEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESDestructionStageChangedEvent>();
BSTEventSource<TESEnterBleedoutEvent>&				g_enterBleedoutEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESEnterBleedoutEvent>();
BSTEventSource<TESEquipEvent>&						g_equipEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESEquipEvent>();
BSTEventSource<TESFormDeleteEvent>&					g_formDeleteEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESFormDeleteEvent>();
BSTEventSource<TESFurnitureEvent>&					g_furnitureEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESFurnitureEvent>();
BSTEventSource<TESGrabReleaseEvent>&				g_grabReleaseEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESGrabReleaseEvent>();
BSTEventSource<TESHitEvent>&						g_hitEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESHitEvent>();
BSTEventSource<TESInitScriptEvent>&					g_initScriptEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESInitScriptEvent>();
BSTEventSource<TESLoadGameEvent>&					g_loadGameEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESLoadGameEvent>();
BSTEventSource<TESLockChangedEvent>&				g_lockChangedEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESLockChangedEvent>();
BSTEventSource<TESMagicEffectApplyEvent>&			g_magicEffectApplyEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESMagicEffectApplyEvent>();
BSTEventSource<TESMagicWardHitEvent>&				g_magicWardHitEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESMagicWardHitEvent>();
BSTEventSource<TESMoveAttachDetachEvent>&			g_moveAttachDetachEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESMoveAttachDetachEvent>();
BSTEventSource<TESObjectLoadedEvent>&				g_objectLoadedEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESObjectLoadedEvent>();
BSTEventSource<TESObjectREFRTranslationEvent>&		g_objectREFRTranslationEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESObjectREFRTranslationEvent>();
BSTEventSource<TESOpenCloseEvent>&					g_openCloseEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESOpenCloseEvent>();
BSTEventSource<TESPackageEvent>&					g_packageEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESPackageEvent>();
BSTEventSource<TESPerkEntryRunEvent>&				g_perkEntryRunEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESPerkEntryRunEvent>();
BSTEventSource<TESQuestInitEvent>&					g_questInitEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESQuestInitEvent>();
BSTEventSource<TESQuestStageEvent>&					g_questStageEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESQuestStageEvent>();
BSTEventSource<TESQuestStageItemDoneEvent>&			g_questStageItemDoneEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESQuestStageItemDoneEvent>();
BSTEventSource<TESQuestStartStopEvent>&				g_questStartStopEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESQuestStartStopEvent>();
BSTEventSource<TESResetEvent>&						g_resetEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESResetEvent>();
BSTEventSource<TESResolveNPCTemplatesEvent>&		g_resolveNPCTemplatesEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESResolveNPCTemplatesEvent>();
BSTEventSource<TESSceneEvent>&						g_sceneEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESSceneEvent>();
BSTEventSource<TESSceneActionEvent>&				g_sceneActionEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESSceneActionEvent>();
BSTEventSource<TESScenePhaseEvent>&					g_scenePhaseEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESScenePhaseEvent>();
BSTEventSource<TESSellEvent>&						g_sellEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESSellEvent>();
BSTEventSource<TESSleepStartEvent>&					g_sleepStartEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESSleepStartEvent>();
BSTEventSource<TESSleepStopEvent>&					g_sleepStopEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESSleepStopEvent>();
BSTEventSource<TESSpellCastEvent>&					g_spellCastEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESSpellCastEvent>();
BSTEventSource<TESPlayerBowShotEvent>&				g_playerBowShotEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESPlayerBowShotEvent>();
BSTEventSource<TESTopicInfoEvent>&					g_topicInfoEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESTopicInfoEvent>();
BSTEventSource<TESTrackedStatsEvent>&				g_trackedStatsEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESTrackedStatsEvent>();
BSTEventSource<TESTrapHitEvent>&					g_trapHitEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESTrapHitEvent>();
BSTEventSource<TESTriggerEvent>&					g_triggerEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESTriggerEvent>();
BSTEventSource<TESTriggerEnterEvent>&				g_triggerEnterEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESTriggerEnterEvent>();
BSTEventSource<TESTriggerLeaveEvent>&				g_triggerLeaveEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESTriggerLeaveEvent>();
BSTEventSource<TESUniqueIDChangeEvent>&				g_uniqueIDChangeEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESUniqueIDChangeEvent>();
BSTEventSource<TESWaitStartEvent>&					g_waitStartEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESWaitStartEvent>();
BSTEventSource<TESWaitStopEvent>&					g_waitStopEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESWaitStopEvent>();
BSTEventSource<TESSwitchRaceCompleteEvent>&			g_switchRaceCompleteEventSource = *TESEventSourceHolder::GetSingleton()->GetEventSource<TESSwitchRaceCompleteEvent>();

