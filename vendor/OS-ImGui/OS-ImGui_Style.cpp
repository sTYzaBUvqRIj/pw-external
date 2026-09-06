#include "OS-ImGui_Style.h"

#include "imgui/imgui.h"

#include "imgui/fonts/tahoma.h" 
#include "imgui/fonts/materialdesignicons-webfont.h"
#include "imgui/fonts/IconsMaterialDesignIcons.h"

#include <algorithm>
#include <cmath>

ImVec4& OSImGui::GetGlobalAccentColor()
{
    static ImVec4 accentColor = { 0.f, 1.f, .512f, 1.f };
	return accentColor;
}

void OSImGui::InitStyle()
{
	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();

	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = { 10.f, 10.f };
	style.WindowTitleAlign = { 0.f, 0.5f };
	style.Alpha = 1.0f;
	style.FramePadding = { 10.f, 5.f };
	style.ItemSpacing = { 8.f, 5.f };
	style.ItemInnerSpacing = {  8.f, 5.f };
	style.GrabMinSize = 27.0f;
	style.ScrollbarSize = 27.0f;
	style.FrameBorderSize = 0.f;
	style.WindowRounding = 12.f;
    style.TabBorderSize = 0.8f;
	style.TabBarBorderSize = 1.6f;
	style.FrameRounding = 8.f;
    style.PopupRounding = 10.f;
    style.TabRounding = 8.f;
	style.WindowBorderSize = 1.0f;
    style.ChildRounding = 12.f;
    style.ScrollbarRounding = 12.f;
    style.GrabRounding = 8.f;
    style.ChildBorderSize = 1.f;

    Glass(GetGlobalAccentColor());
}

void OSImGui::InitFont(float fontSize)
{
	ImGuiIO& io = ImGui::GetIO();

    // Base font
	ImFontConfig fontConfig;
	fontConfig.FontDataOwnedByAtlas = false;
	fontConfig.PixelSnapH = true;
	fontConfig.OversampleH = 1;
	fontConfig.OversampleV = 1;

	MainFont = io.Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), fontSize, &fontConfig);

    // Initializing icon font (merging with tahoma)
    /*
	static ImWchar faRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	ImFontConfig faConfig;
	faConfig.MergeMode = true;
	faConfig.PixelSnapH = true;
	faConfig.OversampleH = 1;
	faConfig.OversampleV = 1;
	io.Fonts->AddFontFromMemoryCompressedTTF(fa_solid_900_compressed_data, fa_solid_900_compressed_size, fontSize, &faConfig, faRanges);
    */

	static ImWchar mdiRanges[] = { ICON_MIN_MDI, ICON_MAX_MDI, 0 };
	ImFontConfig mdiConfig;
	mdiConfig.MergeMode = true;
	mdiConfig.PixelSnapH = true;
	mdiConfig.OversampleH = 1;
	mdiConfig.OversampleV = 1;

    io.Fonts->AddFontFromMemoryCompressedTTF(materialdesignicons_compressed_data, materialdesignicons_compressed_size, fontSize, &mdiConfig, mdiRanges);

    // Initializing default font for executors
    ImFontConfig proggyConfig;
	proggyConfig.FontDataOwnedByAtlas = false;
    proggyConfig.SizePixels = fontSize;
    
    ProggyFont = io.Fonts->AddFontDefault(&proggyConfig);
}

