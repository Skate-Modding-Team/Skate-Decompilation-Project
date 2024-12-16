#include "pegasus.h"

namespace pegasus
{

void RegisterArenaTypes()
{
    tRMeshData::RegisterArenaReadCallbacks();
    tRMeshData::RegisterArenaWriteCallbacks();
    tRModelData::RegisterArenaReadCallbacks();
    tRModelData::RegisterArenaWriteCallbacks();
    tSimpleTriMeshData::RegisterArenaReadCallbacks();
    tSimpleTriMeshData::RegisterArenaWriteCallbacks();
    tSplineData::RegisterArenaReadCallbacks();
    tSplineData::RegisterArenaWriteCallbacks();
    tRMaterialData::RegisterArenaReadCallbacks();
    tRMaterialData::RegisterArenaWriteCallbacks();
    tCMaterialData::RegisterArenaReadCallbacks();
    tCMaterialData::RegisterArenaWriteCallbacks();
    tCModelData::RegisterArenaReadCallbacks();
    tCModelData::RegisterArenaWriteCallbacks();
    tRollerDescData::RegisterArenaReadCallbacks();
    tRollerDescData::RegisterArenaWriteCallbacks();
    tInstanceData::RegisterArenaReadCallbacks();
    tInstanceData::RegisterArenaWriteCallbacks();
    tTriggerInstanceData::RegisterArenaReadCallbacks();
    tTriggerInstanceData::RegisterArenaWriteCallbacks();
    tVersionData::RegisterArenaReadCallbacks();
    tVersionData::RegisterArenaWriteCallbacks();
    tCollisionBezierData::RegisterArenaReadCallbacks();
    tCollisionBezierData::RegisterArenaWriteCallbacks();
    tLocationDescData::RegisterArenaReadCallbacks();
    tLocationDescData::RegisterArenaWriteCallbacks();
    tRBlendShapeData::RegisterArenaReadCallbacks();
    tRBlendShapeData::RegisterArenaWriteCallbacks();
    EA::ArenaDictionary::RegisterArenaReadCallbacks();
    EA::ArenaDictionary::RegisterArenaWriteCallbacks();
    tTableOfContents::RegisterArenaReadCallbacks();
    tTableOfContents::RegisterArenaWriteCallbacks();
    tWorldPainterLayerData::RegisterArenaReadCallbacks();
    tWorldPainterLayerData::RegisterArenaWriteCallbacks();
    tWorldPainterQuadTreeData::RegisterArenaReadCallbacks();
    tWorldPainterQuadTreeData::RegisterArenaWriteCallbacks();
    tWorldPainterDictionaryData::RegisterArenaReadCallbacks();
    tWorldPainterDictionaryData::RegisterArenaWriteCallbacks();
    tNavMeshData::RegisterArenaReadCallbacks();
    tNavMeshData::RegisterArenaWriteCallbacks();
    tRAINData::RegisterArenaReadCallbacks();
    tRAINData::RegisterArenaWriteCallbacks();
    tAIPathData::RegisterArenaReadCallbacks();
    tAIPathData::RegisterArenaWriteCallbacks();
    tLionData::RegisterArenaReadCallbacks();
    tLionData::RegisterArenaWriteCallbacks();
    tStatsData::RegisterArenaReadCallbacks();
    tStatsData::RegisterArenaWriteCallbacks();
    tMassiveData::RegisterArenaReadCallbacks();
    tMassiveData::RegisterArenaWriteCallbacks();
    tDepthMapCPUData::RegisterArenaReadCallbacks();
    tDepthMapCPUData::RegisterArenaWriteCallbacks();
    tWayPointData::RegisterArenaReadCallbacks();
    tWayPointData::RegisterArenaWriteCallbacks();
}

const char* TypeToString(const RwObjectType iType)
{
    int index = 0;
    for (RwObjectType i = TypeToStringTable[0].m_iType; i != -1; i = TypeToStringTable[index].m_iType)
    {
        if ( i == iType )
        {
            break;
        }
        index++;
    }
    return TypeToStringTable[index].m_pszString;
}

template <typename T>
void Offset2Addr(void* pBase, T*& pAddr)
{
    rwASSERT(pAddr);
    pAddr = pBase + pAddr;
}

}