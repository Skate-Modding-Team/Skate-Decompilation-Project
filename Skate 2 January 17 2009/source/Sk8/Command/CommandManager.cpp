#include "CommandManager.h"

namespace Sk8 {

	class CommandManager {

	private:
		eastl::fixed_map<unsigned int, Sk8::ICommandReceiver*, 59, 1, eastl::less<unsigned int>, eastl::allocator> mMap;
		Sk8::SyncLog mSyncLog;

	public:

		CommandManager() {
			mMap = eastl::fixed_map<unsigned int, Sk8::ICommandReceiver*, 59, 1, eastl::less<unsigned int>, eastl::allocator>();
			mSyncLog = Sk8::SyncLog::SyncLog(3, 0, Sk8::GetCRC);
		}


		void Reset() {
			mSyncLog.Clear();
		}

	};

}