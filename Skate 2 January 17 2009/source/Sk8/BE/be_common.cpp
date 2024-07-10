namespace Sk8 {
	namespace BE {

		class CommonBackEnd {

			enum GameMode {
				GM_NoProfileFreeSkate,
				GM_SinglePlayer,
				GM_PartyPlay,
				GM_ProfileFreeSkate,
				GM_OnlineFreeSkate,
				GM_OnlineChallenge,
				GM_Tutorial,
				GM_DebugFE,
				GM_TotalModes
			};

			enum GameQuality {
				GQ_High,
				GQ_Med,
				GQ_Low
			};

			enum CharacterType {
				MARQUEE,
				CAS
			};

			struct CommonData {
				char mCameraSet[128];
			};

			class GameInfo {
				GameMode gameMode;
				GameQuality gameQuality;
				unsigned __int64 challengeKey;

			};

			static GameInfo sGameInfo;



		};

	}
}