// Copyright 2021 Yevhenii Selivanov.

#pragma once

#include "MyPropertyTypeCustomization.h"

/**
 * Allow to choose the function for UGameUserSettings instead of manually typing a name.
 */
class FSettingsFunctionCustomization final : public FMyPropertyTypeCustomization
{
public:
	/* ---------------------------------------------------
	*		Public functions
	* --------------------------------------------------- */

	/** The name of class to be customized. */
	static const FName PropertyClassName;

	/** Default constructor. */
	FSettingsFunctionCustomization();

	/** Makes a new instance of this detail layout class for a specific detail view requesting it. */
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/**
 	 * Called when the header of the property (the row in the details panel where the property is shown)
 	 * If nothing is added to the row, the header is not displayed
	 * @param PropertyHandle Handle to the property being customized
	 * @param HeaderRow	A row that widgets can be added to
	 * @param CustomizationUtils Utilities for customization
	 */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

	/**
	 * Called when the children of the property should be customized or extra rows added.
	 * @param PropertyHandle Handle to the property being customized
	 * @param ChildBuilder A builder for adding children
	 * @param CustomizationUtils Utilities for customization
	 */
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

protected:
	/* ---------------------------------------------------
	*		Protected properties
	* --------------------------------------------------- */

	/** The handle of a property that contains a class of functions to display.
	 * @see FSettingsFunction::Class */
	TSharedPtr<IPropertyHandle> FunctionClassHandleInternal = nullptr;

	/** Contains the function to be compared with all other functions of a class to show in the list only compatible functions.
	 * @see FSettingsFunctionCustomization::RefreshCustomProperty() */
	TWeakObjectPtr<UFunction> TemplateFunctionInternal = nullptr;

	/** A name of last chosen class property. When is not changed, refreshing of a custom property will be skipped.
	 * @see FSettingsFunctionCustomization::RefreshCustomProperty() */
	FName CachedFunctionClassInternal = NAME_None;

	/** If true, will be added FUNC_Static flag to show only static function in the list. */
	bool bIsStaticFunctionInternal = false;

	/* ---------------------------------------------------
	*		Protected functions
	* --------------------------------------------------- */

	/** Is called for each property on building its row. */
	virtual void OnCustomizeChildren(IDetailChildrenBuilder& ChildBuilder, const FPropertyData& PropertyData) override;

	/** Is called on adding the custom property.
	* @see FMyPropertyTypeCustomization::CustomPropertyNameInternal */
	virtual void AddCustomPropertyRow(const FText& PropertyDisplayText, IDetailChildrenBuilder& ChildBuilder) override;

	/** Set new values for the list of selectable members.
	* @see FMyPropertyTypeCustomization::SearchableComboBoxValuesInternal */
	virtual void RefreshCustomProperty() override;

	/** Is called to deactivate custom property. */
	virtual void InvalidateCustomProperty() override;

	/** Returns true if changing custom property currently is not forbidden. */
	virtual bool IsAllowedEnableCustomProperty() const override;

	/** Returns the currently chosen class of functions to display.
	 * @see FSettingsFunctionCustomization::FunctionClassHandleInternal
	 * @see FSettingsFunction::Class */
	const UClass* GetChosenFunctionClass() const;

	/**
	 * Check if all signatures of specified function are compatible with current template function.
	 * Contains the logic UFunction::IsSignatureCompatibleWith but implements some part to return true for any derived UObject
	 * @param Function The function to check.
	 * @return true if compatible.
	 * @see FSettingsFunctionCustomization::TemplateFunctionInternal
	 */
	bool IsSignatureCompatible(const UFunction* Function) const;
};
