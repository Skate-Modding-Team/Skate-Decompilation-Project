#include <rw/core/arena/arena.h>
#include <rw/core/targarena.h>
#include <rw/core/debug/debug.h>

//UnfixContextImpl methods

rw::core::arena::UnfixContextImpl::UnfixContextImpl(
    Arena& arena,
    ArenaSectionManifest& sections,
    rw::core::atom::DynamicAtomTable& atomTable,
    rw::core::atom::UnfixRefixAtoms* unfixRefixAtoms)
    : m_arena(&arena), m_unfixAtomTable(atomTable)
{
    m_unfixAtomCallback = unfixRefixAtoms ? unfixRefixAtoms : runtimeUnfixRefixToGlobalAtomTable;
}

//ArenaFileHeader methods

bool rw::core::arena::ArenaFileHeader::IsValid() const
{
    uint8_t* current = &this;
    uint8_t* target = &rw_ArenaFileHeader; 
    int difference = 0;
    while (current != &this->isBigEndian) //compare the magicNumber
    {
        difference = *current - *target;
        if (*current != *target) {
            break;
        }
        current++;
        target++;
    }
    //compare the remainder
    if (difference == 0 && 
        this->isBigEndian == rwARENA_ISBIGENDIAN && 
        this->pointerSizeInBits == rwARENA_POINTERSIZEINBITS &&
        this->pointerAlignmnet == rwARENA_POINTERALIGNMENT)
    {
        if (strncmp(reinterpret_cast<const char*>(&this->majorVersion), rwARENA_MAJORVERSION, rwARENA_MAGICFIELDSIZE) ||
            strncmp(reinterpret_cast<const char*>(&this->minorVersion), rwARENA_MINORVERSION, rwARENA_MAGICFIELDSIZE) <= 0)
        {
            return true;
        }
        else
        {
            rwMESSAGE("Arena version is not supported by this build.");
        }
    }
    else
    {
        rwMESSAGE("Arena target information does not match target build.");
    }
    return false;
}