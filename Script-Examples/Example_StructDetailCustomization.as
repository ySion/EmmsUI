/**
 * Example of a struct with a detail customization adding extra UI to the details panel.
 */

struct FExampleCustomizationStruct
{
	UPROPERTY()
	int Value = 0;
}

#if EDITOR
class UExampleScriptDetailCustomization : UMMScriptStructDetailCustomization
{
	default DetailStruct = FExampleCustomizationStruct;

	UMMWidget HeaderValueWidget;
	UMMWidget ChildRowWidget;

	UFUNCTION(BlueprintOverride)
	void CustomizeHeader()
	{
		DefaultNameContent();
		HeaderValueWidget = ImmediateValueContent();
	}

	UFUNCTION(BlueprintOverride)
	void CustomizeChildren()
	{
		AddAllPropertyChildRows();
		ChildRowWidget = AddImmediateChildRow();
	}

	UFUNCTION(BlueprintOverride)
	void Tick(float DeltaTime)
	{
		FExampleCustomizationStruct CurrentValue = GetStructValue(FExampleCustomizationStruct);

		// Put some extra buttons to increment the value in the header field
		{
			mm::BeginDraw(HeaderValueWidget);
			mm::BeginHorizontalBox();

				mm::VAlign_Center();
				if (mm::Button("-"))
				{
					CurrentValue.Value -= 1;
					SetStructValue(CurrentValue);
				}

				mm::Padding(5);
				mm::VAlign_Center();
				mm::Text(f"{CurrentValue.Value}", 15);

				mm::VAlign_Center();
				if (mm::Button("+"))
				{
					CurrentValue.Value += 1;
					SetStructValue(CurrentValue);
				}

			mm::EndHorizontalBox();
			mm::EndDraw();
		}

		// Draw an extra row below the struct properties
		{
			mm::BeginDraw(ChildRowWidget);
			if (CurrentValue.Value >= 0)
				mm::Text("Struct is positive!", Color = FLinearColor::Green);
			else
				mm::Text("Struct is negative!", Color = FLinearColor::Red);
			mm::EndDraw();
		}
	}
}
#endif

class AExampleActorWithCustomizedStruct : AActor
{
	UPROPERTY(EditAnywhere)
	FExampleCustomizationStruct CustomizedStruct;
}