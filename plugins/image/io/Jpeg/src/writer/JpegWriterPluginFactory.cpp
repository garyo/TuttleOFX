#include "JpegWriterPluginFactory.hpp"
#include "JpegWriterDefinitions.hpp"
#include "JpegWriterPlugin.hpp"

#include <tuttle/plugin/context/WriterPluginFactory.hpp>

namespace tuttle {
namespace plugin {
namespace jpeg {
namespace writer {

/**
 * @brief Function called to describe the plugin main features.
 * @param[in, out]   desc     Effect descriptor
 */
void JpegWriterPluginFactory::describe( OFX::ImageEffectDescriptor& desc )
{
    desc.setLabels( "TuttleJpegWriter", "JpegWriter",
                    "Jpeg file writer" );
    desc.setPluginGrouping( "tuttle/image/io" );

    // add the supported contexts
    desc.addSupportedContext( OFX::eContextWriter );
    desc.addSupportedContext( OFX::eContextGeneral );

    // add supported pixel depths
    desc.addSupportedBitDepth( OFX::eBitDepthUByte );
    desc.addSupportedBitDepth( OFX::eBitDepthUShort );
    desc.addSupportedBitDepth( OFX::eBitDepthFloat );

    // add supported extensions
    desc.addSupportedExtension( "jpeg" );
    desc.addSupportedExtension( "jpg" );
    desc.addSupportedExtension( "jpe" );
    desc.addSupportedExtension( "jfif" );
    desc.addSupportedExtension( "jfi" );

    // plugin flags
    desc.setRenderThreadSafety( OFX::eRenderFullySafe );
    desc.setHostFrameThreading( false );
    desc.setSupportsMultiResolution( false );
    desc.setSupportsMultipleClipDepths( true );
    desc.setSupportsTiles( kSupportTiles );
}

/**
 * @brief Function called to describe the plugin controls and features.
 * @param[in, out]   desc       Effect descriptor
 * @param[in]        context    Application context
 */
void JpegWriterPluginFactory::describeInContext( OFX::ImageEffectDescriptor& desc,
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

    // Controls
    OFX::StringParamDescriptor* filename = desc.defineStringParam( kParamWriterFilename );
    filename->setLabel( "Filename" );
    filename->setStringType( OFX::eStringTypeFilePath );
    filename->setCacheInvalidation( OFX::eCacheInvalidateValueAll );
    desc.addClipPreferencesSlaveParam( *filename );

    OFX::ChoiceParamDescriptor* bitDepth = desc.defineChoiceParam( kParamWriterBitDepth );
    bitDepth->setLabel( "Bit depth" );
    bitDepth->appendOption( kTuttlePluginBitDepth8 );
    bitDepth->setCacheInvalidation( OFX::eCacheInvalidateValueAll );
    bitDepth->setDefault( 0 );

    OFX::BooleanParamDescriptor* premult = desc.defineBooleanParam( kParamPremult );
    premult->setLabel( "Premult" );
    premult->setCacheInvalidation( OFX::eCacheInvalidateValueAll );
    premult->setDefault( true );

    OFX::IntParamDescriptor* quality = desc.defineIntParam( kParamQuality );
    quality->setLabel( "Quality" );
    quality->setCacheInvalidation( OFX::eCacheInvalidateValueAll );
    quality->setDefault( 80 );

    describeWriterParamsInContext( desc, context );
}

/**
 * @brief Function called to create a plugin effect instance
 * @param[in] handle  effect handle
 * @param[in] context    Application context
 * @return  plugin instance
 */
OFX::ImageEffect* JpegWriterPluginFactory::createInstance( OfxImageEffectHandle handle,
                                                           OFX::EContext        context )
{
    return new JpegWriterPlugin( handle );
}

}
}
}
}
