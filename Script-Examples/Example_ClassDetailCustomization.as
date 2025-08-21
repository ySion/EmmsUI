class AExampleActorWithDetailCustomization : AActor
{
	UPROPERTY(DefaultComponent)
	USceneComponent Root;
}

#if EDITOR
class UExampleActorDetailCustomization : UMMClassDetailCustomization
{
	default DetailClass = AExampleActorWithDetailCustomization;

	UMMWidget LabelledPropertyWidget;
	UMMWidget FullDetailRowWidget;
	
	bool bPropertyCheckboxValue = false;

	UFUNCTION(BlueprintOverride)
	void CustomizeDetails()
	{
		// Create a "property" row with a label to the left, and immediate widgets to the right
		LabelledPropertyWidget = AddImmediateProperty(n"Example Heading", "Labelled Property");
		
		// Create one full row filled with immediate widgets as well
		FullDetailRowWidget = AddImmediateRow(n"Example Heading");
	}

	UFUNCTION(BlueprintOverride)
	void Tick(float DeltaTime)
	{
		// Draw to the "property" row we created before
		mm::BeginDraw(LabelledPropertyWidget);

			// Add some text
			mm::Text("Toggling this checkbox will show a popup message:");

			// Add a checkbox with a label
			mm<UCheckBox> Checkbox = mm::CheckBox(bPropertyCheckboxValue, "Toggle");

			// If the check state was changed this frame, show a popup message
			if (Checkbox.WasCheckStateChanged())
			{
				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(f"Toggle state is now {bPropertyCheckboxValue}"));
			}

		mm::EndDraw();

		// Draw to the detail row we created before
		mm::BeginDraw(FullDetailRowWidget);

			mm::Spacer(10);

			// Add a black box with some text
			mm::HAlign_Center();
			mm::WithinBorder(FLinearColor::Black);
				mm::Padding(10, 4);
				mm::Text("We could add some explanation text to the details panel this way!");
				
			mm::Spacer(10);
			mm::Text("Alternatively, we can add some buttons as well:", bBold=true);

			// Add a horizontal box with some buttons in it
			mm::BeginHorizontalBox();
				if (mm::Button("Delete This Actor"))
					DeleteThisActor();
				if (mm::Button("Teleport Actor Somewhere Random"))
					TeleportActorRandomly();
			mm::EndHorizontalBox();
		mm::EndDraw();
	}

	void DeleteThisActor()
	{
		AActor Actor = Cast<AActor>(GetCustomizedObject());
		Actor.DestroyActor();
	}

	void TeleportActorRandomly()
	{
		AActor Actor = Cast<AActor>(GetCustomizedObject());
		Actor.SetActorLocation(
			Math::VRand() * 10000.0
		);
	}
}
#endif