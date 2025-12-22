//TODO: Figure out what includes are required from rw/core

#include <rw/core/base/ostypes.h>

namespace rw
{
namespace core
{
namespace atom
{
class UnfixRefixAtoms;
class FixupAtoms;
} //atom
} //core
} //rw

namespace rw
{
namespace core
{
namespace arena
{

const size_t rwDEFAULT_ARENAID_MAP_SIZE = 1024;

class ArenaIterator;
struct ArenaDictEntry;
class ArenaSection;
typedef ArenaSection* ArenaSectionPtr; typedef const ArenaSection* ArenaSectionConstPtr;
class ArenaSectionManifest;
class ArenaSectionTypes;
class ArenaSectionExternalArenas;
class ArenaSectionSubreferences;
struct ArenaSectionSubreferencesRecord;
struct SizeAndAlignment;

class Arena;
class ArenaTypeReg;
class RefixContextImpl;
class ArenaGroup;

inline ArenaGroup& GetGlobalArenaGroup();

typedef ArenaTypeReg* ArenaTypeRegPtr; typedef const ArenaTypeReg* ArenaTypeRegConstPtr;

class UnfixContextImpl
{
public:
    UnfixContextImpl(Arena& arena,
        ArenaSectionManifest& sections,
        rw::core::atom::DynamicAtomTable&,
        rw::core::atom::UnfixRefixAtoms*);

    void Serialize(const void*& object);

    void Serialize(ArenaDictEntry& dictEnt);

    void AddOffset(rw::HostPtr offset);

    uint32_t ObjectTypeIdToIndex(uint32_t id) const;

    RwBool ConvertExistingObjectToId(void** object);

    rw::core::atom::AtomID UnfixAtom(rw::core::atom::AtomID);

protected:
    RefixContextImpl& RefixContext();

public:
    Arena* m_arena;
    ArenaSectionTypes* m_types;
    ArenaSectionExternalArenas* m_externalArenas;
    ArenaSectionSubreferences* m_subrefs;
    rw::core::atom::DynamicAtomTable* m_unfixAtomTable;
    rw::core::atom::UnfixRefixAtoms* m_unfixAtomCallback;
    void* m_baseObjectPtr;
    class ArenaIterator* iterator;

private:
    ArenaSectionTypes& Types() const;

    ArenaSectionExternalArenas& ExternalArenas() const;

    void UpdateArenaSubreferencesLinks();

    uint32_t AddSubref(const void* obj, uint32_t objectId, uint32_t subObjectOffset);

    RwBool FindBaseObject(Arena& arena, const void* obj, uint32_t& objectIndex);

    RwBool FindExistingSubObject(const void* obj, uint32_t& objectIndex);

    RwBool FindNewSubObject(Arena& arena, const void* obj, uint32_t& objectIndex, uint32_t& set);

    ArenaSectionSubreferences& Subrefs() const;
};

typedef struct SizeAndAlignment : public UnfixContextImpl
{
    SizeAndAlignment(Arena& arena,
        ArenaSectionManifest& sections,
        rw::core::atom::DynamicAtomTable& atoms,
        rw::core::atom::UnfixRefixAtoms* unfixRefixAtoms)
        : UnfixContextImpl(arena, sections, atoms, unfixRefixAtoms)
    {
        rwFUNCTION();
        rwRETURNVOID();
    }

    void* base;
    uint32_t size;
    uint32_t extraSize;
    uint32_t alignment;
} SizeAndAlignment;


typedef RwBool(*RwWriteCB)(void* ptr, uint32_t size, uint32_t prePad);

typedef RwBool(*RwWriteCBWithData)(void* ptr, uint32_t size, uint32_t prePad, void* data);

struct ArenaDictEntry
{
    void* ptr;
    void* reloc;
    uint32_t size;
    uint32_t align;
    uint32_t typeIndex;
    uint32_t typeId;

