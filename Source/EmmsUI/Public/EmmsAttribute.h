#pragma once
#include "CoreMinimal.h"
#include "AngelscriptType.h"
#include "EmmsWidgetHandle.h"

enum class EEmmsAttributeType
{
	Property,
};

struct EMMSUI_API FEmmsAttributeValue
{
private:
	friend struct FEmmsAttributeSpecification;
	TArray<uint8, TInlineAllocator<8>> Data;

public:
	void* GetDataPtr() const
	{
		return (void*)Data.GetData();
	}

	bool IsEmpty() const
	{
		return Data.IsEmpty();
	}
};

struct EMMSUI_API FEmmsAttributeSpecification
{
	static TMap<FProperty*, FEmmsAttributeSpecification*> AttributeSpecsByProperty;
	static TMap<TPair<FName, UClass*>, FEmmsAttributeSpecification*> SlotAttributeSpecs;
	static TMap<FEmmsAttributeSpecification*, FEmmsAttributeSpecification*> SlotAttributeGenericSpecs;

	EEmmsAttributeType Type = EEmmsAttributeType::Property;
	FAngelscriptTypeUsage ScriptUsage;
	FProperty* AttributeProperty = nullptr;
	bool bRequiresWidgetRebuild = false;
	bool bHasObjectReferences = false;

	TFunction<void(FEmmsAttributeSpecification* Spec, void* Container, void* Value)> AssignValueFunction;
	TFunction<void(FEmmsAttributeSpecification* Spec, void* Container)> ResetToDefaultFunction;

	void* GetRawValuePtr(void* Container) const;

	FName GetAttributeName() const;
	bool IsCompatibleWithContainer(UObject* Object) const;
	void InitializeValue(FEmmsAttributeValue& Value) const;
	void ResetValue(FEmmsAttributeValue& Value) const;
	void AssignValue(FEmmsAttributeValue& Value, void* DataPtr) const;

	void AddReferencedObjects(FReferenceCollector& Collector, FEmmsAttributeValue& Value);
};

struct EMMSUI_API FEmmsAttributeState
{
	FEmmsAttributeValue DefaultValue;
	FEmmsAttributeValue CurrentValue;
	FEmmsAttributeValue PendingValue;
	FEmmsAttributeValue MirroredValue;

	void SetPendingValue(FEmmsAttributeSpecification* Spec, void* Value);
	bool Update(FEmmsAttributeSpecification* Spec, void* Container);
	void Reset(FEmmsAttributeSpecification* Spec);
	void MovePendingToNewContainer(FEmmsAttributeSpecification* Spec);
	void ApplyCurrentToNewContainer(FEmmsAttributeSpecification* Spec, void* Container);
	void UpdateMirroredValue(FEmmsAttributeSpecification* Spec, void* Container);

	void AddReferencedObjects(FEmmsAttributeSpecification* Spec, FReferenceCollector& Collector);
};