#define OFXPLUGIN_VERSION_MAJOR 2
#define OFXPLUGIN_VERSION_MINOR 2

#include <tuttle/plugin/Plugin.hpp>
#include "LensDistortPluginFactory.hpp"

namespace OFX {
namespace Plugin {

void getPluginIDs( OFX::PluginFactoryArray& ids )
{
	mAppendPluginFactory( ids, tuttle::plugin::lens::LensDistortPluginFactory, "tuttle.lensdistort" );
}

}
}
