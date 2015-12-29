#pragma once

#include "GameBSExtraData.h"
#include "GameReferences.h"
#include "GameAPI.h"
#include "GameObjects.h"

	//ExtraHavok
 //	ExtraCell3D
 //	ExtraCellWaterType
 //	ExtraRegionList
 //	ExtraSeenData

 // 0C
class ExtraEditorID : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_EditorID };

	ExtraEditorID(const char *str) { ctor(str); }
	virtual ~ExtraEditorID();					// 0040ED50

	// @override
	virtual UInt32	GetType(void) override;		// 00491870 { return kExtraTypeID; }

	// @members
	BSFixedString editorID;
private:
	EMBED_MEMBER_FN(ctor, ExtraEditorID*, 0x0040A2E0, const char *str);
};

 //	ExtraCellMusicType
 //	ExtraCellSkyRegion
 //	ExtraProcessMiddleLow
 //	ExtraDetachTime
class ExtraPersistentCell : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_PersistentCell };

	ExtraPersistentCell();
	virtual ~ExtraPersistentCell();

	TESObjectCELL* cell;
};
 //	ExtraAction
class ExtraStartingPosition : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_StartingPosition };
	UInt32		unk08;
	UInt32		unk0C;
	UInt32		unk10;
	UInt32		unk14;
	UInt32		unk18;
	UInt32		unk1C;
	UInt32		unk20;

	MEMBER_FN_PREFIX(ExtraStartingPosition);
	DEFINE_MEMBER_FN(ctor, void, 0x0040DC50, UInt32 unk);
};
STATIC_ASSERT(sizeof(ExtraStartingPosition) == 0x24);
//	ExtraAnimGraphManager
 //	ExtraUsedMarkers
 //	ExtraDistantData
 //	ExtraRagDollData
class ExtraHotkey;

class InventoryEntryData
{
public:
	struct EquipData
	{
		SInt32			itemCount;

		BaseExtraList*	itemExtraList;

		BaseExtraList*	wornExtraList;
		BaseExtraList*	wornLeftExtraList;

		bool			isItemWorn;
		bool			isItemWornLeft;
		bool			isTypeWorn;
		bool			isTypeWornLeft;

		EquipData();
	};

	InventoryEntryData(TESForm * item, UInt32 count);

	TESForm* type;
	ExtendDataList* extendDataList;
	SInt32 countDelta;

	// Heap allocated
	static InventoryEntryData * Create(TESForm * item, UInt32 count);
	void Delete(void);

	void GetExtraWornBaseLists(BaseExtraList ** pWornBaseListOut, BaseExtraList ** pWornLeftBaseListOut) const;
	void GetEquipItemData(EquipData& stateOut, SInt32 itemId, SInt32 baseCount) const;

	// himika -->
	template <class Op>
	void ForEach(Op op) {
		if (!extendDataList) {
			return;
		}
		ExtendDataList::Iterator it = extendDataList->Begin();
		while (!it.End()) {
			op(it.Get());
			++it;
		}
		return;
	}

	template <class Op>
	BaseExtraList* Find(Op op) {
		if (!extendDataList) {
			return NULL;
		}
		ExtendDataList::Iterator it = extendDataList->Begin();
		while (!it.End()) {
			BaseExtraList* ex = it.Get();
			if (op(ex)) {
				return ex;
			}
			++it;
		}
		return NULL;
	}
	// <-- himika

	MEMBER_FN_PREFIX(InventoryEntryData);
	DEFINE_MEMBER_FN(GenerateName, const char *, 0x00475AA0);
	DEFINE_MEMBER_FN(GetValue, SInt32, 0x00475450);
	DEFINE_MEMBER_FN(IsOwnedBy, bool, 0x00477010, TESForm * actor, bool unk1);	
};

typedef tList<InventoryEntryData> EntryDataList;

