#include "SeamCarvingPluginFactory.hpp"
#include "SeamCarvingDefinitions.hpp"
#include "SeamCarvingPlugin.hpp"

#include <tuttle/plugin/exceptions.hpp>

#include <ofxsParam.h>
#include <ofxsImageEffect.h>
#include <ofxsMultiThread.h>

#include <limits>

namespace tuttle {
namespace plugin {
namespace seamcarving {

/**
 * @brief Function called to describe the plugin main features.
 * @param[in, out]   desc     Effect descriptor
 */
void SeamCarvingPluginFactory::describe( OFX::ImageEffectDescriptor& desc )
{
        desc.setLabels( "TuttleSeamCarving", "SeamCarving",
                        "Image Seam Carving" );
	desc.setPluginGrouping( "tuttle/image/process/geometry" );

        desc.setDescription( "SeamCarving\n"
                             "Plugin is used to apply the seam carving on images." );

	// add the supported contexts
	desc.addSupportedContext( OFX::eContextFilter );
	desc.addSupportedContext( OFX::eContextGeneral );

	// add supported pixel depths
	desc.addSupportedBitDepth( OFX::eBitDepthUByte );
	desc.addSupportedBitDepth( OFX::eBitDepthUShort );
	desc.addSupportedBitDepth( OFX::eBitDepthFloat );

	// plugin flags
	desc.setSupportsTiles( kSupportTiles );
	desc.setRenderThreadSafety( OFX::eRenderFullySafe );

        //desc.setOverlayInteractDescriptor( new OFX::DefaultEffectOverlayWrap<SeamCarvingEffectOverlay>() );
}

/**
 * @brief Function called to describe the plugin controls and features.
 * @param[in, out]   desc       Effect descriptor
 * @param[in]        context    Application context
 */
void SeamCarvingPluginFactory::describeInContext( OFX::ImageEffectDescriptor& desc,
                                           OFX::EContext               context )
{
	OFX::ClipDescriptor* srcClip = desc.defineClip( kOfxImageEffectSimpleSourceClipName );

	srcClip->addSupportedComponent( OFX::ePixelComponentRGBA );
	srcClip->addSupportedComponent( OFX::ePixelComponentRGB );
	srcClip->addSupportedComponent( OFX::ePixelComponentAlpha );
	srcClip->setSupportsTiles( kSupportTiles );

	OFX::ClipDescriptor* dstClip = desc.defineClip( kOfxImageEffectOutputClipName );
	dstClip->addSupportedComponent( OFX::ePixelComponentRGBA );
	dstClip->addSupportedComponent( OFX::ePixelComponentRGB );
	dstClip->addSupportedComponent( OFX::ePixelComponentAlpha );
	dstClip->setSupportsTiles( kSupportTiles );

        OFX::DoubleParamDescriptor* newWidth = desc.defineDoubleParam( kParamWidth );
        newWidth->setLabel( "Width" );
        newWidth->setHint( "Width of the resized image." );
        newWidth->setDefault( 1.0 );
        newWidth->setDisplayRange( 0.0, 500.0 );

        OFX::DoubleParamDescriptor* newHeight = desc.defineDoubleParam( kParamHeight );
        newHeight->setLabel( "Height" );
        newHeight->setHint( "Height of the resized image." );
        newHeight->setDefault( 1.0 );
        newHeight->setDisplayRange( 0.0, 500.0 );


        OFX::DoubleParamDescriptor* delta = desc.defineDoubleParam( kParamDelta );
        delta->setLabel( "Delta" );
        delta->setHint( "Delta parameter." );
        delta->setDefault( 1.0 );
        delta->setDisplayRange( 0.0, 500.0 );

        OFX::DoubleParamDescriptor* rigidity = desc.defineDoubleParam( kParamRigidity );
        rigidity->setLabel( "Rigidity" );
        rigidity->setHint( "Rigidity parameter." );
        rigidity->setDefault( 0.0 );
        rigidity->setDisplayRange( 0.0, 500.0 );
}

/**
 * @brief Function called to create a plugin effect instance
 * @param[in] handle  effect handle
 * @param[in] context    Application context
 * @return  plugin instance
 */
OFX::ImageEffect* SeamCarvingPluginFactory::createInstance( OfxImageEffectHandle handle,
                                                            OFX::EContext        context )
{
        return new SeamCarvingPlugin( handle );
}

}
}
}
