#pragma once
#include "Object.h"
#include <vector>
#include <memory>
#include "Logging/Logging.h"
#include "MemoryArena.h"

class ObjectCreator
{
private:
public:
	ObjectCreator();
	~ObjectCreator() = default;

	void renderAll();
	void updateAll();

	template <typename T, typename... Args>
		requires std::derived_from<T, Object>
	T* create(Args&&... args)
	{
		if (m_ObjectArenas.empty() || m_ObjectArenas.back().IsFull())
		{
			TRACE("Memory arena is full, creating new arena");
			m_ObjectArenas.emplace_back(m_ArenaSize);
		};

		T* object = m_ObjectArenas.back().alloc<T>(std::forward<Args>(args)...);
		m_Objects.push_back(object);
		return object;
	};

private:
	std::vector<MemoryArena> m_ObjectArenas;
	std::vector<Object*> m_Objects;

	const size_t m_ArenaSize = 1024 * 64;
};
