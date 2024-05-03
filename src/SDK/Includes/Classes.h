#pragma once
#include "vector.h"

enum StereoEye_t
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};

enum EWeaponSlots
{
	SLOT_PRIMARY,
	SLOT_SECONDARY,
	SLOT_MELEE
};

struct Rect_t { int x, y, w, h; };

enum EObserverModes
{
	OBS_MODE_NONE = 0,		// not in spectator mode
	OBS_MODE_DEATHCAM,		// special mode for death cam animation
	OBS_MODE_FREEZECAM,		// zooms to a target, and freeze-frames on them
	OBS_MODE_FIXED,			// view from a fixed camera position
	OBS_MODE_FIRSTPERSON,	// follow a player in first person view
	OBS_MODE_THIRDPERSON,	// follow a player in third person view
	OBS_MODE_ROAMING,		// free roaming
};

enum //this probably needs an updating
{
	TF_WEAPON_NONE = 0,
	TF_WEAPON_BAT,
	TF_WEAPON_BOTTLE,
	TF_WEAPON_FIREAXE,
	TF_WEAPON_CLUB,
	TF_WEAPON_CROWBAR,
	TF_WEAPON_KNIFE,
	TF_WEAPON_FISTS,
	TF_WEAPON_SHOVEL,
	TF_WEAPON_WRENCH,
	TF_WEAPON_BONESAW,
	TF_WEAPON_SHOTGUN_PRIMARY,
	TF_WEAPON_SHOTGUN_SOLDIER,
	TF_WEAPON_SHOTGUN_HWG,
	TF_WEAPON_SHOTGUN_PYRO,
	TF_WEAPON_SCATTERGUN,
	TF_WEAPON_SNIPERRIFLE,
	TF_WEAPON_MINIGUN,
	TF_WEAPON_SMG,
	TF_WEAPON_SYRINGEGUN_MEDIC,
	TF_WEAPON_TRANQ,
	TF_WEAPON_ROCKETLAUNCHER,
	TF_WEAPON_GRENADELAUNCHER,
	TF_WEAPON_PIPEBOMBLAUNCHER,
	TF_WEAPON_FLAMETHROWER,
	TF_WEAPON_GRENADE_NORMAL,
	TF_WEAPON_GRENADE_CONCUSSION,
	TF_WEAPON_GRENADE_NAIL,
	TF_WEAPON_GRENADE_MIRV,
	TF_WEAPON_GRENADE_MIRV_DEMOMAN,
	TF_WEAPON_GRENADE_NAPALM,
	TF_WEAPON_GRENADE_GAS,
	TF_WEAPON_GRENADE_EMP,
	TF_WEAPON_GRENADE_CALTROP,
	TF_WEAPON_GRENADE_PIPEBOMB,
	TF_WEAPON_GRENADE_SMOKE_BOMB,
	TF_WEAPON_GRENADE_HEAL,
	TF_WEAPON_PISTOL,
	TF_WEAPON_PISTOL_SCOUT,
	TF_WEAPON_REVOLVER,
	TF_WEAPON_NAILGUN,
	TF_WEAPON_PDA,
	TF_WEAPON_PDA_ENGINEER_BUILD,
	TF_WEAPON_PDA_ENGINEER_DESTROY,
	TF_WEAPON_PDA_SPY,
	TF_WEAPON_BUILDER,
	TF_WEAPON_MEDIGUN,
	TF_WEAPON_GRENADE_MIRVBOMB,
	TF_WEAPON_FLAMETHROWER_ROCKET,
	TF_WEAPON_GRENADE_DEMOMAN,
	TF_WEAPON_SENTRY_BULLET,
	TF_WEAPON_SENTRY_ROCKET,
	TF_WEAPON_DISPENSER,
	TF_WEAPON_INVIS,
	TF_WEAPON_FLAG,
	TF_WEAPON_FLAREGUN,
	TF_WEAPON_LUNCHBOX,
	TF_WEAPON_COMPOUND_BOW,
	// ADD TF2C WEAPONS AFTER THIS
	TF_WEAPON_HUNTERRIFLE,
	TF_WEAPON_UMBRELLA,
	TF_WEAPON_HAMMERFISTS,
	TF_WEAPON_CHAINSAW,
	TF_WEAPON_HEAVYARTILLERY,
	TF_WEAPON_ASSAULTRIFLE,
	TF_WEAPON_DISPLACER,

