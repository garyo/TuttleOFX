#include "ReaderPlugin.hpp"

namespace tuttle {
namespace plugin {

namespace bfs = boost::filesystem;

ReaderPlugin::ReaderPlugin( OfxImageEffectHandle handle )
	: OFX::ImageEffect( handle )
{
	_clipDst           = fetchClip( kOfxImageEffectOutputClipName );
	_paramFilepath     = fetchStringParam( kParamReaderFilename );
	_isSequence        = _filePattern.initFromDetection( _paramFilepath->getValue() );
	_paramExplicitConv = fetchChoiceParam( kParamReaderExplicitConversion );
	_paramFlip         = fetchBooleanParam( kParamReaderFlip );
}

ReaderPlugin::~ReaderPlugin()
{}

void ReaderPlugin::changedParam( const OFX::InstanceChangedArgs& args, const std::string& paramName )
{
	if( paramName == kParamReaderFilename )
	{
		_isSequence = _filePattern.initFromDetection( _paramFilepath->getValue() );
	}
}

void ReaderPlugin::getClipPreferences( OFX::ClipPreferencesSetter& clipPreferences )
{
	const std::string filename( getAbsoluteFirstFilename() );
	if( !bfs::exists( filename ) )
	{
		BOOST_THROW_EXCEPTION( exception::File()
			<< exception::user( "Unable to open file." )
			<< exception::filename( filename ) );
		BOOST_THROW_EXCEPTION( exception::FileNotExist( filename ) );
	}
	// If pattern detected (frame varying on time)
	clipPreferences.setOutputFrameVarying( varyOnTime() );

	switch( getExplicitConversion() )
	{
		case eParamReaderExplicitConversionByte:
		{
			clipPreferences.setClipBitDepth( *this->_clipDst, OFX::eBitDepthUByte );
			break;
		}
		case eParamReaderExplicitConversionShort:
		{
			clipPreferences.setClipBitDepth( *this->_clipDst, OFX::eBitDepthUShort );
			break;
		}
		case eParamReaderExplicitConversionAuto:
		case eParamReaderExplicitConversionFloat:
		{
			clipPreferences.setClipBitDepth( *this->_clipDst, OFX::eBitDepthFloat );
			break;
		}
	}
	clipPreferences.setClipComponents( *this->_clipDst, OFX::ePixelComponentRGBA );
	clipPreferences.setPixelAspectRatio( *this->_clipDst, 1.0 );
}

bool ReaderPlugin::getTimeDomain( OfxRangeD& range )
{
	range.min = getFirstTime();
	range.max = getLastTime();
	return true;
}

void ReaderPlugin::render( const OFX::RenderArguments& args )
{
	const std::string filename( getAbsoluteFilenameAt( args.time ) );
	if( ! boost::filesystem::exists( filename ) )
	{
		BOOST_THROW_EXCEPTION( exception::File()
			<< exception::user( "Unable to open file." )
			<< exception::filename( filename ) );
		BOOST_THROW_EXCEPTION( exception::FileNotExist( filename ) );

	}
	
}

}
}
