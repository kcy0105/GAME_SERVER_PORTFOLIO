#pragma once
#include "Button.h"
class LatencyLevelButton : public Button
{
public:
	LatencyLevelButton() {}
	virtual ~LatencyLevelButton() {}

	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender(HDC hdc) override;
	virtual void OnRelease() override;

private:
	void OnClickButton();
};

