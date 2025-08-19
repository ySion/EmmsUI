#include "EmmsEventListener.h"
#include "Components/SlateWrapperTypes.h"
#include "MMWidget.h"

FName UEmmsEventListener::NAME_InterceptEvent("InterceptEvent");

#if WITH_ANGELSCRIPT_HAZE
void UEmmsEventListener::ProcessEvent(UFunction* Function, void* Parms, bool bIsRemote)
#else
void UEmmsEventListener::ProcessEvent(UFunction* Function, void* Parms)
#endif
{
	// Don't call anything, just store the event
	TriggeredFrameCounter = GFrameCounter;
	TriggerCount += 1;

	if (SignatureFunction->ParmsSize != 0)
	{
		if (TriggeredParameters == nullptr)
		{
			TriggeredParameters = FMemory::Malloc(
				SignatureFunction->ParmsSize,
				SignatureFunction->GetMinAlignment()
			);
			FMemory::Memzero(TriggeredParameters, SignatureFunction->ParmsSize);

			for (TFieldIterator<FProperty> It(SignatureFunction); It; ++It)
			{
				if (It->HasAnyPropertyFlags(CPF_Parm))
					It->InitializeValue_InContainer(TriggeredParameters);
			}
		}

		for (TFieldIterator<FProperty> It(SignatureFunction); It; ++It)
		{
			if (It->HasAnyPropertyFlags(CPF_Parm))
				It->CopyCompleteValue_InContainer(TriggeredParameters, Parms);
		}
	}

	// If we are actively listening using a WasTriggered call for events that return an FEventReply, consume the event
	if (bReturnsEventReply && LastConsumeCalledFrameCounter >= GFrameCounter - 2)
	{
		FEventReply* ReturnValue = ReturnProperty->ContainerPtrToValuePtr<FEventReply>(Parms);
		*ReturnValue = FEventReply(true);
	}

	// Call any immediate delegates we had bound as well
	for (const FScriptDelegate& Delegate : PendingImmediateDelegates)
	{
		Delegate.ProcessDelegate<UObject>(Parms);
	}

	for (const FScriptDelegate& Delegate : ActiveImmediateDelegates)
	{
		// Don't call delegate that were already pending twice
		if (PendingImmediateDelegates.Contains(Delegate))
			continue;
		Delegate.ProcessDelegate<UObject>(Parms);
	}
}

void UEmmsEventListener::MoveToNewContainer(UObject* Container)
{
	FScriptDelegate BindDelegate;
	BindDelegate.BindUFunction(this, UEmmsEventListener::NAME_InterceptEvent);

	if (DelegateProperty != nullptr)
	{
		DelegateProperty->SetValue_InContainer(
			Container,
			BindDelegate
		);
	}
	else if (EventProperty != nullptr)
	{
		EventProperty->AddDelegate(
			BindDelegate,
			Container
		);
	}
}

bool UEmmsEventListener::ConsumeTriggered()
{
	LastConsumeCalledFrameCounter = GFrameCounter;

	uint64 CurrentDrawCount = 0;
	if (MMWidget.IsValid())
		CurrentDrawCount = MMWidget->DrawCount;

	if (TriggerCount > ConsumedTriggerCount)
	{
		// We have a new trigger to consume
		ConsumedTriggerCount = TriggerCount;
		LastConsumedTriggerDrawCount = CurrentDrawCount;
		LastConsumedTriggerFrameCounter = GFrameCounter;
		return true;
	}
	else if (LastConsumedTriggerDrawCount == CurrentDrawCount)
	{
		// This trigger was consumed during the same draw cycle, so we should still return true
		return true;
	}
	else
	{
		// No new triggers
		return false;
	}
}

void UEmmsEventListener::UpdateEventListener(UObject* Container)
{
	// Swap pending and active lists for next frame
	TArray<FScriptDelegate> PrevDelegates = MoveTemp(ActiveImmediateDelegates);
	ActiveImmediateDelegates = MoveTemp(PendingImmediateDelegates);

	PrevDelegates.Reset();
	PendingImmediateDelegates = MoveTemp(PrevDelegates);
}

void UEmmsEventListener::AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector)
{
	Super::AddReferencedObjects(InThis, Collector);

	UEmmsEventListener* Listener = (UEmmsEventListener*)InThis;
	if (Listener->TriggeredParameters != nullptr)
		Collector.AddPropertyReferences(Listener->SignatureFunction, Listener->TriggeredParameters);
}

void UEmmsEventListener::BeginDestroy()
{
	if (TriggeredParameters != nullptr)
	{
		for (TFieldIterator<FProperty> It(SignatureFunction); It; ++It)
		{
			if (It->HasAnyPropertyFlags(CPF_Parm))
				It->DestroyValue_InContainer(TriggeredParameters);
		}

		FMemory::Free(TriggeredParameters);
		TriggeredParameters = nullptr;
	}

	Super::BeginDestroy();
}