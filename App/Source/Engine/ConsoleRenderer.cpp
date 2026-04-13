#include "ConsoleRenderer.h"

ConsoleRenderer* ConsoleRenderer::consoleRenderer_ = nullptr;

static std::vector<std::string> split(const std::string& s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim))
	{
		result.push_back(item);
	}

	return result;
}

void ConsoleRenderer::Init()
{
}

void ConsoleRenderer::Close()
{
}

void ConsoleRenderer::Draw(int x, int y, int w, int h, std::string buffer)
{
	if (x < 0 || y < 0)
	{
		std::cout << "\nConsoleRenderer::Draw\nInvalid coordinates: (X=" << x << ", Y=" << y << ")" << std::endl;
		return;
	}
	if (!value_.empty())
	{
		std::vector<std::string> splitedBuffer = split(buffer, '\n');

		for (auto split : splitedBuffer)
			value_[y].replace(x, x + split.length(), split); // unused parameter: w, h
	}
}

void ConsoleRenderer::DrawFrame()
{
	for (auto str : value_)
		std::cout << str;
}

void ConsoleRenderer::ClearFrame()
{
	// \033[2J clears the screen, \033[1;1H moves cursor to top-left
	std::cout << "\033[2J\033[1;1H";
}

ConsoleRenderer* ConsoleRenderer::Get(const std::vector<std::string>& value)
{
	if (consoleRenderer_ == nullptr)
	{
		consoleRenderer_ = new ConsoleRenderer(value);
	}
	return consoleRenderer_;
}