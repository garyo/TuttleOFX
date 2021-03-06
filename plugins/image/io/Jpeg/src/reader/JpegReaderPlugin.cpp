#include "JpegReaderPlugin.hpp"
#include "JpegReaderProcess.hpp"
#include "JpegReaderDefinitions.hpp"

#include <boost/gil/gil_all.hpp>
#include <boost/filesystem.hpp>

namespace tuttle {
namespace plugin {
namespace jpeg {
namespace reader {

namespace bfs = boost::filesystem;
using namespace boost::gil;

JpegReaderPlugin::JpegReaderPlugin( OfxImageEffectHandle handle )
	: ReaderPlugin( handle )
{}

JpegReaderProcessParams JpegReaderPlugin::getProcessParams( const OfxTime time )
{
	JpegReaderProcessParams params;

	params._filepath = getAbsoluteFilenameAt( time );
	params._flip = _paramFlip->getValue();
	
	return params;
}

void JpegReaderPlugin::changedParam( const OFX::InstanceChangedArgs& args, const std::string& paramName )
{
	ReaderPlugin::changedParam( args, paramName );
}

bool JpegReaderPlugin::getRegionOfDefinition( const OFX::RegionOfDefinitionArguments& args, OfxRectD& rod )
{
	try
	{
		point2<ptrdiff_t> jpegDims = jpeg_read_dimensions( getAbsoluteFilenameAt( args.time ) );
		rod.x1 = 0;
		rod.x2 = jpegDims.x * this->_clipDst->getPixelAspectRatio();
		rod.y1 = 0;
		rod.y2 = jpegDims.y;
	}
	catch( ... )
	{
			BOOST_THROW_EXCEPTION( exception::File()
			<< exception::user( "Jpeg: Unable to open file." )
			<< exception::filename( getAbsoluteFilenameAt( args.time ) ) );
	}
	return true;
}

void JpegReaderPlugin::getClipPreferences( OFX::ClipPreferencesSetter& clipPreferences )
{
	ReaderPlugin::getClipPreferences( clipPreferences );

	if( getExplicitConversion() == eParamReaderExplicitConversionAuto )
	{
		clipPreferences.setClipBitDepth( *this->_clipDst, OFX::eBitDepthUByte );
	}
	clipPreferences.setClipComponents( *this->_clipDst, OFX::ePixelComponentRGBA ); /// RGB
	clipPreferences.setPixelAspectRatio( *this->_clipDst, 1.0 );
}

/**
 * @brief The overridden render function
 * @param[in]   args     Rendering parameters
 */
void JpegReaderPlugin::render( const OFX::RenderArguments& args )
{
	ReaderPlugin::render(args);
	doGilRender<JpegReaderProcess>( *this, args );
}

}
}
}
}
