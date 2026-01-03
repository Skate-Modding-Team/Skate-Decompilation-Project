

namespace Sk8
{
namespace Physics
{

class GrindData
{
    class Implementation
    {
        class AssetRecord
        {

        };//AssetRecord

    };//Implementation

public:
    void Init();

    void ShutDown();

    void DebugRender();

    void AddSplineData(assman::cAssetID &assetID);

    void RemoveSplineData(assman::cAssetID &assetID);

    bool BoxTest(const rw::math::vpu::Vector3 &aabbCorner0, const rw::math::vpu::Vector3 &aabbCorner1, Sk8::Physics::GrindDataQueryResult &result_outArg);

    
};//GrindData

}//Physics
}//Sk8