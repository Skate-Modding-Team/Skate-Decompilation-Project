namespace Sk8 {
	namespace BE {

		class CheatsBackEndCore : public Sk8::BE::IBackEndModule {
		protected:
			tCheatInfo* mCheatInfo;
			unsigned int mNumCheats;

			enum eCheatsCategory {
				eCheatsCategory_ProSkaters,
				eCheatsCategory_World,
				eCheatsCategory_Skating,
				eCheatsCategory_Camera,
				eCheatsCategory_Character,
				eCheatsCategory_Audio,
				eCheatsCategory_GamePlay,
				eCheatsCategory_Total
			};

			struct tCheatInfo {
				unsigned int mItem;
				eCheatsCategory mCategory;
				const char* mLockID;
				const char* mUnlockID;
				const char* mDescID;
				bool mActivated;
				bool mUnlocked;
			};

			static tCheatInfo StaticCheatInfoTable[44] = {
				{0, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER01\"", "\"ID_COMMON_ALEX_CHALMERS\"", "\"NO_DESC\"", 0, 0},
				{1, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER02\"", "\"ID_COMMON_ALI_BOULALA\"", "\"NO_DESC\"", 0, 0},
				{2, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER03\"", "\"ID_COMMON_CHRIS_COLE\"", "\"NO_DESC\"", 0, 0},
				{3, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER04\"", "\"ID_COMMON_CHRIS_HASLAM\"", "\"NO_DESC\"", 0, 0},
				{4, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER05\"", "\"ID_COMMON_COLIN_MACKAY\"", "\"NO_DESC\"", 0, 0},
				{5, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER06\"", "\"ID_COMMON_DANNY_WAY\"", "\"NO_DESC\"", 0, 0},
				{6, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER07\"", "\"ID_COMMON_DENNIS_BUSENTIZ\"", "\"NO_DESC\"", 0, 0},
				{7, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER08\"", "\"ID_COMMON_JASON_DILL\"", "\"NO_DESC\"", 0, 0},
				{8, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER09\"", "\"ID_COMMON_JERRY_HSU\"", "\"NO_DESC\"", 0, 0},
				{9, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER10\"", "\"ID_COMMON_JOHN_RATTRAY\"", "\"NO_DESC\"", 0, 0},
				{10, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER11\"", "\"ID_COMMON_GONZ\"", "\"NO_DESC\"", 0, 0},
				{11, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER12\"", "\"ID_COMMON_MIKE_CARROLL\"", "\"NO_DESC\"", 0, 0},
				{12, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER13\"", "\"ID_COMMON_PAT_DUFFY\"", "\"NO_DESC\"", 0, 0},
				{13, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER14\"", "\"ID_COMMON_PAUL_RODRIGUEZ\"", "\"NO_DESC\"", 0, 0},
				{14, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER15\"", "\"ID_COMMON_PJ_LADD\"", "\"NO_DESC\"", 0, 0},
				{15, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER16\"", "\"ID_COMMON_ROB_DYRDEK\"", "\"NO_DESC\"", 0, 0},
				{16, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER17\"", "\"ID_COMMON_RYAN_GALLANT\"", "\"NO_DESC\"", 0, 0},
				{17, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER18\"", "\"ID_COMMON_RYAN_SMITH\"", "\"NO_DESC\"", 0, 0},
				{18, eCheatsCategory_ProSkaters, "\"ID_CHEAT_PROSKATER19\"", "\"ID_COMMON_TERRY_KENNEDY\"", "\"NO_DESC\"", 0, 0},
				{19, eCheatsCategory_World, "\"ID_CHEAT_BACKPAINPANDEMIC\"", 0, "\"ID_CHEAT_BACKPAINPANDEMIC_DESC\"", 0, 0},
				{20, eCheatsCategory_World, "\"ID_CHEAT_ROADRAGE\"", 0, "\"ID_CHEAT_ROADRAGE_DESC\"", 0, 0},
				{21, eCheatsCategory_World, "\"ID_CHEAT_PLANETOFSKATERS\"", 0, "\"ID_CHEAT_PLANETOFSKATERS_DESC\"", 0, 0},
				{22, eCheatsCategory_World, "\"ID_CHEAT_MENTAL\"", 0, "\"ID_CHEAT_MENTAL_DESC\"", 0, 0},
				{23, eCheatsCategory_Skating, "\"ID_CHEAT_SLOWMOTION\"", 0, "\"ID_CHEAT_SLOWMOTION_DESC\"", 0, 0},
				{24, eCheatsCategory_Skating, "\"ID_CHEAT_CELEBRATION\"", 0, "\"ID_CHEAT_CELEBRATION_DESC\"", 0, 0},
				{25, eCheatsCategory_Skating, "\"ID_CHEAT_WIPEOUTBUTTON\"", 0, "\"ID_CHEAT_WIPEOUTBUTTON_DESC\"", 0, 0},
				{26, eCheatsCategory_Skating, "\"ID_CHEAT_FLOATINGFREEZEFRAME\"", 0, "\"ID_CHEAT_FLOATINGFREEZEFRAME_DESC\"", 0, 0},
				{27, eCheatsCategory_Skating, "\"ID_CHEAT_ONYOUROWN\"", 0, "\"ID_CHEAT_ONYOUROWN_DESC\"", 0, 0},
				{28, eCheatsCategory_Skating, "\"ID_CHEAT_RAWSLIDE\"", 0, "\"ID_CHEAT_RAWSLIDE_DESC\"", 0, 0},
				{29, eCheatsCategory_Camera, "\"ID_CHEAT_CAMERA1\"", 0, "\"ID_CHEAT_CAMERA1_DESC\"", 0, 0},
				{30, eCheatsCategory_Camera, "\"ID_CHEAT_CAMERA2\"", 0, "\"ID_CHEAT_CAMERA2_DESC\"", 0, 0},
				{31, eCheatsCategory_Camera, "\"ID_CHEAT_CAMERA3\"", 0, "\"ID_CHEAT_CAMERA3_DESC\"", 0, 0},
				{32, eCheatsCategory_Camera, "\"ID_CHEAT_CAMERA4\"", 0, "\"ID_CHEAT_CAMERA4_DESC\"", 0, 0},
				{33, eCheatsCategory_Camera, "\"ID_CHEAT_CAMERA5\"", 0, "\"ID_CHEAT_CAMERA5_DESC\"", 0, 0},
				{34, eCheatsCategory_Character, "\"ID_CHEAT_INVISIBLEBOARD\"", 0, "\"ID_CHEAT_INVISIBLEBOARD_DESC\"", 0, 0},
				{35, eCheatsCategory_Character, "\"ID_CHEAT_BLUEBOXMAN\"", 0, "\"ID_CHEAT_BLUEBOXMAN_DESC\"", 0, 0},
				{36, eCheatsCategory_Character, "\"ID_CHEAT_BIGHEADMODE\"", 0, "\"ID_CHEAT_BIGHEADMODE_DESC\"", 0, 0},
				{37, eCheatsCategory_Character, "\"ID_CHEAT_SPECIALCHARACTER1\"", 0, "\"ID_CHEAT_SPECIALCHARACTER1_DESC\"", 0, 0},
				{38, eCheatsCategory_Character, "\"ID_CHEAT_SPECIALCHARACTER2\"", 0, "\"ID_CHEAT_SPECIALCHARACTER2_DESC\"", 0, 0},
				{39, eCheatsCategory_Character, "\"ID_CHEAT_SPECIALCHARACTER3\"", 0, "\"ID_CHEAT_SPECIALCHARACTER3_DESC\"", 0, 0},
				{40, eCheatsCategory_Audio, "\"ID_CHEAT_SCREAMINGRAILS\"", 0, "\"ID_CHEAT_SCREAMINGRAILS_DESC\"", 0, 0},
				{41, eCheatsCategory_Audio, "\"ID_CHEAT_CLOWNED\"", 0, "\"ID_CHEAT_CLOWNED_DESC\"", 0, 0},
				{42, eCheatsCategory_GamePlay, "\"ID_CHEAT_FREESKATESCORING\"", 0, "\"ID_CHEAT_FREESKATESCORING_DESC\"", 0, 0},
				{43, eCheatsCategory_GamePlay, "\"ID_CHEAT_NOHUD\"", 0, "\"ID_CHEAT_NOHUD_DESC\"", 0, 0}
			};

		public:
			
			CheatsBackEndCore(unsigned int moduleID)
				: Sk8::BE::IBackEndModule(unsigned int moduleID) {}

			void DeactivateCheat(CheatsBackEnd::eCheatItem item) {
				if (!mCheatInfo) {
					xcore::FailAssert("mCheatInfo", "Sk8\\BEcore\\becore_cheats.h", 84);
					DebugBreak();
				}
				if (item >= mNumCheats) {
					xcore::FailAssert("item < mNumCheats", "Sk8\\BEcore\\becore_cheats.h", 88);
					DebugBreak();
				}
				mCheatInfo[item].mActivated = 0;
			}

			tCheatInfo* GetCheat(CheatsBackEnd::eCheatItem item) {
				if (!mCheatInfo) {
					xcore::FailAssert("mCheatInfo", "Sk8\\BEcore\\becore_cheats.h", 96);
					DebugBreak();
				}
				if (item >= mNumCheats) {
					xcore::FailAssert("item < mNumCheats", "Sk8\\BEcore\\becore_cheats.h", 100);
					DebugBreak();
				}
				return (tCheatInfo*)mCheatInfo[item];
			}

			bool IsCheatActivated(CheatsBackEnd::eCheatItem item) {
				if (!mCheatInfo) {
					xcore::FailAssert("mCheatInfo", "Sk8\\BEcore\\becore_cheats.h", 108);
					DebugBreak();
				}
				if (item >= mNumCheats) {
					xcore::FailAssert("item < mNumCheats", "Sk8\\BEcore\\becore_cheats.h", 112);
					DebugBreak();
				}
				return mCheatInfo[item].mActivated;
			}

		};

		class CheatsBackEnd : public CheatsBackEndCore {
		public:
			void Init() {
				mNumCheats = 44;
				mCheatInfo = (tCheatInfo*)StaticCheatInfoTable;
			}

			enum eCheatItem {
				eCheatItem_ProSkater01,
				eCheatItem_ProSkater02,
				eCheatItem_ProSkater03,
				eCheatItem_ProSkater04,
				eCheatItem_ProSkater05,
				eCheatItem_ProSkater06,
				eCheatItem_ProSkater07,
				eCheatItem_ProSkater08,
				eCheatItem_ProSkater09,
				eCheatItem_ProSkater10,
				eCheatItem_ProSkater11,
				eCheatItem_ProSkater12,
				eCheatItem_ProSkater13,
				eCheatItem_ProSkater14,
				eCheatItem_ProSkater15,
				eCheatItem_ProSkater16,
				eCheatItem_ProSkater17,
				eCheatItem_ProSkater18,
				eCheatItem_ProSkater19,
				eCheatItem_World_BackPainPandemic,
				eCheatItem_World_RoadRage,
				eCheatItem_World_PlanetOfSkaters,
				eCheatItem_World_Mental,
				eCheatItem_Skating_SlowMotion,
				eCheatItem_Skating_Celebration,
				eCheatItem_Skating_WipeOutButton,
				eCheatItem_Skating_FloatingFreezeFrame,
				eCheatItem_Skating_OnYourOwn,
				eCheatItem_Skating_RawSlide,
				eCheatItem_Skating_Camera1,
				eCheatItem_Skating_Camera2,
				eCheatItem_Skating_Camera3,
				eCheatItem_Skating_Camera4,
				eCheatItem_Skating_Camera5,
				eCheatItem_Skating_InvisibleBoard,
				eCheatItem_Skating_BlueBoxMan,
				eCheatItem_Skating_BigHeadMode,
				eCheatItem_Skating_SpecialCharacter1,
				eCheatItem_Skating_SpecialCharacter2,
				eCheatItem_Skating_SpecialCharacter3,
				eCheatItem_Skating_ScreamingRails,
				eCheatItem_Skating_Clowned,
				eCheatItem_Skating_FreeSkateScoring,
				eCheatItem_Skating_NoHUD,
				eCheatItem_Total
			};

		};

	}
}