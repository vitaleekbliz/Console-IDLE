#pragma once
#include "Logging/Logging.h"
#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <new>

class MemoryArena
{
public:
	MemoryArena() = default;
	MemoryArena(size_t size)
		: m_Size(size)
	{
		APP_TRACE("[Memory Arena] Creating memory arena %d", size);
		m_Base = static_cast<uint8_t*>(std::malloc(size));
		if (!m_Base)
		{
			APP_ERROR("[Memory Arena] Allocatin failed!");
		}
		m_Current = m_Base;
	}
	MemoryArena(const MemoryArena& other);
	MemoryArena& operator=(const MemoryArena&) = delete;

	// Cleanup
	~MemoryArena() { std::free(m_Base); };

	template <typename T, typename... Args>
	T* alloc(Args&&... args)
	{
		// 1. Calculate alignment padding
		size_t alignment = alignof(T);
		uintptr_t currentAddr = reinterpret_cast<uintptr_t>(m_Current);
		uintptr_t padding = (alignment - (currentAddr % alignment)) % alignment;

		if (m_Current - m_Base + padding + sizeof(T) > m_Size)
		{
			APP_TRACE("Memory arena ran out of memory");
			m_isFull = true;
			return nullptr; // Out of memory
		}

		// 2. Move pointer and construct
		m_Current += padding;
		T* ptr = new (m_Current) T(std::forward<Args>(args)...);
		m_Current += sizeof(T);

		return ptr;
	};

	void Clear();
	bool IsFull() const;

private:
	uint8_t* m_Base = nullptr;
	uint8_t* m_Current = nullptr;
	size_t m_Size = 0;
	bool m_isFull = false;
};
