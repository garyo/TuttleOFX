#ifndef _TUTTLE_PLUGIN_SEAM_CARVING_DEFINITIONS_HPP_
#define _TUTTLE_PLUGIN_SEAM_CARVING_DEFINITIONS_HPP_

#include <tuttle/plugin/global.hpp>

namespace tuttle {
namespace plugin {
namespace seamcarving {

static const bool kSupportTiles              = true;
static const bool kSupportTemporalClipAccess = true;

static const std::string kParamWidth = "width";
static const std::string kParamHeight = "height";

static const std::string kParamDelta = "delta";
static const std::string kParamRigidity = "rigidity";

}
}
}

#endif
