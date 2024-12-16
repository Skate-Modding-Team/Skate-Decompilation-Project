#include "versiondata.h"
#include "pegasus.h"

namespace pegasus
{
//an object specifying what version of pegasus was used for assets
struct tVersionData
{
    enum Version
    {
        VERSION=22,
        REVISION=0
    };

    unsigned int m_uiVersion;
    unsigned int m_uiRevision;

    //yes this is how it is in the skate 1 executable.
    //They manually set the version and revision when adding to an arena.
    //Typical EA moment
    tVersionData()
    {
        m_uiVersion = 0;
        m_uiRevision = 0;
    }

    void Release()
    {
        m_uiVersion = 0;
        m_uiRevision = 0;
    }

    static rw::ResourceDescriptor GetResourceDescriptor()
    {
        return rw::ResourceDescriptor(16, 16);
    }
    
    static tVersionData* Initialize(const rw::Resource& resource)
    {
        tVersionData *versiondata = (tVersionData *)(resource.GetMemoryResource());
        if ( !versiondata )
            return nullptr;
        versiondata->m_uiVersion = 0;
        versiondata->m_uiRevision = 0;
        return versiondata;
    }

    static RwObjectType GetRwType()
    {
        return RWOBJECTTYPE_VERSIONDATA;
    }

    static unsigned int GetAlignment(unsigned int numValues)
    {
        return 16;
    }
    
    static unsigned int GetSize(unsigned int noneed)
    {
        return 8;
    }

    static rw::core::arena::SizeAndAlignment* Unfix(void *ptr, rw::core::arena::SizeAndAlignment *offset)
    {
        return offset;
    }

    static void Refix(void *ptr, void *offset, rw::core::arena::ArenaIterator *iterator)
    {
        Fixup(ptr, iterator);
    }

    static bool Fixup(void *ptr, rw::core::arena::ArenaIterator *iterator)
    {
        rwASSERT(iterator->GetArena());
        //fixup code if applicable
        rwASSERT(iterator->GetArena());
        return true;
    }

    static void RegisterArenaReadCallbacks()
    {
        rw::core::arena::ArenaTypeReg *typeReg =
            rw::core::arena::ArenaTypeRegGetType(GetRwType());
        typeReg->destructCB = 0;
        typeReg->fixupCB = Fixup;
    }

    static void RegisterArenaWriteCallbacks()
    {
        rw::core::arena::ArenaTypeReg *typeReg =
            rw::core::arena::ArenaTypeRegGetType(GetRwType());
        typeReg->unfixCB = Unfix;
        typeReg->refixCB = Refix;
    }

    static void AddToArena(rw::core::arena::Arena *pArena)
    {
        rw::Resource* resource = 
            rw::ResourceAllocatorRegistry::GetDefaultAllocator()->Allocate(GetResourceDescriptor());
        tVersionData* version = 
            (tVersionData *)pArena->IdToObject(
                pArena->AddObject(resource, GetRwType(), GetResourceDescriptor()));
        version->m_uiVersion = VERSION;
        version->m_uiRevision = REVISION;
    }

    static tVersionData* GetFromArena(rw::core::arena::Arena *pArena)
    {
        for (unsigned int objectID = 0; objectID < pArena->GetNumExportedObjects(); objectID++)
        {
            rw::core::arena::ArenaExportedObject object;
            pArena->GetExportedObjectByIndex(objectID, object);
            if (objectID.typeId == GetRwType())
            {
                return static_cast<tVersionData *>object.ptr;
            }
        }
        return nullptr;
    }

    static bool CheckArenaVersion(rw::core::arena::Arena *pArena)
    {
        tVersionData* version = GetFromArena(pArena);
        return (!version || version->m_uiVersion == VERSION);
    }

};
}