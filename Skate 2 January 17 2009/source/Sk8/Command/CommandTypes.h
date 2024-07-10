namespace Sk8 {

	enum CommandTypes {
		Command_Invalid,
		Command_PlayerInput,
		Command_PlayerInputGainFocus,
		Command_PlayerSpawn,
		Command_PlayerUnSpawn,
		Command_PlayerTeleport,
		Command_PlayerWipeout,
		Command_PlayerPin,
		Command_PlayerSetTransform,
		Command_GhostSpawn,
		Command_AiSpawn,
		Command_AiUnSpawn,
		Command_Contact,
		Command_SkateboardContacts,
		Command_SkeletonContacts,
		Command_Count
	};

	enum CommandIDs {
		CommandID_Invalid,
		CommandID_SkaterManager,
		CommandID_GameInput_0,
		CommandID_GameInput_Ghost,
		CommandID_PhysicsSkeleton_0,
		CommandID_PhysicsSkeleton_Ghost,
		CommandID_PhysicsSkateboard_0,
		CommandID_PhysicsSkateboard_Ghost,
		CommandID_Count,
		CommandID_LAST
	};

}