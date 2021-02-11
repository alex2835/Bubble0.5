
#include "ui_module.h"

namespace Bubble
{
	std::atomic<int> UIModule::sGlobalIDCounter = 0;

	UIModule::UIModule(const std::string& name)
		: mID(sGlobalIDCounter++),
		  mIsOpen(true),
		  mWindowFlags(0),
		  mName(name)
	{}

    bool UIModule::IsOpen()
    {
        return mIsOpen;
    }

    int UIModule::GetID()
    {
        return mID;
    }

    UIModule::~UIModule()
    {

    } 

}