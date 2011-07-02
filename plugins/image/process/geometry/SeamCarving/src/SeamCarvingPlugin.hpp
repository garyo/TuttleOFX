#ifndef _TUTTLE_PLUGIN_SEAM_CARVING_PLUGIN_HPP_
#define _TUTTLE_PLUGIN_SEAM_CARVING_PLUGIN_HPP_

#include <tuttle/plugin/ImageEffectGilPlugin.hpp>

#include "SeamCarvingDefinitions.hpp"

namespace tuttle {
namespace plugin {
namespace seamcarving {

template<class Pixel>
struct SeamCarvingProcessParams
{
        double _width;
        double _height;
        double _delta;
        double _rigidity;
};

/**
 * @brief
 *
 */
class SeamCarvingPlugin : public ImageEffectGilPlugin
{
public:
        SeamCarvingPlugin( OfxImageEffectHandle handle );

public:
	template<class Pixel>
        SeamCarvingProcessParams<Pixel> getProcessParams(  ) const;

        OfxRectI getSeamCarvingRegionValue() const;
        OfxRectI computeSeamCarvingRegion( const OfxTime time, const bool fromRatio = false ) const;

	void         changedClip( const OFX::InstanceChangedArgs& args, const std::string& clipName );
	void         changedParam( const OFX::InstanceChangedArgs& args, const std::string& paramName );
	bool         getRegionOfDefinition( const OFX::RegionOfDefinitionArguments& args, OfxRectD& rod );
	
	void render( const OFX::RenderArguments& args );

public:
	
private:
	OFX::InstanceChangedArgs _changedArgs;

        OFX::DoubleParam* _paramWidth;
        OFX::DoubleParam* _paramHeight;

        OFX::DoubleParam* _paramDelta;
        OFX::DoubleParam* _paramRigidity;
};

template<class Pixel>
SeamCarvingProcessParams<Pixel> SeamCarvingPlugin::getProcessParams(  ) const
{
        SeamCarvingProcessParams<Pixel> params;

        params._width = static_cast<double>( _paramWidth->getValue() );
        params._height = static_cast<double>( _paramHeight->getValue() );
        params._delta = static_cast<double>( _paramDelta->getValue() );
        params._rigidity = static_cast<double>( _paramRigidity->getValue() );

	return params;
}


}
}
}

#endif
