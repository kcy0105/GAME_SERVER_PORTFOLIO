#include "pch.h"
#include "LogManager.h"
#include <fstream>

void LogManager::Init(fs::path path)
{
	_path = path;
}

void LogManager::InitLog(string key)
{
	_logs[key] = vector<string>();
}

void LogManager::AddLog(string key, string log)
{
	if (_logs.find(key) == _logs.end())
		InitLog(key);

	_logs[key].push_back(log);
}

void LogManager::WriteLog(string key)
{
    auto it = _logs.find(key);
    if (it == _logs.end())
        return;

    fs::path dir(_path);
    fs::path filePath = dir / (key + ".txt");

    std::ofstream file(filePath);

    if (!file.is_open())
        return;

    for (const string& log : it->second)
    {
        file << log << "\n";
    }

    file.close();
}
