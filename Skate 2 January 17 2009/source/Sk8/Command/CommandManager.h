#include "Command.h"

namespace Sk8 {

	class CommandManager {

	private:
		eastl::fixed_map<unsigned int, Sk8::ICommandReceiver*, 59, 1, eastl::less<unsigned int>, eastl::allocator> mMap;
		Sk8::SyncLog mSyncLog;

	public:

		CommandManager();
		~CommandManager();
		void Reset();
		void DoCommand(const Sk8::Command* command, bool addToCRC);
		void GetSyncLog(Sk8::SyncLog* log);
		void RegisterReceiver(Sk8::ICommandReceiver* receiver);
		void UnregisterReceiver(Sk8::ICommandReceiver* receiver);
	};

}