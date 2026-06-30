#pragma once

#include <JuceHeader.h>

typedef juce::Rectangle<int> Bounds;
typedef juce::String jString;

//return the expanded area
inline Bounds expandBottomOfBounds(Bounds& bounds, int expand)
{
	bounds = bounds.withTrimmedBottom(-expand);
	return bounds.withTop(bounds.getBottom() - expand);
}

template<class ButtonType>
inline void fitButtonInLeftBounds(Bounds& bounds, ButtonType& button, int height = -1)
{
	button.setSize(0, bounds.getHeight());
	button.changeWidthToFitText();

	if (height == -1)
		height = bounds.getHeight();
	button.setBounds(bounds.removeFromLeft(button.getWidth()).withHeight(height));
}

inline void comboBox_setSelectedItemWithText(juce::ComboBox& comboBox, jString text, juce::NotificationType notification = juce::sendNotificationAsync)
{
	for (int i = 0; i < comboBox.getNumItems(); i++)
	{
		if (comboBox.getItemText(i) == text)
		{
			comboBox.setSelectedItemIndex(i, notification);
			break;
		}
	}
}

inline juce::String valueTree_GetID(juce::ValueTree& valueTree) { return valueTree.getType().toString(); }
inline juce::ValueTree valueTree_GetOrAddChild(juce::ValueTree& valueTree, const jString& childName)
{
	if (!valueTree.getChildWithName(childName).isValid())
		valueTree.addChild(juce::ValueTree(childName), -1, nullptr);
	return valueTree.getChildWithName(childName);
}

inline juce::XmlElement::TextFormat getXmlNoWrapFormat()
{
	juce::XmlElement::TextFormat format;
	format.lineWrapLength = 0x7FFFFFFF;
	return format;
}

inline juce::Font getMonoFont() { return juce::Font("Cascadia Mono", 14.f, 0); };

template<class Type>
inline void stdVector_sort(std::vector<Type>& data, std::function<bool(Type& a, Type& b)> swapPredicate)
{
	if (data.empty())
		return;

	size_t n = data.size();
	bool swapped;

	for (int i = 0; i < n - 1; i++)
	{
		swapped = false;
		for (size_t j = 0; j < n - i - 1; j++)
		{
			if (swapPredicate(data[j], data[j + 1]))
			{
				std::swap(data[j], data[j + 1]);
				swapped = true;
			}
		}

		// If no two elements were swapped, then break
		if (!swapped)
			break;
	}
}