void OSImGui::DarkRuda()
{
    ImGuiStyle& style = ImGui::GetStyle();
    
    const ImVec4 Bg          = { 0.11f, 0.15f, 0.17f, 1.00f };
    const ImVec4 Panel       = { 0.20f, 0.25f, 0.29f, 1.00f };
    const ImVec4 PanelDark   = { 0.09f, 0.12f, 0.14f, 1.00f };

    const ImVec4 Border      = { 0.08f, 0.10f, 0.12f, 1.00f };

    const ImVec4 Accent      = { 0.28f, 0.56f, 1.00f, 1.00f };
    const ImVec4 AccentHover = { 0.37f, 0.61f, 1.00f, 1.00f };
    const ImVec4 AccentDark  = { 0.06f, 0.53f, 0.98f, 1.00f };

    const ImVec4 Text        = { 0.95f, 0.96f, 0.98f, 1.00f };
    const ImVec4 TextDim     = { 0.36f, 0.42f, 0.47f, 1.00f };

    // Text
    style.Colors[ImGuiCol_Text]                 = Text;
    style.Colors[ImGuiCol_TextDisabled]         = TextDim;

    // Backgrounds
    style.Colors[ImGuiCol_WindowBg]             = Bg;
    style.Colors[ImGuiCol_ChildBg]              = ImVec4(Bg.x, Bg.y, Bg.z, 0.0f);
    style.Colors[ImGuiCol_PopupBg]              = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);

    // Borders
    style.Colors[ImGuiCol_Border]               = Border;
    style.Colors[ImGuiCol_BorderShadow]         = ImVec4(0,0,0,0);

    // Frame
    style.Colors[ImGuiCol_FrameBg]              = Panel;
    style.Colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.12f, 0.20f, 0.28f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive]        = PanelDark;

    // Title
    style.Colors[ImGuiCol_TitleBg]              = ImVec4(PanelDark.x, PanelDark.y, PanelDark.z, 0.65f);
    style.Colors[ImGuiCol_TitleBgActive]        = Border;
    style.Colors[ImGuiCol_TitleBgCollapsed]     = ImVec4(0,0,0,0.5f);

    style.Colors[ImGuiCol_MenuBarBg]            = ImVec4(0.15f, 0.18f, 0.22f, 1.0f);

    // Scrollbar
    style.Colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
    style.Colors[ImGuiCol_ScrollbarGrab]        = Panel;
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.09f, 0.21f, 0.31f, 1.0f);

    // Checkboxes / Sliders
    style.Colors[ImGuiCol_CheckMark]            = Accent;
    style.Colors[ImGuiCol_CheckboxSelectedBg]   = ImVec4(Accent.x, Accent.y, Accent.z, 0.25f);

    style.Colors[ImGuiCol_SliderGrab]           = Accent;
    style.Colors[ImGuiCol_SliderGrabActive]     = AccentHover;

    // Buttons
    style.Colors[ImGuiCol_Button]               = Panel;
    style.Colors[ImGuiCol_ButtonHovered]        = Accent;
    style.Colors[ImGuiCol_ButtonActive]         = AccentDark;

    // Headers
    style.Colors[ImGuiCol_Header]               = ImVec4(Panel.x, Panel.y, Panel.z, 0.55f);
    style.Colors[ImGuiCol_HeaderHovered]        = ImVec4(Accent.x, Accent.y, Accent.z, 0.80f);
    style.Colors[ImGuiCol_HeaderActive]         = Accent;

    // Separators
    style.Colors[ImGuiCol_Separator]            = Panel;
    style.Colors[ImGuiCol_SeparatorHovered]     = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    style.Colors[ImGuiCol_SeparatorActive]      = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);

    // Resize
    style.Colors[ImGuiCol_ResizeGrip]           = ImVec4(Accent.x, Accent.y, Accent.z, 0.25f);
    style.Colors[ImGuiCol_ResizeGripHovered]    = ImVec4(Accent.x, Accent.y, Accent.z, 0.67f);
    style.Colors[ImGuiCol_ResizeGripActive]     = ImVec4(Accent.x, Accent.y, Accent.z, 0.95f);

    // Input
    style.Colors[ImGuiCol_InputTextCursor]      = Text;

    // Tabs
    style.Colors[ImGuiCol_Tab]                          = Bg;
    style.Colors[ImGuiCol_TabHovered]                   = ImVec4(Accent.x, Accent.y, Accent.z, 0.80f);
    style.Colors[ImGuiCol_TabSelected]                  = Panel;
    style.Colors[ImGuiCol_TabSelectedOverline]          = Accent;

    style.Colors[ImGuiCol_TabDimmed]                    = Bg;
    style.Colors[ImGuiCol_TabDimmedSelected]            = Bg;
    style.Colors[ImGuiCol_TabDimmedSelectedOverline]    = ImVec4(Accent.x, Accent.y, Accent.z, 0.50f);

    // Docking
    style.Colors[ImGuiCol_DockingPreview]       = ImVec4(Accent.x, Accent.y, Accent.z, 0.70f);
    style.Colors[ImGuiCol_DockingEmptyBg]       = Bg;
	
    // Graphs
    style.Colors[ImGuiCol_PlotLines]            = ImVec4(0.61f, 0.61f, 0.61f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered]     = ImVec4(1.00f, 0.43f, 0.35f, 1.0f);

    style.Colors[ImGuiCol_PlotHistogram]        = ImVec4(0.90f, 0.70f, 0.00f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.0f);

    // Tables
    style.Colors[ImGuiCol_TableHeaderBg]        = ImVec4(0.19f, 0.19f, 0.20f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong]    = ImVec4(0.31f, 0.31f, 0.35f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight]     = ImVec4(0.23f, 0.23f, 0.25f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg]           = ImVec4(0,0,0,0);
    style.Colors[ImGuiCol_TableRowBgAlt]        = ImVec4(1,1,1,0.06f);

    // Selection
    style.Colors[ImGuiCol_TextLink]             = AccentHover;
    style.Colors[ImGuiCol_TextSelectedBg]       = ImVec4(Accent.x, Accent.y, Accent.z, 0.35f);
    style.Colors[ImGuiCol_TreeLines]            = Panel;

    // Drag & Drop
    style.Colors[ImGuiCol_DragDropTarget]       = ImVec4(1,1,0,0.90f);
    style.Colors[ImGuiCol_DragDropTargetBg]     = ImVec4(1,1,0,0.15f);

    // Misc
    style.Colors[ImGuiCol_UnsavedMarker]        = ImVec4(1.00f, 0.80f, 0.20f, 1.0f);

    style.Colors[ImGuiCol_NavCursor]            = Accent;
    style.Colors[ImGuiCol_NavWindowingHighlight]= ImVec4(1,1,1,0.70f);
    style.Colors[ImGuiCol_NavWindowingDimBg]    = ImVec4(0.80f,0.80f,0.80f,0.20f);
    style.Colors[ImGuiCol_ModalWindowDimBg]     = ImVec4(0.80f,0.80f,0.80f,0.35f);
}

