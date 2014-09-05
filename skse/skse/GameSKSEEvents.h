#pragma once

#include "GameEvents.h"

class TESForm;
class TESObjectREFR;
class Actor;
class TESCameraState;

struct SKSEModCallbackEvent
{
	BSFixedString	eventName;
	BSFixedString	strArg;
	float			numArg;
	TESForm *		sender;

	SKSEModCallbackEvent(BSFixedString a_eventName, BSFixedString a_strArg, float a_numArg, TESForm * a_sender) :
		eventName(a_eventName.data), strArg(a_strArg.data), numArg(a_numArg), sender(a_sender) {}
};

template <>
class BSTEventSink <SKSEModCallbackEvent>
{
public:
	virtual ~BSTEventSink() {}; // todo?
	virtual	EventResult ReceiveEvent(SKSEModCallbackEvent * evn, EventDispatcher<SKSEModCallbackEvent> * dispatcher) = 0;
};

struct SKSECameraEvent
{
	TESCameraState * oldState;
	TESCameraState * newState;

	SKSECameraEvent(TESCameraState * a_oldState, TESCameraState * a_newState) :
		oldState(a_oldState), newState(a_newState) {}
};

template <>
class BSTEventSink <SKSECameraEvent>
{
public:
	virtual ~BSTEventSink() {}; // todo?
	virtual	EventResult ReceiveEvent(SKSECameraEvent * evn, EventDispatcher<SKSECameraEvent> * dispatcher) = 0;
};

struct SKSECrosshairRefEvent
{
	TESObjectREFR *		crosshairRef;

	SKSECrosshairRefEvent(TESObjectREFR * a_crosshairRef) : crosshairRef(a_crosshairRef) {}
};

template <>
class BSTEventSink <SKSECrosshairRefEvent>
{
public:
	virtual ~BSTEventSink() {}; // todo?
	virtual	EventResult ReceiveEvent(SKSECrosshairRefEvent * evn, EventDispatcher<SKSECrosshairRefEvent> * dispatcher) = 0;
};

struct SKSEActionEvent
{
	enum {
		kType_WeaponSwing = 0,
		kType_SpellCast = 1,
		kType_SpellFire = 2,
		kType_VoiceCast = 3,
		kType_VoiceFire = 4,
		kType_BowDraw = 5,
		kType_BowRelease = 6,
		kType_BeginDraw = 7,
		kType_EndDraw = 8,
		kType_BeginSheathe = 9,
		kType_EndSheathe = 10
	};
	enum {
		kSlot_Left = 0,
		kSlot_Right = 1,
		kSlot_Voice = 2
	};
	UInt32 type;
	Actor * actor;
	TESForm	* sourceForm;
	UInt32	slot;

	SKSEActionEvent(UInt32 a_type, Actor * a_actor, TESForm * a_source, UInt32 a_slot) :
	type(a_type), actor(a_actor), sourceForm(a_source), slot(a_slot) {}
};

template <>
class BSTEventSink <SKSEActionEvent>
{
public:
	virtual ~BSTEventSink() {}; // todo?
	virtual	EventResult ReceiveEvent(SKSEActionEvent * evn, EventDispatcher<SKSEActionEvent> * dispatcher) = 0;
};
