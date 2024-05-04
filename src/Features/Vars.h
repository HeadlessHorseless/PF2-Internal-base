#pragma once
#include "../SDK/SDK.h"

template <class T>
class CVar
{
public:
	T m_Var;
	const wchar_t* m_szDisplayName;
};

namespace Vars
{
	namespace Menu
	{

		inline Rect_t Position = { 100, 100, 800, 420 };
		inline const auto Title = L"This is unused...";
		inline int TitleBarH = 16;

		inline int SpacingX = 8;
		inline int SpacingY = 4;
		inline int SpacingText = 4;

		inline int CheckBoxW = 14;
		inline int CheckBoxH = 14;
		inline int CheckBoxFillSize = 3;

		inline int ButtonW = 90;
		inline int ButtonH = 20;

		inline int ButtonWSmall = 70;
		inline int ButtonHSmall = 16;

		inline int ComboBoxW = 90;
		inline int ComboBoxH = 14;

		inline int InputBoxW = 90;
		inline int InputBoxH = 14;
		inline int InputColorBoxW = 30;

		namespace Colors //Colors for the menu, feel free to edit
		{
			inline Color WindowBackground = { 20, 20, 20, 255 };
			inline Color TitleBar = { 139, 0, 0, 255 };
			inline Color Text = { 255, 255, 255, 190 };
			inline Color Widget = { 20, 20, 20, 255 };
			inline Color WidgetActive = { 70, 70, 70, 255 };
			inline Color OutlineMenu = { 60, 60, 60, 255 }; //I replaced this with the OutlineMenu Colors of Neuoanitic as it was too dark
		}
	}

	namespace ExampleVars
	{
		inline CVar<bool> BoolCheckbox{ true, L"Checkbox Bool" };
		inline CVar<int> Integer{ 0, L"Integer" };
		inline CVar<float> Float{ 0.0f, L"Float" };
		inline CVar<int> Key{ VK_SHIFT, L"Key" }; //For Keybinds
		inline CVar<int> ComboboxInt{ 0, L"Combobox" };
	}
}