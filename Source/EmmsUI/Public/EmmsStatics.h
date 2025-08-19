#pragma once
#include "EmmsWidgetElement.h"
#include "MMWidget.h"
#include "EmmsAttribute.h"
#include "EmmsStatics.generated.h"

UCLASS(Meta = (ScriptName = "mm"))
class EMMSUI_API UEmmsStatics : public UObject
{
	GENERATED_BODY()

public:

	static UWorld* GetWorldForUI(const UObject* WorldContext);

	struct FImplicitHierarchyPanel
	{
		FEmmsWidgetElement* Element = nullptr;
		bool bIsScope = true;

		FImplicitHierarchyPanel(FEmmsWidgetElement* InElement, bool InIsScope = true)
			: Element(InElement), bIsScope(InIsScope)
		{}
	};

	struct FImplicitHierarchy
	{
		UMMWidget* Root = nullptr;
		TArray<FImplicitHierarchyPanel> ActiveWidgets;

		UPanelWidget* GetCurrentPanel();
		FEmmsWidgetElement* GetCurrentElement();
	};

	static TArray<FImplicitHierarchy> ImplicitHierarchy;

	static void ConstructHandle(FEmmsWidgetHandle* Handle);
	static void CopyConstructHandle(FEmmsWidgetHandle* Handle, FEmmsWidgetHandle* OtherHandle);
	static FEmmsWidgetHandle* AssignHandle(FEmmsWidgetHandle* Handle, FEmmsWidgetHandle* OtherHandle);

	static UWidget* GetUnderlyingWidget(FEmmsWidgetHandle* Handle);
	static UPanelSlot* GetUnderlyingSlot(FEmmsWidgetHandle* Handle);
	static FEmmsSlotHandle GetSlot(FEmmsWidgetHandle* Handle);

	static FEmmsWidgetHandle AddChildWidget(FEmmsWidgetHandle* Parent, const TSubclassOf<UWidget>& WidgetType);
	static FEmmsWidgetHandle AddExistingChildWidget(FEmmsWidgetHandle* Parent, FEmmsWidgetHandle* Child);

	static void SetAttributeValue(FEmmsWidgetHandle* Widget, class asCScriptFunction* ScriptFunction, void* Value);
	static void SetSlotAttributeValue(FEmmsSlotHandle* SlotHandle, class asCScriptFunction* ScriptFunction, void* Value);
	static void SetDefaultChildSlotAttributeValue(FEmmsWidgetHandle Widget, FEmmsAttributeSpecification* Spec, void* Value);
	static void* GetAttributeValue(FEmmsWidgetHandle* Widget, class asCScriptFunction* ScriptFunction);
	static FEmmsAttributeValue* GetPartialPendingAttribute(FEmmsWidgetHandle Widget, FEmmsAttributeSpecification* Spec);
	static FEmmsAttributeValue* GetPartialPendingSlotAttribute(FEmmsWidgetHandle Widget, FEmmsAttributeSpecification* Spec);

	static void SetImplicitPendingSlotAttribute(class asCScriptFunction* ScriptFunction, void* Value);
	static FEmmsAttributeValue* GetPartialImplicitPendingSlotAttribute(FEmmsAttributeSpecification* Spec);

	static void BeginDraw_DefaultRoot(UMMWidget* Widget);
	static FEmmsWidgetHandle BeginDraw(UMMWidget* Widget, const TSubclassOf<UPanelWidget>& RootPanel);
	static FEmmsWidgetHandle BeginDrawViewportOverlay(const UObject* WorldContext, const FName& OverlayId, int OverlayZOrder, const TSubclassOf<UPanelWidget>& RootPanel);
	static void EndDraw();

	static FEmmsWidgetHandle BeginWidget(const TSubclassOf<UPanelWidget>& PanelType);
	static FEmmsWidgetHandle BeginExistingWidget(const FEmmsWidgetHandle& PanelWidget);
	static void EndWidget();

	static FEmmsWidgetHandle BeginPanelWidget(class asCScriptFunction* ScriptFunction);
	static void EndPanelWidget(class asCScriptFunction* ScriptFunction);

	static FEmmsWidgetHandle WithinWidget(const TSubclassOf<UPanelWidget>& PanelType);
	static FEmmsWidgetHandle WithinPanelWidget(class asCScriptFunction* ScriptFunction);

	static FEmmsWidgetHandle AddWidget(const TSubclassOf<UWidget>& WidgetType);

	static UEmmsEventListener* GetOrCreateEventListener(FEmmsWidgetHandle* Handle, FProperty* Property);
	static bool WasEventTriggered(FEmmsWidgetHandle* Handle, class asCScriptFunction* ScriptFunction);
	static void WasEventTriggered_Params(class asIScriptGeneric* Generic);
	static void BindToEvent(FEmmsWidgetHandle* Handle, class asCScriptFunction* ScriptFunction, UObject* Object, const FName& FunctionName);

	UFUNCTION(ScriptCallable, Meta = (WorldContext = "WorldContext", OptionalWorldContext, DeterminesOutputType = "WindowClass"))
	static class UMMPopupWindow* SpawnPopupWindow(const UObject* WorldContext, const TSubclassOf<UMMPopupWindow>& WindowClass);

	/**
	 * Asynchronously load an asset by its path.
	 * OBS! This WILL return nullptr every time it's called UNTIL the asset has finished loading!
	 */
	UFUNCTION(ScriptCallable, Meta = (WorldContext = "WorldContext", OptionalWorldContext, DeterminesOutputType = "AssetType"))
	static UObject* AsyncLoadAsset(const UObject* WorldContext, const TSubclassOf<UObject>& AssetType, const FString& AssetPath);
};