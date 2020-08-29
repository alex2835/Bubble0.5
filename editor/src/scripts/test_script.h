
#include "entity/scriptable_entity.h"


namespace Bubble
{
	class TestScript : public ScriptableEntity
	{

		void OnCreate() override
		{

		}


		void OnDestroy() override
		{

		}


		void OnUpdate(DeltaTime dt) override
		{
			LOG_TRACE("Update scriptable entity. Delta time: {0}", dt.GetSeconds());
		}

	};
}