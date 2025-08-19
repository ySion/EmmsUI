#include "EmmsWidgetElement.h"
#include "Components/PanelWidget.h"
#include "EmmsEventListener.h"

FEmmsWidgetElement::~FEmmsWidgetElement()
{
	for (auto& AttribElem : Attributes)
		AttribElem.Value.Reset(AttribElem.Key);

	for (auto& AttribElem : SlotAttributes)
		AttribElem.Value.Reset(AttribElem.Key);

	for (auto& AttribElem : DefaultChildSlotAttributes)
		AttribElem.Key->ResetValue(AttribElem.Value);
}

void FEmmsWidgetElement::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(UMGWidget);
	Collector.AddReferencedObject(UMGSlot);

	for (auto& AttribElem : Attributes)
	{
		if (AttribElem.Key->bHasObjectReferences)
			AttribElem.Value.AddReferencedObjects(AttribElem.Key, Collector);
	}

	for (auto& AttribElem : SlotAttributes)
	{
		if (AttribElem.Key->bHasObjectReferences)
			AttribElem.Value.AddReferencedObjects(AttribElem.Key, Collector);
	}

	for (auto& AttribElem : DefaultChildSlotAttributes)
	{
		if (AttribElem.Key->bHasObjectReferences)
			AttribElem.Key->AddReferencedObjects(Collector, AttribElem.Value);
	}

	for (auto& ListenerElem : EventListeners)
		Collector.AddReferencedObject(ListenerElem.Value);
}
