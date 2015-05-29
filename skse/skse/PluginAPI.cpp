
#include "skse_version.h"
#include "PluginAPI.h"
#include "GameTESEvents.h"
#include "common/IFileStream.h"

#include <string>
#include <shlobj.h>

static HINSTANCE                    hInstance;

static SKSEPlugin*	thePlugin = NULL;

static PluginInfo*	thePluginInfo = NULL;
static PluginHandle	pluginHandle = kPluginHandle_Invalid;
static UInt32 runtimeVersion = 0;
static UInt32 skseVersion = 0;
static UInt32 skseReleaseIndex = 0;
static SKSEScaleformInterface* scaleform = NULL;
static SKSEPapyrusInterface* papyrus = NULL;
static SKSESerializationInterface* serialization = NULL;
static SKSETaskInterface* task = NULL;
static SKSEMessagingInterface* messaging = NULL;

UInt32 skses[] = {
	MAKE_SKYRIM_VERSION(1,3,0),
	MAKE_SKYRIM_VERSION(1,4,0),
	MAKE_SKYRIM_VERSION(1,4,1),
	MAKE_SKYRIM_VERSION(1,4,2),
	MAKE_SKYRIM_VERSION(1,4,3),
	MAKE_SKYRIM_VERSION(1,4,4),
	MAKE_SKYRIM_VERSION(1,4,5),
	MAKE_SKYRIM_VERSION(1,4,6),
	MAKE_SKYRIM_VERSION(1,4,7),
	MAKE_SKYRIM_VERSION(1,4,8),
	MAKE_SKYRIM_VERSION(1,4,9),
	MAKE_SKYRIM_VERSION(1,4,10),
	MAKE_SKYRIM_VERSION(1,4,11),
	MAKE_SKYRIM_VERSION(1,4,12),
	MAKE_SKYRIM_VERSION(1,4,13),
	MAKE_SKYRIM_VERSION(1,4,14),
	MAKE_SKYRIM_VERSION(1,4,15),
	MAKE_SKYRIM_VERSION(1,5,1),
	MAKE_SKYRIM_VERSION(1,5,2),
	MAKE_SKYRIM_VERSION(1,5,3),
	MAKE_SKYRIM_VERSION(1,5,4),
	MAKE_SKYRIM_VERSION(1,5,5),
	MAKE_SKYRIM_VERSION(1,5,6),
	MAKE_SKYRIM_VERSION(1,5,7),
	MAKE_SKYRIM_VERSION(1,5,8),
	MAKE_SKYRIM_VERSION(1,5,9),
	MAKE_SKYRIM_VERSION(1,5,10),
	MAKE_SKYRIM_VERSION(1,5,11),
	MAKE_SKYRIM_VERSION(1,6,0),
	MAKE_SKYRIM_VERSION(1,6,1),
	MAKE_SKYRIM_VERSION(1,6,2),
	MAKE_SKYRIM_VERSION(1,6,3),
	MAKE_SKYRIM_VERSION(1,6,4),
	MAKE_SKYRIM_VERSION(1,6,5),
	MAKE_SKYRIM_VERSION(1,6,6),
	MAKE_SKYRIM_VERSION(1,6,7),
	MAKE_SKYRIM_VERSION(1,6,8),
	MAKE_SKYRIM_VERSION(1,6,9),
	MAKE_SKYRIM_VERSION(1,6,10),
	MAKE_SKYRIM_VERSION(1,6,11),
	MAKE_SKYRIM_VERSION(1,6,12),
	MAKE_SKYRIM_VERSION(1,6,13),
	MAKE_SKYRIM_VERSION(1,6,14),
	MAKE_SKYRIM_VERSION(1,6,15),
	MAKE_SKYRIM_VERSION(1,6,16),
	0
};

SKSEPlugin::SKSEPlugin()
{
	thePlugin = this;
}

// @virtual
bool SKSEPlugin::InitInstance()
{
	return true;
}

// @virtual
bool SKSEPlugin::OnLoad()
{
	return true;
}

// @virtual
void SKSEPlugin::OnModLoaded()
{
}

void SKSEPlugin::SetName(const char* name)
{
	thePluginInfo->name = name;
}

void SKSEPlugin::SetVersion(UInt32 version)
{
	thePluginInfo->version = version;
}

PluginHandle SKSEPlugin::GetPluginHandle() const
{
	return pluginHandle;
}

UInt32 SKSEPlugin::GetRuntimeVersion() const
{
	return runtimeVersion;
}

UInt32 SKSEPlugin::GetSKSEVersion() const
{
	return skseVersion;
}

UInt32 SKSEPlugin::GetSKSEReleaseIndex() const
{
	return skseReleaseIndex;
}

bool SKSEPlugin::Requires(SKSEVersion version) const
{
	return skseVersion >= version;
}

bool SKSEPlugin::Requires(SKSEScaleformInterface::InterfaceVersion version) const
{
	return scaleform->interfaceVersion >= version;
}

bool SKSEPlugin::Requires(SKSEPapyrusInterface::InterfaceVersion version) const
{
	return papyrus->interfaceVersion >= version;
}

bool SKSEPlugin::Requires(SKSESerializationInterface::InterfaceVersion version) const
{
	return serialization->version >= version;
}

bool SKSEPlugin::Requires(SKSETaskInterface::InterfaceVersion version) const
{
	return task->interfaceVersion >= version;
}

bool SKSEPlugin::Requires(SKSEMessagingInterface::InterfaceVersion version) const
{
	return messaging->interfaceVersion >= version;
}

