
#define DHR_EXPORT_SYMBOL
#include "DHR.h"
#include "ui.h"
#include "ui_serialization.h"

Bubble::Scope<Bubble::UI> UI;

DHR_EXPORT void DHR_CALL OnInit(ImGuiContext* context)
{
    Bubble::Log::Init();
    BUBBLE_ASSERT(glewInit() == GLEW_OK, "Glew init failed");
    ImGui::SetCurrentContext(context);
    UI = Bubble::CreateScope<Bubble::UI>();
    Bubble::UIDeserialization();
}

DHR_EXPORT void DHR_CALL OnDraw(Bubble::DeltaTime dt, Bubble::UIArgs args)
{
    UI->mArgs = args;
    UI->OnDraw(dt);
}

DHR_EXPORT void DHR_CALL OnUpdate(Bubble::DeltaTime dt)
{
    // OnUpdate is called out of imgui scope after OnDraw
    UI->OnUpdate(dt);
}

DHR_EXPORT void DHR_CALL OnMenuDraw()
{
    UI->DrawMenuBar();
}

DHR_EXPORT void DHR_CALL OnClose()
{
    Bubble::UISerialization();
}