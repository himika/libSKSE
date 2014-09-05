#include <skse.h>
#include <skse/PluginAPI.h>
#include <skse/GameAPI.h>
#include <skse/GameForms.h>
#include <skse/GameReferences.h>
#include <skse/GameTESEvents.h>
#include <skse/GamePapyrusFunctions.h>
#include <skse/ScaleformCallbacks.h>
#include <skse/ScaleformMovie.h>

#include <shlobj.h>

IDebugLog gLog;

/*=================================
/ scaleform functions
/==================================*/

class SKSEScaleform_ExampleFunction : public GFxFunctionHandler
{
public:
	virtual void	Invoke(Args * args)
	{
		Console_Print("hello world from example plugin");
	}
};

bool RegisterScaleform(GFxMovieView * view, GFxValue * root)
{
	RegisterFunction <SKSEScaleform_ExampleFunction>(root, view, "ExampleFunction");

	return true;
}


/*=================================
/ papyrus functions
/==================================*/

// scriptname PluginExampleQuestScript extends Quest
class PluginExampleQuestScript : public TESQuest
{
public:
	// int Function Add(int a, int b) global native
	static SInt32 Add(SInt32 a, SInt32 b)
	{
		return a+b;
	}

	// Alias Function GetAliasByName(string aliasName) native
	BGSBaseAlias* GetAliasByName(BSFixedString aliasName)
	{
		int i = 0;
		BGSBaseAlias* alias = NULL;
		while (this->aliases.GetNthItem(i++, alias))
		{
			if (alias->name == aliasName)
				return alias;
		}

		return NULL;
	}
};


bool RegisterPapyrus(VMClassRegistry* registry)
{
	REGISTER_PAPYRUS_FUNCTION(PluginExampleQuestScript, Add, registry);
	REGISTER_PAPYRUS_FUNCTION(PluginExampleQuestScript, GetAliasByName, registry);
	REGISTER_PAPYRUS_FUNCTION(PluginExampleQuestScript, GetAliasByName, registry);

	return true;
}

/*=================================
/ event sink
/==================================*/

EventResult OnHit(TESHitEvent* evn)
{
	if (evn->caster == *g_thePlayer)
		_MESSAGE("[ HIT! ]");
		return kEvent_Continue;
}


class SwitchRaceCompleteEventFunctor
{
public:
	SwitchRaceCompleteEventFunctor() {}

	EventResult operator()(TESSwitchRaceCompleteEvent* evn, BSTEventSource<TESSwitchRaceCompleteEvent>* dispatcher)
	{
		if (evn->actor == *g_thePlayer)
			_MESSAGE("[ Switch Race! ]");
		return kEvent_Continue;
	}
};

/*=================================
/ skse plugin
/==================================*/

class ExamplePlugin : public SKSEPlugin
{
public:
	ExamplePlugin()
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim\\SKSE\\skse_plugin_example.log");
	}

	//====================================================
	// ここでプラグイン・インスタンスの初期化処理をする
	// SKSEPlugin_Query() に相当
	//====================================================
	virtual bool InitInstance()
	{
		// PluginExample.esp が MODリストに無けれれば、プラグインをロードしない
		if (!Requires("PluginExample.esp"))
			return false;

		// SKSEのバージョンが1.7.0未満なら、プラグインをロードしない
		if (!Requires(kSKSEVersion_1_7_0))
		{
			_MESSAGE("ERROR: your skse version is too old");
			return false;
		}
		
		// 各々のインタフェースが古い場合は、プラグインをロードしない
		if (!Requires(SKSEScaleformInterface::kInterfaceVersion, SKSEPapyrusInterface::kInterfaceVersion))
		{
			_MESSAGE("ERROR: interfaces are too old");
			return false;
		}

		// Requiresの引数は、一度にまとめて指定できる
		// Requires("PluginExample.esp", kSKSEVersion_1_7_0, SKSEScaleformInterface::kInterfaceVersion, SKSEPapyrusInterface::kInterfaceVersion)


		// プラグインの名前とバージョンを設定（必要）
		SetName("example plugin");
		SetVersion(1);

		// インスタンスの初期化に成功
		return true;
	}

	//====================================================
	// プラグインが正しくロードされた時に呼ばれる
	// SKSEPlugin_Load() に相当
	//====================================================
	virtual bool OnLoad()
	{
		_MESSAGE("load");

		SKSEScaleformInterface *scaleform = GetInterface<SKSEScaleformInterface>();
		scaleform->Register("example_plugin", RegisterScaleform);

		SKSEPapyrusInterface *papyrus = GetInterface<SKSEPapyrusInterface>();
		papyrus->Register(RegisterPapyrus);

		return true;
	}

	//====================================================
	// すべてのMODが読み込まれた後に呼ばれる
	//====================================================
	virtual void OnModLoaded()
	{
		// TopicInfoイベントを受け取るラムダ関数
		auto onTopicInfo = [](TESTopicInfoEvent* e) -> EventResult {
			if (!e->speaker)
				return kEvent_Continue;

			// 会話中に頭をでかくする
			static BSFixedString nodeName = "NPC Head [Head]";
			NiAVObject* node = (NiAVObject*)e->speaker->GetNiNode();
			if(node)
			{
				node = node->GetObjectByName(&nodeName.data);
				if (node)
				{
					// 会話開始で倍率を2.0に、会話終了で1.0に戻す
					node->m_localTransform.scale = (e->flag) ? 1.0 : 2.0;
				}
			}

			return kEvent_Continue;
		};

		// イベントの送信元 (ソース) をイベントの受信側 (シンク) と接続する
		// 受信側には、関数・ラムダ関数・関数オブジェクトを指定可能
		g_topicInfoEventSource += onTopicInfo;					// ラムダ
		g_hitEventSource += OnHit;								// 関数

		static SwitchRaceCompleteEventFunctor switchRaceFunctor;
		g_switchRaceCompleteEventSource += switchRaceFunctor;	// 関数オブジェクト

		// -= で切断
		g_switchRaceCompleteEventSource -= switchRaceFunctor;
		g_topicInfoEventSource -= onTopicInfo;
	}

} thePlugin;
