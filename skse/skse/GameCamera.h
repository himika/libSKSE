#pragma once

#include "GameTypes.h"
#include "GameInput.h"

#include "GameSettings.h"

#include "skse/NiObjects.h"
#include "skse/NiTypes.h"

class TESCamera;
class NiNode;

class TESCameraState
{
public:
	TESCameraState();
	virtual ~TESCameraState();

	virtual void OnStateStart();	// pure
	virtual void OnStateEnd();	// pure
	virtual void OnUpdate(void * unk1);
	virtual void Unk_04();
	virtual void Unk_05();
	virtual void Unk_06();	// pure
	virtual void Unk_07();	// pure
	virtual void Unk_08();	// pure

	BSIntrusiveRefCounted	refCount;		// 04
	TESCamera				* camera;		// 08
	UInt32					stateId;		// 0C
};

class DragonCameraState : public TESCameraState
{
public:
	DragonCameraState();
	virtual ~DragonCameraState();

	PlayerInputHandler		inputHandler;		// 10
	NiNode					* cameraNode;		// 18
	NiNode					* controllerNode;	// 1C
	float					unk20[0x03];		// 20
	UInt32					unk2C[0x07];		// 2C
	float					unk48[0x03];		// 48
	UInt32					unk54[0x11];		// 54
	float					unk98[0x03];		// 98
	UInt32					unkA4[0x04];		// A4
	UInt8					unkB4[0x07];		// B4
	UInt8					padBB;
	// More
};

class HorseCameraState : public TESCameraState
{
public:
	HorseCameraState();
	virtual ~HorseCameraState();

	PlayerInputHandler		inputHandler;		// 10
	NiNode					* cameraNode;		// 18
	NiNode					* controllerNode;	// 1C
	float					unk20[0x03];		// 20
	UInt32					unk2C[0x07];		// 2C
	float					unk48[0x03];		// 48
	UInt32					unk54[0x11];		// 54
	float					unk98[0x03];		// 98
	UInt32					unkA4[0x04];		// A4
	UInt8					unkB4[0x07];		// B4
	UInt8					padBB;
	// More
};

class TweenMenuCameraState : public TESCameraState
{
public:
	TweenMenuCameraState();
	virtual ~TweenMenuCameraState();

	UInt32	unk10[0x0B];	// 10
	UInt8	unk3C;			// 3C
	UInt8	pad3D;			// 3D
	UInt16	pad3E;			// 3E
};

class VATSCameraState : public TESCameraState
{
public:
	VATSCameraState();
	virtual ~VATSCameraState();

	UInt32	unk10[0x03];	// 10
};

class FreeCameraState : public TESCameraState
{
public:
	FreeCameraState();
	virtual ~FreeCameraState();

	PlayerInputHandler		inputHandler;	// 10
	float					unk18;			// 18
	float					unk1C;			// 1C
	float					unk20;			// 20
	UInt32					unk24[0x04];	// 24
	UInt16					unk34;			// 34
	UInt8					unk36;			// 36
	UInt8					unk37;			// 37
};

class AutoVanityState : public TESCameraState
{
public:
	AutoVanityState();
	virtual ~AutoVanityState();
};

class FurnitureCameraState : public TESCameraState
{
public:
	FurnitureCameraState();
	virtual ~FurnitureCameraState();

	UInt32	unk10;	// 10
	float	unk14;	// 14
	float	unk18;	// 18
	float	unk1C;	// 1C
	UInt32	unk20;	// 20
	UInt32	unk24;	// 24
	UInt32	unk28;	// 28
	UInt8	unk2C;	// 2C
	UInt8	unk2D;	// 2D
	UInt8	unk2E;	// 2E
	UInt8	pad2F;	// 2F
};

class IronSightsState : public TESCameraState
{
public:
	IronSightsState();
	virtual ~IronSightsState();

	UInt32	unk10;	// 10
};

class FirstPersonState : public TESCameraState
{
public:
	FirstPersonState();
	virtual ~FirstPersonState();

	PlayerInputHandler		inputHandler;		// 10
	NiNode					* cameraNode;		// 18
	NiNode					* controllerNode;	// 1C
	float					unk20;				// 20 (himika) rotZ ?
	float					unk24;				// 24
	float					unk28;				// 28
	UInt32					unk2C[0x03];		// 2C
	UInt8					unk38[0x05];		// 38
	UInt8					pad3D;				// 3D
	UInt16					pad3E;				// 3E
};

