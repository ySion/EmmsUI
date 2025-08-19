#pragma once
#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "Blueprint/UserWidget.h"
#include "EmmsWidgetHandle.h"
#include "EmmsWidgetElement.h"
#include "MMWidget.generated.h"

UCLASS(NotBlueprintable)
class EMMSUI_API UMMWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UMMWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
	UWidget* DisplayedRootWidget;

	TMap<FEmmsWidgetIdentifier, TArray<FEmmsWidgetElement*, TInlineAllocator<8>>> AvailableWidgets;
	TMap<FEmmsWidgetIdentifier, TArray<FEmmsWidgetElement*, TInlineAllocator<8>>> PendingWidgets;
	TMap<FEmmsAttributeSpecification*, FEmmsAttributeValue> PendingSlotAttributes;

	FEmmsWidgetElement* ActiveRootWidget = nullptr;
	FEmmsWidgetElement* PendingRootWidget = nullptr;

	TFunction<void(UMMWidget* Widget, float DeltaTime)> ExternalDrawFunction;

	bool bHasDrawnThisFrame = false;
	bool bLayoutChanged = false;
	uint64 LastDrawFrameCounter = 0;
	uint64 DrawCount = 0;

	// Whether to call a draw immediately upon the widget getting constructed
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MM Widget")
	bool bDrawOnConstruct = true;
	// Whether drawing the widget is allowed at the moment
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MM Widget")
	bool bAllowDraw = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MM Widget")
	TSubclassOf<UPanelWidget> DefaultRootPanel;

	static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);
	virtual void BeginDestroy() override;

	virtual void OnBeginDraw();
	virtual void OnEndDraw();
	virtual void OnRootWidgetChanged() {}

	void CallDraw(float DeltaTime);

	void UpdateWidgetTree();
	void UpdateWidgetAttributes(FEmmsWidgetElement* Widget);
	void UpdateWidgetHierarchy(FEmmsWidgetElement* Widget);
	void ResetPendingSlotAttributes();

	FEmmsWidgetHandle GetOrCreateRootWidget(
		TSubclassOf<UWidget> WidgetType
	);

	FEmmsWidgetHandle GetOrCreateChildWidget(
		TSubclassOf<UWidget> WidgetType,
		FEmmsWidgetHandle ParentWidget,
		uint32 HashIdent = 0);

	UWidget* GetRootUMGWidget();
	UWidget* CreateNewWidget(UClass* WidgetType);

	UFUNCTION(BlueprintImplementableEvent)
	void DrawWidget(float DeltaTime);

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	void TickDraw(float DeltaTime);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
};
