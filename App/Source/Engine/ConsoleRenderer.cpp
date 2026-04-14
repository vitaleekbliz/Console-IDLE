#include "ConsoleRenderer.h"

void ConsoleRenderer::Init(int width, int height)
{
	// last column will be new line
	m_Width = width;
	m_Height = height;
	m_Buffer.assign((size_t)m_Width * m_Height, '-');
}

void ConsoleRenderer::Close()
{
	m_Buffer.clear();
	m_Width = 0;
	m_Height = 0;
}

void ConsoleRenderer::Draw(int x, int y, int width, int heigh, const std::string& buffer)
{
	if (x < 0 || y < 0 || x > m_Width || y > m_Height)
	{
		ERROR("%s - Drawing out of bounds (x %d, y %d)", __FUNCTION__, x, y);
		return;
	}

	int endX = x + width;
	int endY = y + heigh;

	if (!buffer.size() || endX > m_Width || endY > m_Height)
	{
		ERROR("%s - Drawing empty buffer or buffer size > %d * %d", __FUNCTION__, width, heigh);
		return;
	}

	int localBufferIndex = 0;

	if (endX > m_Width || endY > m_Height)
	{
		ERROR("%s - Drawing out of bounds > %d * %d", __FUNCTION__, width, heigh);
		return;
	}

	for (int j = y; j < endY; j++)
	{
		for (int i = x; i < endX; i++)
		{
			int screenIndex = (j * m_Width) + (i);

			m_Buffer[screenIndex] = buffer[localBufferIndex];
			localBufferIndex++;
		}
	}
}

void ConsoleRenderer::DrawBorder()
{
	int endI = m_Buffer.length();
	for (int i = 0; i < m_Buffer.length(); i++)
	{
		if (
			(i > 0 && i < m_Width)
			|| (i % m_Width == m_Width - 2)
			|| (i % m_Width == 0)
			|| (i >= endI - m_Width))
		{
			m_Buffer[i] = '#';
		}
	}
}

void ConsoleRenderer::DrawFrame()
{
	// change every last column to be new line
	for (int i = 1; i <= m_Height; i++)
	{
		// last column
		int index = (m_Width * i) - 1;
		m_Buffer[index] = '\n';
	}

	// move cursor to top left
	std::cout << "\033[1;1H" << m_Buffer;

	m_Buffer.assign(m_Buffer.size(), ' ');
}

ConsoleRenderer& ConsoleRenderer::Get()
{
	static ConsoleRenderer instance;
	return instance;
}