class ExtraContainerChanges : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_ContainerChanges };

	ExtraContainerChanges();
	virtual ~ExtraContainerChanges();	

	class Data
	{
	public:
		EntryDataList*	objList;
		TESObjectREFR*	owner;
		float			totalWeight;
		float			armorWeight;

		InventoryEntryData * FindItemEntry(TESForm * item) const;

		// Allocate new entry data as a merge between base container data and extra data
		// Uses BaseExtraList*'s from original extra data and combined count
		InventoryEntryData * CreateEquipEntryData(TESForm * item);

		void GetEquipItemData(InventoryEntryData::EquipData& stateOut, TESForm * item, SInt32 itemId) const;

		MEMBER_FN_PREFIX(Data);
		DEFINE_MEMBER_FN(SetUniqueID, void, 0x00482050, BaseExtraList* itemList, TESForm * oldForm, TESForm * newForm);
	};

	Data * data;

	struct FoundEquipData {
		TESForm* pForm;
		BaseExtraList* pExtraData;
	};

	struct FoundHotkeyData {
		TESForm* pForm;
		ExtraHotkey * pHotkey;
	};

	FoundEquipData	FindEquipped(FormMatcher& matcher, bool isWorn = true, bool isWornLeft = true) const;
	FoundHotkeyData	FindHotkey(SInt32 hotkey) const;
	FoundHotkeyData	FindHotkey(TESForm * form) const;
};
typedef ExtraContainerChanges::FoundEquipData EquipData;
typedef ExtraContainerChanges::FoundHotkeyData HotkeyData;
 
 class ExtraWorn : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Worn };

	ExtraWorn();
	virtual ~ExtraWorn();
};

class ExtraWornLeft : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_WornLeft };

	ExtraWornLeft();
	virtual ~ExtraWornLeft();
};
 //	ExtraPackageStartLocation
 //	ExtraPackage
 //	ExtraTresPassPackage
 //	ExtraRunOncePacks
class ExtraReferenceHandle : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_ReferenceHandle };

	ExtraReferenceHandle();
	virtual ~ExtraReferenceHandle();

	UInt32	handle;		// 08

	TESObjectREFR * GetReference();
	static ExtraReferenceHandle* Create();
};

class ExtraFollower : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Follower };

	ExtraFollower();
	virtual ~ExtraFollower();

	UInt32	unk08;		// 08
	UInt32	unk0C;		// 0C
	UInt32	followers;	// 10
};
 //	ExtraLevCreaModifier
 //	ExtraGhost
 //	ExtraOriginalReference
class ExtraOwnership : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Ownership };

	ExtraOwnership();
	virtual ~ExtraOwnership();

	TESForm* owner;
};
 //	ExtraGlobal
class ExtraRank : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Rank };

	ExtraRank();
	virtual ~ExtraRank();

	SInt32	rank;	// 08

	static ExtraRank* Create();
};


class ExtraCount : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Count };

	ExtraCount();
	virtual ~ExtraCount();

	UInt16 count;

	static ExtraCount* Create();
};
class ExtraHealth : public BSExtraData // Tempered
{
public:
	enum { kExtraTypeID = kExtraData_Health };

	ExtraHealth();
	virtual ~ExtraHealth();

	enum { // Multiplier
		kHealthBase = 1
	};

	float health;

	static ExtraHealth* Create();
};

class ExtraTimeLeft : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_TimeLeft };

	ExtraTimeLeft();
	virtual ~ExtraTimeLeft();

	float time;

	static ExtraTimeLeft* Create();
};

class ExtraCharge : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Charge };

	ExtraCharge();
	virtual ~ExtraCharge();

	float charge;

	static ExtraCharge* Create();
};
 //	ExtraLight
class ExtraLock : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Lock };

	ExtraLock();
	virtual ~ExtraLock();

	TESKey* unk;
};

 //	ExtraTeleport
 //	ExtraMapMarker
 //	ExtraLeveledCreature
 //	ExtraLeveledItem
class ExtraScale : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Scale };

	ExtraScale();
	virtual ~ExtraScale();

	float scale;
};
 //	ExtraSeed
 //	ExtraMagicCaster
 //	ExtraPlayerCrimeList
class ExtraEnableStateParent : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_EnableStateParent };

	ExtraEnableStateParent();
	virtual ~ExtraEnableStateParent();

	UInt32	unk08;	// 08
	UInt32	handle;	// 0C handle?

	TESObjectREFR * GetReference();
};
 //	ExtraEnableStateChildren
 //	ExtraItemDropper
 //	ExtraDroppedItemList
 //	ExtraRandomTeleportMarker
 //	ExtraSavedHavokData
class ExtraCannotWear : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_CannotWear };

	ExtraCannotWear();
	virtual ~ExtraCannotWear();

	UInt32	unk08;

	static ExtraCannotWear* Create();
};

class ExtraPoison : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Poison };

	ExtraPoison();
	virtual ~ExtraPoison();

	UInt32			unk08;		// 08
	AlchemyItem*	poison;		// 0C
};

 //	ExtraLastFinishedSequence
 //	ExtraSavedAnimation
 //	ExtraNorthRotation
 //	ExtraSpawnContainer
 //	ExtraFriendHits
 //	ExtraHeadingTarget
 //	ExtraRefractionProperty
 //	ExtraStartingWorldOrCell
