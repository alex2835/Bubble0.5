#pragma once

#include "engine.h"

namespace Bubble
{
    struct SceneCamera : public FreeCamera
    {
        Input& mInput;
        float mBoostSpeed = 5.0f;

        SceneCamera(Input& input, const glm::vec3& position = glm::vec3(0.0f))
            : FreeCamera(position),
              mInput(input)
        {}

        void OnUpdate(DeltaTime dt)
        {
            if (mInput.IsMouseButtonPressed(SDL_BUTTON_RIGHT))
            {
            	// Catch cursor
            	SDL_SetRelativeMouseMode(SDL_TRUE);
            
            	// Boost
                float boost = mInput.IsKeyPressed(SDLK_LSHIFT) ? mBoostSpeed : 1.0f;
            
                float max_speed = MaxSpeed * DeltaSpeed;
            
                // Speed x
                if (mInput.IsKeyPressed(SDLK_w))
                {
                    ProcessMovement(CameraMovement::FORWARD, dt);
                }
                else if (mInput.IsKeyPressed(SDLK_s))
                {
                    ProcessMovement(CameraMovement::BACKWARD, dt);
                }
            
                // Speed y
                if (mInput.IsKeyPressed(SDLK_d))
                {
                    ProcessMovement(CameraMovement::RIGHT, dt);
                }
                else if (mInput.IsKeyPressed(SDLK_a))
                {
                    ProcessMovement(CameraMovement::LEFT, dt);
                }
            
                ProcessMouseMovementShift(-mInput.fGetMouseRelX(), -mInput.fGetMouseRelY());
                ProcessMouseScroll(-mInput.GetMouseWheelOffset());
            
                // Process boost
                if (boost > 1.0f)
                {
                    float old_speedx = SpeedX;
                    float old_speedy = SpeedY;
                    float old_maxspeed = MaxSpeed;
            
                    SpeedX *= boost;
                    SpeedY *= boost;
                    MaxSpeed *= boost;
            
                    FreeCamera::Update(dt);
            
                    SpeedX = old_speedx;
                    SpeedY = old_speedy;
                    MaxSpeed = old_maxspeed;
                }
                else {
                    FreeCamera::Update(dt);
                }
            
            }
            else {
            	// Release cursor
            	SDL_SetRelativeMouseMode(SDL_FALSE);
            
            	// Inertia
            	FreeCamera::Update(dt);
            }
        }
    };

}