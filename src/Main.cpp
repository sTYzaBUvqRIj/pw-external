#include "utils/ProcessManager.hpp"
#include "utils/Il2CppExternal.h"
#include "OS-ImGui/OS-ImGui.h"

#include <iostream>
#include <vector>
#include <cmath>

constexpr DWORD64 TypeInfo_ControllerHelper = 0x5752828;
constexpr DWORD64 TypeInfo_NetworkPlayers = 0x5711aa8;

inline uintptr_t g_moduleBase = 0;
inline uintptr_t g_controllerHelperStatic = 0;
inline uintptr_t g_networkPlayersStatic = 0;

struct Player
{
    uintptr_t ptr = 0x0;
    inline ImVec2 GetPosition() const
    {
        ImVec2 result;
        if (ptr)
            ProcessMgr.ReadMemory(ptr + 0x6FC, result);
        return result;
    }
} g_localPlayer;

struct Camera
{
    ImVec2 topLeft{ 0.f, 0.f };
    ImVec2 center{ 0.f, 0.f };
    ImVec2 scale{ 0.f, 0.f };
    bool isValid = false;

    inline void Update(const ImVec2& displaySize, uintptr_t cameraInstance)
    {
        isValid = false;
        if (!cameraInstance)
            return;
        if (ProcessMgr.ReadMemory(cameraInstance + 0x50, topLeft) &&
            ProcessMgr.ReadMemory(cameraInstance + 0x64, center)) {
            const ImVec2 halfExtent = center - topLeft;
            if (std::abs(halfExtent.x) > 0.001f && std::abs(halfExtent.y) > 0.001f) {
                scale.x = displaySize.x / (halfExtent.x * 2.0f);
                scale.y = displaySize.y / (halfExtent.y * 2.0f);
                isValid = true;
            }
        }
    }
    inline ImVec2 WorldToScreen(const ImVec2& worldPos) const
    {
        if (!isValid)
            return { 0.f, 0.f };
        return {
            (worldPos.x - topLeft.x) * scale.x,
            (worldPos.y - topLeft.y) * scale.y
        };
    }
} g_camera;


struct CollectableData
{
    int id;
    int blockType;
    int inventoryItemType;
    void* inventoryData;
    float posX, posY;
    ImVec2i mapPoint;
    int16_t amount;
    bool isGem;
    int gemType;
};

struct World
{
    uintptr_t ptr = 0x0;

    inline std::vector<CollectableData> GetCollectables() const
    {
        std::vector<CollectableData> result;
        IE::List<uintptr_t> collectables;
        if (ptr && ProcessMgr.ReadMemory(ptr + 0x150, collectables) && collectables.ptr) {
            auto collvec = collectables.ToVector();
            result.resize(collvec.size());
            CollectableData temp;
            for (const auto& collptr : collvec) {
                if (!collptr || !ProcessMgr.ReadMemory(collptr + IE::sizeof_Il2CppObject, temp))
                    break;
                result.push_back(temp);
            }
        }
        return std::move(result);
    }

    inline void ChangeLighting(int newLighting) const
    {
        if (ptr)
            ProcessMgr.WriteMemory(ptr + 0x30, newLighting);
    }

} g_world;

inline std::vector<Player> GetPlayers()
{
    std::vector<Player> result;
    IE::List<uintptr_t> netplayers;
    if (g_networkPlayersStatic && ProcessMgr.ReadMemory(g_networkPlayersStatic, netplayers) && netplayers.ptr) {
        auto playvec = netplayers.ToVector();
        result.reserve(playvec.size());
        Player temp;
        for (const auto& ptr : playvec) {
            if (!ptr || !ProcessMgr.ReadMemory(ptr + 0x18, temp))
                break;
            result.push_back(temp);
        }
    }
    return std::move(result);
}

struct Settings
{
    bool disable_lighting = false;
    bool esp_player = false;
    bool esp_object = false;
} g_settings;