    MemoryResourceDescriptor GetDescriptor() const
    {
        rwFUNCTION();
        rwRETURN(MemoryResourceDescriptor(size, align));
    }
};
typedef ArenaDictEntry* ArenaDictEntryPtr; typedef const ArenaDictEntry* ArenaDictEntryConstPtr;


typedef struct ArenaSectionSubreferencesRecord
{
    uint32_t objectId;
    uint32_t offset;
} ArenaSectionSubreferencesRecord;

struct ArenaExportedObject
{
    ArenaExportedObject()
        : typeId(0), ptr(0), resource(), resourceDescriptor()
    {
        rwFUNCTION();
        rwRETURNVOID();
    }

    ArenaExportedObject(uint32_t typeId_, void* ptr_, const Resource& resource_,
        const ResourceDescriptor& resourceDescriptor_)
        : typeId(typeId_), ptr(ptr_), resource(resource_), resourceDescriptor(resourceDescriptor_)
    {
        rwFUNCTION();
        rwRETURNVOID();
    }

    uint32_t typeId;
    void* ptr;
    Resource resource;
    ResourceDescriptor resourceDescriptor;
};

struct ArenaFileHeaderMagicNumber
{
    uint8_t prefix[4];
    uint8_t body[4];
    uint8_t suffix[4];
};

struct ArenaFileHeader
{
    ArenaFileHeaderMagicNumber magicNumber;
    uint8_t isBigEndian;
    uint8_t pointerSizeInBits;
    uint8_t pointerAlignment;
    uint8_t unused;
    uint8_t majorVersion[4];
    uint8_t minorVersion[4];
    uint32_t buildNo;

    bool IsValid() const;
};

class Arena
{
public:
    ArenaFileHeader fileHeader;
    uint32_t id;
    uint32_t numEntries;
    uint32_t numUsed;
    uint32_t alignment;
    uint32_t virt;
    ArenaDictEntry* dictStart;
    ArenaSectionManifest* sections;
    void* base;

    typedef ArenaIterator FixupContext;
    typedef SizeAndAlignment UnfixContext;
    typedef ArenaIterator RefixContext;

private:
    UnfixContext* m_unfixContext;
    ArenaIterator* m_fixContext;
    ResourceDescriptor m_resourceDescriptor;
    ResourceDescriptor m_resourcesUsed;
    TargetResource m_resource;
    ArenaGroup* m_arenaGroup;

public:

    static ResourceDescriptor GetResourceDescriptor(uint32_t dictSize, RwBool virt_,
            uint32_t, ArenaSection* sections_,
            const ResourceDescriptor& bodyDescriptor =
            rw::ResourceDescriptor(0, 4),
            const ArenaGroup& arenaGroup = GetGlobalArenaGroup());

    static ResourceDescriptor GetResourceDescriptor(uint32_t dictSize, RwBool virt, uint32_t poolSize, uint32_t arenaId,
            ArenaSection* sections,
            const ArenaGroup& arenaGroup = GetGlobalArenaGroup());

    static Arena* Initialize(const Resource& resource, uint32_t dictSize, RwBool virt, uint32_t arenaId,
            ArenaSection* sections,
            const rw::ResourceDescriptor& bodyDescriptor = rw::ResourceDescriptor(0, 4),
            const ArenaGroup& arenaGroup = GetGlobalArenaGroup());

    static Arena* Initialize(const Resource& resource, uint32_t dictSize, RwBool virt, uint32_t poolSize, uint32_t arenaId,
            ArenaSection* sections,
            const ArenaGroup& arenaGroup = GetGlobalArenaGroup());


    static uint32_t GetAlignment(uint32_t dictSize, RwBool virt, uint32_t poolSize, uint32_t arenaId, ArenaSection* sections);

    static uint32_t GetSize(uint32_t dictSize, RwBool virt, uint32_t poolSize, uint32_t arenaId, ArenaSection* sections);

    static Arena* InitializeFromMemoryDump(
            const Resource& resource,
            rw::core::atom::FixupAtoms* fixupAtomsCallback = 0,
            ArenaGroup& arenaGroup = GetGlobalArenaGroup());