void OSImGui::DeepDark()
{
    ImGuiStyle& style = ImGui::GetStyle();

    const ImVec4 Bg          = { 0.10f, 0.10f, 0.10f, 1.00f };
    const ImVec4 Frame       = { 0.05f, 0.05f, 0.05f, 0.54f };
    const ImVec4 Panel       = { 0.19f, 0.19f, 0.19f, 0.92f };

    const ImVec4 Border      = { 0.19f, 0.19f, 0.19f, 0.29f };
    const ImVec4 BorderHover = { 0.44f, 0.44f, 0.44f, 0.29f };

    const ImVec4 Accent      = { 0.33f, 0.67f, 0.86f, 1.00f };
    const ImVec4 AccentSoft  = { 0.33f, 0.67f, 0.86f, 0.30f };

    const ImVec4 Text        = { 1.00f, 1.00f, 1.00f, 1.00f };
    const ImVec4 TextDim     = { 0.50f, 0.50f, 0.50f, 1.00f };

    // Text
    style.Colors[ImGuiCol_Text]                 = Text;
    style.Colors[ImGuiCol_TextDisabled]         = TextDim;

    // Windows
    style.Colors[ImGuiCol_WindowBg]             = Bg;
    style.Colors[ImGuiCol_ChildBg]              = ImVec4(0,0,0,0);
    style.Colors[ImGuiCol_PopupBg]              = Panel;

    // Borders
    style.Colors[ImGuiCol_Border]               = Border;
    style.Colors[ImGuiCol_BorderShadow]         = ImVec4(0,0,0,0.24f);

    // Frame
    style.Colors[ImGuiCol_FrameBg]              = Frame;
    style.Colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.19f,0.19f,0.19f,0.54f);
    style.Colors[ImGuiCol_FrameBgActive]        = ImVec4(0.20f,0.22f,0.23f,1.00f);

    // Title
    style.Colors[ImGuiCol_TitleBg]              = ImVec4(0,0,0,1);
    style.Colors[ImGuiCol_TitleBgActive]        = ImVec4(0.06f,0.06f,0.06f,1);
    style.Colors[ImGuiCol_TitleBgCollapsed]     = ImVec4(0,0,0,1);
    style.Colors[ImGuiCol_MenuBarBg]            = ImVec4(0.14f,0.14f,0.14f,1);

    // Scrollbar
    style.Colors[ImGuiCol_ScrollbarBg]          = Frame;
    style.Colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.34f,0.34f,0.34f,0.54f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f,0.40f,0.40f,0.54f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.56f,0.56f,0.56f,0.54f);

    // Accent widgets
    style.Colors[ImGuiCol_CheckMark]            = Accent;
    style.Colors[ImGuiCol_CheckboxSelectedBg]   = AccentSoft;

    style.Colors[ImGuiCol_SliderGrab]           = ImVec4(0.34f,0.34f,0.34f,0.54f);
    style.Colors[ImGuiCol_SliderGrabActive]     = ImVec4(0.56f,0.56f,0.56f,0.54f);

    // Buttons
    style.Colors[ImGuiCol_Button]               = Frame;
    style.Colors[ImGuiCol_ButtonHovered]        = ImVec4(0.19f,0.19f,0.19f,0.54f);
    style.Colors[ImGuiCol_ButtonActive]         = ImVec4(0.20f,0.22f,0.23f,1.00f);

    // Headers
    style.Colors[ImGuiCol_Header]               = ImVec4(0,0,0,0.52f);
    style.Colors[ImGuiCol_HeaderHovered]        = ImVec4(0,0,0,0.36f);
    style.Colors[ImGuiCol_HeaderActive]         = ImVec4(0.20f,0.22f,0.23f,0.33f);

    // Separator
    style.Colors[ImGuiCol_Separator]            = Border;
    style.Colors[ImGuiCol_SeparatorHovered]     = BorderHover;
    style.Colors[ImGuiCol_SeparatorActive]      = ImVec4(0.40f,0.44f,0.47f,1);

    // Resize
    style.Colors[ImGuiCol_ResizeGrip]           = Border;
    style.Colors[ImGuiCol_ResizeGripHovered]    = BorderHover;
    style.Colors[ImGuiCol_ResizeGripActive]     = ImVec4(0.40f,0.44f,0.47f,1);

    // Input
    style.Colors[ImGuiCol_InputTextCursor]      = Text;

    // Tabs
    style.Colors[ImGuiCol_Tab]                          = ImVec4(0,0,0,0.52f);
    style.Colors[ImGuiCol_TabHovered]                   = ImVec4(0.14f,0.14f,0.14f,1);
    style.Colors[ImGuiCol_TabSelected]                  = ImVec4(0.20f,0.20f,0.20f,0.36f);

    style.Colors[ImGuiCol_TabSelectedOverline]          = Accent;

    style.Colors[ImGuiCol_TabDimmed]                    = ImVec4(0,0,0,0.52f);
    style.Colors[ImGuiCol_TabDimmedSelected]            = ImVec4(0.14f,0.14f,0.14f,1);
    style.Colors[ImGuiCol_TabDimmedSelectedOverline]    = ImVec4(Accent.x, Accent.y, Accent.z, 0.5f);

    // Docking
    style.Colors[ImGuiCol_DockingPreview]       = AccentSoft;
    style.Colors[ImGuiCol_DockingEmptyBg]       = Bg;

    // Plots
    style.Colors[ImGuiCol_PlotLines]            = Accent;
    style.Colors[ImGuiCol_PlotLinesHovered]     = Accent;

    style.Colors[ImGuiCol_PlotHistogram]        = Accent;
    style.Colors[ImGuiCol_PlotHistogramHovered] = Accent;
	
    // Tables
    style.Colors[ImGuiCol_TableHeaderBg]        = ImVec4(0,0,0,0.52f);
    style.Colors[ImGuiCol_TableBorderStrong]    = ImVec4(0,0,0,0.52f);
    style.Colors[ImGuiCol_TableBorderLight]     = Border;
    style.Colors[ImGuiCol_TableRowBg]           = ImVec4(0,0,0,0);
    style.Colors[ImGuiCol_TableRowBgAlt]        = ImVec4(1,1,1,0.06f);


    // Selection
    style.Colors[ImGuiCol_TextLink]             = Accent;
    style.Colors[ImGuiCol_TextSelectedBg]       = ImVec4(0.20f,0.22f,0.23f,1.00f);
    style.Colors[ImGuiCol_TreeLines]            = Border;

    // Drag & Drop
    style.Colors[ImGuiCol_DragDropTarget]       = Accent;
    style.Colors[ImGuiCol_DragDropTargetBg]     = AccentSoft;

    // Misc
    style.Colors[ImGuiCol_UnsavedMarker]        = ImVec4(1.0f,0.8f,0.2f,1.0f);

    style.Colors[ImGuiCol_NavCursor]            = Accent;
    style.Colors[ImGuiCol_NavWindowingHighlight]= Accent;

    style.Colors[ImGuiCol_NavWindowingDimBg]    = ImVec4(0,0,0,0.20f);
    style.Colors[ImGuiCol_ModalWindowDimBg]     = ImVec4(0,0,0,0.35f);
}

