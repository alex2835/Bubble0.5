#pragma once

#include "application/application.h"
#include "bubble.h"

// Implementation on client side
extern Bubble::Application* CreateApplication();

int main(int argc, char* argv[])
{
	Bubble::Log::Init();
	try
	{
		auto* application = CreateApplication();
		application->Run();
		//delete application;
	}
	catch (const std::exception& e)
	{
		LOG_CORE_ERROR("Exception has been triggered:\n {}", e.what());
	}
	return 0;
}