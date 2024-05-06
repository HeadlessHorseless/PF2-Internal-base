#include "Menu.h"

#define FONT_MENU EFonts::MENU_TAHOMA

void CMenu::DrawTooltip()
{
	if (m_szCurTip.empty())
		return;

	int w, h;
	I::Surface->GetTextSize(G::Draw.m_Fonts[FONT_MENU].m_hFont, m_szCurTip.data(), w, h);

	G::Draw.OutlinedRect(g_InputHelper.m_nMouseX + 13, g_InputHelper.m_nMouseY + 13, w + 4, h + 4, { 0, 0, 0, 255 });
	G::Draw.Rect(g_InputHelper.m_nMouseX + 14, g_InputHelper.m_nMouseY + 14, w + 2, h + 2, Vars::Menu::Colors::WindowBackground);
	G::Draw.String(FONT_MENU, g_InputHelper.m_nMouseX + 15, g_InputHelper.m_nMouseY + 15, Vars::Menu::Colors::Text, TXT_DEFAULT, m_szCurTip.data());
}

void CMenu::Separator()
{
	int x = m_LastWidget.x + m_LastWidget.w + Vars::Menu::SpacingX;
	int y = Vars::Menu::Position.y;
	int w = 0;
	int h = 0;

	G::Draw.Line(x, y, x, (y + Vars::Menu::Position.h - 1), Vars::Menu::Colors::OutlineMenu);

	m_LastWidget.x = x + Vars::Menu::SpacingX;
	m_LastWidget.y = y;
	m_LastWidget.w = w;
	m_LastWidget.h = h;
}

bool CMenu::CheckBox(CVar<bool>& Var, const wchar_t* const szToolTip)
{
	bool callback = false;

	int x = m_LastWidget.x;
	int y = m_LastWidget.y + m_LastWidget.h + Vars::Menu::SpacingY;
	int w = Vars::Menu::CheckBoxW;
	int h = Vars::Menu::CheckBoxH;

	if (g_InputHelper.m_nMouseX > x && g_InputHelper.m_nMouseX < x + w && g_InputHelper.m_nMouseY > y && g_InputHelper.m_nMouseY < y + h)
	{
		if (g_InputHelper.IsPressed(VK_LBUTTON)) {
			callback = true;
			Var.m_Var = !Var.m_Var;
		}

		G::Draw.Rect(x, y, w, h, Vars::Menu::Colors::WidgetActive);
		m_szCurTip += szToolTip;
	}

	if (Var.m_Var)
	{
		G::Draw.GradientRect(
			x,
			y,
			x + w,
			y + h,
			Vars::Menu::Colors::Widget, Vars::Menu::Colors::WidgetActive,
			false);
	}

	G::Draw.OutlinedRect(x, y, w, h, Vars::Menu::Colors::OutlineMenu);
	G::Draw.String(FONT_MENU, x + w + Vars::Menu::SpacingText, y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERY, Var.m_szDisplayName);

	m_LastWidget.x = x;
	m_LastWidget.y = y;
	m_LastWidget.w = w;
	m_LastWidget.h = h;

	return callback;
}

bool CMenu::Button(const wchar_t* Label, bool Active, int WidthOverride, int HeightOverride)
{
	bool callback = false;

	int x = m_LastWidget.x;
	int y = m_LastWidget.y + m_LastWidget.h + Vars::Menu::SpacingY;
	int w = WidthOverride ? WidthOverride : Vars::Menu::ButtonW;
	int h = HeightOverride ? HeightOverride : Vars::Menu::ButtonH;

	if (g_InputHelper.m_nMouseX > x && g_InputHelper.m_nMouseX < x + w && g_InputHelper.m_nMouseY > y && g_InputHelper.m_nMouseY < y + h)
	{
		if (g_InputHelper.IsPressed(VK_LBUTTON))
			callback = true;

		G::Draw.Rect(x, y, w, h, Vars::Menu::Colors::WidgetActive);
	}

	if (Active)
		G::Draw.GradientRect(x, y, x + w, y + h, Vars::Menu::Colors::Widget, Vars::Menu::Colors::WidgetActive, false);

	G::Draw.OutlinedRect(x, y, w, h, Vars::Menu::Colors::OutlineMenu);
	G::Draw.String(FONT_MENU, x + (w / 2), y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERXY, Label);

	m_LastWidget.x = x;
	m_LastWidget.y = y;
	m_LastWidget.w = w;
	m_LastWidget.h = h;

	if (callback)
		m_bReopened = true;

	return callback;
}

