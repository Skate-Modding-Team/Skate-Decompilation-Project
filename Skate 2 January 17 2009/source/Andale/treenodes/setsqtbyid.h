namespace Andale {
	
	class SetSQTById, public Andale::SetSQT {
	private:
		unsigned int mSqtId;

	public:

		void DebugDump(int indentLevel, Andale::cAnimDebugDumper* dumper) {
			dumper->DrawText(dumper, indentLevel, "SetSQT"); //virtual func
		}

		int Eval(const Andale::tAnimationEvalParams* params, bool doEval) {
			if (doEval) {
				AnimCmdSys::AnimCommandSystem::SetSQTById(params->ACS, mSqtId);
			}
			return doEval;
		}

	};
}