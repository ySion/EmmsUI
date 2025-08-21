#if EDITOR

/**
 * This is an example for an editor tab that can be opened from the "Tools" menu.
 * 
 * The tab displays a filterable list of all actors in the level, and a details view to edit
 * the properties of the selected actor.
 */
class UExample_EditorTab : UMMEditorUtilityTab
{
	default TabTitle = "Example MM Editor Tab";
	default Category = "Example Tabs";
	default Icon = n"ClassIcon.Actor";

	/**
	 * NB: References to actors in editor tabs should always be weak pointers,
	 * otherwise, if the user opens a different level we will keep the old actors alive, which is illegal.
	 */
	TArray<TWeakObjectPtr<AActor>> VisibleActors;
	TWeakObjectPtr<AActor> SelectedActor;

	UFUNCTION(BlueprintOverride)
	void OnTabOpened()
	{
		// Show all actors when the tab is first opened
		UpdateVisibleActors("");
	}

	UFUNCTION(BlueprintOverride)
	void DrawTab(float DeltaTime)
	{
		// Create a horizontal box that covers the whole tab
		mm::HAlign_Fill();
		mm::Slot_Fill();
		mm::BeginHorizontalBox();

		// First column: a list view of all actors in the level that match the filter
		{
			mm::Slot_Fill(0.33); // Column is 33% of the width
			mm::HAlign_Fill();
			mm::BeginVerticalBox();

			// Search box input to filter actors
			{
				FString UserSearchText;
				mm<UEditableTextBox> SearchInput = mm::EditableTextBox(UserSearchText);
				SearchInput.SetHintText(FText::FromString("Filter actors..."));

				// If the search input changed, apply the filter to the actors list
				if (SearchInput.WasTextChanged())
					UpdateVisibleActors(UserSearchText);
			}

			// List view for actor list
			{
				mm::Slot_Fill();

				// We pass an item count to the list view, which will automatically instantiate that many items
				mm<UListView> ActorList = mm::ListView(VisibleActors.Num());

				// Looping over the list view gives us only entries that are currently visible, so we can render them
				for (UMMListViewEntryWidget VisibleEntry : ActorList)
				{
					// Take the data from the visible actors list based on the item's index
					AActor Actor = VisibleActors[VisibleEntry.ItemIndex].Get();
					if (Actor == nullptr)
						continue;

					FLinearColor BackgroundColor = FLinearColor::Black;
					if (VisibleEntry.IsListItemSelected())
						BackgroundColor = FLinearColor(0.05, 0.23, 0.06);
					else if (VisibleEntry.IsHovered())
						BackgroundColor = FLinearColor(1.0, 1.0, 1.0, 0.1);

					// Draw the list item entry as a separate BeginDraw() block
					mm::BeginDraw(VisibleEntry);
					mm::WithinBorder(BackgroundColor);
					mm::BeginHorizontalBox();
						mm::Image(n"ClassIcon.Actor");
						mm::Padding(5, 0);
						mm::Text(Actor.ActorNameOrLabel);
					mm::EndHorizontalBox();
					mm::EndDraw();
				}

				// If the user selected a different item this frame, store that on the class
				if (ActorList.WasItemSelectionChanged())
				{
					if (VisibleActors.IsValidIndex(ActorList.SelectedIndex))
						SelectedActor = VisibleActors[ActorList.SelectedIndex];
					else
						SelectedActor = nullptr;
				}
			}

			mm::EndVerticalBox();
		}

		// Second column: a details view for the selected actor
		{
			mm::Slot_Fill(0.67); // Column is 67% of the width
			mm::HAlign_Fill();
			mm::Padding(10);

			if (SelectedActor.IsValid())
			{
				mm::BeginVerticalBox();
				mm::Text(SelectedActor.Get().ActorNameOrLabel, 15);

				mm::Slot_Fill();
				mm<UDetailsView> DetailsView = mm::Widget(UDetailsView);
				DetailsView.SetAllowFiltering(true);
				DetailsView.SetObject(SelectedActor.Get());

				mm::EndVerticalBox();
			}
			else
			{
				// Add an empty column if no actor is selected
				mm::Spacer(0);
			}
		}

		mm::EndHorizontalBox();
	}

	void UpdateVisibleActors(FString FilterText)
	{
		VisibleActors.Reset();

		TArray<AActor> ExistingActors;
		Gameplay::GetAllActorsOfClass(AActor, ExistingActors);

		for (AActor Actor : ExistingActors)
		{
			if (FilterText.IsEmpty() || Actor.ActorNameOrLabel.Contains(FilterText))
				VisibleActors.Add(Actor);
		}
	}
}

#endif