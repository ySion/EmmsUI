class UExample_SubsystemWithViewportOverlay : UScriptEngineSubsystem
{
	UFUNCTION(BlueprintOverride)
	void Tick(float DeltaTime)
	{
		// Start drawing an overlay on top of the viewport in immediate mode
		mm::BeginDrawViewportOverlay(n"ExampleOverlay");
			
			// Draw a centered black box with rounded corners at the top of the viewport
			mm::HAlign_Center();
			mm::Padding(4);
			mm::WithinBorder(FLinearColor::Black, 10);

			// Within the black box, add a horizontal box with some buttons
			mm::Padding(4);
			mm::WithinSizeBox(MinHeight=40);
			mm::BeginHorizontalBox();

			// Text displayed in the horizontal box
			{
				mm::VAlign_Center();
				mm::Padding(20, 4);
				mm::Text("Some text to display");
			}

			// Some space between the text and the buttons
			{
				mm::Spacer(30, 0);
			}

			// The first button which logs a message when clicked
			{
				mm::Padding(4);
				if (mm::Button("Button One"))
				{
					Log("Button one clicked!");
				}
			}

			// The second button which logs a message when clicked
			{
				mm::Padding(4);
				if (mm::Button("Button Two"))
				{
					Log("Button two clicked!");
				}
			}

			mm::EndHorizontalBox();
		mm::EndDraw();
	}
}