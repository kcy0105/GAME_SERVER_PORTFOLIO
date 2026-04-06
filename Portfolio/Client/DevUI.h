#pragma once
#include "Panel.h"
class DevUI : public Panel
{
public:
	DevUI() {}
	virtual ~DevUI() override {}

	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender(HDC hdc) override;
	virtual void OnRelease() override;
};

