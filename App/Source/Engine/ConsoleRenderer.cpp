#include "ConsoleRenderer.h"
#include <cstdio>
#include "Logging/Logging.h"

static ConsoleRenderer* s_Instance = nullptr;

void ConsoleRenderer::Init(int width, int height)
{
	fwrite("\x1b[?25l", 1, 6, stdout);
	// last column will be new line
	m_Width = width;
	m_Height = height;
	m_Buffer.assign((size_t)m_Width * m_Height, '-');
}

void ConsoleRenderer::Close()
{
	delete s_Instance;
	s_Instance = nullptr;
}

void ConsoleRenderer::Draw(int x, int y, int width, int heigh, const std::string& buffer)
{
	if (x < 0 || y < 0 || x > m_Width || y > m_Height)
	{
		APP_ERROR("%s - Drawing out of bounds (x %d, y %d)", __FUNCTION__, x, y);
		return;
	}

	int endX = x + width;
	int endY = y + heigh;

	if (!buffer.size() || endX > m_Width || endY > m_Height)
	{
		APP_ERROR("%s - Drawing empty buffer or buffer size > %d * %d", __FUNCTION__, width, heigh);
		return;
	}

	int localBufferIndex = 0;

	if (endX > m_Width || endY > m_Height)
	{
		APP_ERROR("%s - Drawing out of bounds > %d * %d", __FUNCTION__, width, heigh);
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

static void FormatBuffer(int width, int height, std::string& buffer)
{
	for (int i = 0; i < height * width; i++)
	{
		int row = i / width;
		int col = i % width;

		// 1. Handle Newlines (The very last character of every row)
		if (col == width - 1)
		{
			buffer[i] = '\n';
		}
		// 2. Handle Horizontal Borders (First and Last Row)
		else if (row == 0 || row == height - 1)
		{
			buffer[i] = '#';
		}
		// 3. Handle Vertical Borders (First and Last visible Column)
		else if (col == 0 || col == width - 2)
		{
			buffer[i] = '#';
		}
	}
}

void ConsoleRenderer::DrawFrame()
{
	FormatBuffer(m_Width, m_Height, m_Buffer);

	// 2. Move cursor to top-left (row 1, col 1)
	fwrite("\x1b[H", 1, 4, stdout);

	fwrite(m_Buffer.c_str(), 1, m_Buffer.size() + 1, stdout);

	fflush(stdout);

	std::fill(m_Buffer.begin(), m_Buffer.end(), '-');
}

ConsoleRenderer::ConsoleRenderer()
{
	// hide cursor
	fwrite("\x1b[?25l", 1, 6, stdout);
}

ConsoleRenderer::~ConsoleRenderer()
{
	// show cursor
	fwrite("\x1b[?25h", 1, 6, stdout);
}

ConsoleRenderer& ConsoleRenderer::Get()
{
	if (!s_Instance)
		s_Instance = new ConsoleRenderer();

	return *s_Instance;
}