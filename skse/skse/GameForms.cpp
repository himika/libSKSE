#include "GameForms.h"
#include "GameObjects.h"

const _LookupFormByID LookupFormByID = (_LookupFormByID)0x00451A30;

BGSDefaultObjectManager *	BGSDefaultObjectManager::GetSingleton(void)
{
	return (BGSDefaultObjectManager *)0x012E2500;
}

void TESForm::CopyFromEx(TESForm * rhsForm)
{
	if(!rhsForm || rhsForm->formType != formType)
		return;

	switch(formType)
	{
		case kFormType_CombatStyle:
		{
			TESCombatStyle	* lhs = (TESCombatStyle *)this;
			TESCombatStyle	* rhs = (TESCombatStyle *)rhsForm;

			lhs->general =				rhs->general;
			lhs->melee =				rhs->melee;
			lhs->closeRange =			rhs->closeRange;
			lhs->longRange =			rhs->longRange;
			lhs->flight =				rhs->flight;
			lhs->flags =				rhs->flags;
		}
		break;

		// Untested, probably shouldn't use this
		case kFormType_Armor:
		{
			TESObjectARMO	* lhs = (TESObjectARMO*)this;
			TESObjectARMO	* rhs = (TESObjectARMO*)rhsForm;

			lhs->fullName.CopyFromBase(&rhs->fullName);
			lhs->race.CopyFromBase(&rhs->race);
			lhs->enchantable.CopyFromBase(&rhs->enchantable);
			lhs->value.CopyFromBase(&rhs->value);
			lhs->weight.CopyFromBase(&rhs->weight);
			lhs->destructible.CopyFromBase(&rhs->destructible);
			lhs->pickupSounds.CopyFromBase(&rhs->pickupSounds);
			lhs->bipedModel.CopyFromBase(&rhs->bipedModel);
			lhs->equipType.CopyFromBase(&rhs->equipType);
			lhs->bipedObject.CopyFromBase(&rhs->bipedObject);
			lhs->blockBash.CopyFromBase(&rhs->blockBash);
			lhs->keyword.CopyFromBase(&rhs->keyword);
			lhs->description.CopyFromBase(&rhs->description);

			lhs->armorValTimes100	= rhs->armorValTimes100;
			lhs->armorAddons.CopyFrom(&rhs->armorAddons);
			lhs->templateArmor = rhs->templateArmor;
		}
		break;

		default:
			// unsupported
			break;
	}
}

const _GetFormWeight GetFormWeight = (_GetFormWeight)0x00457EC0;

UInt32 BGSListForm::GetSize()
{
	UInt32 totalSize = forms.count;
	if(addedForms) {
		totalSize += addedForms->count;
	}

	return totalSize;
}

bool BGSListForm::Visit(BGSListForm::Visitor & visitor)
{
	// Base Added Forms
	for(UInt32 i = 0; i < forms.count; i++)
	{
		TESForm* childForm = NULL;
		if(forms.GetNthItem(i, childForm))
		{
			if(visitor.Accept(childForm))
				return true;
		}
	}

	// Script Added Forms
	if(addedForms) {
		for(int i = 0; i < addedForms->count; i++) {
			UInt32 formid = 0;
			addedForms->GetNthItem(i, formid);
			TESForm* childForm = LookupFormByID(formid);
			if(visitor.Accept(childForm))
				return true;
		}
	}

	return false;
}

// 005DEFA0 - 1.9.32
bool TESPackage::IsExtraType()
{
	switch(type)
	{
	case kPackageType_Activate:
	case kPackageType_Alarm:
	case kPackageType_Flee:
	case kPackageType_Trespass:
	case kPackageType_Spectator:
	case kPackageType_ReactToDead:
	case kPackageType_DoNothing:
	case kPackageType_InGameDialogue:
	case kPackageType_Surface:
	case kPackageType_AvoidPlayer:
	case kPackageType_ReactToDestroyedObject:
	case kPackageType_ReactToGrenadeOrMine:
	case kPackageType_StealWarning:
	case kPackageType_PickPocketWarning:
	case kPackageType_MovementBlocked:
	case kPackageType_Unk37:
	case kPackageType_Unk38:
		return true;
		break;
	}

	return false;
}
// ==== (himika) ====

#include "GameReferences.h"
#include "GameRTTI.h"

UInt32 TESForm::GetGoldValue()
{
	typedef UInt32 (*_GetGoldValue)(TESForm* akForm);
	const static _GetGoldValue fnGetGoldValue = (_GetGoldValue)0x00457DA0;

	TESObjectREFR* ref = this->GetObjectREFR();
	return fnGetGoldValue(ref ? ref->baseForm : this);
}


bool TESForm::HasKeyword(BGSKeyword* keyword)	// 008FCCA0
{
	BGSKeywordForm* keywordForm = NULL;

	switch (this->formType)
	{
	case kFormType_EffectSetting:
		keywordForm = &((EffectSetting*)this)->keywordForm;
		break;
	case kFormType_NPC:
		keywordForm = &((TESActorBase*)this)->keyword;
		break;
	case kFormType_Race:
		keywordForm = &((TESRace*)this)->keyword;
		break;
	case kFormType_Armor:
		keywordForm = &((TESObjectARMO*)this)->keyword;
		break;
	case kFormType_Weapon:
		keywordForm = &((TESObjectWEAP*)this)->keyword;
		break;
	case kFormType_Location:
		keywordForm = &((BGSLocation*)this)->keyword;
		break;
	case kFormType_Activator:
	case kFormType_TalkingActivator:
	case kFormType_Flora:
	case kFormType_Furniture:
		keywordForm = &((TESObjectACTI*)this)->keyword;
		break;
	case kFormType_Enchantment:
	case kFormType_Spell:
	case kFormType_ScrollItem:
	case kFormType_Ingredient:
	case kFormType_Potion:
		keywordForm = &((MagicItem*)this)->keyword;
		break;
	case kFormType_Misc:
	case kFormType_Apparatus:
	case kFormType_Key:
	case kFormType_SoulGem:
		keywordForm = &((TESObjectMISC*)this)->keyword;
		break;
	case kFormType_Ammo:
		keywordForm = &((TESAmmo*)this)->keyword;
		break;
	case kFormType_Book:
		keywordForm = &((TESObjectBOOK*)this)->keyword;
		break;
	default:
		// keywordForm = (BGSKeywordForm*)DYNAMIC_CAST(this, TESForm, BGSKeywordForm);
		break;
	}
	if (keywordForm)
	{
		return keywordForm->HasKeyword(keyword);
	}

	TESObjectREFR* ref = this->GetObjectREFR();
	if (ref)
	{
		return ref->HasKeyword(keyword);
	}

	return false;
}


bool TESQuest::IsRunning() const
{
	return ((unk07C.flags & 1) != 0 && ((unk07C.flags >> 7) & 1) == 0 && unk148 == 0);
}

BGSBaseAlias* TESQuest::GetAlias(UInt32 iAliasID)
{
	UInt32 i=0;
	BGSBaseAlias* alias = NULL;
	while (aliases.GetNthItem(i++, alias)) {
		if (alias->aliasId == iAliasID)
			return alias;
	}
	return NULL;
}

void BGSScene::ForceStart(void)
{
	if (GetOwningQuest()->IsRunning())
		CALL_MEMBER_FN(this, ForceStart)();
}

void BGSScene::Start(void)
{
	if (GetOwningQuest()->IsRunning())
		CALL_MEMBER_FN(this, Start)(1);
}

void BGSScene::Stop(void)
{
	CALL_MEMBER_FN(this, Start)(0);
}
