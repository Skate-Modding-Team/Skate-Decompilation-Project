
namespace Sk8 {
	namespace Dmo {

		class SimManager : public Sk8::Dmo::Registration, public Sk8::Physics::IDynamicGrindSplineProvider {
		private:
			Sk8::Physics::World* mWorld;
			Sk8::INetworkGameCollisionQuery* mQuery;
			eastl::fixed_vector<Sk8::Dmo::Body*, 50, 0, eastl::allocator> mStaticSim;
			eastl::fixed_vector<Sk8::Dmo::Body*, 50, 0, eastl::allocator> mStaticViz;
			signed int mId;
			Sk8::Dmo::SpawnMode mMode;
			signed int mPlayerId;
		
		public:

			void SimManager(Sk8::Physics::World* world, Sk8::INetworkGameCollisionQuery* query) {

			}

			void Reset() {
				if (Sk8::BE::CommonBackEnd::sGhostSystemEnabled) {
					SpawnStatic();
				}
				else if (mMode) {
					UnspawnAll();
				}
			}

		};
	}
}