    static Arena* InitializeFromMemoryDump(
            Arena* arena,
            rw::core::atom::FixupAtoms* fixupAtomsCallback = 0,
            ArenaGroup& arenaGroup = GetGlobalArenaGroup());

    void Release();

    const ResourceDescriptor& GetResourceDescriptor() const
    {
        rwFUNCTION();
        rwRETURN(m_resourceDescriptor);
    }

    ResourceDescriptor& GetResourceDescriptor()
    {
        rwFUNCTION();
        rwRETURN(m_resourceDescriptor);
    }

    Resource GetResource() const
    {
        rwFUNCTION();
        rwRETURN(m_resource.ToResource());
    }

    uint32_t AddObject(const rw::Resource& resource, uint32_t typeId, const rw::ResourceDescriptor& resourceDescriptor);

    Resource Allocate(const rw::ResourceDescriptor& resourceDescriptor);

    uint32_t ObjectToId(const void* obj);

    const void* IdToObject(uint32_t id) const;

    void* IdToObject(uint32_t id);

    template <typename T>
    inline void ReplaceIdWithObject(T*& ptr)
    {
        rwFUNCTION();
        ptr = reinterpret_cast<T*>(IdToObject(static_cast<uint32_t>(RwPtrToOffset(ptr))));
        rwRETURNVOID();
    }

    template <typename T>
    inline void ReplaceObjectWithId(T*& ptr)
    {
        rwFUNCTION();
        ptr = RwPtrFromOffset<T>(ObjectToId(RwPtrToHostPtr(ptr)));
        rwRETURNVOID();
    }

    RwBool ConvertExistingObjectToId(void** object);

    RwBool UnfixStart(ArenaIterator* iterator, void* base);

    static RwBool UnfixNext(ArenaIterator* iterator);

    static RwBool RefixStart(ArenaIterator* iterator, RwWriteCB writeCB);

    static RwBool RefixStart(ArenaIterator* iterator, RwWriteCBWithData writeCBWithData, void* data);

    static RwBool RefixNext(ArenaIterator* iterator);

    static RwBool FixupStart(Arena* arena, ArenaIterator* iterator, const Resource& resource, RwBool* isFixupOk);

    static RwBool FixupStart(Arena* arena, ArenaIterator* iterator, RwBool* isFixupOk);

    static RwBool FixupNext(ArenaIterator* iterator);

    static void DestructStart(Arena* arena, ArenaIterator* iterator);

    static RwBool DestructNext(ArenaIterator* iterator);

    uint32_t GetId() const
    {
        rwFUNCTION();
        rwRETURN(id);
    }

    uint32_t GetNumExportedObjects() const;

    RwBool GetExportedObjectByIndex(uint32_t objectIndex, ArenaExportedObject* retVal);

    void SetArenaGroup(ArenaGroup* arenaGroup)
    {
        rwFUNCTION();
        m_arenaGroup = arenaGroup;
        rwRETURNVOID();
    }

    ArenaGroup* GetArenaGroup()
    {
        rwFUNCTION();
        rwRETURN(m_arenaGroup);
    }

private:

    static void WriteDictionary(Arena&, ArenaIterator*);

    static RwBool RefixStart(ArenaIterator* iterator);
};
typedef Arena* ArenaPtr; typedef const Arena* ArenaConstPtr;


typedef Arena::UnfixContext* (*RwUnfixCB)(void* obj, Arena::UnfixContext* context);
typedef void (*RwRefixCB)(void* obj, void* offset, Arena::RefixContext* context);
typedef RwBool(*RwFixupCB)(void* obj, Arena::FixupContext* context);
typedef void (*RwDestructCB)(void* obj);

class FixupContextImpl
{
public:
    FixupContextImpl();

    void Serialize(ArenaDictEntry& entry);

    rw::core::atom::AtomID FixupAtom(rw::core::atom::AtomID) const;

    void SetArenaLocalAtomTable(const rw::core::atom::StaticAtomTable& table)
    {
        rwFUNCTION();
        m_fixupAtomTable = &table;
        rwRETURNVOID();
    }

