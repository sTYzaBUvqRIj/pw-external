#pragma once

#include "imgui/imgui.h"

namespace OSImGui
{
	ImVec4& GetGlobalAccentColor();

	inline ImFont* MainFont = NULL;
	inline ImFont* ProggyFont = NULL;
	
	void InitStyle();
	void InitFont(float fontSize);

	void DarkRuda();
	void DeepDark();
	void PSDark();
	void VSCDark();
	void Glass(const ImVec4& accent);

	void AdvanceRGB(ImVec4& cols, float step);
}