
class ExecutionMan {
	virtual ~ExecutionMan() {}
	virtual void Init(int timerHz) = 0;
	virtual void InitRenderThread() = 0;
	virtual void PurgeRenderThread() = 0;
	virtual void PurgeTimerThread() = 0;
	virtual void Purge() = 0;
	virtual void Wait() = 0;
	virtual void Wakeup() = 0;
	virtual void Exit() = 0;
	virtual void GetCurrentThreadId() = 0;
	virtual void GetMainThreadId() = 0;
	virtual void GetRenderThreadId() = 0;
	virtual void GetLoadThreadId() = 0;
	virtual void SetTimerHz(int timerHz) = 0;
	virtual void GetTimerHz() = 0;
	virtual void Load() = 0;
	virtual void IsLoadDone() = 0;
	virtual void Update() = 0;
};

class XBox2ExecutionMan : public ExecutionMan {



};

void systemInit() {

}

int main(int ac, char** av) {
	systemInit();
	XBox2ExecutionMan execMan;
	Sk8::Behaviors::TakeDownTargetablePredictions::CreateInstance();

	if (!AppMan::sTheAppMan) {
		xcore::FailAssert("sTheAppMan", "Sk8\\Scaffold\\appman\\appman.h", 0);
		DebugBreak();
	}

	return 0;
}