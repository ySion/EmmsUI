#include "EmmsSlotHelpers.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "AngelscriptBinds.h"
#include "AngelscriptDocs.h"

FEmmsAttributeSpecification* UEmmsSlotHelpers::Attr_HAlign;
FEmmsAttributeSpecification* UEmmsSlotHelpers::Attr_VAlign;
FEmmsAttributeSpecification* UEmmsSlotHelpers::Attr_LayoutData;
FEmmsAttributeSpecification* UEmmsSlotHelpers::Attr_Padding;
FEmmsAttributeSpecification* UEmmsSlotHelpers::Attr_Size;

void UEmmsSlotHelpers::HAlign_Left()
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<TEnumAsByte<EHorizontalAlignment>>(Attr_HAlign);
	if (Value == nullptr)
		return;
	*Value = EHorizontalAlignment::HAlign_Left;
}

void UEmmsSlotHelpers::HAlign_Right()
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<TEnumAsByte<EHorizontalAlignment>>(Attr_HAlign);
	if (Value == nullptr)
		return;
	*Value = EHorizontalAlignment::HAlign_Right;
}

void UEmmsSlotHelpers::HAlign_Center()
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<TEnumAsByte<EHorizontalAlignment>>(Attr_HAlign);
	if (Value == nullptr)
		return;
	*Value = EHorizontalAlignment::HAlign_Center;
}

void UEmmsSlotHelpers::HAlign_Fill()
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<TEnumAsByte<EHorizontalAlignment>>(Attr_HAlign);
	if (Value == nullptr)
		return;
	*Value = EHorizontalAlignment::HAlign_Fill;
}

void UEmmsSlotHelpers::VAlign_Top()
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<TEnumAsByte<EVerticalAlignment>>(Attr_VAlign);
	if (Value == nullptr)
		return;
	*Value = EVerticalAlignment::VAlign_Top;
}

void UEmmsSlotHelpers::VAlign_Center()
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<TEnumAsByte<EVerticalAlignment>>(Attr_VAlign);
	if (Value == nullptr)
		return;
	*Value = EVerticalAlignment::VAlign_Center;
}

void UEmmsSlotHelpers::VAlign_Bottom()
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<TEnumAsByte<EVerticalAlignment>>(Attr_VAlign);
	if (Value == nullptr)
		return;
	*Value = EVerticalAlignment::VAlign_Bottom;
}

void UEmmsSlotHelpers::VAlign_Fill()
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<TEnumAsByte<EVerticalAlignment>>(Attr_VAlign);
	if (Value == nullptr)
		return;
	*Value = EVerticalAlignment::VAlign_Fill;
}

void UEmmsSlotHelpers::Slot_Fill(float FillPercentage)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FSlateChildSize>(Attr_Size);
	if (Value == nullptr)
		return;
	*Value = FSlateChildSize(ESlateSizeRule::Fill);
	Value->Value = FillPercentage;
}

void UEmmsSlotHelpers::Slot_Auto()
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FSlateChildSize>(Attr_Size);
	if (Value == nullptr)
		return;
	*Value = FSlateChildSize(ESlateSizeRule::Automatic);
}

void UEmmsSlotHelpers::Anchors_Uniform(float UniformAnchors)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FAnchorData>(Attr_LayoutData);
	if (Value == nullptr)
		return;
	Value->Anchors = FAnchors(UniformAnchors);
}

void UEmmsSlotHelpers::Anchors_HorizVert(float Horiz, float Vert)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FAnchorData>(Attr_LayoutData);
	if (Value == nullptr)
		return;
	Value->Anchors = FAnchors(Horiz, Vert);
}

void UEmmsSlotHelpers::Anchors(float MinX, float MinY, float MaxX, float MaxY)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FAnchorData>(Attr_LayoutData);
	if (Value == nullptr)
		return;
	Value->Anchors = FAnchors(MinX, MinY, MaxX, MaxY);
}

void UEmmsSlotHelpers::Offsets_Uniform(float Uniform)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FAnchorData>(Attr_LayoutData);
	if (Value == nullptr)
		return;
	Value->Offsets = FMargin(Uniform);
}

void UEmmsSlotHelpers::Offsets_HorizVert(float Horiz, float Vert)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FAnchorData>(Attr_LayoutData);
	if (Value == nullptr)
		return;
	Value->Offsets = FMargin(Horiz, Vert);
}

