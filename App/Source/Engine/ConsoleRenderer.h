#pragma once
#include <string>

class ConsoleRenderer
{
public:
	ConsoleRenderer(const ConsoleRenderer&) = delete;
	void operator=(const ConsoleRenderer&) = delete;

	static ConsoleRenderer& Get();

	void Init(int width, int height);
	void Close();

	void Draw(int x, int y, int w, int h, const std::string& buffer);
	void DrawFrame();

private:
	ConsoleRenderer();
	~ConsoleRenderer();

	int m_Width = 0;
	int m_Height = 0;

	std::string m_Buffer;
};