bool CMenu::ComboBox(CVar<int>& Var, const std::vector<CVar<int>>& List)
{
	auto FindCurItemName = [&]() -> const wchar_t*
	{
		for (const auto& Item : List)
		{
			if (Item.m_Var == Var.m_Var)
				return Item.m_szDisplayName;
		}

		return L"UNKNOWN_ITEM";
	};

	auto FindCurItemIndex = [&]() -> int
	{
		for (size_t n = 0; n < List.size(); n++)
		{
			if (List[n].m_Var == Var.m_Var)
				return n;
		}

		return 0;
	};

	bool callback = false;

	int x = m_LastWidget.x;
	int y = m_LastWidget.y + m_LastWidget.h + Vars::Menu::SpacingY;
	int w = Vars::Menu::ComboBoxW;
	int h = Vars::Menu::ComboBoxH;

	static std::map<CVar<int>*, int> indexes = {};
	static std::map<CVar<int>*, bool> inits = {};

	if (!inits[&Var] || m_bReopened) {
		indexes[&Var] = FindCurItemIndex();
		inits[&Var] = true;
	}

	if (g_InputHelper.m_nMouseX > x && g_InputHelper.m_nMouseX < x + (w / 2) && g_InputHelper.m_nMouseY > y && g_InputHelper.m_nMouseY < y + h)
	{
		if (indexes[&Var] > 0)
		{
			if (g_InputHelper.IsPressed(VK_LBUTTON)) {
				Var.m_Var = List[--indexes[&Var]].m_Var;
				callback = true;
			}

			G::Draw.GradientRect(x, y, x + (w / 2), y + h, Vars::Menu::Colors::WidgetActive, Vars::Menu::Colors::Widget, true);
		}
	}

	else if (g_InputHelper.m_nMouseX > x + (w / 2) && g_InputHelper.m_nMouseX < x + w && g_InputHelper.m_nMouseY > y && g_InputHelper.m_nMouseY < y + h)
	{
		if (indexes[&Var] < int(List.size() - 1))
		{
			if (g_InputHelper.IsPressed(VK_LBUTTON)) {
				Var.m_Var = List[++indexes[&Var]].m_Var;
				callback = true;
			}

			G::Draw.GradientRect(x + (w / 2), y, x + w, y + h, Vars::Menu::Colors::Widget, Vars::Menu::Colors::WidgetActive, true);
		}
	}

	G::Draw.OutlinedRect(x, y, w, h, Vars::Menu::Colors::OutlineMenu);
	G::Draw.String(FONT_MENU, x + (w / 2), y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERXY, FindCurItemName());
	G::Draw.String(FONT_MENU, x + w + Vars::Menu::SpacingText, y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERY, Var.m_szDisplayName);

	m_LastWidget.x = x;
	m_LastWidget.y = y;
	m_LastWidget.w = w;
	m_LastWidget.h = h;

	return callback;
}

