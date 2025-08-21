class UExample_MMWidget : UMMWidget
{
	UFUNCTION(BlueprintOverride)
	void DrawWidget(float DeltaTime)
	{
		mm::BeginHorizontalBox();

			mm::VAlign_Center();
			mm::Text("Label Button", bBold=true);

			mm::Spacer(10, 0);

			mm::Button("Click!");

		mm::EndHorizontalBox();
	}
}