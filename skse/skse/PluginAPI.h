#pragma once

typedef UInt32	PluginHandle;	// treat this as an opaque type
class GFxMovieView;
class GFxValue;
class TaskDelegate;
class UIDelegate;
class UIDelegate_v1;
class InventoryEntryData;
enum
{
	kPluginHandle_Invalid = 0xFFFFFFFF
};

enum
{
	kInterface_Invalid = 0,
	kInterface_Scaleform,
	kInterface_Papyrus,
	kInterface_Serialization,
	kInterface_Task,
	kInterface_Messaging,
	kInterface_Max,
};

struct SKSEInterface
{
	UInt32	skseVersion;
	UInt32	runtimeVersion;
	UInt32	editorVersion;
	UInt32	isEditor;
	void *	(* QueryInterface)(UInt32 id);

	// call during your Query or Load functions to get a PluginHandle uniquely identifying your plugin
	// invalid if called at any other time, so call it once and save the result
	PluginHandle	(* GetPluginHandle)(void);
	
	// returns the SKSE build's release index
	UInt32			(* GetReleaseIndex)(void);
};

struct SKSEScaleformInterface
{
	enum InterfaceVersion
	{
		Version_1 = 1,
		Version_2 = 2,
		CurrentVersion = 2,
		kInterfaceVersion = 2
	};

	UInt32	interfaceVersion;

	// This callback will be called once for every new menu that is created.
	// Create your objects relative to the 'root' GFxValue parameter.
	typedef bool (* RegisterCallback)(GFxMovieView * view, GFxValue * root);
	typedef void (* RegisterInventoryCallback)(GFxMovieView * view, GFxValue * object, InventoryEntryData * item);

	// Register your plugin's scaleform API creation callback here.
	// The "name" parameter will be used to create an object with the path:
	// "skse.plugins.name" that will be passed to the callback.
	// Make sure that the memory it points to is valid from the point the callback
	// is registered until the game exits.
	bool	(* Register)(const char * name, RegisterCallback callback);

	// Registers your plugin for when item data is extended to the UI
	// either favorites menu, or inventory menu
	void    (* RegisterForInventory)(RegisterInventoryCallback callback);
};

struct SKSESerializationInterface
{
	enum InterfaceVersion
	{
		Version_1 = 1,
		Version_2 = 2,
		Version_3 = 3,
		Version_4 = 4,
		CurrentVersion = 4,
		kVersion = 4
	};
	
	typedef void (* EventCallback)(SKSESerializationInterface * intfc);

	typedef void (* FormDeleteCallback)(UInt64 handle);

	UInt32	version;

	void	(* SetUniqueID)(PluginHandle plugin, UInt32 uid);

	void	(* SetRevertCallback)(PluginHandle plugin, EventCallback callback);
	void	(* SetSaveCallback)(PluginHandle plugin, EventCallback callback);
	void	(* SetLoadCallback)(PluginHandle plugin, EventCallback callback);
	void	(* SetFormDeleteCallback)(PluginHandle plugin, FormDeleteCallback callback);

	bool	(* WriteRecord)(UInt32 type, UInt32 version, const void * buf, UInt32 length);
	bool	(* OpenRecord)(UInt32 type, UInt32 version);
	bool	(* WriteRecordData)(const void * buf, UInt32 length);

	bool	(* GetNextRecordInfo)(UInt32 * type, UInt32 * version, UInt32 * length);
	UInt32	(* ReadRecordData)(void * buf, UInt32 length);
	bool	(* ResolveHandle)(UInt64 handle, UInt64 * handleOut);
	bool	(* ResolveFormId)(UInt32 formId, UInt32 * formIdOut);
};

struct SKSETaskInterface
{
	enum InterfaceVersion
	{
		Version_1 = 1,
		Version_2 = 2,
		CurrentVersion = 2,
		kInterfaceVersion = 2
	};

	UInt32	interfaceVersion;

	// Derive your type from TaskDelegate or UIDelegate
	// Allocate before adding
	// Define your Run function
	// Delete your object in the Dispose call
	void	(* AddTask)(TaskDelegate * task);
	void	(* AddUITask)(UIDelegate_v1 * task);
};

//#ifdef _PPAPI

// ### this code is unsupported and will be changed in the future

class VMClassRegistry;