    void SetFixupCallback(rw::core::atom::FixupAtoms* fixupCallback)
    {
        rwFUNCTION();
        fixupAtomCallback = fixupCallback;
        rwRETURNVOID();
    }

protected:
    RwBool* m_isFixupOk;
    const rw::core::atom::StaticAtomTable* m_fixupAtomTable;
    rw::core::atom::FixupAtoms* fixupAtomCallback;

private:
    ArenaSectionTypes& Types();
    ArenaIterator& Iterator();
};

class RefixContextImpl
{
public:
    RefixContextImpl();

    ~RefixContextImpl();

    void AllocateTemporaryRefixStorage(const ResourceDescriptor& requirements);
    void SetTemporaryRefixStorageAllocator(IResourceAllocator* allocator);
    Resource GetTemporaryRefixStorage() const;
    ResourceDescriptor GetTemporaryRefixStorageUsage() const;

    rw::core::atom::AtomID RefixAtom(rw::core::atom::AtomID) const;

    void Serialize(ArenaDictEntry& entry);

    void SetRefixAtomTable(const rw::core::atom::DynamicAtomTable* atoms)
    {
        m_refixAtomTable = atoms;
    }

    ResourceDescriptor m_alignmentRequirements;

protected:
    RwWriteCB m_writeCB;
    RwWriteCBWithData m_writeCBWithData;
    void* m_writeCBData;
    IResourceAllocator* m_refixStorageAllocator;
    Resource m_refixStorage;
    ResourceDescriptor m_refixStorageUsage;
    const rw::core::atom::DynamicAtomTable* m_refixAtomTable;
    rw::core::atom::UnfixRefixAtoms* m_refixAtomCallback;
    void* m_baseObjectPtr;

    void SetWriteCB(RwWriteCB& writeCB)
    {
        rwFUNCTION();
        m_writeCB = writeCB;
        m_writeCBWithData = 0;
        m_writeCBData = 0;
        rwRETURNVOID();
    }

    void SetWriteCB(RwWriteCBWithData& writeCB, void* data)
    {
        rwFUNCTION();
        m_writeCB = 0;
        m_writeCBWithData = writeCB;
        m_writeCBData = data;
        rwRETURNVOID();
    }

    RwBool CallWriteCB(void* ptr, uint32_t size, uint32_t prePad) const
    {
        rwFUNCTION();
        if (m_writeCB)
        {
            rwRETURN((m_writeCB)(ptr, size, prePad));
        }
        rwRETURN((m_writeCBWithData)(ptr, size, prePad, m_writeCBData));
    }

private:
    ArenaSectionTypes& Types();

    ArenaIterator& Iterator();
};

class DynamicArenaSubreferencesData
{
public:
    DynamicArenaSubreferencesData(IResourceAllocator& allocator);
    ~DynamicArenaSubreferencesData();

    void Clear();

    ArenaSectionSubreferencesRecord* GetRecords();
    ArenaDictEntry* GetDict();

    uint32_t Size();

    uint32_t AddNewSubreference();

private:
    DynamicArenaSubreferencesData(const DynamicArenaSubreferencesData& other);
    DynamicArenaSubreferencesData& operator=(const DynamicArenaSubreferencesData& other);

    SimpleVector<ArenaSectionSubreferencesRecord> m_records;
    SimpleVector<ArenaDictEntry> m_dict;
};

class ArenaIterator : public FixupContextImpl, public RefixContextImpl
{
public:
    ArenaIterator();
    ~ArenaIterator();

    void AddOffset(rw::HostPtr addVal)
    {
        rwFUNCTION();
        offset = MemAddOffset(offset, addVal);
        MemoryResourceDescriptor& descriptor = m_resourceDescriptor.GetMemoryResourceDescriptor();
        descriptor += MemoryResourceDescriptor(addVal, 1);
        rwRETURNVOID();
    }

    void Align(uint32_t alignTo)
    {
        rwFUNCTION();
        offset = MemAlign(offset, alignTo);
        MemoryResourceDescriptor& descriptor = m_resourceDescriptor.GetMemoryResourceDescriptor();
        descriptor.Align(MemoryResourceDescriptor(0, alignTo));
        rwRETURNVOID();
    }

