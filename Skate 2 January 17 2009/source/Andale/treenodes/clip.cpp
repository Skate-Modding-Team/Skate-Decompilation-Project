namespace Andale {

	class Clip : public Andale::Animation {

	private:
		float mDebugPrintOldTime;
		unsigned int mDebugPrintNumLoops;
		void* mClipHeader;
		float mSpeed;
		float mLength;
		float mTime;
		float mOldTime;
		unsigned int mNumLoops;
		float mNbFrames;
		void* mLoopingAnim;
		float mFps;
		float mBaseSpeed;
		void* mTrimmed;

	public:

		void Reset() {
			mNumLoops = 0;
			mTime = 0.0;
			mOldTime = 0.0;
		}

		float GetLength() {
			return *((float*)&mLength + 1);
		}

		float FrameToTime(double frame) {

			if (mSpeed == 0.0 || mBaseSpeed == 0.0) {

			}

		}

	};
}