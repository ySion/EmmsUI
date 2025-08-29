#include "EmmsDefaultWidgetStyles.h"

#include "Styling/SlateTypes.h"
#include "Styling/StyleColors.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Brushes/SlateColorBrush.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SpinBox.h"
#include "Components/Slider.h"
#include "Components/ListView.h"
#include "Components/ScrollBox.h"
#include "Components/ComboBoxString.h"
#include "Components/CheckBox.h"
#include "Components/EditableTextBox.h"

UEmmsDefaultWidgetStyles::UEmmsDefaultWidgetStyles()
{
    auto& TextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
    DefaultStyle_Font = FSlateFontInfo(TextStyle.Font);

    DefaultStyle_Button = FButtonStyle();
    DefaultStyle_Button.SetNormal(FSlateRoundedBoxBrush(FStyleColors::Secondary, 4.0f, FStyleColors::Input, 1.0f))
        .SetHovered(FSlateRoundedBoxBrush(FStyleColors::Hover, 4.0f, FStyleColors::Input, 1.0f))
        .SetPressed(FSlateRoundedBoxBrush(FStyleColors::Header, 4.0f, FStyleColors::Input, 1.0f))
        .SetDisabled(FSlateRoundedBoxBrush(FStyleColors::Dropdown, 4.0f, FStyleColors::Recessed, 1.0f))
        .SetNormalForeground(FStyleColors::ForegroundHover)
        .SetHoveredForeground(FStyleColors::ForegroundHover)
        .SetPressedForeground(FStyleColors::ForegroundHover)
        .SetDisabledForeground(FStyleColors::Foreground)
        .SetNormalPadding(FMargin(12.f, 1.5f, 12.f, 1.5f))
        .SetPressedPadding(FMargin(12.f, 2.5f, 12.f, 0.5f));

    DefaultStyle_EditableTextBox = FEditableTextBoxStyle(FCoreStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("NormalEditableTextBox"));
    DefaultStyle_Scrollbar = FScrollBarStyle(FCoreStyle::Get().GetWidgetStyle<FScrollBarStyle>("Scrollbar"));
    DefaultStyle_ComboBox = FComboBoxStyle(FCoreStyle::Get().GetWidgetStyle<FComboBoxStyle>("ComboBox"));
    DefaultStyle_SpinBox = FSpinBoxStyle(FCoreStyle::Get().GetWidgetStyle<FSpinBoxStyle>("SpinBox"));
    DefaultStyle_Slider = FSliderStyle(FCoreStyle::Get().GetWidgetStyle<FSliderStyle>("Slider"));
    DefaultStyle_CheckBox = FCheckBoxStyle(FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("CheckBox"));

    DefaultStyle_ComboBox_Item = FTableRowStyle(FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("ComboBox.Row"));
    DefaultStyle_ComboBox_Item.SetEvenRowBackgroundBrush(FSlateColorBrush(FStyleColors::Input));
    DefaultStyle_ComboBox_Item.SetOddRowBackgroundBrush(FSlateColorBrush(FStyleColors::Input));
    DefaultStyle_ComboBox_Item.SetActiveBrush(FSlateRoundedBoxBrush(FStyleColors::Input, 4.0f, FStyleColors::Select, 1.f));
}

void UEmmsDefaultWidgetStyles::ApplyDefaultStyleToNewWidgetImpl(UWidget* Widget) const
{
    if (UButton* Button = Cast<UButton>(Widget))
    {
        Button->SetStyle(DefaultStyle_Button);
    }
    else if (UTextBlock* TextBlock = Cast<UTextBlock>(Widget))
    {
        TextBlock->SetFont(DefaultStyle_Font);
    }
    else if (UScrollBox* ScrollBox = Cast<UScrollBox>(Widget))
    {
        ScrollBox->SetWidgetBarStyle(DefaultStyle_Scrollbar);
    }
    else if (USpinBox* SpinBox = Cast<USpinBox>(Widget))
    {
        SpinBox->SetWidgetStyle(DefaultStyle_SpinBox);
        SpinBox->SetFont(DefaultStyle_Font);
        SpinBox->SetForegroundColor(DefaultStyle_SpinBox.ForegroundColor);
    }
    else if (USlider* Slider = Cast<USlider>(Widget))
    {
        Slider->SetWidgetStyle(DefaultStyle_Slider);
    }
    else if (UCheckBox* CheckBox = Cast<UCheckBox>(Widget))
    {
        CheckBox->SetWidgetStyle(DefaultStyle_CheckBox);
    }
    else if (UEditableTextBox* EditableTextBox = Cast<UEditableTextBox>(Widget))
    {
        EditableTextBox->WidgetStyle = DefaultStyle_EditableTextBox;
    }
    else if (UListView* ListView = Cast<UListView>(Widget))
    {
        // Why would this not be public??
        FProperty* ScrollBarStyleProperty = ListView->GetClass()->FindPropertyByName(TEXT("ScrollBarStyle"));
        ScrollBarStyleProperty->SetValue_InContainer(Widget, &DefaultStyle_Scrollbar);
    }
    else if (UComboBoxString* ComboBox = Cast<UComboBoxString>(Widget))
    {
        ComboBox->SetWidgetStyle(DefaultStyle_ComboBox);
        ComboBox->SetItemStyle(DefaultStyle_ComboBox_Item);
        PRAGMA_DISABLE_DEPRECATION_WARNINGS
        ComboBox->Font = DefaultStyle_Font;
        ComboBox->ForegroundColor = DefaultStyle_ComboBox_Item.TextColor;
        ComboBox->ScrollBarStyle = DefaultStyle_Scrollbar;
        PRAGMA_DISABLE_DEPRECATION_WARNINGS
    }
}

void UEmmsDefaultWidgetStyles::ApplyDefaultStyleToNewWidget(UWidget* Widget)
{
    static const UEmmsDefaultWidgetStyles* Config = GetDefault<UEmmsDefaultWidgetStyles>();
    Config->ApplyDefaultStyleToNewWidgetImpl(Widget);
}

FSlateFontInfo UEmmsDefaultWidgetStyles::GetDefaultFont()
{
    static const UEmmsDefaultWidgetStyles* Config = GetDefault<UEmmsDefaultWidgetStyles>();
    return Config->DefaultFont;
}