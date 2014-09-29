#pragma once

#include "Utilities.h"
#include "GameTypes.h"

template <typename T> class BSTEventSink;

enum EventResult
{
	kEvent_Continue = 0,
	kEvent_Abort
};

// 030
template <typename EventT, typename EventArgT = EventT>
class EventDispatcher
{
	typedef BSTEventSink<EventT> SinkT;

	SimpleLock			lock;				// 000
	tArray<SinkT*>		eventSinks;			// 008
	tArray<SinkT*>		addBuffer;			// 014 - schedule for add
	tArray<SinkT*>		removeBuffer;		// 020 - schedule for remove
	bool				stateFlag;			// 02C - some internal state changed while sending
	char				pad[3];

	MEMBER_FN_PREFIX(EventDispatcher);
	DEFINE_MEMBER_FN(AddEventSink_Internal, void, 0x006E3E30, SinkT * eventSink);
	DEFINE_MEMBER_FN(RemoveEventSink_Internal, void, 0x008CE0C0, SinkT * eventSink);
	DEFINE_MEMBER_FN(SendEvent_Internal, void, 0x006EBC10, EventArgT * evn);

public:

	EventDispatcher() : stateFlag(false) {}

	void AddEventSink(SinkT * eventSink)		{ CALL_MEMBER_FN(this,AddEventSink_Internal)(eventSink); }
	void RemoveEventSink(SinkT * eventSink)		{ CALL_MEMBER_FN(this,RemoveEventSink_Internal)(eventSink); }
	void SendEvent(EventArgT * evn)				{ CALL_MEMBER_FN(this,SendEvent_Internal)(evn); }
};
STATIC_ASSERT(sizeof(EventDispatcher<void*>) == 0x30);

// 04
template <typename T>
class BSTEventSink
{
public:
	virtual ~BSTEventSink();
	virtual	EventResult	ReceiveEvent(T * evn, EventDispatcher<T> * dispatcher); // pure
//	void	** _vtbl;	// 00
};

// 30
template <typename EventT, typename EventArgT = EventT>
class BSTEventSource
{
public:
	typedef BSTEventSink<EventT> SinkT;

	BSTEventSource() : stateFlag(false) {}

	void AddEventSink(SinkT * eventSink)		{ CALL_MEMBER_FN(this,AddEventSink_Internal)(eventSink); }
	void RemoveEventSink(SinkT * eventSink)		{ CALL_MEMBER_FN(this,RemoveEventSink_Internal)(eventSink); }
	void SendEvent(EventArgT * evn)				{ CALL_MEMBER_FN(this,SendEvent_Internal)(evn); }

private:
	template <typename Fn, typename Arguments, typename Compare>
	class EventSink : public SinkT
	{
	public:
		typedef decltype(TypeHelper::SourceType(&SinkT::ReceiveEvent)) SourceT;
		EventSink(Fn f) : fn(f) {}
		virtual ~EventSink() {}
		virtual EventResult ReceiveEvent(EventArgT* evn, SourceT* source) {
			return Arguments::Call(fn, evn, source, this);
		}
		static SinkT* Create(Fn f) {
			return (SinkT*)new EventSink(f);
		}
		void Destroy() {
			delete this;
		}
		bool operator==(SinkT& sink) {
			void* vtblA = *reinterpret_cast<void**>(this);
			void* vtblB = *reinterpret_cast<void**>(&sink);
			return (vtblA == vtblB && Compare::Equal(this, reinterpret_cast<EventSink*>(&sink)));
		}
		Fn fn;
	};

	struct TypeHelper
	{
		typedef EventResult (*FuncPtr0)();
		typedef EventResult (*FuncPtr1)(EventArgT*);
		typedef EventResult (*FuncPtr2)(EventArgT*, BSTEventSource*);
		typedef EventResult (*FuncPtr3)(EventArgT*, BSTEventSource*, SinkT*);

		struct Arg0	{ template <typename Fn> static inline EventResult Call(Fn f, EventArgT* e, BSTEventSource* src, SinkT* snk) {return f();} };
		struct Arg1	{ template <typename Fn> static inline EventResult Call(Fn f, EventArgT* e, BSTEventSource* src, SinkT* snk) {return f(e);} };
		struct Arg2	{ template <typename Fn> static inline EventResult Call(Fn f, EventArgT* e, BSTEventSource* src, SinkT* snk) {return f(e, src);} };
		struct Arg3	{ template <typename Fn> static inline EventResult Call(Fn f, EventArgT* e, BSTEventSource* src, SinkT* snk) {return f(e, src, snk);} };

		struct CompFunction	{ template <typename Sn> static inline bool Equal(Sn* a, Sn* b) {return a->fn == b->fn;} };
		struct CompFunctor	{ template <typename Sn> static inline bool Equal(Sn* a, Sn* b) {return &a->fn == &b->fn;} };
		struct CompLambda	{ template <typename Sn> static inline bool Equal(Sn* a, Sn* b) {return true;} };

		template <typename F> static EventSink<F&,Arg0,CompFunctor> ObjSinkType(EventResult (F::*)());
		template <typename F> static EventSink<F, Arg0,CompLambda>  ObjSinkType(EventResult (F::*)() const);
		template <typename F> static EventSink<F&,Arg1,CompFunctor> ObjSinkType(EventResult (F::*)(EventArgT*));
		template <typename F> static EventSink<F, Arg1,CompLambda>  ObjSinkType(EventResult (F::*)(EventArgT*) const);
		template <typename F> static EventSink<F&,Arg2,CompFunctor> ObjSinkType(EventResult (F::*)(EventArgT*, BSTEventSource*));
		template <typename F> static EventSink<F, Arg2,CompLambda>  ObjSinkType(EventResult (F::*)(EventArgT*, BSTEventSource*) const);
		template <typename F> static EventSink<F&,Arg3,CompFunctor> ObjSinkType(EventResult (F::*)(EventArgT*, BSTEventSource*, SinkT*));
		template <typename F> static EventSink<F, Arg3,CompLambda>  ObjSinkType(EventResult (F::*)(EventArgT*, BSTEventSource*, SinkT*) const);

