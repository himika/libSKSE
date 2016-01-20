#include "GameReferences.h"
#include "GameObjects.h"
#include "GameForms.h"
#include "GameExtraData.h"
#include "GameRTTI.h"
#include "GameData.h"
#include "NiNodes.h"

const _CreateRefHandleByREFR	CreateRefHandleByREFR = (_CreateRefHandleByREFR)0x0065CC00;
const _LookupREFRByHandle		LookupREFRByHandle = (_LookupREFRByHandle)0x004A9180;
const _LookupREFRObjectByHandle		LookupREFRObjectByHandle = (_LookupREFRObjectByHandle)0x004951F0;

const UInt32 * g_invalidRefHandle = (UInt32*)0x01310630;

const _MoveRefrToPosition MoveRefrToPosition = (_MoveRefrToPosition)0x90C9F0;
const _PlaceAtMe_Native PlaceAtMe_Native = (_PlaceAtMe_Native)0x90D1D0;
const _AddItem_Native AddItem_Native = (_AddItem_Native)0x908120;

UInt32 GetOrCreateRefrHandle(TESObjectREFR* ref)
{
	if (ref == NULL)
		return *g_invalidRefHandle;

	ExtraReferenceHandle* xRefHandle = static_cast<ExtraReferenceHandle*>(ref->extraData.GetByType(kExtraData_ReferenceHandle));

	UInt32 result = xRefHandle != NULL ?
		xRefHandle->handle :
		*g_invalidRefHandle;

	if (result == *g_invalidRefHandle)
		result = ref->CreateRefHandle();

	return result;
}

UInt32 TESObjectREFR::CreateRefHandle(void)
{
	if (handleRefObject.GetRefCount() > 0)
	{
		UInt32 refHandle = 0;
		CreateRefHandleByREFR(&refHandle, this);
		return refHandle;
	}
	else
	{
		return *g_invalidRefHandle;
	}
}

TESForm * Actor::GetEquippedObject(bool abLeftHand)
{
	if(!processManager) 
		return NULL;

	if(abLeftHand)
		return processManager->equippedObject[ActorProcessManager::kEquippedHand_Left];
	else
		return processManager->equippedObject[ActorProcessManager::kEquippedHand_Right];

	return NULL;
}

TintMask * PlayerCharacter::GetOverlayTintMask(TintMask * original)
{
	SInt32 curIndex = -1;
	if(!overlayTintMasks)
		return NULL;

	TintMask * foundMask;
	for(UInt32 i = 0; i < tintMasks.count; i++)
	{
		tintMasks.GetNthItem(i, foundMask);
		if(foundMask == original) {
			curIndex = i;
			break;
		}
	}

	overlayTintMasks->GetNthItem(curIndex, foundMask);
	if(foundMask)
		return foundMask;

	return NULL;
}

void Actor::UpdateHairColor()
{
	TESNPC* npc = DYNAMIC_CAST(baseForm, TESForm, TESNPC);
	if(npc && npc->headData) {
		BGSColorForm * hairColor = npc->headData->hairColor; // Non-player actors won't have this
		if(hairColor) {
			NiColorA val;
			val.r = hairColor->color.red / 128.0;
			val.g = hairColor->color.green / 128.0;
			val.b = hairColor->color.blue / 128.0;
			NiColorA * color = &val;

			NiNode * model = GetNiRootNode(0);
			if(model) {
				UpdateModelHair(model, &color);
			}
		}
	}
}

bool Actor::IsRunning()
{
	return CALL_MEMBER_FN(this, IsRunning)();
}

void Actor::UpdateSkinColor()
{
	TESNPC* npc = DYNAMIC_CAST(baseForm, TESForm, TESNPC);
	if(npc) {
		NiColorA val;
		val.r = npc->color.red / 255.0;
		val.g = npc->color.green / 255.0;
		val.b = npc->color.blue / 255.0;
		NiColorA * color = &val;

		NiNode * thirdPerson = GetNiRootNode(0);
		NiNode * firstPerson = GetNiRootNode(1);
		if(thirdPerson) {
			UpdateModelSkin(thirdPerson, &color); // Update for 3rd Person
		}
		if(firstPerson) {
			UpdateModelSkin(firstPerson, &color); // Update for 1st Person
		}
	}
}

bool Actor::VisitFactions(FactionVisitor & visitor)
{
	TESNPC* npc = DYNAMIC_CAST(baseForm, TESForm, TESNPC);
	if(npc) {
		for(UInt32 i = 0; i < npc->actorData.factions.count; i++)
		{
			TESActorBaseData::FactionInfo info;
			npc->actorData.factions.GetNthItem(i, info);
			if(visitor.Accept(info.faction, info.rank))
				return true;
		}

		ExtraFactionChanges* pFactionChanges = static_cast<ExtraFactionChanges*>(extraData.GetByType(kExtraData_FactionChanges));
		if (pFactionChanges) {
			for(UInt32 i = 0; i < pFactionChanges->factions.count; i++)
			{
				ExtraFactionChanges::FactionInfo info;
				pFactionChanges->factions.GetNthItem(i, info);
				if(visitor.Accept(info.faction, info.rank))
					return true;
			}
		}
	}

	return false;
}

// ==== (himika) ====
void TESObjectREFR::BlockActivation(bool bBlocked)
{
	extraData.BlockActivation(bBlocked);
}

void TESObjectREFR::ClearDestruction(void)
{
	typedef void (*_ClearDestruction)(TESObjectREFR* ref);
	const static _ClearDestruction fnClearDestruction = (_ClearDestruction)0x00449630;

	fnClearDestruction(this);
}

void TESObjectREFR::CreateDetectionEvent(Actor* owner, UInt32 soundLevel)
{
	if (owner && owner->processManager)
	{
		CALL_MEMBER_FN(owner->processManager, CreateDetectionEvent)(owner, &this->pos, soundLevel, this);
	}
}

TESNPC* TESObjectREFR::GetActorOwner(void)
{
	ExtraOwnership* exOwnership = extraData.GetByType<ExtraOwnership>();
	if (exOwnership && exOwnership->owner)
	{
		TESNPC* owner = static_cast<TESNPC*>(exOwnership->owner);
		if (owner->formType == kFormType_NPC)
			return owner;
	}
	return NULL;
}

bool Actor::HasLOS(TESObjectREFR* target)
{
	typedef bool (*_HasLOS)(Actor* viewer, TESObjectREFR* target, bool& result);
	const _HasLOS fnHasLos = (_HasLOS)0x008C0FA0;

	bool result = false;
	if (fnHasLos(this, target, result))
	{
		return result;
	}

	return false;
}

TESObjectREFR* BGSRefAlias::GetReference(void)
{
	UInt32 handle = 0;
	TESObjectREFR* ref = NULL;

	if (owner == NULL)
		return NULL;
	
	CALL_MEMBER_FN(owner, CreateRefHandleByAliasID)(&handle, aliasId);
	if (handle != *g_invalidRefHandle)
	{
		if (!LookupREFRByHandle(&handle, &ref))
		{
			ref = NULL;
		}
	}

	return ref;
}

Actor* BGSRefAlias::GetActorReference(void)
{
	TESObjectREFR* actor = this->GetReference();

	if (actor == NULL || actor->formType != kFormType_Character)
		actor = NULL;

	return (Actor*)actor;
}
