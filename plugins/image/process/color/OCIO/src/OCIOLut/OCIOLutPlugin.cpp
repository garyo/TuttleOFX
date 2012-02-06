#include "OCIOLutPlugin.hpp"
#include "OCIOLutProcess.hpp"


#include <tuttle/common/utils/color.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/filesystem.hpp>

namespace OCIO = OCIO_NAMESPACE;

namespace bfs = boost::filesystem;

namespace tuttle {
namespace plugin {
namespace ocio {
namespace lut {

using namespace boost::gil;
static const std::string kLutHelpString =
	"<b>Image Luter</b> is used to lut components of an image.  <br />";

OCIOLutPlugin::OCIOLutPlugin( OfxImageEffectHandle handle ) :
ImageEffectGilPlugin( handle )
{
	_sFilename = fetchStringParam( kInputFilename );
	_interpolationType = fetchChoiceParam( kInterpolationType );
	_fileTransform = OCIO::FileTransform::Create( );
}

/**
 * @brief The overridden render function
 * @param[in]   args     Rendering parameters
 */
void OCIOLutPlugin::render( const OFX::RenderArguments& args )
{
	/// @todo: move all this computation things to getProcessParams() called from Process::setup() fonction (which is called before multi-threading).
	bool verbose = true;
	std::string inputspace;
	std::string outputspace;

	EInterpolationType interpolationType =
		static_cast<EInterpolationType> ( _interpolationType->getValue( ) );

	std::string str;
	_sFilename->getValue( str );
	if( !bfs::exists( str ) )
	{
		BOOST_THROW_EXCEPTION( exception::FileNotExist( )
							 << exception::filename( str ) );
	}
	//Init the OCIO file transform
	_fileTransform->setSrc( str.c_str( ) );
	_fileTransform->setInterpolation( getOCIOInterpolationType( interpolationType ) );

	//Add the file transform to the group, required by the transform process
	_groupTransform = OCIO::GroupTransform::Create( );
	_groupTransform->push_back( _fileTransform );

	// Create the OCIO processor for the specified transform.
	_config = OCIO::Config::Create( );

	OCIO::ColorSpaceRcPtr inputColorSpace = OCIO::ColorSpace::Create( );
	inputspace = "RawInput";
	inputColorSpace->setName( inputspace.c_str( ) );
	_config->addColorSpace( inputColorSpace );

	OCIO::ColorSpaceRcPtr outputColorSpace = OCIO::ColorSpace::Create( );
	outputspace = "ProcessedOutput";
	outputColorSpace->setName( outputspace.c_str( ) );

	outputColorSpace->setTransform( _groupTransform,
								 OCIO::COLORSPACE_DIR_FROM_REFERENCE );

	if( verbose )
	{
		TUTTLE_COUT( tuttle::common::kColorMagenta << "[OpenColorIO DEBUG]: Specified Transform:" << *_groupTransform << "\n" << tuttle::common::kColorStd );
	}

	_config->addColorSpace( outputColorSpace );
	
	{
		using namespace boost::gil;
		// instantiate the render code based on the pixel depth of the dst clip
		OFX::EBitDepth bitDepth = _clipDst->getPixelDepth( );
		OFX::EPixelComponent components = _clipDst->getPixelComponents( );

		// do the rendering
		switch( components )
		{
			case OFX::ePixelComponentRGBA:
			{
				switch( bitDepth )
				{
					case OFX::eBitDepthFloat:
					{
						doGilRender<OCIOLutProcess, false, rgba_layout_t, bits32f>( *this, args );
						return;
					}
					case OFX::eBitDepthUByte:
					case OFX::eBitDepthUShort:
					case OFX::eBitDepthCustom:
					case OFX::eBitDepthNone:
					{
						BOOST_THROW_EXCEPTION( exception::Unsupported()
							<< exception::user() + "Bit depth (" + mapBitDepthEnumToString(bitDepth) + ") not recognized by the plugin." );
					}
				}
				break;
			}
			case OFX::ePixelComponentRGB:
			{
				switch( bitDepth )
				{
					case OFX::eBitDepthFloat:
					{
						doGilRender<OCIOLutProcess, false, rgb_layout_t, bits32f>( *this, args );
						return;
					}
					case OFX::eBitDepthUByte:
					case OFX::eBitDepthUShort:
					case OFX::eBitDepthCustom:
					case OFX::eBitDepthNone:
					{
						BOOST_THROW_EXCEPTION( exception::Unsupported()
							<< exception::user() + "Bit depth (" + mapBitDepthEnumToString(bitDepth) + ") not recognized by the plugin." );
					}
				}
				break;
			}
			case OFX::ePixelComponentAlpha:
			case OFX::ePixelComponentCustom:
			case OFX::ePixelComponentNone:
			{
				BOOST_THROW_EXCEPTION( exception::Unsupported()
					<< exception::user() + "Pixel components (" + mapPixelComponentEnumToString(components) + ") not supported by the plugin." );
			}
		}
		BOOST_THROW_EXCEPTION( exception::Unknown() );
	}
}

void OCIOLutPlugin::changedParam( const OFX::InstanceChangedArgs& args,
								  const std::string& paramName )
{
	if( paramName == kHelp )
	{
		sendMessage( OFX::Message::eMessageMessage, "", // No XML resources
					 kLutHelpString );
	}
	else if( paramName == kInputFilename )
	{
		std::string str;
		_sFilename->getValue( str );
		if( bfs::exists( str ) )
		{
			_fileTransform->setSrc( str.c_str( ) );
		}
	}
	else if( paramName == kInterpolationType )
	{
		EInterpolationType interpolationType =
			static_cast<EInterpolationType> ( _interpolationType->getValue( ) );
		_fileTransform->setInterpolation( getOCIOInterpolationType( interpolationType ) );
	}
}

}
}
}
}