#pragma once
#include "../SDK/SDK.h"

namespace Vars
{
	namespace Aimbot
	{
		inline bool Enabled = true;
		inline int Hitbox = 0;
		inline bool Autoshoot = true;
		inline int AimKey = VK_SHIFT;
		inline bool SilentAim = true;
		inline bool IgnoreInvulnerable = true;
		inline bool IgnoreCloaked = true;
	}

	namespace ESP
	{
		inline bool Enabled = true;
		inline bool Outline = false;

		namespace Players
		{
			inline bool Enabled = true;
			inline bool Teammates = false;
			inline bool Name = true;
			inline bool Class = true;
			inline bool Health = true;
			inline bool Cond = true;
			inline bool HealthBar = true;
			inline bool Box = false;
			inline bool BoxCorners = true;
		}
	}

	namespace Visual
	{
		inline bool RemoveVisualRecoil = true;
	}

	namespace Misc
	{
		inline bool Bunnyhop = true;
	}
}