#include "core/component/renderer.h"

#include "utils/logger.h"
#include "mat4x4.h"
#include "vector2.h"

using namespace jormungandr;
using namespace jormungandr::component;

void manager::init(Renderer& p_Renderer, uint32_t p_ID)
{
	p_Renderer._matID = 0;
	p_Renderer._type = ComponentType::RENDERER;

	p_Renderer._id = p_ID;

	p_Renderer._transform = alfar::mat4x4::identity();

	const float defaultX[] = {0, 32, 0, 32, 32, 0};
	const float defaultY[] = {0, 0, 32, 0, 32, 32};
	const float defaultU[] = {0, 1, 0, 1, 1, 0};
	const float defaultV[] = {0, 0, 1, 0, 1, 1};

	for(uint8_t i = 0; i < 6; ++i)
	{
		p_Renderer._vertex[i]._position = alfar::vector3::create(defaultX[i], defaultY[i],1);
		p_Renderer._vertex[i]._uv = alfar::vector2::create(defaultU[i],defaultV[i]);
		p_Renderer._vertex[i]._color = alfar::vector3::create(-1,-1,-1);
	}
}

//====================================================

void renderer::setMaterial(Renderer& p_Renderer, uint32_t p_MaterialID)
{
	p_Renderer._matID = p_MaterialID;
}
//=====================================================

void renderer::setTransform(Renderer& p_Renderer, alfar::Matrix4x4 p_Transform)
{

}