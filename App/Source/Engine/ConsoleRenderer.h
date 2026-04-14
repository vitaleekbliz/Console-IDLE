#pragma once
#include "Logging/Logging.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class ConsoleRenderer
{
public:
	ConsoleRenderer(const ConsoleRenderer&) = delete;
	void operator=(const ConsoleRenderer&) = delete;

	static ConsoleRenderer& Get();

	void Init(int width, int height);
	void Close();
	void Draw(int x, int y, int w, int h, const std::string& buffer);
	void DrawBorder();
	void DrawFrame();

private:
	ConsoleRenderer() = default;
	~ConsoleRenderer() = default;

	int m_Width = 0;
	int m_Height = 0;

	std::string m_Buffer;
};