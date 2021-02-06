#pragma once

#include "core/log.h"
#include "core/application.h"

#include <vector>


// Implementation on client side
extern Bubble::Application* CreateApplication();


int main(int argc, char* argv[])
{
	Bubble::Log::init();
	try
	{
		Bubble::Application* app = CreateApplication();
		app->Run();
		delete app;
	}
	catch (const std::exception& e)
	{
		LOG_CORE_ERROR("Exception has been trigered:\n {}", e.what());
	}
	return 0;
}