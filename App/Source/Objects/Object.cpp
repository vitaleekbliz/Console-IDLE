#include "Object.h"

Object::Object(ResourcesManager* resourcesManager)
	: m_ResourceManager(resourcesManager)
{
}

const bool Object::isRenderable() const
{
	return m_isRenderable;
}

void Object::setRenderMode(bool state)
{
	m_isRenderable = state;
}