class ThirdPersonState : public TESCameraState
{
public:
	ThirdPersonState();
	virtual ~ThirdPersonState();
	virtual void Unk_09(void);
	virtual void Unk_0A(void);
	virtual void UpdateMode(bool weaponDrawn);

	PlayerInputHandler		inputHandler;		// 10
	NiNode					* cameraNode;		// 18
	NiNode					* controllerNode;	// 1C
	float					unk20[0x03];		// 20
	UInt32					unk2C[0x04];		// 2C
	float					fOverShoulderPosX;	// 3C
	float					fOverShoulderCombatAddY;	// 40
	float					fOverShoulderPosZ;	// 44
	float					basePosX;			// 48 | (himika)
	float					basePosY;			// 4C |
	float					basePosZ;			// 50 |
	float					dstPosY;			// 54 | destination
	float					curPosY;			// 58 | current position
	float					unk5C;				// 5C | player->rot.z + diffRotZ
	float					unk60;				// 60 | equal unk5C ?
	float					unk64;				// 64 | initial position 1st->3rd
	UInt32					pad68[(0xAC - 0x68) >> 2];
	float					diffRotZ;			// AC | diff from player rotZ
	float					diffRotX;			// B0 | diff from player rotX
	bool					unkB4;				// B4 | weapon sheathed
	bool					unkB5;				// B5 | auto switch 1st-person camera when dstPosY==curPosY
	UInt8					unkB6;
	UInt8					unkB7;
	UInt8					unkB8;
	UInt8					unkB9;
	UInt8					unkBA;
	UInt8					unkBB;
};

STATIC_ASSERT(offsetof(ThirdPersonState, fOverShoulderPosX) == 0x3C);
STATIC_ASSERT(offsetof(ThirdPersonState, basePosX) == 0x48);

class BleedoutCameraState : public ThirdPersonState
{
public:
	BleedoutCameraState();
	virtual ~BleedoutCameraState();

	PlayerInputHandler		inputHandler;		// 10
	NiNode					* cameraNode;		// 18
	NiNode					* controllerNode;	// 1C
	float					unk20[0x03];		// 20
	UInt32					unk2C[0x07];		// 2C
	float					unk48[0x03];		// 48
	UInt32					unk54[0x11];		// 54
	float					unk98[0x03];		// 98
	UInt32					unkA4[0x04];		// A4
	UInt8					unkB4[0x07];		// B4
	UInt8					padBB;
	// More
};

class PlayerCameraTransitionState : public TESCameraState
{
public:
	PlayerCameraTransitionState();
	virtual ~PlayerCameraTransitionState();

	UInt32	unk10[0x05];	// 10
	UInt8	unk24;			// 24
	UInt8	unk25;			// 25
	UInt16	pad26;
};

class TESCamera
{
public:
	TESCamera();
	virtual ~TESCamera();

	virtual void SetNode(NiNode * node);
	virtual void Update();

	float		rotZ;	// 04
	float		rotX;	// 08
	NiPoint3	pos;	// 0C
	float		zoom;	// 18
	NiNode		* cameraNode;	// 1C - First child is usually NiCamera
	TESCameraState	* cameraState;	// 20
	UInt8		unk24;			// 24
	UInt8		pad25[3];		// 25

	MEMBER_FN_PREFIX(TESCamera);
	DEFINE_MEMBER_FN(SetCameraState, UInt32, 0x006533D0, TESCameraState * cameraState);
};

STATIC_ASSERT(offsetof(TESCamera, cameraNode) == 0x1C);

class LocalMapCamera : public TESCamera
{
public:
	LocalMapCamera();
	virtual ~LocalMapCamera();

	class DefaultState : public TESCameraState
	{
	public:
		NiPoint3	someBoundMax;		// 10
		NiPoint3	someBoundMin;		// 1C
		float		zoomPercent;		// 28
		float		minFrustumWidth;	// 2C
		float		minFrustumHeight;	// 30
	};

