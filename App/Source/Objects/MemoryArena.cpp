#include "MemoryArena.h"
#include <string.h>

MemoryArena::MemoryArena(const MemoryArena& other)
{
	// This function throws fatal error if copying arena with different memory sizes
	// In this case arena will only exist inside Object creator so every arena should be fixed size
	// General purpose was to use templates and implement basic Memory Arena.
	if (m_Current)
	{
		WARN("[Memory Arena] Copying To non empty memory arena");
	}

	size_t ocupiedMemory = other.m_Current - other.m_Base;

	if (m_Size < other.m_Size)
	{
		if (m_Size < ocupiedMemory)
		{
			FATAL("Size is different from in %s", __FUNCTION__);
		}
	}

	m_Size = other.m_Size;

	memcpy_s(m_Base, ocupiedMemory, other.m_Base, ocupiedMemory);
}

void MemoryArena::Clear()
{
	m_Current = m_Base;
	m_isFull = false;
}

bool MemoryArena::IsFull() const
{
	return m_isFull;
}
