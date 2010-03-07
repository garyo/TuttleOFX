#include "PNGWriterDefinitions.hpp"
#include "PNGWriterPlugin.hpp"

#include <tuttle/common/image/gilGlobals.hpp>
#include <tuttle/plugin/ImageGilProcessor.hpp>
#include <tuttle/plugin/PluginException.hpp>

#include <cmath>
#include <vector>
#include <ofxsImageEffect.h>
#include <ofxsMultiThread.h>
#include <boost/gil/gil_all.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include <boost/filesystem/fstream.hpp>

namespace tuttle {
namespace plugin {
namespace png {
namespace writer {

using namespace boost::gil;

template<class View>
PNGWriterProcess<View>::PNGWriterProcess( PNGWriterPlugin& instance )
	: ImageGilProcessor<View>( instance ),
	_plugin( instance )
{
	_filepath = instance.fetchStringParam( kOutputFilename );
}

template<class View>
void PNGWriterProcess<View>::setup( const OFX::RenderArguments& args )
{
	// Fetch input image
	boost::scoped_ptr<OFX::Image> src( _plugin.getSrcClip()->fetchImage( args.time ) );
	if( !src.get() )
		throw( tuttle::plugin::ImageNotReadyException() );
	OfxRectI sBounds = src->getBounds();

	// Build destination view
	_srcView = interleaved_view( std::abs( sBounds.x2 - sBounds.x1 ), std::abs( sBounds.y2 - sBounds.y1 ),
								 static_cast<Pixel*>( src->getPixelData() ),
								 src->getRowBytes() );

	boost::scoped_ptr<OFX::Image> dst( _plugin.getDstClip()->fetchImage( args.time ) );
	if( !dst.get() )
		throw( tuttle::plugin::ImageNotReadyException() );
	OfxRectI dBounds = dst->getBounds();

	// Build destination view
	_dstView = interleaved_view( std::abs( dBounds.x2 - dBounds.x1 ), std::abs( dBounds.y2 - dBounds.y1 ),
								 static_cast<Pixel*>( dst->getPixelData() ),
								 dst->getRowBytes() );
}

/**
 * @brief Function called by rendering thread each time
 *        a process must be done.
 *
 * @param[in] procWindow  Processing window
 *
 * @warning no multithread here !
 */
template<class View>
void PNGWriterProcess<View>::multiThreadProcessImages( const OfxRectI& procWindow )
{
	try
	{
		std::string filepath;
		this->_filepath->getValue( filepath );
		writeImage( _srcView, filepath );
		copy_pixels( _srcView, _dstView );
	}
	catch( tuttle::plugin::PluginException& e )
	{
		COUT_EXCEPTION( e );
	}
}

/**
 * @brief Function called to apply an anisotropic blur
 *
 * @param[out]  dst     Destination image view
 * @param[in]   amplitude     Amplitude of the anisotropic blur
 * @param dl    spatial discretization.
 * @param da    angular discretization.
 * @param gauss_prec    precision of the gaussian function
 * @param fast_approx   Tell to use the fast approximation or not.
 *
 * @return Result view of the blurring process
 */
template<class View>
void PNGWriterProcess<View>::writeImage( View& src, std::string& filepath ) throw( tuttle::plugin::PluginException )
{
	View flippedView = flipped_up_down_view( src );

	png_write_view( filepath, clamp<rgb8_pixel_t>( flippedView ) );
}

}
}
}
}