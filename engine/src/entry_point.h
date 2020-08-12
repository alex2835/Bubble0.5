#pragma once

#include <vector>

#include "application/application.h"
#include "log/log.h"


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
		LOG_CORE_ERROR("Exception has been trigered: {0}", e.what());
	}

	return 0;
}
