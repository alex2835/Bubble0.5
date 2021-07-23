
#include "ui_module.h"

namespace Bubble
{
	UIModule::UIModule(const std::string& name)
		: mIsOpen(true),
		  mWindowFlags(0),
		  mName(name)
	{}

    bool UIModule::IsOpen()
    {
        return mIsOpen;
    }

    UIModule::~UIModule()
    {
    } 

}