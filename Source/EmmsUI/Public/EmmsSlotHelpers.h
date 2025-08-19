#pragma once
#include "EmmsWidgetElement.h"
#include "EmmsAttribute.h"
#include "EmmsStatics.h"
#include "EmmsSlotHelpers.generated.h"

UCLASS()
class EMMSUI_API UEmmsSlotHelpers : public UObject
{
	GENERATED_BODY()

public:

	static FEmmsAttributeSpecification* Attr_HAlign;
	static FEmmsAttributeSpecification* Attr_VAlign;
	static FEmmsAttributeSpecification* Attr_LayoutData;
	static FEmmsAttributeSpecification* Attr_Padding;
	static FEmmsAttributeSpecification* Attr_Size;

	template<typename T>
	static T* GetPartialImplicitPendingSlotAttribute(FEmmsAttributeSpecification* Spec)
	{
		if (FEmmsAttributeValue* AttrValue = UEmmsStatics::GetPartialImplicitPendingSlotAttribute(Spec))
			return (T*)AttrValue->GetDataPtr();
		else
			return nullptr;
	}

	static void HAlign_Left();
	static void HAlign_Right();
	static void HAlign_Center();
	static void HAlign_Fill();

	static void VAlign_Top();
	static void VAlign_Center();
	static void VAlign_Bottom();
	static void VAlign_Fill();

	static void Slot_Fill(float FillPercentage = 1.f);
	static void Slot_Auto();

	static void Anchors_Uniform(float UniformAnchors);
	static void Anchors_HorizVert(float Horizontal, float Vertical);
	static void Anchors(float MinX, float MinY, float MaxX, float MaxY);

	static void Offsets_Uniform(float UniformOffset);
	static void Offsets_HorizVert(float Horizontal, float Vertical);
	static void Offsets(float Left, float Top, float Right, float Bottom);

	static void Alignment(float Horiz, float Vert);

	static void Padding_Uniform(float UniformPadding);
	static void Padding_HorizVert(float Horizontal, float Vertical);
	static void Padding(float Left, float Top, float Right, float Bottom);
};