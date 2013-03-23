#include "core/component/transform.h"

#include "core/engine.h"
#include "core/scene.h"

#include "core/manager/transformmanager.h"

#include "mat4x4.h"
#include "vector3.h"

using namespace jormungandr;
using namespace jormungandr::component;

void manager::init(Transform& p_Transform, uint32_t p_ID)
{
	p_Transform._position = alfar::vector3::create(0,0,0);
	p_Transform._matrix = alfar::mat4x4::identity();

	p_Transform._type = component::ComponentType::TRANSFORM;
	p_Transform._id = p_ID;
}

//========================================================

void transform::translate(uint32_t p_ID, alfar::Vector3 p_Delta)
{
	Transform& trans = jormungandr::g_engine->_current->_transformManager._datas[p_ID];

	trans._position = alfar::vector3::add(trans._position, p_Delta);

	jormungandr::transformmanager::toSync(jormungandr::g_engine->_current->_transformManager, p_ID);
}