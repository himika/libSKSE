#include "GameCamera.h"

void LocalMapCamera::SetDefaultStateMinFrustumDimensions(float width, float height)
{
	defaultState->minFrustumWidth = width / 2.0;
	defaultState->minFrustumHeight = height / 2.0;
}

void LocalMapCamera::SetAreaBounds(NiPoint3 * maxBound, NiPoint3 * minBound)
{
	areaBoundsMin = *minBound;
	areaBoundsMax = *maxBound;
	areaBoundsMax.z += (*g_mapLocalHeight);
}

void LocalMapCamera::SetDefaultStateMaxBound(NiPoint3 * maxBound)
{
	defaultState->someBoundMax = *maxBound;
	defaultState->someBoundMax.z += (*g_mapLocalHeight);
}

void LocalMapCamera::SetDefaultStateBounds(float x, float y, float z)
{
	defaultState->someBoundMin.x = x - defaultState->someBoundMax.x;
	defaultState->someBoundMin.y = y - defaultState->someBoundMax.y;
	defaultState->someBoundMin.z = z - defaultState->someBoundMax.z;
}


// ==== (himika) ====
void PlayerCamera::ForceFirstPersonSmooth(void)
{
	if (cameraState->stateId == kCameraState_ThirdPerson2)
	{
		ThirdPersonState* state = (ThirdPersonState*)cameraState;
		if (state->unkB5 == 0)
		{
			state->unk64   = state->curPosY;
			state->dstPosY = -0.2f;
			state->unkB5 = 1;
		}
		else
		{
			state->curPosY = state->dstPosY;
		}
	}
}

void PlayerCamera::ForceThirdPersonInstant(void)
{
	if (cameraState == NULL || cameraState->stateId < kCameraState_ThirdPerson2)
	{
		ThirdPersonState* tps = (ThirdPersonState*)cameraStates[kCameraState_ThirdPerson2];

		tps->basePosX = tps->fOverShoulderPosX;
		tps->basePosY = tps->fOverShoulderCombatAddY;
		tps->basePosZ = tps->fOverShoulderPosZ;
		tps->curPosY  = tps->dstPosY;

		CALL_MEMBER_FN(this, SetCameraState)(tps);
	}
}
	
void PlayerCamera::ForceThirdPersonSmooth(void)
{
	if (cameraState == NULL || cameraState->stateId < kCameraState_ThirdPerson2)
	{
		ThirdPersonState* tps = (ThirdPersonState*)cameraStates[kCameraState_ThirdPerson2];

		tps->basePosX = tps->fOverShoulderPosX;
		tps->basePosY = tps->fOverShoulderCombatAddY;
		tps->basePosZ = tps->fOverShoulderPosZ;
		tps->curPosY  = -0.2f;
		tps->dstPosY  = tps->unk64;

		CALL_MEMBER_FN(this, SetCameraState)(tps);
	}
}

TESCameraController* TESCameraController::GetSingleton()
{
	return (TESCameraController*)0x01277C58;
}
