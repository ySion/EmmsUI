#pragma once
#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "EmmsEventListener.generated.h"

UCLASS(NotBlueprintType)
class EMMSUI_API UEmmsEventListener : public UObject
{
	GENERATED_BODY()

public:

	static FName NAME_InterceptEvent;

	FDelegateProperty* DelegateProperty = nullptr;
	FMulticastDelegateProperty* EventProperty = nullptr;

	TWeakObjectPtr<class UMMWidget> MMWidget;

	UPROPERTY()
	UFunction* SignatureFunction = nullptr;

	void* TriggeredParameters = nullptr;
	uint64 TriggeredFrameCounter = 0;
	uint64 TriggerCount = 0;

	uint64 ConsumedTriggerCount = 0;
	uint64 LastConsumedTriggerFrameCounter = 0;
	uint64 LastConsumedTriggerDrawCount = 0;
	uint64 LastConsumeCalledFrameCounter = 0;

	bool bReturnsEventReply = false;
	FProperty* ReturnProperty = nullptr;

	bool ConsumeTriggered();

	TArray<FScriptDelegate> ActiveImmediateDelegates;
	TArray<FScriptDelegate> PendingImmediateDelegates;

	void UpdateEventListener(UObject* Container);
	void MoveToNewContainer(UObject* Container);

	static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);
	virtual void BeginDestroy() override;

#if WITH_ANGELSCRIPT_HAZE
	virtual void ProcessEvent(UFunction* Function, void* Parms, bool bIsRemote) override;
#else
	virtual void ProcessEvent(UFunction* Function, void* Parms) override;
#endif

	UFUNCTION()
	void InterceptEvent() {}
};