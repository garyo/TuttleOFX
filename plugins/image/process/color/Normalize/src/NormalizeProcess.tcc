#include "NormalizeAlgorithm.hpp"
#include "NormalizeDefinitions.hpp"
#include "NormalizePlugin.hpp"
#include "NormalizeProcess.hpp"

#include <tuttle/plugin/exceptions.hpp>

#include <terry/globals.hpp>
#include <terry/algorithm/transform_pixels_progress.hpp>
#include <terry/numeric/operations.hpp>
#include <terry/numeric/assign.hpp>
#include <terry/numeric/init.hpp>
#include <terry/numeric/scale.hpp>

#include <boost/gil/color_base_algorithm.hpp>


namespace tuttle {
namespace plugin {
namespace normalize {

template<class View>
NormalizeProcess<View>::NormalizeProcess( NormalizePlugin &effect )
: ImageGilFilterProcessor<View>( effect )
, _plugin( effect )
{
}

template<class View>
void NormalizeProcess<View>::setup( const OFX::RenderArguments& args )
{
	using namespace terry;
	using namespace terry::numeric;
	typedef rgba32f_pixel_t PixelParam;
	typedef pixel<typename channel_type<View>::type, gray_layout_t> PixelGray;

	ImageGilFilterProcessor<View>::setup( args );
	_params = _plugin.getProcessParams( args.renderScale );

	View src = this->_srcView;
	Pixel smin;
	Pixel smax;
	pixel_zeros_t<Pixel>()(smax);
	switch( _params._mode )
	{
		case eParamModeAnalyse:
		{
			analyseInputMinMax<View>( src, _params._analyseMode, smin, smax, *this );
			break;
		}
		case eParamModeCustom:
		{
			smin = _params._srcMinColor;
			smax = _params._srcMaxColor;
			break;
		}
	}
	for( std::ssize_t n = 0; n < boost::gil::num_channels<Pixel>::type::value; ++n )
	{
		_sMin[n] = smin[n];
		_dMin[n] = _params._dstMinColor[n];
		if( (smax[n] - smin[n]) == 0 )
			_ratio[n] = 0;
		else
			_ratio[n] = (_params._dstMaxColor[n] - _params._dstMinColor[n]) / (smax[n] - smin[n]);
	}

//	TUTTLE_COUT("");
//	TUTTLE_COUT_VAR( get_color( _sMin, red_t() ) );
//	TUTTLE_COUT_VAR( get_color( _sMin, green_t() ) );
//	TUTTLE_COUT_VAR( get_color( _sMin, blue_t() ) );
//	TUTTLE_COUT_VAR( get_color( _sMin, alpha_t() ) );
//	TUTTLE_COUT("");
//	TUTTLE_COUT_VAR( get_color( _dMin, red_t() ) );
//	TUTTLE_COUT_VAR( get_color( _dMin, green_t() ) );
//	TUTTLE_COUT_VAR( get_color( _dMin, blue_t() ) );
//	TUTTLE_COUT_VAR( get_color( _dMin, alpha_t() ) );
//	TUTTLE_COUT("");
//	TUTTLE_COUT_VAR( get_color( _ratio, red_t() ) );
//	TUTTLE_COUT_VAR( get_color( _ratio, green_t() ) );
//	TUTTLE_COUT_VAR( get_color( _ratio, blue_t() ) );
//	TUTTLE_COUT_VAR( get_color( _ratio, alpha_t() ) );
//	TUTTLE_COUT("");
}

/**
 * @brief Function called by rendering thread each time a process must be done.
 * @param[in] procWindowRoW  Processing window
 */
template<class View>
void NormalizeProcess<View>::multiThreadProcessImages( const OfxRectI& procWindowRoW )
{
	using namespace terry;
	using namespace terry::numeric;
	using namespace terry::algorithm;
	const OfxRectI procWindowOutput = this->translateRoWToOutputClipCoordinates( procWindowRoW );
	const OfxRectI procWindowSrc = translateRegion( procWindowRoW, this->_srcPixelRod );
	const OfxPointI procWindowSize = { procWindowRoW.x2 - procWindowRoW.x1,
							           procWindowRoW.y2 - procWindowRoW.y1 };
	View src = subimage_view( this->_srcView, procWindowSrc.x1, procWindowSrc.y1,
							                  procWindowSize.x, procWindowSize.y );
	View dst = subimage_view( this->_dstView, procWindowOutput.x1, procWindowOutput.y1,
	                                          procWindowSize.x, procWindowSize.y );

	if( _params._processR &&
	    _params._processG &&
	    _params._processB &&
	    _params._processA )
	{
		transform_pixels_progress(
			src,
			dst,
			pixel_scale_t<Pixel,Pixel>(_ratio, _sMin, _dMin),
			*this );
	}
	else
	{
		// by channel:
		// red
		{
			typedef red_t LocalChannel;
			if( _params._processR )
			{
				typedef channel_view_type<LocalChannel,View> LocalView;
				typedef typename LocalView::type::value_type LocalPixel;
				typename LocalView::type localSrcView( LocalView::make(src) );
				typename LocalView::type localDstView( LocalView::make(dst) );

				transform_pixels_progress(
					localSrcView,
					localDstView,
					pixel_scale_t<LocalPixel,LocalPixel>(
						LocalPixel( get_color( _ratio, LocalChannel() ) ),
						LocalPixel( get_color( _sMin, LocalChannel() ) ),
						LocalPixel( get_color( _dMin, LocalChannel() ) )
						),
					*this );
			}
			else
			{
				copy_pixels( channel_view<LocalChannel>(src), channel_view<LocalChannel>(dst) );
			}
		}
		// green
		{
			typedef green_t LocalChannel;
			if( _params._processG )
			{
				typedef channel_view_type<LocalChannel,View> LocalView;
				typedef typename LocalView::type::value_type LocalPixel;
				typename LocalView::type localSrcView( LocalView::make(src) );
				typename LocalView::type localDstView( LocalView::make(dst) );

				transform_pixels_progress(
					localSrcView,
					localDstView,
					pixel_scale_t<LocalPixel>(
						LocalPixel( get_color( _ratio, LocalChannel() ) ),
						LocalPixel( get_color( _sMin, LocalChannel() ) ),
						LocalPixel( get_color( _dMin, LocalChannel() ) )
						),
					*this );
			}
			else
			{
				copy_pixels( channel_view<LocalChannel>(src), channel_view<LocalChannel>(dst) );
			}
		}
		// blue
		{
			typedef blue_t LocalChannel;
			if( _params._processB )
			{
				typedef channel_view_type<LocalChannel,View> LocalView;
				typedef typename LocalView::type::value_type LocalPixel;
				typename LocalView::type localSrcView( LocalView::make(src) );
				typename LocalView::type localDstView( LocalView::make(dst) );

				transform_pixels_progress(
					localSrcView,
					localDstView,
					pixel_scale_t<LocalPixel>(
						LocalPixel( get_color( _ratio, LocalChannel() ) ),
						LocalPixel( get_color( _sMin, LocalChannel() ) ),
						LocalPixel( get_color( _dMin, LocalChannel() ) )
						),
					*this );
			}
			else
			{
				copy_pixels( channel_view<LocalChannel>(src), channel_view<LocalChannel>(dst) );
			}
		}
		// alpha
		{
			typedef alpha_t LocalChannel;
			if( _params._processA )
			{
				typedef channel_view_type<LocalChannel,View> LocalView;
				typedef typename LocalView::type::value_type LocalPixel;
				typename LocalView::type localSrcView( LocalView::make(src) );
				typename LocalView::type localDstView( LocalView::make(dst) );

				transform_pixels_progress(
					localSrcView,
					localDstView,
					pixel_scale_t<LocalPixel>(
						LocalPixel( get_color( _ratio, LocalChannel() ) ),
						LocalPixel( get_color( _sMin, LocalChannel() ) ),
						LocalPixel( get_color( _dMin, LocalChannel() ) )
						),
					*this );
			}
			else
			{
				copy_pixels( channel_view<LocalChannel>(src), channel_view<LocalChannel>(dst) );
			}
		}

	}

}

}
}
}
