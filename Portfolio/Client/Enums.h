#pragma once

enum class SceneType
{
	None,
	DevScene,
};

enum class ColliderType
{
	Box,
	Circle,
};

enum class SyncMode
{
	Snap,
	Interpolation,
	Velocity,
	DeadReckoning_Snap,
	DeadReckoning_Follow,

	Count,
};