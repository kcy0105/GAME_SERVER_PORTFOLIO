#include "pch.h"
#include "FlipbookRenderer.h"
#include "Flipbook.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Object.h"
#include "Texture.h"

void FlipbookRenderer::Init()
{
}

void FlipbookRenderer::SetFlipbook(Flipbook* flipbook)
{
	_flipbooks.clear();

	if (flipbook)
		_flipbooks.push_back(flipbook);

	_fbIndex = 0;
	_idx = 0;
	_sumTime = 0.f;
}

void FlipbookRenderer::SetFlipbook(const vector<Flipbook*>& flipbooks)
{
	_flipbooks = flipbooks;

	_fbIndex = 0;
	_idx = 0;
	_sumTime = 0.f;
}

Flipbook* FlipbookRenderer::GetCurrentFlipbook()
{
	if (_flipbooks.empty())
		return nullptr;

	return _flipbooks[_fbIndex];
}

void FlipbookRenderer::Update()
{
	Flipbook* fb = GetCurrentFlipbook();
	if (fb == nullptr)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	int32 frameCount = (fb->GetEnd() - fb->GetStart() + 1);
	float delta = fb->GetDuration() / frameCount;

	if (_sumTime >= delta)
	{
		_sumTime = 0.f;
		_idx++;

		// 마지막 프레임 도달
		if (_idx >= frameCount)
		{
			if (fb->GetLoop())
			{
				_idx = 0;
			}
			else
			{
				// 다음 Flipbook으로 이동
				if (_fbIndex + 1 < (int32)_flipbooks.size())
				{
					_fbIndex++;
					_idx = 0;
				}
				else
				{
					// 마지막 Flipbook이면 멈춤
					_idx = frameCount - 1;
				}
			}
		}
	}
}

void FlipbookRenderer::LateUpdate()
{
}

void FlipbookRenderer::Render(HDC hdc)
{
	Flipbook* fb = GetCurrentFlipbook();
	if (fb == nullptr)
		return;

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2 pos = GetOwner()->GetPos();

	int32 drawX = (int32)pos.x - fb->GetPivot().x - ((int32)cameraPos.x - GWinSizeX / 2);
	int32 drawY = (int32)pos.y - fb->GetPivot().y - ((int32)cameraPos.y - GWinSizeY / 2);

	int32 width = fb->GetSize().x;
	int32 height = fb->GetSize().y;

	int32 srcX = (fb->GetStart() + _idx) * width;
	int32 srcY = fb->GetLine() * height;

	HDC srcDC = fb->GetTexture()->GetDC();
	COLORREF transparent = fb->GetTexture()->GetTransparent();

	// 일반 렌더링
	if (_flipX == false)
	{
		::TransparentBlt(hdc,
			drawX,
			drawY,
			width,
			height,
			srcDC,
			srcX,
			srcY,
			width,
			height,
			transparent);
	}
	// 좌우 반전 렌더링
	else
	{
		HDC tempDC = CreateCompatibleDC(hdc);
		HBITMAP tempBmp = CreateCompatibleBitmap(hdc, width, height);
		HBITMAP oldBmp = (HBITMAP)SelectObject(tempDC, tempBmp);

		// 보간 제거 (중요)
		SetStretchBltMode(tempDC, COLORONCOLOR);

		// 1. 뒤집어서 복사 (1px 보정 포함)
		StretchBlt(tempDC,
			0, 0, width, height,
			srcDC,
			srcX + width - 1,   // 핵심
			srcY,
			-(width - 1),       // 핵심
			height,
			SRCCOPY);

		// 2. 투명 처리
		TransparentBlt(hdc,
			drawX,
			drawY,
			width,
			height,
			tempDC,
			0,
			0,
			width,
			height,
			transparent);

		// 정리
		SelectObject(tempDC, oldBmp);
		DeleteObject(tempBmp);
		DeleteDC(tempDC);
	}
}

void FlipbookRenderer::Release()
{
}