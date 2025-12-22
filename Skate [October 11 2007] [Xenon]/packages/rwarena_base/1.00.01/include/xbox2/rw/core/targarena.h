#pragma once
#include <rw/core/base/targtype.h>
#include <rw/core/arena/arena.h>

#define rwARENA_MAGIC {0x89, 'R', 'W', '4'}
#define rwARENA_MAGICSUFFIX {0xD, 0xA, 0x1A, 0xA}

#define rwARENA_ISBIGENDIAN (rwTARGET_ENDIAN == rwBIENDIAN)
#define rwARENA_POINTERSIZEINBITS rwTARGET_POINTERSIZE * 8
#define rwARENA_POINTERALIGNMENT rwTARGET_POINTERALIGNMENT

//versioning inherited from the rw4 platform sdk which had a final version of 4.5.5.4
#define rwARENA_MAJORVERSION "454"
#define rwARENA_MINORVERSION "000"
#define rwARENA_BUILDNUMBER 0

//xbox 2 definitions
#define rwARENA_PLATFORMMAGIC "xb2"

static const struct rw::core::arena::ArenaFileHeader rw_ArenaFileHeader = {
    { //magicNumber
        rwARENA_MAGIC, //prefix
        rwARENA_PLATFORMMAGIC, //body
        rwARENA_MAGICSUFFIX, //suffix
    },
    rwARENA_ISBIGENDIAN, 
    rwARENA_POINTERSIZEINBITS, 
    rwARENA_POINTERALIGNMENT, 
    0, //padding
    rwARENA_MAJORVERSION, 
    rwARENA_MINORVERSION, 
    rwARENA_BUILDNUMBER 
};