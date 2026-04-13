#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class ConsoleRenderer
{
public:
	ConsoleRenderer(ConsoleRenderer& other) = delete;

	void operator=(const ConsoleRenderer&) = delete;

	static ConsoleRenderer* Get(const std::vector<std::string>& value);

	void Init();
	void Close();
	void Draw(int x, int y, int w, int h, std::string buffer);
	void DrawFrame();
	void ClearFrame();

protected:
	ConsoleRenderer(const std::vector<std::string> value)
		: value_(value) {}
	~ConsoleRenderer();

	static ConsoleRenderer* consoleRenderer_;

	std::vector<std::string> value_;
};