#pragma once

#include "engine.h"

namespace Bubble
{
    struct SceneCamera : public FreeCamera
    {
        Input* mInput;
        float mBoostSpeed = 5.0f;

        SceneCamera(Input* input, const glm::vec3& position = glm::vec3(0.0f))
            : FreeCamera(position),
              mInput(input)
        {}

        void OnUpdate(DeltaTime dt)
        {
            //if (Input::IsMouseButtonPressed(SDL_BUTTON_RIGHT))
            //{
            //	// Catch cursor
            //	SDL_SetRelativeMouseMode(SDL_TRUE);
            //
            //	// Boost
            //    float boost = Input::IsKeyPressed(SDLK_LSHIFT) ? mBoostSpeed : 1.0f;
            //
            //    float max_speed = MaxSpeed * DeltaSpeed;
            //
            //    // Speed x
            //    if (Input::IsKeyPressed(SDLK_w))
            //    {
            //        ProcessMovement(CameraMovement::FORWARD, dt);
            //    }
            //    else if (Input::IsKeyPressed(SDLK_s))
            //    {
            //        ProcessMovement(CameraMovement::BACKWARD, dt);
            //    }
            //
            //    // Speed y
            //    if (Input::IsKeyPressed(SDLK_d))
            //    {
            //        ProcessMovement(CameraMovement::RIGHT, dt);
            //    }
            //    else if (Input::IsKeyPressed(SDLK_a))
            //    {
            //        ProcessMovement(CameraMovement::LEFT, dt);
            //    }
            //
            //    ProcessMouseMovementShift(-Input::fGetMouseRelX(), -Input::fGetMouseRelY());
            //    ProcessMouseScroll(-Input::GetMouseWheelOffset());
            //
            //    // Process boost
            //    if (boost > 1.0f)
            //    {
            //        float old_speedx = SpeedX;
            //        float old_speedy = SpeedY;
            //        float old_maxspeed = MaxSpeed;
            //
            //        SpeedX *= boost;
            //        SpeedY *= boost;
            //        MaxSpeed *= boost;
            //
            //        FreeCamera::Update(dt);
            //
            //        SpeedX = old_speedx;
            //        SpeedY = old_speedy;
            //        MaxSpeed = old_maxspeed;
            //    }
            //    else {
            //        FreeCamera::Update(dt);
            //    }
            //
            //}
            //else {
            //	// Release cursor
            //	SDL_SetRelativeMouseMode(SDL_FALSE);
            //
            //	// Inertia
            //	FreeCamera::Update(dt);
            //}
        }
    };

}