template <> SKSEScaleformInterface* SKSEPlugin::GetInterface<SKSEScaleformInterface>() const			{return scaleform;}
template <> SKSEPapyrusInterface* SKSEPlugin::GetInterface<SKSEPapyrusInterface>() const				{return papyrus;}
template <> SKSESerializationInterface* SKSEPlugin::GetInterface<SKSESerializationInterface>() const	{return serialization;}
template <> SKSETaskInterface* SKSEPlugin::GetInterface<SKSETaskInterface>() const						{return task;}
template <> SKSEMessagingInterface* SKSEPlugin::GetInterface<SKSEMessagingInterface>() const			{return messaging;}

template <> UInt32 SKSEPlugin::GetInterfaceVersion<SKSEScaleformInterface>() const		{return scaleform ? scaleform->interfaceVersion : -1;}
template <> UInt32 SKSEPlugin::GetInterfaceVersion<SKSEPapyrusInterface>() const		{return papyrus ? papyrus->interfaceVersion : -1;}
template <> UInt32 SKSEPlugin::GetInterfaceVersion<SKSESerializationInterface>() const	{return serialization ? serialization->version : -1;}
template <> UInt32 SKSEPlugin::GetInterfaceVersion<SKSETaskInterface>() const			{return task ? task->interfaceVersion : -1;}
template <> UInt32 SKSEPlugin::GetInterfaceVersion<SKSEMessagingInterface>() const		{return messaging ? messaging->interfaceVersion : -1;}

bool SKSEPlugin::Requires(const char* modName) const
{
	char buf[MAX_PATH];
	ASSERT(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, buf)));

	std::string	modlistPath = buf;
	modlistPath += "\\Skyrim\\plugins.txt";

	bool bFound = false;
	IFileStream modlistFile;
	if (modlistFile.Open(modlistPath.c_str()))
	{
		while(!modlistFile.HitEOF())
		{
			modlistFile.ReadString(buf, MAX_PATH, '\n', '\r');

			if (buf[0] == '#')
				continue;

			if (_stricmp(buf, modName) == 0)
			{
				bFound = true;
				break;
			}
		}
	}

	modlistFile.Close();

	return bFound;
}


class ModLoadedEventSink : public BSTEventSink<TESMagicEffectApplyEvent>
{
public:
	ModLoadedEventSink() {}
	virtual EventResult ReceiveEvent(TESMagicEffectApplyEvent* evn, BSTEventSource<TESMagicEffectApplyEvent>* source)
	{
		source->RemoveEventSink(this);

		thePlugin->OnModLoaded();
		return kEvent_Continue;
	}
};


//=======================================================================================================

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		hInstance = hinstDLL;
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}

extern "C"
{

bool __declspec(dllexport) SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
{
	if (!thePlugin)
		return false;

	thePluginInfo  = info;
	pluginHandle   = skse->GetPluginHandle();
	runtimeVersion = skse->runtimeVersion;
	skseVersion    = skse->skseVersion;

	if (!gLog.IsOpen())
	{
		char path[MAX_PATH];
		char fname[MAX_PATH];
		GetModuleFileName(hInstance, path, MAX_PATH);
		_splitpath_s(path, NULL, 0, NULL, 0, fname, MAX_PATH, NULL, 0);

		SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, path);
		strcat_s(path, sizeof(path), "\\My Games\\Skyrim\\SKSE\\");
		strcat_s(path, sizeof(path), fname);
		strcat_s(path, sizeof(path), ".log");
		gLog.Open(path);
	}

	if (skseVersion >= MAKE_SKYRIM_VERSION(1, 7, 0))
	{
		skseReleaseIndex = skse->GetReleaseIndex();
	}
	else
	{
		for (int i = 0; skses[i]; i++)
		{
			if (skses[i] >= skseVersion)
			{
				skseReleaseIndex = i;
				break;
			}
		}
	}

	if(skse->isEditor)
	{
		_MESSAGE("loaded in editor, marking as incompatible");
		return false;
	}

	UInt32 runtimeVersion = skse->runtimeVersion;
	int major = (runtimeVersion >> 24) & 0xFF;
	int minor = (runtimeVersion >> 16) & 0xFF;
	int build = (runtimeVersion >> 8) & 0xFF;
	int sub   = runtimeVersion & 0xFF;

	if(skse->runtimeVersion != RUNTIME_VERSION_1_9_32_0)
	{
		_MESSAGE("unsupported runtime version 1.%d.%d.%d", major, minor, build);
		_MESSAGE("(this plugin needs 1.%d.%d.%d)", major, minor, build);
		return false;
	}

	scaleform     = (SKSEScaleformInterface*)skse->QueryInterface(kInterface_Scaleform);
	papyrus       = (SKSEPapyrusInterface*)skse->QueryInterface(kInterface_Papyrus);
	serialization = (SKSESerializationInterface*)skse->QueryInterface(kInterface_Serialization);
	task          = (SKSETaskInterface*)skse->QueryInterface(kInterface_Task);
	messaging     = (SKSEMessagingInterface*)skse->QueryInterface(kInterface_Messaging);

	return thePlugin->InitInstance();
}


bool __declspec(dllexport) SKSEPlugin_Load(const SKSEInterface * skse)
{
	if (!thePlugin)
		return false;

	if (!thePlugin->OnLoad())
		return false;

	static ModLoadedEventSink modLoadedSink;
	g_magicEffectApplyEventSource.AddEventSink(&modLoadedSink);

	return true;
}


}
