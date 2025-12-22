#pragma once

#include "aipathdata.h"
#include "arenadictionary.h"
#include "arenadictionarybuilder.h"
#include "cmaterialdata.h"
#include "cmodeldata.h"
#include "collisionbezier.h"
#include "collisiongrouptypes.h"
#include "collisionsurfacetypes.h"
#include "depthmapcpudata.h"
#include "instancedata.h"
#include "instancetypes.h"
#include "liondata.h"
#include "locationdescdata.h"
#include "massivedata.h"
#include "navmeshdata.h"
#include "raindata.h"
#include "rblendshapedata.h"
#include "rmaterialdata.h"
#include "rmeshdata.h"
#include "rmodeldata.h"
#include "rollerdescdata.h"
#include "simpletrimeshdata.h"
#include "splinedata.h"
#include "statsdata.h"
#include "tableofcontents.h"
#include "triggerinstancedata.h"
#include "versiondata.h"
#include "waypointdata.h"
#include "wpdictionarydata.h"
#include "wplayerdata.h"
#include "wpquadtreedata.h"

namespace pegasus
{
    const uint kAssetType_Instance_CreateACharacter = rw::RwHash32String(kInstanceType_CreateACharacter);
    const uint kAssetType_Instance_Environment = rw::RwHash32String(kInstanceType_Environment);
    const uint kAssetType_Instance_LivingWorld = rw::RwHash32String(kInstanceType_LivingWorld);
    const uint kAssetType_Instance_Marquee = rw::RwHash32String(kInstanceType_Marquee);
    const uint kAssetType_Instance_Prop = rw::RwHash32String(kInstanceType_Prop);
    const uint kAssetType_Instance_Trigger = rw::RwHash32String(kInstanceType_Trigger);
}