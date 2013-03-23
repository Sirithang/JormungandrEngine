#pragma once

#include "math_types.h"
#include "core/component.h"

namespace jormungandr
{
	namespace component
	{
		struct Transform : public Component
		{
			alfar::Vector3 _position;

			alfar::Matrix4x4 _matrix;
		};

		namespace transform
		{
			void translate(uint32_t p_ID, alfar::Vector3 p_Delta);
		}
	}

	//**********

	
	namespace manager
	{
		void init(component::Transform& p_Transform, uint32_t p_ID);
	}
}