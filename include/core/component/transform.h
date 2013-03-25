#pragma once

#include "math_types.h"
#include "core/component.h"

namespace jormungandr
{
	namespace component
	{
		struct Transform : public Component
		{
			//definition of shortcut usefull for sync.
			uint32_t _renderer;

			uint32_t _parent;

			uint32_t _hierarchyDepth;//all parent id combined. used for ordering.

			alfar::Vector3 _position;
			alfar::Matrix4x4 _matrix;
		};

		inline bool operator<(const Transform& p_A, const Transform& p_B)
		{
			return p_A._hierarchyDepth < p_B._hierarchyDepth;
		}

		namespace transform
		{
			void translate(uint32_t p_ID, alfar::Vector3 p_Delta);
			void setPosition(uint32_t p_ID, alfar::Vector3 p_Pos);
		}
	}

	//**********

	
	namespace manager
	{
		void init(component::Transform& p_Transform, uint32_t p_ID);
	}
}