#include "skse/NiProperties.h"
#include "skse/NiControllers.h"

void NiProperty::Update(float time)
{
	NiTimeController *controller = m_controller;

	while (controller)
	{
		controller->Update(time);
		controller = (NiTimeController *)controller->next;
	}
}