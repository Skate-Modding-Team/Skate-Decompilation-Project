
namespace xcore {

	class PrintMacroHelper {
	private:
		char* mChannelName;
		char* mFile;
		unsigned int mLine;

	public:
		PrintMacroHelper(const char* file, unsigned int line) {
			mFile = file;
			mLine = line;
			mChannelName = 0;
		}

		PrintMacroHelper(const char* file, unsigned int line, const char* channelName) {
			mFile = file;
			mLine = line;
			mChannelName = channelName;
		}
	};

	FailAssert(const char* msg, const char* file, int line) {
		PrintMacroHelper pmh("xcore\\a");
	}

}