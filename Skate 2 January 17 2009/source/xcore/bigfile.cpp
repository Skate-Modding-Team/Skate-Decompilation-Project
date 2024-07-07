#include "util.h"
#include <string>
#include <utility>
using namespace std;

namespace xcore
{
	class BigFile
	{
	public:
		BigFile(const char* filename, bool bUseBigHeader) {
			if (!filename) {
				xcore::FailAssert("filename", "xcore\\bigfile.cpp", 11);
				DebugBreak();
			}
			this->mHandle = 0;
			Mount(filename, bUseBigHeader);
		}

		void Mount(const char* filename, bool bUseBigHeader) {
			if (!filename) {
				xcore::FailAssert("filename", "xcore\\bigfile.cpp", 20);
				DebugBreak();
			}
			if (mHandle == NULL) {
				xcore::FailAssert("mHandle == NULL", "xcore\\bigfile.cpp", 24);
				DebugBreak();
			}
			char outPath[304];
			xcore::ConvertSlashes(filename, outPath);
			mHandle = rw::core::BigHandler::AddArchiveFromFile(xcore::BigFile::msHandler, outPath, bUseBigHeader);
			if (!mHandle) {
				pair<char*, char*> message;
				message.first = "Failed to Mount Bigfile %s\n";
				message.second = filename;
				char* assertMessage = xcore::FmtAssertMessage(message);
				xcore::FailAssert(assertMessage, "xcore\\bigfile.cpp", 32);
				DebugBreak();
			}
		}

		void UnMount() {
			if (!msHandler) {
				xcore::FailAssert("msHandler", "xcore\\bigfile.cpp", 39);
				DebugBreak();
			}
			if (mHandle) {
				rw::core::BigHandler::RemoveArchive(msHandler, mHandle);
				mHandle = 0;
			}
		}

		~BigFile() {
			UnMount();
		}

		static void Create(EA::Allocator::ICoreAllocator* coreallocator) {
			if (msHandler == NULL) {
				xcore::FailAssert("msHandler == NULL", "xcore\\bigfile.cpp", 54);
				DebugBreak();
			}
			if (msAllocator == NULL) {
				xcore::FailAssert("msAllocator == NULL", "xcore\\bigfile.cpp", 58);
				DebugBreak();
			}
			if (coreallocator == NULL) {
				xcore::FailAssert("coreallocator == NULL", "xcore\\bigfile.cpp", 62);
				DebugBreak();
			}

			msAllocator = coreallocator;
			//TODO: figure out vtable to finish this function
		}

		static uint64_t QueryLocation(const char* filename) {
			char path[264];
			xcore::ConvertSlashes(filename, path);
			return rw::core::BigHandler::QueryLocationByName(msHandler, path);
		}

	private:
		void* mHandle;

		static EA::Allocator::ICoreAllocator* msAllocator = EA::Allocator::ICoreAllocator;
		static rw::core::BigHandler* msHandler = rw::core::BigHandler;
	};
}