		static EventSink<FuncPtr0,Arg0,CompFunction> SinkType(FuncPtr0);
		static EventSink<FuncPtr1,Arg1,CompFunction> SinkType(FuncPtr1);
		static EventSink<FuncPtr2,Arg2,CompFunction> SinkType(FuncPtr2);
		static EventSink<FuncPtr3,Arg3,CompFunction> SinkType(FuncPtr3);
		template <typename F> static auto SinkType(F f) -> decltype(TypeHelper::ObjSinkType(&F::operator())) {};

		template <typename Sink, typename Disp> static Disp SourceType(EventResult (Sink::*)(EventArgT*, Disp*));
	};

public:
	template <typename F>
	BSTEventSource& operator+=(F& f) {
		typedef decltype(TypeHelper::SinkType(f)) SinkType;
		SinkT* sink = SinkType::Create(f);
		AddEventSink(sink);
		return *this;
	}

	template <typename F>
	BSTEventSource& operator-=(F& f) {
		typedef decltype(TypeHelper::SinkType(f)) SinkType;
		SinkType tmpSink(f);
		int i = 0;
		SinkT* sink = NULL;
		while (eventSinks.GetNthItem(i++, sink)) {
			if (tmpSink == *sink) {
				RemoveEventSink(sink);
				reinterpret_cast<SinkType*>(sink)->Destroy();
				break;
			}
		}
		return *this;
	}

	void operator()(EventArgT e) {
		SendEvent(e);
	}

private:
	SimpleLock			lock;				// 000
	tArray<SinkT*>		eventSinks;			// 008
	tArray<SinkT*>		addBuffer;			// 014 - schedule for add
	tArray<SinkT*>		removeBuffer;		// 020 - schedule for remove
	bool				stateFlag;			// 02C - some internal state changed while sending
	char				pad[3];

	MEMBER_FN_PREFIX(BSTEventSource);
	DEFINE_MEMBER_FN(AddEventSink_Internal, void, 0x006E3E30, SinkT * eventSink);
	DEFINE_MEMBER_FN(RemoveEventSink_Internal, void, 0x008CE0C0, SinkT * eventSink);
	DEFINE_MEMBER_FN(SendEvent_Internal, void, 0x006EBC10, EventArgT * evn);
};
STATIC_ASSERT(sizeof(BSTEventSource<void*>) == 0x30);


//===========================================================================
// events
//===========================================================================

// 08
class MenuOpenCloseEvent
{
public:
	BSFixedString	menuName;	// 00
	bool			opening;	// 04
	char			pad[3];
};

// Todo
class MenuModeChangeEvent
{
};

class UserEventEnabledEvent
{
	// 01B37FB4
};


class BSTransformDeltaEvent
{
};

class BSAnimationGraphEvent
{
};

class bhkCharacterMoveFinishEvent
{
};

struct BGSActorCellEvent
{
	enum
	{
		kFlags_Enter = 0,
		kFlags_Leave = 1
	};
	UInt32	refHandle;
	UInt32	cellID;
	UInt32	flags;
};

struct BGSActorDeathEvent
{
};

struct BGSFootstepEvent
{
	UInt32	actorHandle;
};

struct PositionPlayerEvent
{
};

struct HavokImpulseEvent
{
	// 0x01B380A0
};

struct HavokThreadmemoryEvent
{
	// 0x01B4AE14
};

struct ScriptArchiveRegisteredEvent
{
	// 0x01B417D8
	const char* bsaFileName;
};

struct FavoriteWeaponEvent
{
	// 0x01B39C5C
};

struct FavoriteSpellEvent
{
	// 0x01B3B04C
};

struct FavoriteShoutEvent
{
	// 0x01B39C90
};

// EventSource Address
//   EventSink

// 01B107B4
//   DefaultObjectInitListener@?A0x9360cbd9@@
//   UIBlurManager@@

// 01B410BC
//   TES@@+34

// 01B37F60
//   PlayerContorols@@+0

// 01B37F60
//   BGSMoviePlayer@@+30

// 01B37E88
//   PathingCallbackMgr@SkyrimScript@@

// 0x01B37FB4
//   PlayerCharacter@@->userEventEnabled
//   HUDMenu@@+1C

// 01B417A8
//   LooseAudioRegistrar@@


//===========================================================================
// sinks
//===========================================================================

template <>
class BSTEventSink <MenuOpenCloseEvent>
{
public:
	virtual ~BSTEventSink() {}
	virtual	EventResult ReceiveEvent(MenuOpenCloseEvent * evn, EventDispatcher<MenuOpenCloseEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <MenuModeChangeEvent>
{
public:
	virtual ~BSTEventSink() {}
	virtual	EventResult ReceiveEvent(MenuModeChangeEvent * evn, EventDispatcher<MenuModeChangeEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <BGSActorCellEvent>
{
public:
	virtual ~BSTEventSink() {}
	virtual	EventResult ReceiveEvent(BGSActorCellEvent * evn, BSTEventSource<BGSActorCellEvent> * source) = 0;
};

template <>
class BSTEventSink <BGSFootstepEvent>
{
public:
	virtual ~BSTEventSink() {}
	virtual	EventResult ReceiveEvent(BGSFootstepEvent * evn, BSTEventSource<BGSFootstepEvent> * source) = 0;
};
