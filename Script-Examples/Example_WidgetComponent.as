class AExample_WidgetComponent : AActor
{
	UPROPERTY(DefaultComponent)
	UWidgetComponent WidgetComponent;
	default WidgetComponent.WidgetClass = UMMWidget;

	UFUNCTION(BlueprintOverride)
	void Tick(float DeltaSeconds)
	{
		UMMWidget DisplayedWidget = Cast<UMMWidget>(WidgetComponent.GetWidget());
		mm::BeginDraw(DisplayedWidget);
			mm::Text("Text drawn to a Widget Component", Color=FLinearColor::Black);
		mm::EndDraw();
	}
}