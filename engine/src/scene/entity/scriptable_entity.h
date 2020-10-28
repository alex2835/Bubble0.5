#pragma once

//#include "entity.h"
//
//
//namespace Bubble
//{
//	struct ScriptableEntity
//	{
//		Entity mEntity;
//		friend class Scene;
//
//		virtual ~ScriptableEntity() {}
//
//		template<typename T>
//		T& GetComponent()
//		{
//			return mEntity.GetComponent<T>();
//		}
//	
//	protected:
//		virtual void OnCreate() {}
//		virtual void OnDestroy() {}
//		virtual void OnUpdate(DeltaTime dt) {}
//	};
//}