bool CMenu::InputFloat(CVar<float>& Var, float Min, float Max, float Step, const wchar_t* Fmt)
{
	bool callback = false;

	int x = m_LastWidget.x;
	int y = m_LastWidget.y + m_LastWidget.h + Vars::Menu::SpacingY;
	int w = Vars::Menu::InputBoxW;
	int h = Vars::Menu::InputBoxH;

	if (Var.m_Var != Min)
	{
		if (g_InputHelper.m_nMouseX > x && g_InputHelper.m_nMouseX < x + (w / 2) && g_InputHelper.m_nMouseY > y && g_InputHelper.m_nMouseY < y + h)
		{
			if (g_InputHelper.IsPressedAndHeld(VK_LBUTTON)) {
				Var.m_Var -= Step;
				Var.m_Var = std::clamp(Var.m_Var, Min, Max);
				callback = true;
			}

			G::Draw.GradientRect(x, y, x + (w / 2), y + h, Vars::Menu::Colors::WidgetActive, Vars::Menu::Colors::Widget, true);
		}
	}

	if (Var.m_Var != Max)
	{
		if (g_InputHelper.m_nMouseX > x + (w / 2) && g_InputHelper.m_nMouseX < x + w && g_InputHelper.m_nMouseY > y && g_InputHelper.m_nMouseY < y + h)
		{
			if (g_InputHelper.IsPressedAndHeld(VK_LBUTTON)) {
				Var.m_Var += Step;
				Var.m_Var = std::clamp(Var.m_Var, Min, Max);
				callback = true;
			}

			G::Draw.GradientRect(x + (w / 2), y, x + w, y + h, Vars::Menu::Colors::Widget, Vars::Menu::Colors::WidgetActive, true);
		}
	}

	G::Draw.OutlinedRect(x, y, w, h, Vars::Menu::Colors::OutlineMenu);
	G::Draw.String(FONT_MENU, x + (w / 2), y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERXY, Fmt, Var.m_Var);
	G::Draw.String(FONT_MENU, x + w + Vars::Menu::SpacingText, y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERY, Var.m_szDisplayName);

	m_LastWidget.x = x;
	m_LastWidget.y = y;
	m_LastWidget.w = w;
	m_LastWidget.h = h;

	return callback;
}

bool CMenu::InputInt(CVar<int>& Var, int Min, int Max, int Step)
{
	bool callback = false;

	int x = m_LastWidget.x;
	int y = m_LastWidget.y + m_LastWidget.h + Vars::Menu::SpacingY;
	int w = Vars::Menu::InputBoxW;
	int h = Vars::Menu::InputBoxH;

	if (Var.m_Var != Min)
	{
		if (g_InputHelper.m_nMouseX > x && g_InputHelper.m_nMouseX < x + (w / 2) && g_InputHelper.m_nMouseY > y && g_InputHelper.m_nMouseY < y + h)
		{
			if (g_InputHelper.IsPressedAndHeld(VK_LBUTTON)) {
				Var.m_Var -= Step;
				Var.m_Var = std::clamp(Var.m_Var, Min, Max);
				callback = true;
			}

			G::Draw.GradientRect(x, y, x + (w / 2), y + h, Vars::Menu::Colors::WidgetActive, Vars::Menu::Colors::Widget, true);
		}
	}

	if (Var.m_Var != Max)
	{
		if (g_InputHelper.m_nMouseX > x + (w / 2) && g_InputHelper.m_nMouseX < x + w && g_InputHelper.m_nMouseY > y && g_InputHelper.m_nMouseY < y + h)
		{
			if (g_InputHelper.IsPressedAndHeld(VK_LBUTTON)) {
				Var.m_Var += Step;
				Var.m_Var = std::clamp(Var.m_Var, Min, Max);
				callback = true;
			}

			G::Draw.GradientRect(x + (w / 2), y, x + w, y + h, Vars::Menu::Colors::Widget, Vars::Menu::Colors::WidgetActive, true);
		}
	}

	G::Draw.OutlinedRect(x, y, w, h, Vars::Menu::Colors::OutlineMenu);
	G::Draw.String(FONT_MENU, x + (w / 2), y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERXY, "%d", Var.m_Var);
	G::Draw.String(FONT_MENU, x + w + Vars::Menu::SpacingText, y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERY, Var.m_szDisplayName);

	m_LastWidget.x = x;
	m_LastWidget.y = y;
	m_LastWidget.w = w;
	m_LastWidget.h = h;

	return callback;
}

