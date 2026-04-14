#pragma once

class ResourcesManager;

class Object
{
public:
	Object(ResourcesManager* resourcesManager);
	virtual ~Object() = default;

	virtual void render() {};
	virtual void update() {};

	const bool isRenderable() const;
	void setRenderMode(bool state);

protected:
private:
	ResourcesManager* m_ResourceManager = nullptr;
	bool m_isRenderable = false;
};