void UEmmsSlotHelpers::Offsets(float Left, float Top, float Right, float Bottom)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FAnchorData>(Attr_LayoutData);
	if (Value == nullptr)
		return;
	Value->Offsets = FMargin(Left, Top, Right, Bottom);
}

void UEmmsSlotHelpers::Alignment(float Horiz, float Vert)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FAnchorData>(Attr_LayoutData);
	if (Value == nullptr)
		return;
	Value->Alignment = FVector2D(Horiz, Vert);
}

void UEmmsSlotHelpers::Padding_Uniform(float Uniform)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FMargin>(Attr_Padding);
	if (Value == nullptr)
		return;
	*Value = FMargin(Uniform);
}

void UEmmsSlotHelpers::Padding_HorizVert(float Horiz, float Vert)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FMargin>(Attr_Padding);
	if (Value == nullptr)
		return;
	*Value = FMargin(Horiz, Vert);
}

void UEmmsSlotHelpers::Padding(float Left, float Top, float Right, float Bottom)
{
	auto* Value = GetPartialImplicitPendingSlotAttribute<FMargin>(Attr_Padding);
	if (Value == nullptr)
		return;
	*Value = FMargin(Left, Top, Right, Bottom);
}

FEmmsAttributeSpecification* GetSlotAttrGenericSpec(FName Name, UClass* Class)
{
	auto* ResolvedSpec = FEmmsAttributeSpecification::SlotAttributeSpecs.FindRef(TPair<FName,UClass*>(Name, Class));
	check(ResolvedSpec != nullptr);
	auto* GenericSpec = FEmmsAttributeSpecification::SlotAttributeGenericSpecs.FindRef(ResolvedSpec);
	check(GenericSpec != nullptr);
	return GenericSpec;
}

