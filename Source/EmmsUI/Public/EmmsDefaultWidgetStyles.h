#pragma once
#include "Components/Button.h"
#include "EmmsDefaultWidgetStyles.generated.h"

UCLASS(Config=Game, defaultconfig, meta=(DisplayName="Emmsui Setting"))
class UEmmsDefaultWidgetStyles : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config)
	FSlateFontInfo DefaultFont = FSlateFontInfo();

    UPROPERTY(EditAnywhere, Config)
    FSlateFontInfo DefaultStyle_Font = FSlateFontInfo();

    UPROPERTY(EditAnywhere, Config)
    FTextBlockStyle DefaultTextStyle = FTextBlockStyle();

    UPROPERTY(EditAnywhere, Config)
    FButtonStyle DefaultButtonStyle = FButtonStyle();
    
    UPROPERTY(EditAnywhere, Config)
    FButtonStyle DefaultStyle_Button = FButtonStyle();
    
    UPROPERTY(EditAnywhere, Config)
    FSpinBoxStyle DefaultStyle_SpinBox = FSpinBoxStyle();
    
    UPROPERTY(EditAnywhere, Config)
    FSliderStyle DefaultStyle_Slider = FSliderStyle();
    
    UPROPERTY(EditAnywhere, Config)
    FScrollBarStyle DefaultStyle_Scrollbar = FScrollBarStyle();
    
    UPROPERTY(EditAnywhere, Config)
    FEditableTextBoxStyle DefaultStyle_EditableTextBox = FEditableTextBoxStyle();
    
    UPROPERTY(EditAnywhere, Config)
    FComboBoxStyle DefaultStyle_ComboBox = FComboBoxStyle();
    
    UPROPERTY(EditAnywhere, Config)
    FTableRowStyle DefaultStyle_ComboBox_Item = FTableRowStyle();
    
    UPROPERTY(EditAnywhere, Config)
    FCheckBoxStyle DefaultStyle_CheckBox = FCheckBoxStyle();

    UEmmsDefaultWidgetStyles();
    
    void ApplyDefaultStyleToNewWidgetImpl(UWidget* Widget) const;

    static void ApplyDefaultStyleToNewWidget(UWidget* Widget);

    static FSlateFontInfo GetDefaultFont();
};
