//===========================================================================//
// 
// 
//		A base class for the client-side representation of entities.
//	
//
//===========================================================================//

#ifndef C_BASEENTITY_H
#define C_BASEENTITY_H
#ifdef _WIN32
#pragma once
#endif

#include "../NetVarManager/NetVarManager.h"

// WARNING: Although this class extends from IClientEntity like other classes copy/pasted from SSDK, this class calls things by VFunc Indexes instead of using direct virtual calls.
class C_BaseCombatWeapon;

//-----------------------------------------------------------------------------
// Purpose: Base client side entity object
//-----------------------------------------------------------------------------
class C_BaseEntity : public IClientEntity
{
public:
	inline Vector WorldSpaceCenter()
	{
		float* flRet = VFunc_Get<float* (__thiscall*)(void*)>(this, 66u)(this);
		Vector vRet = Vector(flRet[0], flRet[1], flRet[2]);
		return vRet;
	}

	inline bool InLocalTeam()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 78u)(this);
	}

	inline int GetHealth()
	{
		return VFunc_Get<int(__thiscall*)(void*)>(this, 106u)(this);
	}

	inline int GetMaxHealth()
	{
		return VFunc_Get<int(__thiscall*)(void*)>(this, 107u)(this);
	}

	inline bool IsAlive()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 132u)(this);
	}

	inline bool IsPlayer()
	{
		return VFunc_Get<bool(__thiscall*)(void*)>(this, 133u)(this);
	}

	M_NETVAR(GetFlags, int, "CBasePlayer", "m_fFlags");
	M_NETVAR(GetCollideableMins, Vector, "CBaseEntity", "m_vecMins");
	M_NETVAR(GetCollideableMaxs, Vector, "CBaseEntity", "m_vecMaxs");
	M_NETVAR(GetHitboxSet, int, "CBaseAnimating", "m_nHitboxSet");
	M_NETVAR(m_iClass, int, "CTFPlayer", "m_iClass");
	M_NETVAR(GetTeamNumber, int, "CBaseEntity", "m_iTeamNum");
	M_NETVAR(m_nPlayerCond, int, "CTFPlayer", "m_nPlayerCond");
	M_NETVAR(m_nPlayerCondEx, int, "CTFPlayer", "m_nPlayerCondEx");
	M_NETVAR(m_nPlayerCondEx2, int, "CTFPlayer", "m_nPlayerCondEx2");
	M_NETVAR(m_nPlayerCondEx3, int, "CTFPlayer", "m_nPlayerCondEx3");
	M_NETVAR(m_nPlayerCondEx4, int, "CTFPlayer", "m_nPlayerCondEx4");
	M_NETVAR(GetObserverMode, int, "CBasePlayer", "m_iObserverMode");
	M_NETVAR(m_iFOV, int, "CBasePlayer", "m_iFOV");
	M_NETVAR(m_nModelIndex, int, "CBaseEntity", "m_nModelIndex");

	inline int SaveData(const char* const context, const int slot, const int type)
	{
		return reinterpret_cast<int(__thiscall*)(void*, const char*, int, int)>(g_Pattern.Find("client.dll", "55 8B EC 81 EC 90 ? ? ? A1 30 D5 6A ? 33 C5 89 45 FC 8B 45 08 53"))(this, context, slot, type);
	}

	inline C_BaseCombatWeapon* GetActiveWeapon()
	{
		static const int nOffset = GetNetVar("CBaseCombatCharacter", "m_hActiveWeapon");
		CBaseHandle hHandle = *reinterpret_cast<CBaseHandle*>(reinterpret_cast<DWORD>(this) + nOffset);
		C_BaseCombatWeapon* pWeapon = reinterpret_cast<C_BaseCombatWeapon*>(I::ClientEntityList->GetClientEntityFromHandle(hHandle));
		return pWeapon;
	}

	inline bool GetHitboxPosition(const int nHitbox, Vector& vPosition)
	{
		const model_t* pModel = this->GetModel();

		if (!pModel)
			return false;

		const studiohdr_t* pStudioHdr = I::ModelInfo->GetStudiomodel(pModel);

		if (!pStudioHdr)
			return false;

		const mstudiobbox_t* pBox = pStudioHdr->pHitbox(nHitbox, this->GetHitboxSet());

		if (!pBox || (pBox->bone >= 128) || (pBox->bone < 0))
			return false;

		matrix3x4_t Matrix[128];
		if (!SetupBones(Matrix, 128, 0x100, I::GlobalVars->curtime))
			return false;

		VectorTransform((pBox->bbmax + pBox->bbmin) * 0.5f, Matrix[pBox->bone], vPosition);
		return true;
	}

	inline bool IsOnGround()
	{
		return (this->GetFlags() & FL_ONGROUND);
	}

	inline Vector EyePosition()
	{
		static const int nOffset = GetNetVar("CBasePlayer", "m_vecViewOffset[0]");
		Vector vOffset = *reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(this) + nOffset);
		return (vOffset + GetAbsOrigin());
	}

	//Credits to KGB
	inline bool InCond(const int iCond)
	{
		switch (iCond / 32)
		{
		case 0:
		{
			const int bit = (1 << iCond);
			if ((m_nPlayerCond() & bit) == bit)
				return true;

			break;
		}
		case 1:
		{
			const int bit = 1 << (iCond - 32);
			if ((m_nPlayerCondEx() & bit) == bit)
				return true;

			break;
		}
		case 2:
		{
			const int bit = 1 << (iCond - 64);
			if ((m_nPlayerCondEx2() & bit) == bit)
				return true;

			break;
		}
		case 3:
		{
			const int bit = 1 << (iCond - 96);
			if ((m_nPlayerCondEx3() & bit) == bit)
				return true;

			break;
		}
		case 4:
		{
			const int bit = 1 << (iCond - 128);
			if ((m_nPlayerCondEx4() & bit) == bit)
				return true;

			break;
		}
		default:
			break;
		}

		return false;
	}

	inline bool IsInvulnerable()
	{
		return InCond(TF_COND_INVULNERABLE);
	}

	inline bool IsCloaked()
	{
		return InCond(TF_COND_STEALTHED)
			|| InCond(TF_COND_STEALTHED_BLINK);
	}

	inline bool IsScoped()
	{
		return InCond(TF_COND_ZOOMED);
	}
};

#endif
