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
			lhs->unk120				= rhs->unk120;
		}
		break;

		default:
			// unsupported
			break;
	}
}

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
			if(childForm) {
				if(visitor.Accept(childForm))
					return true;
			}
		}
	}

	return false;
}


// ==== (himika) ====

#include "GameReferences.h"

UInt32 TESForm::GetGoldValue()
{
	typedef UInt32 (*_GetGoldValue)(TESForm* akForm);
	const static _GetGoldValue fnGetGoldValue = (_GetGoldValue)0x00457DA0;

	TESObjectREFR* ref = this->GetObjectREFR();
	return fnGetGoldValue(ref ? ref->baseForm : this);
}


bool TESQuest::IsRunning() const
{
	return ((unk07C.flags & 1) != 0 && ((unk07C.flags >> 7) & 1) == 0 && unk148 == 0);
}

BGSBaseAlias* TESQuest::GetAlias(UInt32 iAliasID)
{
	UInt32 i;
	BGSBaseAlias* alias = NULL;
	while (aliases.GetNthItem(i++, alias)) {
		if (alias->aliasId == iAliasID)
			return alias;
	}
	return NULL;
}
