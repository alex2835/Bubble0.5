#pragma once

extern Bubble::Application* create_application();


int main(int argc, char** argv)
{
	Bubble::Log::init();

	Bubble::Application* app = Bubble::create_application();
	app->run();
	
	delete app;
	return 0;
}