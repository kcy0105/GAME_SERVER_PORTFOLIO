#pragma once
class LogManager
{
	DECLARE_SINGLE(LogManager)

public:
	void Init(fs::path path);
	void InitLog(string key);
	void AddLog(string key, string log);
	void WriteLog(string key);

private:
	unordered_map<string, vector<string>> _logs;
	fs::path _path;
};