    ResourceDescriptor& GetResourceDescriptor()
    {
        rwFUNCTION();
        rwRETURN(m_resourceDescriptor);
    }

    RwBool WriteCallback(void* ptr, uint32_t size, uint32_t prePad) const
    {
        rwFUNCTION();
        rwRETURN(CallWriteCB(ptr, size, prePad));
    }

    Arena* GetArena(void) const
    {
        rwFUNCTION();
        rwRETURN(m_arena);
    }

    void SetUnfixRefixAtomIDCallback(rw::core::atom::UnfixRefixAtoms* callback)
    {
        rwFUNCTION();
        m_unfixRefixAtoms = callback;
        m_refixAtomCallback = callback;
        rwRETURN();
    }

    void Serialize(const void*& object) const;

    void SetTemporaryStorageAllocator(IResourceAllocator* allocator);
    IResourceAllocator& GetTemporaryStorageAllocator();

    void UpdateSubreferencesData();

    uint32_t AddNewSubreference();

    ArenaSectionSubreferences& Subrefs() const;

    ArenaSectionExternalArenas& ExternalArenas() const;

    friend class Arena;
    friend class RefixContextImpl;
    friend class FixupContextImpl;

    Arena* m_arena;
    void* offset;

private:
    UnfixContextImpl& UnfixContext();

    RefixContextImpl& RefixContext();

    FixupContextImpl& FixupContext();

    void* m_origOffset;
    void* m_dictStart;
    uint32_t m_align;
    uint32_t m_dictEntry;

    bool m_arenaLocalAtomTableAdded;

    rw::core::atom::DynamicAtomTable m_unfixRefixAtomTable;

    rw::core::atom::UnfixRefixAtoms* m_unfixRefixAtoms;

    ResourceDescriptor m_resourceDescriptor;

    IResourceAllocator* m_temporaryStorageAllocator;

    DynamicArenaSubreferencesData m_subreferencesData;
    Resource m_subreferencesResource;

    ArenaIterator(const ArenaIterator&);
    ArenaIterator& operator=(const ArenaIterator&);
};

class ArenaIdMapHashTraits
{
public:
    typedef uint32_t KeyType;
    typedef Arena* DatumType;
    typedef SeparateKeyAndDatumContained<uint32_t, Arena*> Contained;

    static const KeyType BadKey()
    {
        rwFUNCTION();
        rwRETURN((0xffffffffu));
    }

    static const Contained DefaultContained()
    {
        rwFUNCTION();
        rwRETURN(Contained(BadKey(), 0));
    }

    static const KeyType& GetKey(const Contained& obj)
    {
        rwFUNCTION();
        rwRETURN(obj.GetKey());
    }

    static DatumType& GetData(Contained& obj)
    {
        rwFUNCTION();
        rwRETURN(obj.GetData());
    }

    static const DatumType& GetData(const Contained& obj)
    {
        rwFUNCTION();
        rwRETURN(obj.GetData());
    }

    static size_t Hash(size_t hashSize, const KeyType& key)
    {
        rwFUNCTION();
        rwRETURN(RwHash32UInt32(key, rw::RWHASH32_INIT) % hashSize);
    }

    static bool EqualTo(const KeyType& lhs, const KeyType& rhs)
    {
        rwFUNCTION();
        rwRETURN(lhs == rhs);
    }

    static size_t GetAlign()
    {
        rwFUNCTION();
        rwRETURN(sizeof(Contained));
    }
};

typedef HashContainer<PreallocatedBufferPolicy<ArenaIdMapHashTraits>, ArenaIdMapHashTraits> ArenaIdMap;

class ArenaManagerData;

class ArenaManager
{
public:
    ArenaManager()
    {
        rwFUNCTION();
        rwRETURNVOID();
    }

    virtual ~ArenaManager()
    {
        rwFUNCTION();
        rwRETURNVOID();
    }

    virtual ArenaManagerData& Data() const;

