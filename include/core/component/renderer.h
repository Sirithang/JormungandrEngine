#pragma once

#include "core/component.h"
#include "vector3.h"

namespace jormungandr
{
	namespace component
	{
		namespace renderer
		{
			struct Vertex
			{
				alfar::Vector3 _position;
				alfar::Vector2 _uv;
				alfar::Vector3 _color;
			};
		}

		struct Renderer : public Component
		{
			uint16_t _matID;
			renderer::Vertex _vertex[6];
			alfar::Matrix4x4 _transform;
		};

		namespace renderer
		{
			void setMaterial(Renderer& p_Renderer, uint32_t p_MaterialID);

			void setTransform(Renderer& p_Renderer, alfar::Matrix4x4 p_Transform);
		}
	}

	//******

	namespace manager
	{
			void init(component::Renderer& p_Renderer, uint32_t p_ID);
	}
}