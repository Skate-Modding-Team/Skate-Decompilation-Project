namespace Sk8 {
	namespace BE {

		public class IBackEndModule {
		protected:
			unsigned int mInterfaceIndex;
			void* mLastThreadId;

			IBackEndModule(unsigned int interfaceIndex) {
				mInterfaceIndex = interfaceIndex;
				mLastThreadId = EA::Thread::GetThreadId();
			}

			virtual ~IBackEndModule() {}

		public:

			virtual void Init() = 0;
			virtual void Purge() = 0;
			virtual void SimUpdate = 0;
			virtual void RenderUpdate = 0;

		};

	}
}