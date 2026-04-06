#pragma once
#include "Button.h"
class SyncModeButton : public Button
{
public:
	SyncModeButton() {}
	virtual ~SyncModeButton() {}

	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender(HDC hdc) override;
	virtual void OnRelease() override;

private:
	void OnClickButton();
};

