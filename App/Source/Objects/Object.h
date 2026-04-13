#pragma once

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	virtual void render() {};
	virtual void update() {};

	const bool isActive() const;
	void setActive();

private:
	bool m_isActive = false;
};