	TF_WEAPON_COUNT
};

enum EClassNumbers
{
	CLASS_SCOUT = 1,
	CLASS_SNIPER, //2
	CLASS_SOLDIER, //3
	CLASS_DEMO, //4
	CLASS_MEDIC, //5
	CLASS_HEAVY, //6
	CLASS_PYRO, //7
	CLASS_SPY, //8
	CLASS_ENGINEER, //9
	CLASS_CIVILIAN //10
};



enum /*class*/ ConVarFlags_t
{
	FCVAR_NONE = 0, // The default, no flags at all

	FCVAR_UNREGISTERED = (1 << 0), // If this is set, don't add to linked list, etc.
	FCVAR_DEVELOPMENT_ONLY = (1 << 1), // Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
	FCVAR_GAME_DLL = (1 << 2), // defined by the game DLL
	FCVAR_CLIENT_DLL = (1 << 3), // defined by the client DLL
	FCVAR_HIDDEN = (1 << 4), // Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.

	FCVAR_PROTECTED = (1 << 5),  // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
	FCVAR_SP_ONLY = (1 << 6),  // This cvar cannot be changed by clients connected to a multiplayer server.
	FCVAR_ARCHIVE = (1 << 7),  // set to cause it to be saved to vars.rc
	FCVAR_NOTIFY = (1 << 8),  // notifies players when changed
	FCVAR_USER_INFO = (1 << 9),  // changes the client's info string
	FCVAR_CHEAT = (1 << 14), // Only useable in singleplayer / debug / multiplayer & sv_cheats

	FCVAR_PRINTABLE_ONLY = (1 << 10), // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
	FCVAR_UN_LOGGED = (1 << 11), // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
	FCVAR_NEVER_AS_STRING = (1 << 12), // never try to print that cvar

	FCVAR_REPLICATED = (1 << 13), // server setting enforced on clients, TODO rename to FCAR_SERVER at some time
	FCVAR_DEMO = (1 << 16), // record this cvar when starting a demo file
	FCVAR_DONT_RECORD = (1 << 17), // don't record these command in demofiles
	FCVAR_RELOAD_MATERIALS = (1 << 20), // If this cvar changes, it forces a material reload
	FCVAR_RELOAD_TEXTURES = (1 << 21), // If this cvar changes, if forces a texture reload

	FCVAR_NOT_CONNECTED = (1 << 22), // cvar cannot be changed by a client that is connected to a server
	FCVAR_MATERIAL_SYSTEM_THREAD = (1 << 23), // Indicates this cvar is read from the material system thread
	FCVAR_ARCHIVE_XBOX = (1 << 24), // cvar written to config.cfg on the Xbox

	FCVAR_ACCESSIBLE_FROM_THREADS = (1 << 25), // used as a debugging tool necessary to check material system thread convars

	FCVAR_SERVER_CAN_EXECUTE = (1 << 28), // the server is allowed to execute this command on clients via ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd.
	FCVAR_SERVER_CANNOT_QUERY = (1 << 29), // If this is set, then the server is not allowed to query this cvar's value (via IServerPluginHelpers::StartQueryCvarValue).
	FCVAR_CLIENT_CMD_CAN_EXECUTE = (1 << 30), // IVEngineClient::ClientCmd is allowed to execute this command.

	FCVAR_MATERIAL_THREAD_MASK = (FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD)
};

enum ELifeStates
{
	LIFE_ALIVE,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY,
};

enum ETFHitboxes //the int method wasn't functioning in pf2 so we going enums
{
	HITBOX_HEAD, //0
	HITBOX_PELVIS, //1
	HITBOX_SPINE_0, //2
	HITBOX_SPINE_1, //3
	HITBOX_SPINE_2, //4
	HITBOX_SPINE_3, //5
	HITBOX_UPPERARM_L, //6
	HITBOX_LOWERARM_L, //7
	HITBOX_HAND_L, //8
	HITBOX_UPPERARM_R, //9
	HITBOX_LOWERARM_R, //10
	HITBOX_HAND_R, //11
	HITBOX_HIP_L, //12
	HITBOX_KNEE_L, //13
	HITBOX_FOOT_L, //14
	HITBOX_HIP_R, //15
	HITBOX_KNEE_R, //16
	HITBOX_FOOT_R, //17
	HITBOX_MAX
};


