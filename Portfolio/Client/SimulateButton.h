#pragma once
#include "Button.h"
class SimulateButton : public Button
{
public:
	SimulateButton() {}
	virtual ~SimulateButton() {}

	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender(HDC hdc) override;
	virtual void OnRelease() override;

private:
	void OnClickButton();
};

