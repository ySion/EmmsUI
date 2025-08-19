#pragma once
#include "CoreMinimal.h"
#include "EmmsWidgetHandle.generated.h"

USTRUCT()
struct EMMSUI_API FEmmsWidgetHandle
{
	GENERATED_BODY()

	class UMMWidget* WidgetTree = nullptr;
	struct FEmmsWidgetElement* Element = nullptr;
};

USTRUCT(BlueprintType)
struct EMMSUI_API FEmmsSlotHandle
{
	GENERATED_BODY()

	class UMMWidget* WidgetTree = nullptr;
	struct FEmmsWidgetElement* Element = nullptr;
};