void OSImGui::PSDark()
{
    ImGuiStyle& style = ImGui::GetStyle();

    const ImVec4 bg0(0.168f, 0.168f, 0.168f, 1.0f); // #2B2B2B
    const ImVec4 bg1(0.200f, 0.200f, 0.200f, 1.0f); // #333333
    const ImVec4 bg2(0.235f, 0.235f, 0.235f, 1.0f); // #3C3C3C

    const ImVec4 border(0.290f, 0.290f, 0.290f, 1.0f);
    const ImVec4 text(0.878f, 0.878f, 0.878f, 1.0f);

    const ImVec4 accent(0.290f, 0.565f, 0.886f, 1.0f);
    const ImVec4 accentHover(0.361f, 0.627f, 0.941f, 1.0f);

    style.Colors[ImGuiCol_Text] = text;
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.54f,0.54f,0.54f,1);

    style.Colors[ImGuiCol_WindowBg] = bg0;
    style.Colors[ImGuiCol_ChildBg] = bg0;
    style.Colors[ImGuiCol_PopupBg] = bg1;

    style.Colors[ImGuiCol_Border] = border;
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0,0,0,0);

    style.Colors[ImGuiCol_FrameBg] = bg2;
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(
        accentHover.x,
        accentHover.y,
        accentHover.z,
        0.25f);

    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(
        accent.x,
        accent.y,
        accent.z,
        0.35f);

    style.Colors[ImGuiCol_TitleBg] = bg1;
    style.Colors[ImGuiCol_TitleBgActive] = bg1;
    style.Colors[ImGuiCol_TitleBgCollapsed] = bg1;

    style.Colors[ImGuiCol_MenuBarBg] = bg1;

    style.Colors[ImGuiCol_ScrollbarBg] = bg0;
    style.Colors[ImGuiCol_ScrollbarGrab] = bg2;
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f,0.30f,0.30f,1);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.38f,0.38f,0.38f,1);

    style.Colors[ImGuiCol_CheckMark] = accent;
    style.Colors[ImGuiCol_CheckboxSelectedBg] = ImVec4(
        accent.x,
        accent.y,
        accent.z,
        0.20f);

    style.Colors[ImGuiCol_SliderGrab] = accent;
    style.Colors[ImGuiCol_SliderGrabActive] = accentHover;

    style.Colors[ImGuiCol_Button] = bg2;

    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(
        accentHover.x,
        accentHover.y,
        accentHover.z,
        0.25f);

    style.Colors[ImGuiCol_ButtonActive] = ImVec4(
        accent.x,
        accent.y,
        accent.z,
        0.35f);

    style.Colors[ImGuiCol_Header] = bg2;

    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(
        accentHover.x,
        accentHover.y,
        accentHover.z,
        0.25f);

    style.Colors[ImGuiCol_HeaderActive] = ImVec4(
        accent.x,
        accent.y,
        accent.z,
        0.35f);

    style.Colors[ImGuiCol_Separator] = border;
    style.Colors[ImGuiCol_SeparatorHovered] = accent;
    style.Colors[ImGuiCol_SeparatorActive] = accentHover;

    style.Colors[ImGuiCol_ResizeGrip] = bg2;
    style.Colors[ImGuiCol_ResizeGripHovered] = accent;
    style.Colors[ImGuiCol_ResizeGripActive] = accentHover;

    style.Colors[ImGuiCol_InputTextCursor] = text;

    style.Colors[ImGuiCol_Tab] = bg1;

    style.Colors[ImGuiCol_TabHovered] = ImVec4(
        accentHover.x,
        accentHover.y,
        accentHover.z,
        0.20f);

    style.Colors[ImGuiCol_TabSelected] = bg2;

    style.Colors[ImGuiCol_TabSelectedOverline] = accent;

    style.Colors[ImGuiCol_TabDimmed] = bg0;
    style.Colors[ImGuiCol_TabDimmedSelected] = bg1;

    style.Colors[ImGuiCol_TabDimmedSelectedOverline] =
        ImVec4(
            accent.x,
            accent.y,
            accent.z,
            0.50f);

    style.Colors[ImGuiCol_DockingPreview] =
        ImVec4(
            accent.x,
            accent.y,
            accent.z,
            0.40f);

    style.Colors[ImGuiCol_DockingEmptyBg] = bg0;

    style.Colors[ImGuiCol_PlotLines] = accent;
    style.Colors[ImGuiCol_PlotLinesHovered] = accentHover;

    style.Colors[ImGuiCol_PlotHistogram] = accent;
    style.Colors[ImGuiCol_PlotHistogramHovered] = accentHover;

    style.Colors[ImGuiCol_TableHeaderBg] = bg1;
    style.Colors[ImGuiCol_TableBorderStrong] = border;
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f,0.23f,0.23f,1);

    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0,0,0,0);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1,1,1,0.02f);

    style.Colors[ImGuiCol_TextLink] = accentHover;

    style.Colors[ImGuiCol_TextSelectedBg] =
        ImVec4(
            accent.x,
            accent.y,
            accent.z,
            0.30f);

    style.Colors[ImGuiCol_TreeLines] = border;

    style.Colors[ImGuiCol_DragDropTarget] = accent;
    style.Colors[ImGuiCol_DragDropTargetBg] =
        ImVec4(
            accent.x,
            accent.y,
            accent.z,
            0.15f);

    style.Colors[ImGuiCol_UnsavedMarker] =
        ImVec4(1.0f,0.72f,0.20f,1);

    style.Colors[ImGuiCol_NavCursor] = accent;
    style.Colors[ImGuiCol_NavWindowingHighlight] = accentHover;

    style.Colors[ImGuiCol_NavWindowingDimBg] =
        ImVec4(0,0,0,0.25f);

    style.Colors[ImGuiCol_ModalWindowDimBg] =
        ImVec4(0,0,0,0.45f);
}