struct SKSEPapyrusInterface
{
	enum InterfaceVersion
	{
		Version_1 = 1,
		CurrentVersion = 1,
		kInterfaceVersion = 1
	};
	UInt32	interfaceVersion;
	typedef bool (* RegisterFunctions)(VMClassRegistry * registry);
	bool	(* Register)(RegisterFunctions callback);
};

//#endif


/**** Messaging API docs ********************************************************************
 *
 *	Messaging API allows inter-plugin communication at run-time. A plugin may register
 *	one callback for each plugin from which it wishes to receive messages, specifying
 *	the sender by name in the call to RegisterListener(). RegisterListener returns false
 *	if the specified plugin is not loaded, true otherwise. Any messages dispatched by
 *	the specified plugin will then be forwarded to the listener as they occur. Passing NULL as 
 *	the sender registers the calling plugin as a listener to every loaded plugin.
 *
 *	Messages may be dispatched via Dispatch() to either a specific listener (specified
 *	by name) or to all listeners (with NULL passed as the receiver). The contents and format of
 *	messageData are left up to the sender, and the receiver is responsible for casting the message
 *	to the expected type. If no plugins are registered as listeners for the sender, 
 *	Dispatch() returns false, otherwise it returns true.
 *
 *	Calling RegisterListener() or Dispatch() during plugin load is not advised as the requested plugin
 *	may not yet be loaded at that point. Instead, if you wish to register as a listener or dispatch a
 *	message immediately after plugin load, use RegisterListener() during load to register to receive
 *	messages from SKSE (sender name: "SKSE"). You will then receive a message from SKSE once 
 *	all plugins have been loaded, at which point it is safe to establish communications between
 *	plugins.
 *
 *	Some plugin authors may wish to use strings instead of integers to denote message type. In
 *	that case the receiver can pass the address of the string as an integer and require the receiver
 *	to cast it back to a char* on receipt.
 *
 *********************************************************************************************/

struct SKSEMessagingInterface
{
	struct Message {
		const char	* sender;
		UInt32		type;
		UInt32		dataLen;
		void		* data;
	};

	typedef void (* EventCallback)(Message* msg);

	enum InterfaceVersion
	{
		Version_1 = 1,
		Version_2 = 2,
		CurrentVersion = 2,
		kInterfaceVersion = 2
	};

	// SKSE messages
	enum {
		kMessage_PostLoad,		// sent to registered plugins once all plugins have been loaded (no data)
		kMessage_PostPostLoad,	// sent right after kMessage_PostLoad to facilitate the correct dispatching/registering of messages/listeners
		kMessage_PreLoadGame,	// dispatched immediately before savegame is read by Fallout
								// dataLen: length of file path, data: char* file path of .ess savegame file
		kMessage_PostLoadGame,	//dispatched after an attempt to load a saved game has finished (the game's LoadGame() routine
								//has returned). You will probably want to handle this event if your plugin uses a Preload callback
								//as there is a chance that after that callback is invoked the game will encounter an error
								//while loading the saved game (eg. corrupted save) which may require you to reset some of your
								//plugin state.
								//data: bool, true if game successfully loaded, false otherwise
								// plugins may register as listeners during the first callback while deferring dispatches until the next
		kMessage_SaveGame,
		kMessage_DeleteGame,	// sent right before deleting the .skse cosave and the .ess save.
								// dataLen: length of file path, data: char* file path of .ess savegame file
		kMessage_InputLoaded,	// sent right after game input is loaded, right before the main menu initializes
		kMessage_NewGame,		// sent after a new game is created, before the game has loaded (Sends CharGen TESQuest pointer)
		kMessage_DataLoaded		// send after the data handler has loaded all its forms
	};

	UInt32	interfaceVersion;
	bool	(* RegisterListener)(PluginHandle listener, const char* sender, EventCallback handler);
	bool	(* Dispatch)(PluginHandle sender, UInt32 messageType, void * data, UInt32 dataLen, const char* receiver);

	enum
	{
		kDispatcher_ModEvent = 0,
		kDispatcher_CameraEvent,
		kDispatcher_CrosshairEvent,
		kDispatcher_ActionEvent,
		kDispatcher_NiNodeUpdateEvent
	};

	// Use this to acquire SKSE's internal EventDispatchers so that you can sink to them
	void	* (* GetEventDispatcher)(UInt32 dispatcherId);
};