bool CMenu::InputString(const wchar_t* Label, std::wstring& output)
{
	bool callback = false;

	int x = m_LastWidget.x;
	int y = m_LastWidget.y + m_LastWidget.h + Vars::Menu::SpacingY;
	int w = Vars::Menu::InputBoxW * 2;
	int h = Vars::Menu::ButtonH;

	static bool active = false;
	static std::wstring active_str = {};

	if (g_InputHelper.IsPressed(VK_LBUTTON))
	{
		if (g_InputHelper.m_nMouseX > x && g_InputHelper.m_nMouseX < x + w && g_InputHelper.m_nMouseY > y && g_InputHelper.m_nMouseY < y + h)
			active = !active;

		else active = false;
	}

	if (active)
	{
		m_bTyping = true;

		if (g_InputHelper.IsPressed(VK_INSERT)) {
			active = false;
			return false;
		}

		if (active_str.length() < 21)
		{
			if (g_InputHelper.IsPressed(VK_SPACE))
				active_str += char(VK_SPACE);

			for (int16_t key = L'A'; key < L'Z' + 1; key++)
			{
				if (g_InputHelper.IsPressed(key))
					active_str += wchar_t(key);
			}
		}

		if (g_InputHelper.IsPressedAndHeld(VK_BACK) && !active_str.empty())
			active_str.erase(active_str.end() - 1);

		if (g_InputHelper.IsPressed(VK_RETURN))
		{
			active = false;

			if (!active_str.empty())
			{
				output = active_str;
				callback = true;
			}
		}

		G::Draw.String(FONT_MENU, x + (w / 2), y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERXY, "%ws", active_str.empty() ? L"Enter a Name" : active_str.c_str());
	}

	else
	{
		active_str = {};
		G::Draw.String(FONT_MENU, x + (w / 2), y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERXY, "%ws", Label);
	}

	G::Draw.OutlinedRect(x, y, w, h, Vars::Menu::Colors::OutlineMenu);

	m_LastWidget.x = x;
	m_LastWidget.y = y;
	m_LastWidget.w = w;
	m_LastWidget.h = h;

	return callback;
}

bool CMenu::InputKey(CVar<int>& output, bool bAllowNone)
{
	auto VK2STR = [&](const short key) -> std::wstring
	{
		switch (key) {
		case VK_LBUTTON: return L"LButton";
		case VK_RBUTTON: return L"RButton";
		case VK_MBUTTON: return L"MButton";
		case VK_XBUTTON1: return L"XButton1";
		case VK_XBUTTON2: return L"XButton2";
		case 0x0: return L"None";
		default: break;
		}

		WCHAR output[16] = { L"\0" };

		if (const int result = GetKeyNameTextW(MapVirtualKeyW(key, MAPVK_VK_TO_VSC) << 16, output, 16))
			return output;

		return L"VK2STR_FAILED";
	};

	bool callback = false;

	int x = m_LastWidget.x;
	int y = m_LastWidget.y + m_LastWidget.h + Vars::Menu::SpacingY;
	int w = Vars::Menu::InputBoxW;
	int h = Vars::Menu::InputBoxH;

	static bool active = false, old_active = active;
	static float time = I::EngineClient->Time();
	float elapsed = I::EngineClient->Time() - time;

	if (old_active != active) {
		time = I::EngineClient->Time();
		old_active = active;
	}

	if (!active && elapsed > 0.1f && g_InputHelper.IsPressed(VK_LBUTTON))
	{
		if (g_InputHelper.m_nMouseX > x && g_InputHelper.m_nMouseX < x + w && g_InputHelper.m_nMouseY > y && g_InputHelper.m_nMouseY < y + h) {
			active = true;
			g_InputHelper.NullKey(VK_LBUTTON);
		}
	}

	static float time_notactive = 0.0f;

	if (active)
	{
		m_bTyping = true;

		if (I::EngineClient->Time() - time_notactive > 0.1f)
		{
			for (short n = 0; n < 256; n++)
			{
				if ((n > 0x0 && n < 0x7)
					|| (n > L'A' - 1 && n < L'Z' + 1)
					|| n == VK_LSHIFT || n == VK_RSHIFT || n == VK_SHIFT
					|| n == VK_ESCAPE || n == VK_INSERT)
				{
					if (g_InputHelper.IsPressed(n))
					{
						if (n == VK_INSERT) {
							active = false;
							break;
						}

						if (n == VK_ESCAPE && bAllowNone) {
							output.m_Var = 0x0;
							active = false;
							break;
						}

						output.m_Var = n;
						active = false;
						break;
					}
				}
			}
		}

		G::Draw.String(FONT_MENU, x + (w / 2), y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERXY, "%ws", L"Press a Key");
	}

	else
	{
		time_notactive = I::EngineClient->Time();
		G::Draw.String(FONT_MENU, x + (w / 2), y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERXY, "%ws", VK2STR(output.m_Var).c_str());
	}

	G::Draw.String(FONT_MENU, x + w + Vars::Menu::SpacingText, y + (h / 2), Vars::Menu::Colors::Text, TXT_CENTERY, output.m_szDisplayName);
	G::Draw.OutlinedRect(x, y, w, h, Vars::Menu::Colors::OutlineMenu);

	m_LastWidget.x = x;
	m_LastWidget.y = y;
	m_LastWidget.w = w;
	m_LastWidget.h = h;

	return callback;
}