//stolen from pf2 0.6 src
enum
{
	TF_COND_AIMING = 0,		// Sniper aiming, Heavy minigun.
	TF_COND_ZOOMED, //1
	TF_COND_DISGUISING, //2
	TF_COND_DISGUISED, //3
	TF_COND_STEALTHED, //4
	TF_COND_INVULNERABLE, //5
	TF_COND_TELEPORTED, //6
	TF_COND_TAUNTING, //7
	TF_COND_INVULNERABLE_WEARINGOFF, //8
	TF_COND_STEALTHED_BLINK, //9
	TF_COND_SELECTED_TO_TELEPORT, //10
	//TF_COND_CRITS, ///crits //11
	//TF_COND_CRITS2, ///crits //12
	TF_COND_TRANQUILIZED, //12
	TF_COND_DIZZY, ///13
	TF_COND_SMOKE_BOMB, //14

	// The following conditions all expire faster when the player is being healed
	// If you add a new condition that shouldn't have this behavior, add it before this section.
	TF_COND_HEALTH_BUFF, //15
	TF_COND_BURNING, //16
	TF_COND_LEG_DAMAGED, //17
	TF_COND_INFECTED,
	TF_COND_HALLUCINATING,
	TF_COND_NAPALM_BURNING,
	TF_COND_BUILDING_DETPACK,

	// Add new conditions that should be affected by healing here

	TF_COND_LAST
};

//Reloading modes. Use with m_iReloadMode
enum
{
	TF_RELOAD_START = 0,
	TF_RELOADING,
	TF_RELOADING_CONTINUE,
	TF_RELOAD_FINISH
};

class VMatrix {
private:
	Vector m[4][4];

public:
	const matrix3x4_t& As3x4() const {
		return *((const matrix3x4_t*)this);
	}
};

struct PlayerInfo_t
{
	// scoreboard information
	char			name[32];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[32 + 1];
	// friends identification number
	unsigned int		friendsID;
	// friends name
	char			friendsName[32];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
	// custom files CRC for this player
	unsigned long	customFiles[4];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
};

// edict->movetype values
enum MoveType_t
{
	MOVETYPE_NONE = 0,	// never moves
	MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,				// Player only - moving on the ground
	MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,				// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
	MOVETYPE_PUSH,				// no clip to world, push and crush
	MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,			// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

	// should always be defined as the last item in the list
	MOVETYPE_LAST = MOVETYPE_CUSTOM,

	MOVETYPE_MAX_BITS = 4
};

class CViewSetup
{
public:
	// left side of view window
	int			x;
	int			m_nUnscaledX;
	// top side of view window
	int			y;
	int			m_nUnscaledY;
	// width of view window
	int			width;
	int			m_nUnscaledWidth;
	// height of view window
	int			height;
	// which eye are we rendering?
	StereoEye_t m_eStereoEye;
	int			m_nUnscaledHeight;

	// the rest are only used by 3D views

		// Orthographic projection?
	bool		m_bOrtho;
	// View-space rectangle for ortho projection.
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;

	// horizontal FOV in degrees
	float		fov;
	// horizontal FOV in degrees for in-view model
	float		fovViewmodel;

	// 3D origin of camera
	Vector		origin;

	// heading of camera (pitch, yaw, roll)
	Vector		angles;
	// local Z coordinate of near plane of camera
	float		zNear;
	// local Z coordinate of far plane of camera
	float		zFar;

	// local Z coordinate of near plane of camera ( when rendering view model )
	float		zNearViewmodel;
	// local Z coordinate of far plane of camera ( when rendering view model )
	float		zFarViewmodel;

	// set to true if this is to draw into a subrect of the larger screen
	// this really is a hack, but no more than the rest of the way this class is used
	bool		m_bRenderToSubrectOfLargerScreen;

	// The aspect ratio to use for computing the perspective projection matrix
	// (0.0f means use the viewport)
	float		m_flAspectRatio;

	// Controls for off-center projection (needed for poster rendering)
	bool		m_bOffCenter;
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;

	// Control that the SFM needs to tell the engine not to do certain post-processing steps
	bool		m_bDoBloomAndToneMapping;

	// Cached mode for certain full-scene per-frame varying state such as sun entity coverage
	bool		m_bCacheFullSceneState;