void DrawCallback()
{
    static bool isRunning = true;

    if (!isRunning || !ProcessMgr.IsActive()) {
        Gui.Quit();
        return;
    }

    if (!g_moduleBase) {
        g_moduleBase = reinterpret_cast<DWORD64>(ProcessMgr.GetProcessModuleHandle("GameAssembly.dll"));
        if (!g_moduleBase)
            return;
    }

    if (!g_controllerHelperStatic) {
        g_controllerHelperStatic = ProcessMgr.TraceAddress(g_moduleBase + TypeInfo_ControllerHelper, { 0xB8, 0x0 });
        if (!g_controllerHelperStatic)
            return;
    }

    if (!g_networkPlayersStatic) {
        g_networkPlayersStatic = ProcessMgr.TraceAddress(g_moduleBase + TypeInfo_NetworkPlayers, { 0xB8, 0x0 });
        if (!g_networkPlayersStatic)
            return;
    }

    DWORD64 controllerHelperFields[18]{};
    if (!ProcessMgr.ReadMemory(g_controllerHelperStatic, controllerHelperFields)) {
        g_controllerHelperStatic = 0;
        return;
    }

    if (controllerHelperFields[1]) {
        DWORD64 cameraInstance = 0;
        if (ProcessMgr.ReadMemory(controllerHelperFields[1] + 0x28, cameraInstance) && cameraInstance) {
            g_camera.Update(ImGui::GetIO().DisplaySize, cameraInstance);
        }
    }

    if (controllerHelperFields[7]) {
        ProcessMgr.ReadMemory(controllerHelperFields[7] + 0x40, g_localPlayer);
        ProcessMgr.ReadMemory(controllerHelperFields[7] + 0x38, g_world);
        if (g_settings.disable_lighting) {
            g_world.ChangeLighting(0);
            // disabling fogOfWar
            uintptr_t fow = 0;
            IE::Array<ImVec4> cols;
            if (ProcessMgr.ReadMemory(controllerHelperFields[7] + 0x360, fow)
                && fow
                && ProcessMgr.ReadMemory(fow + 0x28, cols)
                && cols.ptr) {
                const size_t sz = cols.size();
                const ImVec4 zero = { 0.f, 0.f, 0.f, 0.0001f };
                for (size_t i = (rand() % 100); i < sz; i += 100) {
                    cols.set(i, zero);
                }
            }
        }
    }

    if (ImGui::Begin("Pixel Worlds External", &isRunning)) {
        ImGui::Text("Framerate: %.1f FPS", ImGui::GetIO().Framerate);
        ImGui::Separator();
        ImGui::Checkbox("Disable world lighting", &g_settings.disable_lighting);
        ImGui::Checkbox("ESP Player", &g_settings.esp_player);
        ImGui::Checkbox("ESP Object", &g_settings.esp_object);
    }
    ImGui::End();

    if (!g_camera.isValid)
        return;
    
    const auto pos1 = g_camera.WorldToScreen(g_localPlayer.GetPosition());
    auto drawList = ImGui::GetBackgroundDrawList();
    
    if (g_settings.esp_player) {
        for (const auto& play : GetPlayers()) {
            drawList->AddLine(pos1,
                g_camera.WorldToScreen(play.GetPosition()),
                IM_COL32(0, 255, 0, 255));
        }
    }

    if (g_settings.esp_object) {
        for (const auto& coll : g_world.GetCollectables()) {
            drawList->AddLine(pos1,
                g_camera.WorldToScreen({coll.posX * 0.32f, coll.posY * 0.32f}),
                IM_COL32(0, 0, 255, 255));
        }
    }
}

int main()
{
    std::cout << "Attaching to \x50\x69\x78\x65\x6C\x57\x6F\x72\x6C\x64\x73\x2E\x65\x78\x65..." << std::endl;
    const StatusCode status = ProcessMgr.Attach("\x50\x69\x78\x65\x6C\x57\x6F\x72\x6C\x64\x73\x2E\x65\x78\x65");
    if (status != SUCCEED) {
        const char* errorMsg = "Error: Unknown error!";
        switch (status) {
        case StatusCode::FAILE_PROCESSID:
            errorMsg = "Error: Process ID not found! Make sure Pixel Worlds is running.";
            break;
        case StatusCode::FAILE_HPROCESS:
            errorMsg = "Error: Failed to open process handle! Run as administrator.";
            break;
        case StatusCode::FAILE_MODULE:
            errorMsg = "Error: Failed to obtain process module handle!";
            break;
        default:
            break;
        }

        std::cerr << errorMsg << std::endl;
        system("pause");
        return 1;
    }

    std::cout << "Attached to process successfully!" << std::endl;

    try {
        Gui.AttachAnotherWindow("\x50\x69\x78\x65\x6C\x20\x57\x6F\x72\x6C\x64\x73", "", &DrawCallback);
    }
    catch (const OSImGui::OSException& e) {
        std::cerr << "OS-ImGui Exception: " << e.what() << std::endl;
    }

    std::cout << "Cleaning up..." << std::endl;
    ProcessMgr.Detach();
    std::cout << "Detached from process." << std::endl;
    return 0;
}