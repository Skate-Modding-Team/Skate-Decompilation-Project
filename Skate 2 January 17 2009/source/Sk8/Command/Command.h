#include "CommandTypes.h"

namespace Sk8 {

	class Command {

		typedef MAX_COMMAND_SIZE 0xFF;

	private:
		Sk8::CommandTypes mType;
		Sk8::CommandIDs mReceiverID;
		unsigned int mDataSize;
		char mData[255];

	public:

		Command(const Sk8::Command* src) {
			mType = src->mType;
			mReceiverID = src->mReceiverID;
			mDataSize = src->mDataSize;
			if (src->mDataSize) {
				memcpy(mData, src->mData, src->mDataSize);
			}
		}

		Command(Sk8::CommandIDs receiverID, Sk8::CommandTypes type, const char* data, unsigned int size) {
			mType = type;
			mReceiverID = receiverID;
			mDataSize = size;
			if (data) {
				if (size) {
					memcpy(mData, data, size);
				}
			}
		}

		template <typename T>
		void GetData(T* data) {
			if (mType != T::DATA_TYPE) {
				xcore::FailAssert("mType == T::DATA_TYPE", "Sk8\\Command\\Command.h", 40);
				DebugBreak();
			}

			Sk8::ByteStream bs;
			bs.Reset();
			bs.Attach(mData, mDataSize);
			data.Unpack(bs);
			bs.Reset();
		}

		template <typename T>
		void SetData(const T* data) {

			mType = T::DATA_TYPE;

			Sk8::ByteStream bs;
			bs.Reset();
			bs.Attach(mData, 0xFFu);
			data->Pack(bs);
			mDataSize = bs.GetPos();
			if (bs.HadError()) {
				xcore::FailAssert("!bs.HadError()", "Sk8\\Command\\Command.h", 62);
				DebugBreak();
			}
			bs.Reset();
		}
	};

}