void CMenu::GroupBoxStart()
{
	m_LastGroupBox.x = m_LastWidget.x;
	m_LastGroupBox.y = m_LastWidget.y + m_LastWidget.h + Vars::Menu::SpacingY;

	m_LastWidget.x += Vars::Menu::SpacingX;
	m_LastWidget.y += Vars::Menu::SpacingY * 2;
}

void CMenu::GroupBoxEnd(const wchar_t* Label, int Width)
{
	int h = m_LastWidget.y - m_LastGroupBox.y + m_LastWidget.h + Vars::Menu::SpacingY;

	int label_w, label_h;
	I::Surface->GetTextSize(G::Draw.m_Fonts[FONT_MENU].m_hFont, Label, label_w, label_h);

	int label_x = m_LastGroupBox.x + Vars::Menu::SpacingText;
	int label_y = m_LastGroupBox.y - (label_h / 2);

	G::Draw.Line(m_LastGroupBox.x, m_LastGroupBox.y, label_x, m_LastGroupBox.y, Vars::Menu::Colors::OutlineMenu);
	G::Draw.Line(label_x + label_w, m_LastGroupBox.y, m_LastGroupBox.x + Width, m_LastGroupBox.y, Vars::Menu::Colors::OutlineMenu);
	G::Draw.Line(m_LastGroupBox.x + Width, m_LastGroupBox.y, m_LastGroupBox.x + Width, m_LastGroupBox.y + h, Vars::Menu::Colors::OutlineMenu);
	G::Draw.Line(m_LastGroupBox.x + Width, m_LastGroupBox.y + h, m_LastGroupBox.x, m_LastGroupBox.y + h, Vars::Menu::Colors::OutlineMenu);
	G::Draw.Line(m_LastGroupBox.x, m_LastGroupBox.y + h, m_LastGroupBox.x, m_LastGroupBox.y, Vars::Menu::Colors::OutlineMenu);

	G::Draw.String(FONT_MENU, label_x, label_y, Vars::Menu::Colors::Text, TXT_DEFAULT, Label);

	m_LastWidget.x -= Vars::Menu::SpacingX;
	m_LastWidget.y += Vars::Menu::SpacingY * 2;
	m_LastGroupBox.h = h;
}

bool CMenu::String(const size_t& Font, const char* const str, const Color& clr)
{
	bool callback = false;

	int x = m_LastWidget.x;
	int y = m_LastWidget.y + m_LastWidget.h + Vars::Menu::SpacingY;
	int w = 0;
	int h = Vars::Menu::CheckBoxH;

	G::Draw.String(Font, x + w + Vars::Menu::SpacingText, y + (h / 2), clr, TXT_CENTERY, str);
	

	m_LastWidget.x = x;
	m_LastWidget.y = y;
	m_LastWidget.w = w;
	m_LastWidget.h = h;

	return callback;
}

