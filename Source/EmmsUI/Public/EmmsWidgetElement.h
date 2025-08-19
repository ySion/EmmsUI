#pragma once
#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "EmmsWidgetHandle.h"
#include "EmmsAttribute.h"

struct EMMSUI_API FEmmsWidgetIdentifier
{
	TObjectPtr<UClass> WidgetType = nullptr;
	struct FEmmsWidgetElement* ParentIdent = nullptr;
	uint32 HashIdent = 0;

	bool operator==(const FEmmsWidgetIdentifier& Other) const
	{
		return WidgetType == Other.WidgetType
			&& ParentIdent == Other.ParentIdent
			&& HashIdent == Other.HashIdent
		;
	}

	friend uint32 GetTypeHash(const FEmmsWidgetIdentifier& Identifier)
	{
		return HashCombine(
			HashCombine(
				GetTypeHash(Identifier.WidgetType),
				GetTypeHash(Identifier.ParentIdent)
			),
			GetTypeHash(Identifier.HashIdent));
	}
};

struct FEmmsWidgetElement
{
	TObjectPtr<UWidget> UMGWidget = nullptr;
	TObjectPtr<UPanelSlot> UMGSlot = nullptr;
	FEmmsWidgetElement* Parent = nullptr;

	TArray<FEmmsWidgetElement*, TInlineAllocator<4>> ActiveChildren;
	TArray<FEmmsWidgetElement*, TInlineAllocator<4>> PendingChildren;
	TMap<FEmmsAttributeSpecification*, FEmmsAttributeState> Attributes;
	TMap<FEmmsAttributeSpecification*, FEmmsAttributeState> SlotAttributes;
	TMap<FEmmsAttributeSpecification*, FEmmsAttributeValue> DefaultChildSlotAttributes;
	TMap<FProperty*, TObjectPtr<class UEmmsEventListener>> EventListeners;

	bool bNeedUpdateChildren = false;

	~FEmmsWidgetElement();

	void AddReferencedObjects(FReferenceCollector& Collector);
};