void OSImGui::VSCDark()
{
	ImGuiStyle& style = ImGui::GetStyle();

	// Core
	style.Colors[ImGuiCol_Text]                 = ImVec4(0.831f, 0.831f, 0.831f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled]         = ImVec4(0.529f, 0.529f, 0.529f, 1.0f);

	style.Colors[ImGuiCol_WindowBg]             = ImVec4(0.118f, 0.118f, 0.118f, 1.0f); // #1E1E1E
	style.Colors[ImGuiCol_ChildBg]              = ImVec4(0.118f, 0.118f, 0.118f, 0.0f);
	style.Colors[ImGuiCol_PopupBg]              = ImVec4(0.145f, 0.145f, 0.149f, 1.0f);

	style.Colors[ImGuiCol_Border]               = ImVec4(0.235f, 0.235f, 0.235f, 1.0f); // #3C3C3C
	style.Colors[ImGuiCol_BorderShadow]         = ImVec4(0, 0, 0, 0);

	// Frames
	style.Colors[ImGuiCol_FrameBg]              = ImVec4(0.145f, 0.145f, 0.149f, 1.0f); // #252526
	style.Colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.122f, 0.541f, 0.824f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive]        = ImVec4(0.000f, 0.478f, 0.800f, 1.0f);

	// Title/Menu
	style.Colors[ImGuiCol_TitleBg]              = ImVec4(0.118f, 0.118f, 0.118f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive]        = ImVec4(0.118f, 0.118f, 0.118f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed]     = ImVec4(0.118f, 0.118f, 0.118f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg]            = ImVec4(0.145f, 0.145f, 0.149f, 1.0f);

	// Scrollbar
	style.Colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.118f, 0.118f, 0.118f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.333f, 0.333f, 0.333f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.400f, 0.400f, 0.400f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.500f, 0.500f, 0.500f, 1.0f);

	// Accent
	style.Colors[ImGuiCol_CheckMark]            = ImVec4(0.000f, 0.478f, 0.800f, 1.0f);
	style.Colors[ImGuiCol_CheckboxSelectedBg]   = ImVec4(0.000f, 0.478f, 0.800f, 0.25f);

	style.Colors[ImGuiCol_SliderGrab]           = ImVec4(0.122f, 0.541f, 0.824f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive]     = ImVec4(0.000f, 0.478f, 0.800f, 1.0f);

	style.Colors[ImGuiCol_Button]               = ImVec4(0.145f, 0.145f, 0.149f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered]        = ImVec4(0.122f, 0.541f, 0.824f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive]         = ImVec4(0.000f, 0.478f, 0.800f, 1.0f);

	style.Colors[ImGuiCol_Header]               = ImVec4(0.145f, 0.145f, 0.149f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered]        = ImVec4(0.122f, 0.541f, 0.824f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive]         = ImVec4(0.000f, 0.478f, 0.800f, 1.0f);

	style.Colors[ImGuiCol_Separator]        = ImVec4(0.235f, 0.235f, 0.235f, 1.00f); // #3C3C3C
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.350f, 0.350f, 0.350f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive]  = ImVec4(0.000f, 0.478f, 0.800f, 1.00f); // #007ACC

	// resize grip
    style.Colors[ImGuiCol_ResizeGrip]        = ImVec4(0, 0, 0, 0);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0, 0, 0, 0);
	style.Colors[ImGuiCol_ResizeGripActive]  = ImVec4(0, 0, 0, 0);

	style.Colors[ImGuiCol_InputTextCursor] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);

	// Tabs
	style.Colors[ImGuiCol_Tab]                  = ImVec4(0.145f, 0.145f, 0.149f, 1.0f);
	style.Colors[ImGuiCol_TabHovered]           = ImVec4(0.122f, 0.541f, 0.824f, 1.0f);
	style.Colors[ImGuiCol_TabSelected]          = ImVec4(0.000f, 0.478f, 0.800f, 1.0f);
	style.Colors[ImGuiCol_TabSelectedOverline]  = ImVec4(0.122f, 0.541f, 0.824f, 1.0f);

	style.Colors[ImGuiCol_TabDimmed]            = ImVec4(0.118f, 0.118f, 0.118f, 1.0f);
	style.Colors[ImGuiCol_TabDimmedSelected]    = ImVec4(0.000f, 0.478f, 0.800f, 0.65f);
	style.Colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.122f, 0.541f, 0.824f, 0.65f);

	style.Colors[ImGuiCol_DockingPreview]       = ImVec4(0.000f, 0.478f, 0.800f, 0.70f);
	style.Colors[ImGuiCol_DockingEmptyBg]       = ImVec4(0.118f, 0.118f, 0.118f, 1.0f);

	style.Colors[ImGuiCol_PlotLines]            = ImVec4(0.808f, 0.522f, 0.247f, 1.000f); // #CE8454
	style.Colors[ImGuiCol_PlotLinesHovered]     = ImVec4(0.910f, 0.620f, 0.330f, 1.000f);

	style.Colors[ImGuiCol_PlotHistogram]        = ImVec4(0.808f, 0.522f, 0.247f, 1.000f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.910f, 0.620f, 0.330f, 1.000f);

	// Tables
	style.Colors[ImGuiCol_TableHeaderBg]        = ImVec4(0.145f, 0.145f, 0.149f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong]    = ImVec4(0.235f, 0.235f, 0.235f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight]     = ImVec4(0.180f, 0.180f, 0.180f, 1.0f);

	style.Colors[ImGuiCol_TableRowBg]           = ImVec4(0,0,0,0);
	style.Colors[ImGuiCol_TableRowBgAlt]        = ImVec4(1,1,1,0.03f);

	// Misc
	style.Colors[ImGuiCol_TextLink]             = ImVec4(0.220f, 0.650f, 1.000f, 1.0f);
	style.Colors[ImGuiCol_TextSelectedBg]       = ImVec4(0.000f, 0.478f, 0.800f, 0.35f);

	style.Colors[ImGuiCol_TreeLines]            = ImVec4(0.235f, 0.235f, 0.235f, 1.0f);

	
	style.Colors[ImGuiCol_DragDropTarget]       = ImVec4(0.000f, 0.478f, 0.800f, 1.0f);
	style.Colors[ImGuiCol_DragDropTargetBg]     = ImVec4(0.000f, 0.478f, 0.800f, 0.20f);

	style.Colors[ImGuiCol_UnsavedMarker]        = ImVec4(1.0f, 0.80f, 0.20f, 1.0f);

	style.Colors[ImGuiCol_NavCursor]            = ImVec4(0.000f, 0.478f, 0.800f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight]= ImVec4(1,1,1,0.7f);
	style.Colors[ImGuiCol_NavWindowingDimBg]    = ImVec4(0,0,0,0.2f);
	style.Colors[ImGuiCol_ModalWindowDimBg]     = ImVec4(0,0,0,0.5f);
}

