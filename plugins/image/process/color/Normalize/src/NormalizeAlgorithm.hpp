#ifndef _TUTTLE_PLUGIN_NORMALIZE_ALGORITHM_HPP_
#define _TUTTLE_PLUGIN_NORMALIZE_ALGORITHM_HPP_

#include <terry/channel.hpp>
#include <terry/channel_view.hpp>
#include <terry/algorithm/static_channel_recursion.hpp>
#include <terry/numeric/operations.hpp>
#include <terry/numeric/assign.hpp>
#include <terry/numeric/minmax.hpp>
#include <terry/algorithm/transform_pixels_progress.hpp>

namespace tuttle {
namespace plugin {
namespace normalize {

/**
 * @brief compute min and max from input view analyse.
 *
 * @param[in] src: input image to analyse
 * @param[in] analyseMode: choose the analyse method
 * @param[out] min: output min values
 * @param[out] max: output max values
 */
template<class View>
void analyseInputMinMax( const View& src, const EParamAnalyseMode analyseMode, typename View::value_type& min, typename View::value_type& max, IProgress& p )
{
	using namespace terry;
	using namespace terry::numeric;
	using namespace terry::algorithm;
	
	typedef typename View::value_type Pixel;

	switch( analyseMode )
	{
		case eParamAnalyseModePerChannel:
		{
			pixel_minmax_by_channel_t<Pixel> minmax( src(0,0) );
			// compute the maximum value
			transform_pixels_progress(
				src,
				minmax,
				p );
			min = minmax.min;
			max = minmax.max;
			break;
		}
		case eParamAnalyseModeLuminosity:
		{
			typedef pixel<typename channel_type<View>::type, gray_layout_t> PixelGray;
			typedef typename color_converted_view_type<View, PixelGray>::type LocalView;
			LocalView localView(src);
			pixel_minmax_by_channel_t<typename LocalView::value_type> minmax( localView(0,0) );
			transform_pixels_progress(
				localView,
				minmax,
				p );
			static_fill( min, minmax.min[0] );
			static_fill( max, minmax.max[0] );
			break;
		}
		case eParamAnalyseModeR:
		{
			typedef channel_view_type<red_t,View> LocalView;
			typename LocalView::type localView( LocalView::make(src) );
			pixel_minmax_by_channel_t<typename LocalView::type::value_type> minmax( localView(0,0) );
			transform_pixels_progress(
				localView,
				minmax,
				p );
			static_fill( min, minmax.min[0] );
			static_fill( max, minmax.max[0] );
			break;
		}
		case eParamAnalyseModeG:
		{
			typedef channel_view_type<green_t,View> LocalView;
			typename LocalView::type localView( LocalView::make(src) );
			pixel_minmax_by_channel_t<typename LocalView::type::value_type> minmax( localView(0,0) );
			transform_pixels_progress(
				localView,
				minmax,
				p );
			static_fill( min, minmax.min[0] );
			static_fill( max, minmax.max[0] );
			break;
		}
		case eParamAnalyseModeB:
		{
			typedef channel_view_type<blue_t,View> LocalView;
			typename LocalView::type localView( LocalView::make(src) );
			pixel_minmax_by_channel_t<typename LocalView::type::value_type> minmax( localView(0,0) );
			transform_pixels_progress(
				localView,
				minmax,
				p );
			static_fill( min, minmax.min[0] );
			static_fill( max, minmax.max[0] );
			break;
		}
		case eParamAnalyseModeA:
		{
			typedef channel_view_type<alpha_t,View> LocalView;
			typename LocalView::type localView( LocalView::make(src) );
			pixel_minmax_by_channel_t<typename LocalView::type::value_type> minmax( localView(0,0) );
			transform_pixels_progress(
				localView,
				minmax,
				p );
			static_fill( min, minmax.min[0] );
			static_fill( max, minmax.max[0] );
			break;
		}
	}
}


}
}
}

#endif