class ExtraHotkey : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Hotkey };

	ExtraHotkey();
	virtual ~ExtraHotkey();

	SInt8	hotkey;	// 08 (1 to 8, -1 unbound)

	static ExtraHotkey* Create();
};
 //	ExtraEditiorRefMoveData
 //	ExtraInfoGeneralTopic
 //	ExtraHasNoRumors
 //	ExtraSound
 //	ExtraTerminalState
class ExtraLinkedRef : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_LinkedRef };

	ExtraLinkedRef();
	virtual ~ExtraLinkedRef();

	static ExtraLinkedRef* Create();

	enum
	{
		kLocalAlloc = 0x80000000,
	};
	struct Pair
	{
		BGSKeyword	* keyword;
		UInt32		  unk04;
	};

	UInt32		allocatedCount;	// 08
	union {
		Pair	* pairs;		// 0C
		Pair	singlePair;		// 0C - used when kLocalAlloc is set
	};
	UInt32		pairCount;		// 14
};
STATIC_ASSERT(sizeof(ExtraLinkedRef) == 0x18);

class ExtraLinkedRefChildren : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_LinkedRefChildren };

	ExtraLinkedRefChildren();
	virtual ~ExtraLinkedRefChildren();

	static ExtraLinkedRefChildren* Create();

	UInt32 unk08;
	UInt32 unk0C;
	UInt32 unk10;
	UInt32 unk14;
};
STATIC_ASSERT(sizeof(ExtraLinkedRefChildren) == 0x18);
 //	ExtraActivateRef
 //	ExtraActivateRefChildren
 //	ExtraCanTalkToPlayer
 //	ExtraObjectHealth
 //	ExtraCellImageSpace
 //	ExtraNavMeshPortal
 //	ExtraModelSwap
 //	ExtraRadius
struct ExtraFactionChanges : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_FactionChanges };

	ExtraFactionChanges();
	virtual ~ExtraFactionChanges();

	struct FactionInfo
	{
		TESFaction	* faction;	// 00
		SInt8		rank;		// 04
		UInt8		pad[3];		// 05
	};

	UInt32	unk08;
	tArray<FactionInfo> factions;
};
 //	ExtraDismemberedLimbs
 //	ExtraActorCause
 //	ExtraMultiBound
 //	ExtraMultiBoundData
 //	ExtraMultiBoundRef
 //	ExtraReflectedRefs
 //	ExtraReflectorRefs
 //	ExtraEmittanceSource
 //	ExtraRadioData
 //	ExtraCombatStyle
struct ExtraPrimitive : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Primitive };

	ExtraPrimitive();
	virtual ~ExtraPrimitive();

	BGSPrimitive	* primitive;
};
 //	ExtraOpenCloseActivateRef
 //	ExtraAnimNoteReceiver
 //	ExtraAmmo
 //	ExtraPatrolRefData
 //	ExtraPackageData
 //	ExtraOcclusionShape
struct ExtraCollisionData : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_CollisionData };

	ExtraCollisionData();
	virtual ~ExtraCollisionData();

	struct Data
	{
		UInt32	collisionLayer; // LayerId
	};

	Data	* data;
};
 //	ExtraSayTopicInfoOnceADay
struct ExtraEncounterZone : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_EncounterZone };

	ExtraEncounterZone();
	virtual ~ExtraEncounterZone();

	BGSEncounterZone* encounterZone;
};
 //	ExtraSayTopicInfo
 //	ExtraOcclusionPlaneRefData
 //	ExtraPortalRefData
 //	ExtraPortal
 //	ExtraRoom
 //	ExtraHealthPerc
 //	ExtraRoomRefData
 //	ExtraGuardedRefData
 //	ExtraCreatureAwakeSound
 //	ExtraHorse
 //	ExtraIgnoredBySandbox
 //	ExtraCellAcousticSpace
 //	ExtraReservedMarkers
 //	ExtraWeaponIdleSound
 //	ExtraWaterLightRefs
 //	ExtraWeaponAttackSound
 //	ExtraActivateLoopSound
 //	ExtraPatrolRefInUseData
class ExtraAshPileRef : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_AshPileRef };

	ExtraAshPileRef();
	virtual ~ExtraAshPileRef();

	UInt32	handle;	// 08

};

class ExtraFollowerSwimBreadcrumbs : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_FollowerSwimBreadcrumbs };

	ExtraFollowerSwimBreadcrumbs();
	virtual ~ExtraFollowerSwimBreadcrumbs();

	UInt32	unk08;
	float	unk0C; // Looks like a position?
	float	unk10;
	float	unk14;
};