void CMenu::Run()
{
	m_bReopened = false;
	m_bTyping = false;

	static bool bOldOpen = m_bOpen;

	if (bOldOpen != m_bOpen)
	{
		bOldOpen = m_bOpen;

		if (m_bOpen)
			m_bReopened = true;
	}

	if (I::EngineClient->IsDrawingLoadingImage()) {
		m_bOpen = false;
		return;
	}

	static float flTimeOnChange = 0.0f;

	if (/*Utils::IsGameWindowInFocus() &&*/ (GetAsyncKeyState(VK_INSERT) & 1)) {
		I::Surface->SetCursorAlwaysVisible(m_bOpen = !m_bOpen);
		flTimeOnChange = I::EngineClient->Time();
	}

	m_flFadeElapsed = I::EngineClient->Time() - flTimeOnChange;

	if (m_flFadeElapsed < m_flFadeDuration) {
		m_flFadeAlpha = RemapValClamped(m_flFadeElapsed, 0.0f, m_flFadeDuration, !m_bOpen ? 1.0f : 0.0f, m_bOpen ? 1.0f : 0.0f);
		I::Surface->DrawSetAlphaMultiplier(m_flFadeAlpha);
	}

	if (m_bOpen || m_flFadeElapsed < m_flFadeDuration)
	{
		m_szCurTip = L"";
		g_InputHelper.Update();

		//Do the Watermark
		{
			G::Draw.Rect(20, 25, 160, 5, Vars::Menu::Colors::TitleBar);
			G::Draw.Rect(20, 30, 160, (G::Draw.m_Fonts[FONT_MENU].m_nTall * 3) + 5, Vars::Menu::Colors::WindowBackground);
			G::Draw.String(FONT_MENU, 22, 32, Vars::Menu::Colors::Text, TXT_DEFAULT, "PF2 Internal Base");
			G::Draw.String(FONT_MENU, 22, 32 + G::Draw.m_Fonts[FONT_MENU].m_nTall, Vars::Menu::Colors::Text, TXT_DEFAULT, "Build: " __DATE__);
			G::Draw.String(FONT_MENU, 22, 32 + (G::Draw.m_Fonts[FONT_MENU].m_nTall * 2), Vars::Menu::Colors::Text, TXT_DEFAULT, "Meant for Devs");
		}

		//Do the Window
		{
			g_InputHelper.Drag(
				g_InputHelper.m_nMouseX,
				g_InputHelper.m_nMouseY,
				Vars::Menu::Position.x,
				Vars::Menu::Position.y,
				Vars::Menu::Position.w,
				Vars::Menu::TitleBarH,
				Vars::Menu::TitleBarH);


			//The menu is created and drawn here
			G::Draw.Rect(
				Vars::Menu::Position.x,
				Vars::Menu::Position.y,
				Vars::Menu::Position.w,
				Vars::Menu::Position.h,
				Vars::Menu::Colors::WindowBackground);

			G::Draw.Rect(
				Vars::Menu::Position.x,
				Vars::Menu::Position.y - Vars::Menu::TitleBarH,
				Vars::Menu::Position.w,
				Vars::Menu::TitleBarH,
				Vars::Menu::Colors::TitleBar);

			G::Draw.String(FONT_MENU,
				Vars::Menu::Position.x + (Vars::Menu::Position.w / 2),
				Vars::Menu::Position.y - (Vars::Menu::TitleBarH / 2),
				Vars::Menu::Colors::Text,
				TXT_CENTERXY,
				"%ls", L"Your menu name goes here");
		}

		//Do the Widgets
		{

			//All your tabs are defined here
			//Usually they should be named TAB_<Feature>
			enum struct EMainTabs { TAB_1, TAB_2, TAB_3, TAB_4, TAB_5, TAB_6, TAB_7 };
			m_LastWidget = { Vars::Menu::Position.x, Vars::Menu::Position.y + Vars::Menu::SpacingY, 0, 0 };
			

			Rect_t checkpoint = m_LastWidget;

			//Push things slightly to the right as the groupbox get slightly cut off if we don't do this
			checkpoint.x += 5 + Vars::Menu::SpacingX;
			m_LastWidget = checkpoint;

			static EMainTabs Tab = EMainTabs::TAB_1; //Defines the default tab
			{
				//===============================
				//Button tabs
				//This would normally be far simpler if it was positioned on the left side but oh well
				Rect_t checkpoint_line = m_LastWidget;
				checkpoint_line.x -= Vars::Menu::SpacingX;
				checkpoint_line.y += Vars::Menu::ButtonHSmall + (2 * 2);
				Rect_t checkpoint_move = m_LastWidget;
				checkpoint_move.x -= 5;
				m_LastWidget = checkpoint_move;

				if (Button(L"Tab 1", Tab == EMainTabs::TAB_1, Vars::Menu::ButtonWSmall, Vars::Menu::ButtonHSmall))
					Tab = EMainTabs::TAB_1;

				checkpoint_move.x += Vars::Menu::ButtonWSmall + 2;
				m_LastWidget = checkpoint_move;

				if (Button(L"Tab 2", Tab == EMainTabs::TAB_2, Vars::Menu::ButtonWSmall, Vars::Menu::ButtonHSmall))
					Tab = EMainTabs::TAB_2;

				checkpoint_move.x += Vars::Menu::ButtonWSmall + 2;
				m_LastWidget = checkpoint_move;


				if (Button(L"Tab 3", Tab == EMainTabs::TAB_3, Vars::Menu::ButtonWSmall, Vars::Menu::ButtonHSmall))
					Tab = EMainTabs::TAB_3;

				checkpoint_move.x += Vars::Menu::ButtonWSmall + 2;
				m_LastWidget = checkpoint_move;

				if (Button(L"Tab 4", Tab == EMainTabs::TAB_4, Vars::Menu::ButtonWSmall, Vars::Menu::ButtonHSmall))
					Tab = EMainTabs::TAB_4;

				checkpoint_move.x += Vars::Menu::ButtonWSmall + 2;
				m_LastWidget = checkpoint_move;

				//New tabs are defined like this:
				//	if (Button(L"TAB NAME", Tab == EMainTabs::TAB_xyz, Vars::Menu::ButtonWSmall, Vars::Menu::ButtonHSmall))
				//	Tab = EMainTabs::TAB_xyz;
				//
				//	checkpoint_move.x += Vars::Menu::ButtonWSmall + 2;
				//	m_LastWidget = checkpoint_move;


				m_LastWidget = checkpoint_line;
				G::Draw.Line(checkpoint_line.x, checkpoint_line.y, Vars::Menu::Position.x + Vars::Menu::Position.w - 1, checkpoint_line.y, Vars::Menu::Colors::OutlineMenu);
				checkpoint_line.x += Vars::Menu::SpacingX;
				checkpoint_line.y += Vars::Menu::SpacingY;
				m_LastWidget = checkpoint_line;
				//===============================

				//Tabs are defined here

				//They are done like this:

				//case EMainTabs::<tab name here ie TAB_1>
				//{
				// Rect_t checkpoint = m_LastWidget //Resets checkpoint so it doesn't cause horrifying misalignments
				// 
				// Menu widgets are in between here
				// 
				// 
				// break; //required since we are using case here
				//}

				switch (Tab)
				{
				case EMainTabs::TAB_1:
				{
					Rect_t checkpoint = m_LastWidget;
					GroupBoxStart();
					{
						String(FONT_MENU, "Example String", Vars::Menu::Colors::Text);
						CheckBox(Vars::ExampleVars::BoolCheckbox, L"Tooltip for Checkbox");
						InputKey(Vars::ExampleVars::Key, false);
						InputFloat(Vars::ExampleVars::Float, 1.0f, 180.0f, 1.0f, L"%.0f");
						InputInt(Vars::ExampleVars::Integer, -123, 123, 1);
						ComboBox(Vars::ExampleVars::ComboboxInt, { {0, L"First"}, {1, L"Second"}, {2, L"Third"}, {3, L"And so forth.."} });

						//Buttons, unlike every other widget are not controlled by Vars
						if (Button(L"Button", false, Vars::Menu::ButtonW, Vars::Menu::ButtonH))
						{
							I::EngineClient->ClientCmd_Unrestricted("echo Hello World");
						}
					}
					GroupBoxEnd(L"Groupbox 1", 180);

					//Everything after this will be moved to the right side of the menu
					checkpoint.x += 180 + Vars::Menu::SpacingX;
					m_LastWidget = checkpoint;

					GroupBoxStart();
					{
						String(FONT_MENU, "Example String", Vars::Menu::Colors::Text);
						CheckBox(Vars::ExampleVars::BoolCheckbox, L"Tooltip for Checkbox");
						InputKey(Vars::ExampleVars::Key, false);
						InputFloat(Vars::ExampleVars::Float, 1.0f, 180.0f, 1.0f, L"%.0f");
						InputInt(Vars::ExampleVars::Integer, -123, 123, 1);
						ComboBox(Vars::ExampleVars::ComboboxInt, { {0, L"First"}, {1, L"Second"}, {2, L"Third"}, {3, L"And so forth.."} });
						//Buttons, unlike every other widget are not controlled by Vars
						if (Button(L"Button", false, Vars::Menu::ButtonW, Vars::Menu::ButtonH))
						{
							I::EngineClient->ClientCmd_Unrestricted("echo Hello World");
						}
					}
					GroupBoxEnd(L"Groupbox 2", 180);


					break;
				}
				//Second tab
				case EMainTabs::TAB_2:
				{
					Rect_t checkpoint = m_LastWidget;
					GroupBoxStart();
					{
						String(FONT_MENU, "Example String", Vars::Menu::Colors::Text);
						CheckBox(Vars::ExampleVars::BoolCheckbox, L"Tooltip for Checkbox");
						InputKey(Vars::ExampleVars::Key, false);
						InputFloat(Vars::ExampleVars::Float, 1.0f, 180.0f, 1.0f, L"%.0f");
						InputInt(Vars::ExampleVars::Integer, -123, 123, 1);
						ComboBox(Vars::ExampleVars::ComboboxInt, { {0, L"First"}, {1, L"Second"}, {2, L"Third"}, {3, L"And so forth.."} });

						//Buttons, unlike every other widget are not controlled by Vars
						if (Button(L"Button", false, Vars::Menu::ButtonW, Vars::Menu::ButtonH))
						{
							I::EngineClient->ClientCmd_Unrestricted("echo Hello World");
						}
					}
					GroupBoxEnd(L"Groupbox 1", 180);

					//Everything after this will be moved to the right side of the menu
					checkpoint.x += 180 + Vars::Menu::SpacingX;
					m_LastWidget = checkpoint;

					GroupBoxStart();
					{
						String(FONT_MENU, "Example String", Vars::Menu::Colors::Text);
						CheckBox(Vars::ExampleVars::BoolCheckbox, L"Tooltip for Checkbox");
						InputKey(Vars::ExampleVars::Key, false);
						InputFloat(Vars::ExampleVars::Float, 1.0f, 180.0f, 1.0f, L"%.0f");
						InputInt(Vars::ExampleVars::Integer, -123, 123, 1);
						ComboBox(Vars::ExampleVars::ComboboxInt, { {0, L"First"}, {1, L"Second"}, {2, L"Third"}, {3, L"And so forth.."} });
						//Buttons, unlike every other widget are not controlled by Vars
						if (Button(L"Button", false, Vars::Menu::ButtonW, Vars::Menu::ButtonH))
						{
							I::EngineClient->ClientCmd_Unrestricted("echo Hello World");
						}
					}
					GroupBoxEnd(L"Groupbox 2", 180);
					break;
				}
				case EMainTabs::TAB_3:
				{
					Rect_t checkpoint = m_LastWidget;
					String(FONT_MENU, "Stuff can be added here", Vars::Menu::Colors::Text);
					break;
				}
				case EMainTabs::TAB_4:
				{
					Rect_t checkpoint = m_LastWidget;
					String(FONT_MENU, "Stuff can be added here", Vars::Menu::Colors::Text);
					break;
				}
				case EMainTabs::TAB_5:
				{
					Rect_t checkpoint = m_LastWidget;
					String(FONT_MENU, "Stuff can be added here", Vars::Menu::Colors::Text);
					break;
				}
				case EMainTabs::TAB_6:
				{
					Rect_t checkpoint = m_LastWidget;
					String(FONT_MENU, "Stuff can be added here", Vars::Menu::Colors::Text);
					break;
				}
				default: //If we somehow get to an invalid tab we draw nothing
				{
					break;
				}
				}
			}

			

			
		}

		DrawTooltip();
	}

	I::Surface->DrawSetAlphaMultiplier(1.0f);
}

//All Credit for menu goes to Spook953 and Lak3
