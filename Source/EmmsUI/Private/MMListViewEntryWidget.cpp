#include "MMListViewEntryWidget.h"
#include "Components/ListView.h"
#include "Components/TreeView.h"

UObject* UMMListViewEntryWidget::GetListItem(const TSubclassOf<UObject>& ItemClass) const
{
	if (ItemClass == nullptr || ListItem == nullptr || !ListItem->IsA(ItemClass))
		return nullptr;
	return ListItem;
}

int UMMListViewEntryWidget::GetItemIndex() const
{
	if (ListItem == nullptr)
		return -1;
	if (UListView* ListView = Cast<UListView>(GetOwningListView()))
		return ListView->GetIndexForItem(ListItem);
	else
		return -1;
}

bool UMMListViewEntryWidget::AS_IsListItemSelected() const
{
	return IsListItemSelected();
}

bool UMMListViewEntryWidget::AS_IsListItemExpanded() const
{
	return IsListItemExpanded();
}

void UMMListViewEntryWidget::AS_SetListItemExpanded(bool bExpanded)
{
	if (UTreeView* TreeView = Cast<UTreeView>(GetOwningListView()))
		TreeView->SetItemExpansion(ListItem, bExpanded);
}

UListViewBase* UMMListViewEntryWidget::AS_GetOwningListView() const
{
	return GetOwningListView();
}

void UMMListViewEntryWidget::OnRootWidgetChanged()
{
	if (UListView* ListView = Cast<UListView>(GetOwningListView()))
		ListView->RequestRefresh();
}

void UMMListViewEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (ListItemObject != ListItem)
	{
		ListItem = ListItemObject;
		IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

		bAllowDraw = (ListItem != nullptr);
		CallDraw(0.f);
	}
}