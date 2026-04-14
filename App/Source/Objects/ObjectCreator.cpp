#include "ObjectCreator.h"

ObjectCreator::ObjectCreator()
{
	m_Objects.reserve(100);
}

void ObjectCreator::updateAll()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->update();
	}
}

void ObjectCreator::renderAll()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->isRenderable())
			m_Objects[i]->render();
	}
}