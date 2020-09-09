#pragma once

#include "application/application.h"
#include "log/log.h"

#include <vector>


// Implementation on client side
extern Bubble::Application* CreateApplication();


int main(int argc, char* argv[])
{
	Bubble::Log::init();
	try
	{
		Bubble::Application* app = CreateApplication();
		app->SetCurrentDir(argv[0]);
		app->Run();
		delete app;
	}
	catch (const std::exception& e) {
		LOG_CORE_ERROR("Exception has been trigered:\n {0}", e.what());
	}

	return 0;
}
