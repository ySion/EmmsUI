#if EDITOR

/**
 * This is an example for an editor tab that has a button that opens a popup prompt to fill out properties for a struct.
 */
class UExample_ButtonWithPrompt : UMMEditorUtilityTab
{
	default TabTitle = "Example MM Button With Prompt";
	default Category = "Example Tabs";

	UFUNCTION(BlueprintOverride)
	void DrawTab(float DeltaTime)
	{
		// Draw a button in the editor tab to start the tool operation
		if (mm::Button("Start Operation"))
		{
			// This will prompt the user with a window to fill out the properties of a struct
			FEditorToolOperationSettings UserSettings;

			FScriptEditorPromptOptions PromptOptions;
			PromptOptions.OKButtonText = FText::FromString("Start Operation");
			PromptOptions.WindowTitle = FText::FromString("Editor Tool Operation");

			bool bProceed = EditorPrompt::ShowPromptForStruct(UserSettings, PromptOptions);

			// If the user cancelled the window, this will be false and we don't do the operation
			if (bProceed)
				PerformOperation(UserSettings);
		}
	}

	void PerformOperation(FEditorToolOperationSettings UserSettings)
	{
		// Here we can use the settings configured by the user in the struct
		// For now we just show a message box back to the user stating what they selected
		FString Message = "You selected these options:\n";
		Message += f"Name: {UserSettings.OperationName}\n";
		Message += f"Attachment Rule: {UserSettings.AttachmentRule}";

		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
	}
}

struct FEditorToolOperationSettings
{
	UPROPERTY()
	FString OperationName = "String Value";
	UPROPERTY()
	EAttachmentRule AttachmentRule = EAttachmentRule::KeepWorld;
}

#endif