struct SKSEObjectInterface
{
	enum InterfaceVersion
	{
		Version_1 = 1,
		CurrentVersion = 1,
		kInterfaceVersion = 1
	};

	UInt32	interfaceVersion;

	// Derive your type from TaskDelegate or UIDelegate
	// Allocate before adding
	// Define your Run function
	// Delete your object in the Dispose call
	void	(* AddTask)(TaskDelegate * task);
	void	(* AddUITask)(UIDelegate_v1 * task);
};

struct PluginInfo
{
	enum
	{
		Version_1 = 1,
		CurrentVersion = 1,
		kInfoVersion = 1
	};

	UInt32			infoVersion;
	const char *	name;
	UInt32			version;
};

typedef bool (* _SKSEPlugin_Query)(const SKSEInterface * skse, PluginInfo * info);
typedef bool (* _SKSEPlugin_Load)(const SKSEInterface * skse);

/**** plugin API docs **********************************************************
 *	
 *	The base API is pretty simple. Create a project based on the
 *	skse_plugin_example project included with the SKSE source code, then define
 *	and export these functions:
 *	
 *	bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
 *	
 *	This primary purposes of this function are to fill out the PluginInfo
 *	structure, and to perform basic version checks based on the info in the
 *	SKSEInterface structure. Return false if your plugin is incompatible with
 *	the version of SKSE or the runtime passed in, otherwise return true. In
 *	either case, fill out the PluginInfo structure.
 *	
 *	Do not do anything other than fill out the PluginInfo structure and return
 *	true/false in this callback.
 *	
 *	If the plugin is being loaded in the context of the editor, isEditor will be
 *	non-zero, editorVersion will contain the current editor version, and
 *	runtimeVersion will be zero. In this case you can probably just return
 *	true, however if you have multiple DLLs implementing the same behavior, for
 *	example one for each version of ther runtime, only one of them should return
 *	true.
 *	
 *	The PluginInfo fields should be filled out as follows:
 *	- infoVersion should be set to PluginInfo::kInfoVersion
 *	- name should be a pointer to a null-terminated string uniquely identifying
 *	  your plugin, it will be used in the plugin querying API
 *	- version is only used by the plugin query API, and will be returned to
 *	  scripts requesting the current version of your plugin
 *	
 *	bool SKSEPlugin_Load(const SKSEInterface * skse)
 *	
 *	In this function, use the interfaces above to register your commands, patch
 *	memory, generally do whatever you need to for integration with the runtime.
 *	
 *	At this time, or at any point forward you can call the QueryInterface
 *	callback to retrieve an interface structure for the base services provided
 *	by the SKSE core.
 *	
 *	You may optionally return false from this function to unload your plugin,
 *	but make sure that you DO NOT register any commands if you do.
 *	
 *	Note that all structure versions are backwards-compatible, so you only need
 *	to check against the latest version that you need. New fields will be only
 *	added to the end, and all old fields will remain compatible with their
 *	previous implementations.
 *	
 ******************************************************************************/
