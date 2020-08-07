#pragma once

#include <vector>

#include "application/application.h"
#include "log/log.h"


// Implementation on client side
extern Bubble::Application* CreateApplication();


int main(int argc, char* argv[])
{
	Bubble::Log::init();

	Bubble::Application* app = Bubble::CreateApplication();
	app->Run();
	
	delete app;
	return 0;
}