AS_FORCE_LINK const FAngelscriptBinds::FBind Bind_EmmsSlotHelpers((int32)FAngelscriptBinds::EOrder::Late + 250, []
{
	FAngelscriptBinds::FNamespace ns("mm");

	UEmmsSlotHelpers::Attr_HAlign = GetSlotAttrGenericSpec("HorizontalAlignment", UHorizontalBoxSlot::StaticClass());
	FAngelscriptBinds::BindGlobalFunction("void HAlign_Left()", &UEmmsSlotHelpers::HAlign_Left);
	SCRIPT_BIND_DOCUMENTATION("The next widget drawn will be horizontally aligned to the left within its containing slot");
	FAngelscriptBinds::BindGlobalFunction("void HAlign_Center()", &UEmmsSlotHelpers::HAlign_Center);
	SCRIPT_BIND_DOCUMENTATION("The next widget drawn will be horizontally aligned to the center within its containing slot");
	FAngelscriptBinds::BindGlobalFunction("void HAlign_Right()", &UEmmsSlotHelpers::HAlign_Right);
	SCRIPT_BIND_DOCUMENTATION("The next widget drawn will be horizontally aligned to the right within its containing slot");
	FAngelscriptBinds::BindGlobalFunction("void HAlign_Fill()", &UEmmsSlotHelpers::HAlign_Fill);
	SCRIPT_BIND_DOCUMENTATION("The next widget drawn will be horizontally aligned to fill its entire containing slot");

	UEmmsSlotHelpers::Attr_VAlign = GetSlotAttrGenericSpec("VerticalAlignment", UHorizontalBoxSlot::StaticClass());
	FAngelscriptBinds::BindGlobalFunction("void VAlign_Top()", &UEmmsSlotHelpers::VAlign_Top);
	SCRIPT_BIND_DOCUMENTATION("The next widget drawn will be vertically aligned to the top within its containing slot");
	FAngelscriptBinds::BindGlobalFunction("void VAlign_Center()", &UEmmsSlotHelpers::VAlign_Center);
	SCRIPT_BIND_DOCUMENTATION("The next widget drawn will be vertically aligned to the center within its containing slot");
	FAngelscriptBinds::BindGlobalFunction("void VAlign_Bottom()", &UEmmsSlotHelpers::VAlign_Bottom);
	SCRIPT_BIND_DOCUMENTATION("The next widget drawn will be vertically aligned to the bottom within its containing slot");
	FAngelscriptBinds::BindGlobalFunction("void VAlign_Fill()", &UEmmsSlotHelpers::VAlign_Fill);
	SCRIPT_BIND_DOCUMENTATION("The next widget drawn will be vertically aligned to fill its entire containing slot");

	UEmmsSlotHelpers::Attr_Size = GetSlotAttrGenericSpec("Size", UHorizontalBoxSlot::StaticClass());
	FAngelscriptBinds::BindGlobalFunction("void Slot_Fill(float32 FillPercentage = 1.0)", &UEmmsSlotHelpers::Slot_Fill);
	SCRIPT_BIND_DOCUMENTATION("The slot for the next widget drawn will fill its containing panel, with the specified fill percentage relative to the other slots");
	FAngelscriptBinds::BindGlobalFunction("void Slot_Auto()", &UEmmsSlotHelpers::Slot_Auto);
	SCRIPT_BIND_DOCUMENTATION("The slot for the next widget drawn will be auto-sized within its containing panel");

	UEmmsSlotHelpers::Attr_LayoutData = GetSlotAttrGenericSpec("LayoutData", UCanvasPanelSlot::StaticClass());
	FAngelscriptBinds::BindGlobalFunction("void Anchors(float32 UniformAnchors)", &UEmmsSlotHelpers::Anchors_Uniform);
	SCRIPT_BIND_DOCUMENTATION("The canvas panel slot for the next widget drawn will use the specified anchors");
	FAngelscriptBinds::BindGlobalFunction("void Anchors(float32 Horizontal, float32 Vertical)", &UEmmsSlotHelpers::Anchors_HorizVert);
	SCRIPT_BIND_DOCUMENTATION("The canvas panel slot for the next widget drawn will use the specified anchors");
	FAngelscriptBinds::BindGlobalFunction("void Anchors(float32 MinX, float32 MinY, float32 MaxX, float32 MaxY)", &UEmmsSlotHelpers::Anchors);
	SCRIPT_BIND_DOCUMENTATION("The canvas panel slot for the next widget drawn will use the specified anchors");

	FAngelscriptBinds::BindGlobalFunction("void Offsets(float32 UniformOffsets)", &UEmmsSlotHelpers::Offsets_Uniform);
	SCRIPT_BIND_DOCUMENTATION("The canvas panel slot for the next widget drawn will use the specified offsets");
	FAngelscriptBinds::BindGlobalFunction("void Offsets(float32 Horizontal, float32 Vertical)", &UEmmsSlotHelpers::Offsets_HorizVert);
	SCRIPT_BIND_DOCUMENTATION("The canvas panel slot for the next widget drawn will use the specified offsets");
	FAngelscriptBinds::BindGlobalFunction("void Offsets(float32 Left, float32 Top, float32 Right, float32 Bottom)", &UEmmsSlotHelpers::Offsets);
	SCRIPT_BIND_DOCUMENTATION("The canvas panel slot for the next widget drawn will use the specified offsets");

	FAngelscriptBinds::BindGlobalFunction("void Alignment(float32 Horizontal, float32 Vertical)", &UEmmsSlotHelpers::Alignment);
	SCRIPT_BIND_DOCUMENTATION("The canvas slot for the next widget drawn will use the specified alignment");

	UEmmsSlotHelpers::Attr_Padding = GetSlotAttrGenericSpec("Padding", UHorizontalBoxSlot::StaticClass());
	FAngelscriptBinds::BindGlobalFunction("void Padding(float32 UniformPadding)", &UEmmsSlotHelpers::Padding_Uniform);
	SCRIPT_BIND_DOCUMENTATION("The slot for the next widget drawn will use the specified padding");
	FAngelscriptBinds::BindGlobalFunction("void Padding(float32 Horizontal, float32 Vertical)", &UEmmsSlotHelpers::Padding_HorizVert);
	SCRIPT_BIND_DOCUMENTATION("The slot for the next widget drawn will use the specified padding");
	FAngelscriptBinds::BindGlobalFunction("void Padding(float32 Left, float32 Top, float32 Right, float32 Bottom)", &UEmmsSlotHelpers::Padding);
	SCRIPT_BIND_DOCUMENTATION("The slot for the next widget drawn will use the specified padding");
});