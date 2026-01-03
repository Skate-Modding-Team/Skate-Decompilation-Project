
namespace rw {
namespace core {
namespace arena {

#define RW_BASERESOURCE_INDEXSTART RW_CORE_BASERESOURCE_START - 0x00000001
#define RW_BASERESOURCE_NUMINDICES RW_CORE_BASERESOURCE_RESERVEDTO - RW_CORE_BASERESOURCE_START

unsigned int TypeIdToBaseResourceIndex(unsigned int typeId) {
    if (typeId - RW_CORE_BASERESOURCE_START <= RW_BASERESOURCE_NUMINDICES) {
        return typeId - RW_BASERESOURCE_INDEXSTART;
    }
    else {
        return BASERESOURCE_MAINMEMORY;
    }
}

template <Adder ArenaAdder>
void AddResourceToArena(const class Resource & resource, const class ResourceDescriptor & descriptor, unsigned int mainTypeId, class ArenaAdder & adder) {
    void* baseResource;

    for (unsigned int i = 1; i < BASERESOURCE_NUMBEROFBASERESOURCETYPES; i++) {
        baseResource = resource.GetBaseResource(i);
        if (baseResource) {
            BaseResourceDescriptor baseResourceDescriptor = descriptor.GetBaseResourceDescriptor(i);
            unsigned int baseResourceTypeId = BaseResourceIndexToTypeId(i);
            adder.Add(baseResource, baseResourceDescriptor, baseResourceTypeId);
        }
    }

    baseResource = resource.GetMemoryResource();
    adder.Add(baseResource, descriptor.begin(), mainTypeId);
}

unsigned int BaseResourceIndexToTypeId(unsigned int typeIndex) {
    if (typeIndex) {
        typeIndex += RW_BASERESOURCE_INDEXSTART;
    }
    return typeIndex;
}

RwBool IsTypeIdOfMemoryResource(unsigned int typeId) {
    return typeId - RW_CORE_BASERESOURCE_START > RW_BASERESOURCE_NUMINDICES;
}

} //namespace arena
} //namespace core
} //namespace rw