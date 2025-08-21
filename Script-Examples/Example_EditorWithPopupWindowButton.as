/**
 * An example actor that opens an UMMPopupWindow when a CallInEditor button is clicked
 */
class AExample_ActorWithPopupWindowButton : AActor
{
	UFUNCTION(CallInEditor)
	void OpenImmediateWindow()
	{
		mm::SpawnPopupWindow(UExample_ActorMMPopupWindow);
	}
}

class UExample_ActorMMPopupWindow : UMMPopupWindow
{
	default WindowTitle = "Example Popup Window";
	default DefaultWindowSize = FVector2D(500, 200);

	UFUNCTION(BlueprintOverride)
	void DrawWindow(float DeltaTime)
	{
		mm::Text("This is a popup window opened from an actor");
		if (mm::Button("Test"))
			CloseWindow();
	}
}