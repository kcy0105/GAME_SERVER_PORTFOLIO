#pragma once
class Object
{
public:
	Object();
	virtual ~Object();

	bool IsPlayer() const { return _isPlayer; }

public:
	Protocol::ObjectInfo* objectInfo;
	Protocol::PosInfo* posInfo;

public:
	atomic<weak_ptr<Room>> room;

public:
	static atomic<uint64> s_idGenerator;

protected:
	bool _isPlayer = false;
};

