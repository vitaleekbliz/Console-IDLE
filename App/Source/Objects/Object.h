#pragma once
#include "Logging/Logging.h"

class ResourcesManager;
class ObjectCreator;

class Object
{
public:
	Object(ResourcesManager* resourcesManager, ObjectCreator* objectCreator);
	virtual ~Object() = default;

	virtual void render() {};
	virtual void update() {};

	const bool isRenderable() const;
	void setRenderMode(bool state);

protected:
	template <typename T, typename... Args>
		requires std::derived_from<T, Object>
	T* createObject(Args&&... args)
	{
		if (!m_ObjectCreator)
		{
			APP_ERROR("%s doesn't have Object Creator", typeid(*this).name())
			return nullptr;
		}
		m_ObjectCreator->create()
	}

private:
	ResourcesManager* m_ResourceManager = nullptr;
	ObjectCreator* m_ObjectCreator = nullptr;
	bool m_isRenderable = false;
};