	// If using VR, the headset calibration will feed you a projection matrix per-eye.
	// This does NOT override the Z range - that will be set up as normal (i.e. the values in this matrix will be ignored).
	bool        m_bViewToProjectionOverride;
	VMatrix     m_ViewToProjection;
};

struct mstudiobbox_t
{
	int bone;
	int group;
	Vector bbmin;
	Vector bbmax;
	int szhitboxnameindex;
	Vector angle;
	float m_radius;
	uint8_t _padding[0x10];
	//int bone;
	//int group;
	//Vector bbmin;
	//Vector bbmax;
	//int szhitboxnameindex;
	////Vector angle;
	////float m_radius; //??
	//int unused[8];
	//Vector angle;
	const char* pszHitboxName()
	{
		if (szhitboxnameindex == 0)
			return "";

		return ((const char*)this) + szhitboxnameindex;
	}
};

struct mstudiohitboxset_t
{
	int sznameindex;
	inline char* const	pszName(void) const { return ((char*)this) + sznameindex; }
	int numhitboxes;
	int hitboxindex;
	inline mstudiobbox_t* pHitbox(int i) const { return (mstudiobbox_t*)(((unsigned char*)this) + hitboxindex) + i; };
};

struct studiohdr_t
{
	unsigned char		pad00[12];
	char				name[64];
	unsigned char		pad01[80];
	int					numbones;
	int					boneindex;
	unsigned char		pad02[12];
	int					hitboxsetindex;
	unsigned char		pad03[228];

	mstudiohitboxset_t* pHitboxSet(int i) const
	{
		return (mstudiohitboxset_t*)(((unsigned char*)this) + hitboxsetindex) + i;
	};

	inline mstudiobbox_t* pHitbox(int i, int set) const
	{
		mstudiohitboxset_t const* s = pHitboxSet(set);
		if (!s)
			return NULL;

		return s->pHitbox(i);
	};

	inline int iHitboxCount(int set) const
	{
		mstudiohitboxset_t const* s = pHitboxSet(set);
		if (!s)
			return 0;

		return s->numhitboxes;
	};
};

class C_MoveData
{
public:
	bool m_bFirstRunOfFunctions : 1;
	bool m_bGameCodeMovedPlayer : 1;

	void* m_nPlayerHandle; // edict index on server, client entity handle on client

	int    m_nImpulseCommand; // Impulse command issued.
	Vector m_vecViewAngles; // Command view angles (local space)
	Vector m_vecAbsViewAngles; // Command view angles (world space)
	int    m_nButtons; // Attack buttons.
	int    m_nOldButtons; // From host_client->oldbuttons;
	float  m_flForwardMove;
	float  m_flSideMove;
	float  m_flUpMove;

	float m_flMaxSpeed;
	float m_flClientMaxSpeed;

	// Variables from the player edict (sv_player) or entvars on the client.
	// These are copied in here before calling and copied out after calling.
	Vector m_vecVelocity; // edict::velocity		// Current movement direction.
	Vector m_vecAngles; // edict::angles
	Vector m_vecOldAngles;

	// Output only
	float  m_outStepHeight; // how much you climbed this move
	Vector m_outWishVel; // This is where you tried
	Vector m_outJumpVel; // This is your jump velocity

	// Movement constraints	(radius 0 means no constraint)
	Vector m_vecConstraintCenter;
	float  m_flConstraintRadius;
	float  m_flConstraintWidth;
	float  m_flConstraintSpeedFactor;

	void        SetAbsOrigin(const Vector& vec);
	const Vector& GetAbsOrigin() const;

	// private:
	Vector m_vecAbsOrigin; // edict::origin
};