enum SKSEVersion
{
	kSKSEVersion_1_3_0  = 0x01030000,
	kSKSEVersion_1_4_0  = 0x01040000,
	kSKSEVersion_1_4_1  = 0x01040010,
	kSKSEVersion_1_4_2  = 0x01040020,
	kSKSEVersion_1_4_3  = 0x01040030,
	kSKSEVersion_1_4_4  = 0x01040040,
	kSKSEVersion_1_4_5  = 0x01040050,
	kSKSEVersion_1_4_6  = 0x01040060,
	kSKSEVersion_1_4_7  = 0x01040070,
	kSKSEVersion_1_4_8  = 0x01040080,
	kSKSEVersion_1_4_9  = 0x01040090,
	kSKSEVersion_1_4_10 = 0x010400A0,
	kSKSEVersion_1_4_11 = 0x010400B0,
	kSKSEVersion_1_4_12 = 0x010400C0,
	kSKSEVersion_1_4_13 = 0x010400D0,
	kSKSEVersion_1_4_14 = 0x010400E0,
	kSKSEVersion_1_4_15 = 0x010400F0,
	kSKSEVersion_1_5_1  = 0x01050010,
	kSKSEVersion_1_5_2  = 0x01050020,
	kSKSEVersion_1_5_3  = 0x01050030,
	kSKSEVersion_1_5_4  = 0x01050040,
	kSKSEVersion_1_5_5  = 0x01050050,
	kSKSEVersion_1_5_6  = 0x01050060,
	kSKSEVersion_1_5_7  = 0x01050070,
	kSKSEVersion_1_5_8  = 0x01050080,
	kSKSEVersion_1_5_9  = 0x01050090,
	kSKSEVersion_1_5_10 = 0x010500A0,
	kSKSEVersion_1_5_11 = 0x010500B0,
	kSKSEVersion_1_6_0  = 0x01060000,
	kSKSEVersion_1_6_1  = 0x01060010,
	kSKSEVersion_1_6_2  = 0x01060020,
	kSKSEVersion_1_6_3  = 0x01060030,
	kSKSEVersion_1_6_4  = 0x01060040,
	kSKSEVersion_1_6_5  = 0x01060050,
	kSKSEVersion_1_6_6  = 0x01060060,
	kSKSEVersion_1_6_7  = 0x01060070,
	kSKSEVersion_1_6_8  = 0x01060080,
	kSKSEVersion_1_6_9  = 0x01060090,
	kSKSEVersion_1_6_10 = 0x010600A0,
	kSKSEVersion_1_6_11 = 0x010600B0,
	kSKSEVersion_1_6_12 = 0x010600C0,
	kSKSEVersion_1_6_13 = 0x010600D0,
	kSKSEVersion_1_6_14 = 0x010600E0,
	kSKSEVersion_1_6_15 = 0x010600F0,
	kSKSEVersion_1_6_16 = 0x01060100,
	kSKSEVersion_1_7_0  = 0x01070000,
	kSKSEVersion_1_7_1  = 0x01070010,
	kSKSEVersion_1_7_2  = 0x01070020,
	kSKSEVersion_1_7_3  = 0x01070030
};


class SKSEPlugin
{
public:
	SKSEPlugin();
	
	virtual bool InitInstance();
	virtual bool OnLoad();
	virtual void OnModLoaded();

	void SetName(const char* name);
	void SetVersion(UInt32 version);
	
	PluginHandle GetPluginHandle() const;
	UInt32 GetRuntimeVersion() const;
	UInt32 GetSKSEVersion() const;
	UInt32 GetSKSEReleaseIndex() const;

	template <typename Version>
	bool Requires(Version version) const;
	bool Requires(SKSEVersion version) const;
	bool Requires(SKSEScaleformInterface::InterfaceVersion version) const;
	bool Requires(SKSEPapyrusInterface::InterfaceVersion version) const;
	bool Requires(SKSESerializationInterface::InterfaceVersion version) const;
	bool Requires(SKSETaskInterface::InterfaceVersion version) const;
	bool Requires(SKSEMessagingInterface::InterfaceVersion version) const;
	bool Requires(const char* modName) const;

	template <typename IV1, typename IV2>
	bool Requires(IV1 iv1, IV2 iv2) {return Requires(iv1) && Requires(iv2);}
	template <typename IV1, typename IV2, typename IV3>
	bool Requires(IV1 iv1, IV2 iv2, IV3 iv3) {return Requires(iv1) && Requires(iv2) && Requires(iv3);}
	template <typename IV1, typename IV2, typename IV3, typename IV4>
	bool Requires(IV1 iv1, IV2 iv2, IV3 iv3, IV4 iv4) {return Requires(iv1) && Requires(iv2) && Requires(iv3) && Requires(iv4);}
	template <typename IV1, typename IV2, typename IV3, typename IV4, typename IV5>
	bool Requires(IV1 iv1, IV2 iv2, IV3 iv3, IV4 iv4, IV5 iv5) {return Requires(iv1) && Requires(iv2) && Requires(iv3) && Requires(iv4) && Requires(iv5);}
	template <typename IV1, typename IV2, typename IV3, typename IV4, typename IV5, typename IV6>
	bool Requires(IV1 iv1, IV2 iv2, IV3 iv3, IV4 iv4, IV5 iv5, IV6 iv6) {return Requires(iv1) && Requires(iv2) && Requires(iv3) && Requires(iv4) && Requires(iv5) && Requires(iv6);}

	template <typename Interface>
	Interface* GetInterface() const;

	template <typename Interface>
	UInt32 GetInterfaceVersion() const;
};