	NiPoint3	areaBoundsMax;			// 28
	NiPoint3	areaBoundsMin;			// 34
	DefaultState	* defaultState;		// 40
	NiObject	* niCamera;				// 44
	float		northRotation;			// 48

	void SetDefaultStateMinFrustumDimensions(float width, float height);
	void SetAreaBounds(NiPoint3 * maxBound, NiPoint3 * minBound);
	void SetDefaultStateMaxBound(NiPoint3 * maxBound);
	void SetDefaultStateBounds(float x, float y, float z);

	MEMBER_FN_PREFIX(LocalMapCamera);
	DEFINE_MEMBER_FN(ctor, void, 0x00487420);
	DEFINE_MEMBER_FN(SetNorthRotation, void, 0x00486440, float northRotation);
};

STATIC_ASSERT(offsetof(LocalMapCamera, northRotation) == 0x48);

class MapCamera : public TESCamera
{
public:
	MapCamera();
	virtual ~MapCamera();
};

class RaceSexCamera : public TESCamera
{
public:
	RaceSexCamera();
	virtual ~RaceSexCamera();
};

class PlayerCamera : public TESCamera
{
public:
	PlayerCamera();
	virtual ~PlayerCamera();

	static PlayerCamera *	GetSingleton(void)
	{
		return *((PlayerCamera **)0x012E7288);
	}

	enum
	{
		kCameraState_FirstPerson = 0,
		kCameraState_AutoVanity,
		kCameraState_VATS,
		kCameraState_Free,
		kCameraState_IronSights,
		kCameraState_Furniture,
		kCameraState_Transition,
		kCameraState_TweenMenu,
		kCameraState_ThirdPerson1,
		kCameraState_ThirdPerson2,
		kCameraState_Horse,
		kCameraState_Bleedout,
		kCameraState_Dragon,
		kNumCameraStates
	};

	UInt32 unk34[(0x6C - 0x28) >> 2];					// 34
	TESCameraState * cameraStates[kNumCameraStates];	// 6C
	UInt32	unkA0;										// A0
	UInt32	unkA4;										// A4
	UInt32	unkA8;										// A8
	float	worldFOV;									// AC
	float	firstPersonFOV;								// B0
//	UInt32	unkB4[(0xD0 - 0xB4) >> 2];					// B4 * (himika)
	UInt32	padB4[(0xC4 - 0xB4) >> 2];					// B4 |
	float	unkC4;										// C4 |
	UInt32	padC8[(0xD0 - 0xC8) >> 2];					// C8 |
	bool	allowTogglePov;								// D0 allow switch pov
	bool	unkD1;										// D1 eagle eye related. reduce stamina
	UInt8	unkD2;										// D2
	UInt8	unkD3;										// D3
	UInt8	unkD4;										// D4
	UInt8	unkD5;										// D5
	UInt8	padD6[2];									// D6

	MEMBER_FN_PREFIX(PlayerCamera);
	DEFINE_MEMBER_FN(UpdateThirdPerson, void, 0x0083C7E0, bool weaponDrawn);
	DEFINE_MEMBER_FN(ToggleFlyCam, void, 0x0083E4C0, bool);		// (himika)

	void ForceFirstPersonSmooth(void);
	void ForceThirdPersonSmooth(void);
};

STATIC_ASSERT(offsetof(PlayerCamera, cameraStates) == 0x6C);
STATIC_ASSERT(offsetof(PlayerCamera, padD6) == 0xD6);

// ==== (himika) ====
class TESCameraController
{
public:
	TESCameraController() {}

	UInt32 unk00;
	float  startRotZ; // 04
	float  startRotX; // 08
	float  endRotZ;   // 0C
	float  endRotX;   // 10
	UInt32 unk14;     // 14
	UInt32 unk18;     // 18
	UInt8  unk1C;     // 1C
	UInt8  pad1D[3];  // 1D

	static TESCameraController* GetSingleton();
	void Rotate(float startRotZ, float startRotX, float endRotZ, float endRotX, float fWait, float arg2) {
		CALL_MEMBER_FN(this, Rotate)(startRotZ, startRotX, endRotZ, endRotX, fWait, arg2);
	}

	MEMBER_FN_PREFIX(TESCameraController);
	DEFINE_MEMBER_FN(Rotate, void, 0x00736480, float, float, float, float, float, float);
};