//the most important one
	enum ETFClassIds
	{
		CTFWrench = 230,
	CTFSyringeGun = 214,
	CSniperDot = 94,
	CTFSniperRifle = 212,
	CTFSMG_Medic = 210,
	CTFSMG_Scout = 211,
	CTFSMG = 209,
	CTFShovel = 208,
	CTFShotgun_Scout = 206,
	CTFShotgun_Pyro = 205,
	CTFShotgun_HWG = 204,
	CTFShotgun_Soldier = 207,
	CTFShotgun = 203,
	CTFRocketLauncher = 202,
	CTFRevolver = 201,
	CTFPistol_Spy = 194,
	CTFPistol = 193,
	CTFPipebombLauncher = 192,
	CTFWeaponPDA_Spy = 229,
	CTFWeaponPDA_Engineer_Destroy = 228,
	CTFWeaponPDA_Engineer_Build = 227,
	CTFWeaponPDA = 226,
	CTFMinigun = 188,
	CWeaponMedigun = 238,
	CTFKnife = 187,
	CTFWeaponInvis = 225,
	CTFGrenadeLauncher = 175,
	CTFFlameThrower = 164,
	CTFCubemap = 163,
	CTFClub = 162,
	CTFBottle = 160,
	CTFBat = 159,
	CTFWeaponBuilder = 224,
	CTFBaseRocket = 158,
	CTFWeaponBaseMelee = 223,
	CTFWeaponBaseGun = 222,
	CTFWeaponBaseGrenadeProj = 221,
	CTFWeaponBase = 219,
	CTFBaseProjectile = 157,
	CTFProjectile_FlameRocket = 197,
	CTFProjectile_Rocket = 198,
	CTFViewModel = 218,
	CBaseObjectUpgrade = 10,
	CTFItem = 186,
	CTFGameRulesProxy = 165,
	CTETFParticleEffect = 154,
	CTETFExplosion = 153,
	CCaptureFlagReturnIcon = 23,
	CCaptureFlag = 22,
	CTFTeam = 215,
	CTFPlayerResource = 196,
	CTFPlayer = 195,
	CTFRagdoll = 200,
	CTEPlayerAnimEvent = 141,
	CTFObjectiveResource = 190,
	CTEFireBullets = 129,
	CTFAmmoPack = 156,
	CObjectTeleporter = 70,
	CObjectSentrygun = 68,
	CTFProjectile_SentryRocket = 199,
	CObjectSapper = 67,
	CObjectCartDispenser = 65,
	CObjectDispenser = 66,
	CFuncRespawnRoomVisualizer = 54,
	CFuncRespawnRoom = 53,
	CCaptureZone = 24,
	CBaseObject = 9,
	CTestTraceline = 152,
	CTEWorldDecal = 155,
	CTESpriteSpray = 150,
	CTESprite = 149,
	CTESparks = 148,
	CTESmoke = 147,
	CTEShowLine = 145,
	CTEProjectedDecal = 143,
	CTEPlayerDecal = 142,
	CTEPhysicsProp = 140,
	CTEParticleSystem = 139,
	CTEMuzzleFlash = 138,
	CTELargeFunnel = 136,
	CTEKillPlayerAttachments = 135,
	CTEImpact = 134,
	CTEGlowSprite = 133,
	CTEShatterSurface = 144,
	CTEFootprintDecal = 131,
	CTEFizz = 130,
	CTEExplosion = 128,
	CTEEnergySplash = 127,
	CTEEffectDispatch = 126,
	CTEDynamicLight = 125,
	CTEDecal = 123,
	CTEClientProjectile = 122,
	CTEBubbleTrail = 121,
	CTEBubbles = 120,
	CTEBSPDecal = 119,
	CTEBreakModel = 118,
	CTEBloodStream = 117,
	CTEBloodSprite = 116,
	CTEBeamSpline = 115,
	CTEBeamRingPoint = 114,
	CTEBeamRing = 113,
	CTEBeamPoints = 112,
	CTEBeamLaser = 111,
	CTEBeamFollow = 110,
	CTEBeamEnts = 109,
	CTEBeamEntPoint = 108,
	CTEBaseBeam = 107,
	CTEArmorRicochet = 106,
	CTEMetalSparks = 137,
	CSteamJet = 99,
	CSmokeStack = 93,
	DustTrail = 240,
	CFireTrail = 42,
	SporeTrail = 246,
	SporeExplosion = 245,
	RocketTrail = 243,
	SmokeTrail = 244,
	CPropVehicleDriveable = 85,
	ParticleSmokeGrenade = 242,
	CParticleFire = 71,
	MovieExplosion = 241,
	CTEGaussExplosion = 132,
	CEnvQuadraticBeam = 36,
	CEmbers = 29,
	CEnvWind = 40,
	CPrecipitation = 84,
	CBaseTempEntity = 16,
	CTFUmbrella = 217,
	CTFTranq = 216,
	CTFSyringe = 213,
	CTFPipe = 191,
	CTFNailgun = 189,
	CTFBrandingIron = 161,
	CTFGrenadePipebombProjectile = 185,
	CTFGrenadeNormalProjectile = 184,
	CTFGrenadeNormal = 183,
	CTFGrenadeNapalmEffect = 181,
	CTFGrenadeNapalmProjectile = 182,
	CTFGrenadeNapalm = 180,
	CTFGrenadeNailProjectile = 179,
	CTFGrenadeNail = 178,
	CTFGrenadeMirvProjectile = 177,
	CTFGrenadeMirv = 176,
	CTFGrenadeHeal = 174,
	CTFGasGrenadeEffect = 166,
	CTFGrenadeGasProjectile = 173,
	CTFGrenadeGas = 172,
	CTFGrenadeEmp = 171,
	CTFGrenadeConcussionProjectile = 170,
	CTFGrenadeConcussion = 169,
	CTFGrenadeCaltropProjectile = 168,
	CTFGrenadeCaltrop = 167,
	CTFWeaponBaseGrenade = 220,
	CObjectSpawnroomTurret = 69,
	CTeamControlPoint = 102,
	CWeaponIFMSteadyCam = 237,
	CWeaponIFMBaseCamera = 236,
	CWeaponIFMBase = 235,
	CHandleTest = 59,
	CTeamplayRoundBasedRulesProxy = 103,
	CTeamRoundTimer = 104,
	CSpriteTrail = 98,
	CSpriteOriented = 97,
	CSprite = 96,
	CRagdollPropAttached = 88,
	CRagdollProp = 87,
	CPoseController = 83,
	CGameRulesProxy = 58,
	CInfoLadderDismount = 60,
	CFuncLadder = 49,
	CEnvDetailController = 33,
	CWorld = 239,
	CWaterLODControl = 234,
	CWaterBullet = 233,
	CVoteController = 232,
	CVGuiScreen = 231,
	CPropJeep = 0,
	CPropVehicleChoreoGeneric = 0,
	CTest_ProxyToggle_Networkable = 151,
	CTesla = 146,
	CTeamTrainWatcher = 105,
	CBaseTeamObjectiveResource = 15,
	CTeam = 101,
	CSun = 100,
	CParticlePerformanceMonitor = 72,
	CSpotlightEnd = 95,
	CSlideshowDisplay = 92,
	CShadowControl = 91,
	CSceneEntity = 90,
	CRopeKeyframe = 89,
	CRagdollManager = 86,
	CPhysicsPropMultiplayer = 77,
	CPhysBoxMultiplayer = 75,
	CBasePropDoor = 14,
	CDynamicProp = 28,
	CPointCommentaryNode = 82,
	CPointCamera = 81,
	CPlayerResource = 80,
	CPlasma = 79,
	CPhysMagnet = 78,
	CPhysicsProp = 76,
	CPhysBox = 74,
	CParticleSystem = 73,
	CMaterialModifyControl = 64,
	CLightGlow = 63,
	CInfoOverlayAccessor = 62,
	CFuncTrackTrain = 57,
	CFuncSmokeVolume = 56,
	CFuncRotating = 55,
	CFuncReflectiveGlass = 52,
	CFuncOccluder = 51,
	CFuncMonitor = 50,
	CFunc_LOD = 46,
	CTEDust = 124,
	CFunc_Dust = 45,
	CFuncConveyor = 48,
	CBreakableSurface = 21,
	CFuncAreaPortalWindow = 47,
	CFish = 43,
	CEntityFlame = 31,
	CFireSmoke = 41,
	CEnvTonemapController = 39,
	CEnvScreenEffect = 37,
	CEnvScreenOverlay = 38,
	CEnvProjectedTexture = 35,
	CEnvParticleScript = 34,
	CFogController = 44,
	CEntityParticleTrail = 32,
	CEntityDissolve = 30,
	CDynamicLight = 27,
	CColorCorrectionVolume = 26,
	CColorCorrection = 25,
	CBreakableProp = 20,
	CBasePlayer = 12,
	CBaseFlex = 7,
	CBaseEntity = 6,
	CBaseDoor = 5,
	CBaseCombatCharacter = 3,
	CBaseAnimatingOverlay = 2,
	CBoneFollower = 19,
	CBaseAnimating = 1,
	CInfoLightingRelative = 61,
	CAI_BaseNPC = 0,
	CBeam = 18,
	CBaseViewModel = 17,
	CBaseProjectile = 13,
	CBaseParticleEntity = 11,
	CBaseGrenade = 8,
	CBaseCombatWeapon = 4,
};
