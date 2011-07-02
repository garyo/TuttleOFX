#include "SeamCarvingDefinitions.hpp"
#include "SeamCarvingPlugin.hpp"
#include "SeamCarvingProcess.hpp"

#include <tuttle/plugin/image/ofxToGil.hpp>

#include <boost/gil/gil_all.hpp>

namespace tuttle {
namespace plugin {
namespace seamcarving {

using namespace boost::math;
using namespace boost::gil;

SeamCarvingPlugin::SeamCarvingPlugin( OfxImageEffectHandle handle )
	: ImageEffectGilPlugin( handle )
{
        _paramWidth		= fetchDoubleParam	( kParamWidth );
        _paramHeight    	= fetchDoubleParam	( kParamHeight );
        _paramDelta		= fetchDoubleParam	( kParamDelta );
        _paramRigidity    	= fetchDoubleParam	( kParamRigidity );
}

OfxRectI SeamCarvingPlugin::getSeamCarvingRegionValue() const
{

	OfxRectI cropRegion;
	return cropRegion;
}

OfxRectI SeamCarvingPlugin::computeSeamCarvingRegion( const OfxTime time, const bool fromRatio ) const
{
        OfxRectI cropRegion = getSeamCarvingRegionValue();

	return cropRegion;
}

void SeamCarvingPlugin::changedClip( const OFX::InstanceChangedArgs& args, const std::string& clipName )
{
//	TUTTLE_TCOUT( "changedClip:" << clipName );

}

void SeamCarvingPlugin::changedParam( const OFX::InstanceChangedArgs& args, const std::string& paramName )
{

}

bool SeamCarvingPlugin::getRegionOfDefinition( const OFX::RegionOfDefinitionArguments& args, OfxRectD& rod )
{
        //SeamCarvingProcessParams<rgba32f_pixel_t> params = getProcessParams<rgba32f_pixel_t>( args.time, args.renderScale );


	return false;
}

/**
 * @brief The overridden render function
 * @param[in]   args     Rendering parameters
 */
void SeamCarvingPlugin::render( const OFX::RenderArguments& args )
{
        doGilRender<SeamCarvingProcess>( *this, args );
}

}
}
}
