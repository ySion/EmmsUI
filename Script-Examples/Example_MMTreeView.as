#if EDITOR

class UExample_MMTreeView : UMMEditorUtilityTab
{
	default TabTitle = "Example MM Tree View";
	default Category = "Example Tabs";
	default Icon = n"ClassIcon.Actor";

	TArray<UExampleMMTreeViewItem> ExampleItems;

	UFUNCTION(BlueprintOverride)
	void DrawTab(float DeltaTime)
	{
		// Create a tree view and set the root items to show
		mm<UTreeView> TreeView = mm::Widget(UTreeView);
		TreeView.SetListItems(ExampleItems);
		TreeView.SetEntryWidgetClass(UExampleMMTreeViewEntryWidget);

		// Bind function to let the treeview discover children
		TreeView.OnGetItemChildren(this, n"OnGetTreeViewChildren");
	}

	UFUNCTION()
	private void OnGetTreeViewChildren(UObject Item, TArray<UObject>& Children)
	{
		UExampleMMTreeViewItem TreeItem = Cast<UExampleMMTreeViewItem>(Item);
		Children = TreeItem.Children;
	}

	UFUNCTION(BlueprintOverride)
	void OnTabOpened()
	{
		// Build a simple tree
		{
			UExampleMMTreeViewItem Item = UExampleMMTreeViewItem();
			Item.ItemName = "First Parent";
			ExampleItems.Add(Item);

			{
				UExampleMMTreeViewItem Child = UExampleMMTreeViewItem();
				Child.ItemName = "Child 1-1";
				Item.Children.Add(Child);
			}

			{
				UExampleMMTreeViewItem Child = UExampleMMTreeViewItem();
				Child.ItemName = "Child 1-2";
				Item.Children.Add(Child);
			}
		}

		{
			UExampleMMTreeViewItem Item = UExampleMMTreeViewItem();
			Item.ItemName = "Second Parent";
			ExampleItems.Add(Item);

			{
				UExampleMMTreeViewItem Child = UExampleMMTreeViewItem();
				Child.ItemName = "Child 2-1";
				Item.Children.Add(Child);
			}
		}

		{
			UExampleMMTreeViewItem Item = UExampleMMTreeViewItem();
			Item.ItemName = "Third Parent";
			ExampleItems.Add(Item);
		}
	}
}

class UExampleMMTreeViewItem
{
	FString ItemName;
	TArray<UExampleMMTreeViewItem> Children;
}

class UExampleMMTreeViewEntryWidget : UMMListViewEntryWidget
{
	UFUNCTION(BlueprintOverride)
	void DrawWidget(float DeltaTime)
	{
		// Get the item data associated with the tree view
		UExampleMMTreeViewItem Item = GetListItem(UExampleMMTreeViewItem);

		// Draw a black background for the item widget
		mm<UBorder> Border = mm::WithinBorder(FLinearColor::Black);
		mm::BeginHorizontalBox();

			// Show a plus if the item is expanded
			if (IsListItemExpanded() && Item.Children.Num() != 0)
				mm::Image(n"Plus", 16, 16);
			else
				mm::Spacer(16);

			mm::Spacer(10);

			// Show the name of the item
			mm::Text(Item.ItemName);

		mm::EndHorizontalBox();

		// Expand the item if it's clicked
		if (Border.WasClicked())
			SetListItemExpanded(!IsListItemExpanded());
	}
}

#endif