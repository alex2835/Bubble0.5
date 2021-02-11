
#define DHR_EXPORT_SYMBOL
#include "DHR.h"
#include "ui.h"

DHR_EXPORT void DHR_CALL OnInit(ImGuiContext* context)
{
    ImGui::SetCurrentContext(context);
}

DHR_EXPORT void DHR_CALL OnDraw()
{
    bool open = true;
    ImGui::ShowDemoWindow(&open);

    ImGui::Begin("MyWindow", &open);
    ImGui::Button("Button", { 100, 50 });

    ImGui::End();
}

DHR_EXPORT void DHR_CALL OnUpdate()
{

}

DHR_EXPORT void DHR_CALL OnMenuDraw()
{

}