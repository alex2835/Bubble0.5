
#include "entt/entt.hpp"
#include "engine.h"

// Just create meta information at the compiletime
void InitComponents()
{
   entt::registry r;
   auto entity = r.create();
   r.emplace<Bubble::TagComponent>(entity);
   r.emplace<Bubble::PositionComponent>(entity);
   r.emplace<Bubble::RotationComponent>(entity);
   r.emplace<Bubble::ScaleComponent>(entity);
   r.emplace<Bubble::TransformComponent>(entity);
   r.emplace<Bubble::LightComponent>(entity);
   r.emplace<Bubble::ModelComponent>(entity);
}