class ExtraAliasInstanceArray : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_AliasInstanceArray };

	ExtraAliasInstanceArray();
	virtual ~ExtraAliasInstanceArray();

	struct AliasInfo
	{
		TESQuest		* quest;
		BGSBaseAlias	* alias;
		tArray<TESPackage*>	* packages;
	};

	tArray<AliasInfo*> aliases;	// 08
};

class ExtraLocation : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Location };

	ExtraLocation(); // Related to protected/essential
	~ExtraLocation();

	BGSLocation* location;
};
 //	ExtraLitWaterRefs
class ExtraLocationRefType : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_LocationRefType };

	ExtraLocationRefType();
	virtual ~ExtraLocationRefType();

	BGSLocationRefType* refType;
};

class ExtraPromotedRef : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_PromotedRef };

	ExtraPromotedRef();
	virtual ~ExtraPromotedRef();

	tArray<TESForm*> unk08;
};
 //	ExtraOutfitItem
 //	ExtraLeveledItemBase
class ExtraLightData : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_LightData };

	ExtraLightData();
	virtual ~ExtraLightData();

	float	unk08;
	UInt32	unk0C;
	UInt32	unk10;
	float	unk14;
	UInt8	unk18;
	UInt8	pad19[3];
};
 //	ExtraSceneData
 //	ExtraBadPosition
 //	ExtraHeadTrackingWeight
 //	ExtraFromAlias
 //	ExtraShouldWear
 //	ExtraFavorCost
 //	ExtraAttachedArrows3D
class ExtraTextDisplayData : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_TextDisplayData };

	ExtraTextDisplayData();
	virtual ~ExtraTextDisplayData();

	BSFixedString	name;				// 08
	BGSMessage		* message;			// 0C
	TESQuest		* owner;			// 10
	SInt32			unk14;				// 14 -1 default -2 explicit name?
	float			extraHealthValue;	// 18
	UInt16			unk1C;				// 1C
	UInt16			pad1E;				// 1E

	const char* GenerateName(TESForm * form, float extraHealthValue);

	static ExtraTextDisplayData* Create();

	MEMBER_FN_PREFIX(ExtraTextDisplayData);
	DEFINE_MEMBER_FN(SetName_Internal, void, 0x00423140, const char * name);	
	DEFINE_MEMBER_FN(GenerateName_Internal, const char*, 0x00428CA0, TESForm * form, float extraHealthValue);	
};
 //	ExtraAlphaCutoff
class ExtraEnchantment : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Enchantment };

	ExtraEnchantment();
	virtual ~ExtraEnchantment();

	EnchantmentItem*	enchant;		// 08
	UInt16				maxCharge;		// 0C
	UInt8				unk0E;			// 0E - usually 0
	UInt8				pad0F;			// 0F

	static ExtraEnchantment* Create();
};

class ExtraSoul : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Soul };

	ExtraSoul();
	virtual ~ExtraSoul();

	UInt32 count;

	static ExtraSoul* Create();
};

class ExtraForcedTarget : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_ForcedTarget };

	ExtraForcedTarget();
	virtual ~ExtraForcedTarget();

	UInt32	handle;	// 08

	static ExtraForcedTarget* Create();
	TESObjectREFR * GetReference();
};
STATIC_ASSERT(sizeof(ExtraForcedTarget) == 0x0C);

class ExtraUniqueID : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_UniqueID };

	ExtraUniqueID();
	virtual ~ExtraUniqueID();

	UInt32	ownerFormId;
	UInt16	uniqueId;
	UInt16	pad;

	static ExtraUniqueID* Create();
};
 //	ExtraUniqueID
 //	ExtraFlags
class ExtraFlags : public BSExtraData
{
public:
	enum { kExtraTypeID = kExtraData_Flags };

	ExtraFlags();
	virtual ~ExtraFlags();

	UInt32 flags;
};
 //	ExtraRefrPath
 //	ExtraDecalGroup
 //	ExtraLockList
 //	ExtraForcedLandingMarker
 //	ExtraLargeRefOwnerCells
 //	ExtraCelLWaterEnvMap
 //	ExtraCellGrassData
 //	ExtraTeleportName
 //	ExtraInteraction
 //	ExtraWaterData
 //	ExtraWaterCurrentZoneData
 //	ExtraAttachRef
 //	ExtraAttachRefChildren
 //	ExtraGroupConstraint
 //	ExtraScriptedAnimDependence
 //	ExtraCachedScale
 //	ExtraRaceData
 //	ExtraGIDBuffer
 //	ExtraMissingRefIDs