    virtual ArenaManagerData*& SharedData() const;
};

extern ArenaIdMap* GetDefaultArenaMap();

extern void rwArenaOpen(void* buf, uint32_t bufSize, ArenaIdMap* arenaIdMap = GetDefaultArenaMap());

extern void rwArenaClose(void);

extern Arena* ArenaFind(uint32_t id);

extern void ArenaSystemAddArena(Arena* arena);

extern void ArenaSystemRemoveArena(Arena* arena);

class ArenaGroup
{
public:
    ArenaGroup()
        : m_ArenaIdMap(0)
    {
    }

    explicit ArenaGroup(ArenaIdMap* arenaIdMap);

    ~ArenaGroup();

    Arena* FindArena(uint32_t id) const;

    void AddArena(Arena* arena);
    void RemoveArena(Arena* arena);

    void AddSharedArena(Arena* arena)
    {
        rwFUNCTION();
        DoAddArena(arena);
        rwRETURNVOID();
    }

    void RemoveSharedArena(Arena* arena)
    {
        rwFUNCTION();
        DoRemoveArena(arena);
        rwRETURNVOID();
    }

    ArenaIdMap*& GetArenaIdMap()
    {
        rwFUNCTION();
        rwRETURNVOID(m_ArenaIdMap);
    }

private:
    ArenaIdMap* m_ArenaIdMap;
    void DoAddArena(Arena* arena);
    void DoRemoveArena(Arena* arena);
};

class ArenaGroupHolder
{
public:
    explicit ArenaGroupHolder(size_t mapSize = rwDEFAULT_ARENAID_MAP_SIZE);
    ~ArenaGroupHolder();

    ArenaGroup& GetArenaGroup()
    {
        rwFUNCTION();
        rwRETURN(*m_arenaGroup);
    }

private:
    ArenaGroupHolder(ArenaGroupHolder&);
    ArenaGroupHolder& operator=(ArenaGroupHolder&);

    ArenaIdMap::Contained* m_buffer;
    ArenaGroup* m_arenaGroup;
};

} //arena
} //core
} //rw



namespace rw
{
namespace core
{
namespace arena
{

extern ArenaTypeReg* rw_FindTypeReg(uint32_t typeId);

extern uint32_t rw_GetArenaId(const Arena& arena);

extern Arena* rw_FindArena(uint32_t arenaId);

class rw_ArenaTypeRegistry;
struct rw_NullArenaHolderType;

class ArenaManagerData
{
public:
    ArenaManagerData()
        : m_typeRegistry(0),
        m_ArenaGroup(),
        m_NullArenaHolder(0)
    {
        rwFUNCTION();
        rwRETURNVOID();
    }

    ~ArenaManagerData()
    {
        rwFUNCTION();

        ArenaIdMap* arenaIdMap = GetArenaIdMap();
        if (arenaIdMap)
        {

            arenaIdMap->Clear();
        }
        rwRETURNVOID();
    }

    rw_ArenaTypeRegistry*& TypeRegistry()
    {
        rwFUNCTION();
        rwRETURN(m_typeRegistry);
    }

    ArenaGroup& GetArenaGroup()
    {
        rwFUNCTION();
        rwRETURN(m_ArenaGroup);
    }

    ArenaIdMap*& GetArenaIdMap()
    {
        rwFUNCTION();
        rwRETURN(m_ArenaGroup.GetArenaIdMap());
    }

    rw_NullArenaHolderType*& NullArenaHolder()
    {
        rwFUNCTION();
        rwRETURN(m_NullArenaHolder);
    }

private:
    rw_ArenaTypeRegistry* m_typeRegistry;
    ArenaGroup m_ArenaGroup;
    rw_NullArenaHolderType* m_NullArenaHolder;
};

inline ArenaGroup& GetGlobalArenaGroup()
{
    rwFUNCTION();
    rwRETURN(ArenaManager().Data().GetArenaGroup());
}

template <typename T>
RwBool IsSmallEnoughForuint32_t(const T& value)
{
    rwFUNCTION();
    rwRETURN((RwBool)((value & T(0xffffffff)) == value));
}


} //arena
} //core
} //rw