void OSImGui::Glass(const ImVec4& accent)
{
    auto& style = ImGui::GetStyle();

    const ImVec4 bg        = ImVec4(0.08f, 0.08f, 0.10f, 0.65f);
    const ImVec4 bgChild   = ImVec4(0.10f, 0.10f, 0.12f, 0.45f);
    const ImVec4 bgPopup   = ImVec4(0.10f, 0.10f, 0.12f, 0.85f);
    const ImVec4 border    = ImVec4(1.f, 1.f, 1.f, 0.10f);

    style.Colors[ImGuiCol_Text]                 = ImVec4(0.95f, 0.95f, 0.97f, 1.f);
    style.Colors[ImGuiCol_TextDisabled]         = ImVec4(0.55f, 0.55f, 0.60f, 1.f);

    style.Colors[ImGuiCol_WindowBg]             = bg;
    style.Colors[ImGuiCol_ChildBg]              = bgChild;
    style.Colors[ImGuiCol_PopupBg]              = bgPopup;

    style.Colors[ImGuiCol_Border]               = border;
    style.Colors[ImGuiCol_BorderShadow]         = ImVec4(0,0,0,0);

    style.Colors[ImGuiCol_FrameBg]              = ImVec4(1.f,1.f,1.f,0.05f);
    style.Colors[ImGuiCol_FrameBgHovered]       = ImVec4(1.f,1.f,1.f,0.10f);
    style.Colors[ImGuiCol_FrameBgActive]        = ImVec4(1.f,1.f,1.f,0.15f);

    style.Colors[ImGuiCol_TitleBg]              = ImVec4(0.04f,0.04f,0.05f,0.55f);
    style.Colors[ImGuiCol_TitleBgActive]        = ImVec4(0.05f,0.05f,0.06f,0.75f);
    style.Colors[ImGuiCol_TitleBgCollapsed]     = ImVec4(0.f,0.f,0.f,0.35f);

    style.Colors[ImGuiCol_MenuBarBg]            = ImVec4(1.f,1.f,1.f,0.04f);

    style.Colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.f,0.f,0.f,0.10f);
    style.Colors[ImGuiCol_ScrollbarGrab]        = ImVec4(accent.x, accent.y, accent.z, 0.35f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(accent.x, accent.y, accent.z, 0.55f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]  = accent;

    style.Colors[ImGuiCol_CheckMark]            = accent;
    style.Colors[ImGuiCol_CheckboxSelectedBg]   = ImVec4(accent.x, accent.y, accent.z, 0.30f);

    style.Colors[ImGuiCol_SliderGrab]           = accent;
    style.Colors[ImGuiCol_SliderGrabActive]     = accent;

    style.Colors[ImGuiCol_Button]               = ImVec4(accent.x, accent.y, accent.z, 0.15f);
    style.Colors[ImGuiCol_ButtonHovered]        = ImVec4(accent.x, accent.y, accent.z, 0.35f);
    style.Colors[ImGuiCol_ButtonActive]         = ImVec4(accent.x, accent.y, accent.z, 0.55f);

    style.Colors[ImGuiCol_Header]               = ImVec4(accent.x, accent.y, accent.z, 0.15f);
    style.Colors[ImGuiCol_HeaderHovered]        = ImVec4(accent.x, accent.y, accent.z, 0.35f);
    style.Colors[ImGuiCol_HeaderActive]         = ImVec4(accent.x, accent.y, accent.z, 0.55f);

    style.Colors[ImGuiCol_Separator]            = border;
    style.Colors[ImGuiCol_SeparatorHovered]     = accent;
    style.Colors[ImGuiCol_SeparatorActive]      = accent;

    style.Colors[ImGuiCol_ResizeGrip]           = ImVec4(accent.x, accent.y, accent.z, 0.20f);
    style.Colors[ImGuiCol_ResizeGripHovered]    = ImVec4(accent.x, accent.y, accent.z, 0.50f);
    style.Colors[ImGuiCol_ResizeGripActive]     = accent;

	style.Colors[ImGuiCol_InputTextCursor]		= ImVec4(1.f, 1.f, 1.f, 1.f);

    style.Colors[ImGuiCol_Tab]                  = ImVec4(accent.x, accent.y, accent.z, 0.12f);
    style.Colors[ImGuiCol_TabHovered]           = ImVec4(accent.x, accent.y, accent.z, 0.35f);
    style.Colors[ImGuiCol_TabSelected]          = ImVec4(accent.x, accent.y, accent.z, 0.55f);
    style.Colors[ImGuiCol_TabSelectedOverline]	= ImVec4(accent.x, accent.y, accent.z, 1.f);

	style.Colors[ImGuiCol_TabDimmed]            = ImVec4(1.f,1.f,1.f,0.04f);
    style.Colors[ImGuiCol_TabDimmedSelected]    = ImVec4(accent.x, accent.y, accent.z, 0.25f);
	style.Colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(accent.x, accent.y, accent.z, 0.5f);

    style.Colors[ImGuiCol_DockingPreview]       = ImVec4(accent.x, accent.y, accent.z, 0.35f);
    style.Colors[ImGuiCol_DockingEmptyBg]       = bg;
	style.Colors[ImGuiCol_PlotLines] =
		ImVec4(1.f, 1.f, 1.f, 0.8f);

	style.Colors[ImGuiCol_PlotLinesHovered] =
		ImVec4(accent.x, accent.y, accent.z, 1.f);

	style.Colors[ImGuiCol_PlotHistogram] =
		ImVec4(accent.x, accent.y, accent.z, 0.8f);

	style.Colors[ImGuiCol_PlotHistogramHovered] =
		ImVec4(accent.x, accent.y, accent.z, 1.f);

	style.Colors[ImGuiCol_TableHeaderBg] =
		ImVec4(1.f, 1.f, 1.f, 0.08f);

	style.Colors[ImGuiCol_TableBorderStrong] =
		ImVec4(1.f, 1.f, 1.f, 0.15f);

	style.Colors[ImGuiCol_TableBorderLight] =
		ImVec4(1.f, 1.f, 1.f, 0.05f);

	style.Colors[ImGuiCol_TableRowBg] =
		ImVec4(0.f, 0.f, 0.f, 0.f);

	style.Colors[ImGuiCol_TableRowBgAlt] =
		ImVec4(1.f, 1.f, 1.f, 0.03f);

	style.Colors[ImGuiCol_TextLink] =
    	ImVec4(accent.x, accent.y, accent.z, 1.f);
	style.Colors[ImGuiCol_TextSelectedBg]       = ImVec4(accent.x, accent.y, accent.z, 0.35f);
	style.Colors[ImGuiCol_TreeLines] =
    	ImVec4(1.f, 1.f, 1.f, 0.10f);
	
    style.Colors[ImGuiCol_DragDropTarget]       = accent;
    style.Colors[ImGuiCol_DragDropTargetBg]     = ImVec4(accent.x, accent.y, accent.z, 0.20f);

	style.Colors[ImGuiCol_UnsavedMarker] =
		ImVec4(1.f, 0.75f, 0.15f, 1.f);

	style.Colors[ImGuiCol_NavCursor]            = accent;
    style.Colors[ImGuiCol_NavWindowingHighlight]= accent;

    style.Colors[ImGuiCol_ModalWindowDimBg]     = ImVec4(0.f,0.f,0.f,0.30f);
	style.Colors[ImGuiCol_ModalWindowDimBg] =
    	ImVec4(0.f, 0.f, 0.f, 0.35f);
}

void OSImGui::AdvanceRGB(ImVec4& col, float step)
{
    float h, s, v;
    ImGui::ColorConvertRGBtoHSV(col.x, col.y, col.z, h, s, v);
	/*
    h = std::fmod(h + step, 1.f);
	if (h < 0.f)
		h += 1.f;
	*/
	h += step;
	if (h > 1.f) h -= 1.f;
	if (h < 0.f) h += 1.f;

    ImGui::ColorConvertHSVtoRGB(h, s, v, col.x, col.y, col.z);
}