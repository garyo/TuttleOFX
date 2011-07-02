#include <tuttle/common/math/rectOp.hpp>
#include <tuttle/plugin/exceptions.hpp>
#include <tuttle/plugin/image/gil/fill.hpp>
#include <tuttle/plugin/image/gil/basic_colors.hpp>
#include <tuttle/plugin/image/gil/globals.hpp>
#include <tuttle/plugin/global.hpp>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>


namespace tuttle {
namespace plugin {
namespace seamcarving {

using namespace boost::gil;

template<class View>
SeamCarvingProcess<View>::SeamCarvingProcess( SeamCarvingPlugin& instance )
	: ImageGilFilterProcessor<View>( instance )
	, _plugin( instance )
{
}

template<class View>
void SeamCarvingProcess<View>::setup( const OFX::RenderArguments& args )
{
	ImageGilFilterProcessor<View>::setup( args );

        _params = _plugin.getProcessParams<Pixel>( );
}

/**
 * @brief Function called by rendering thread each time a process must be done.
 * @param[in] procWindowRoW  Processing window in RoW
 */
template<class View>
void SeamCarvingProcess<View>::multiThreadProcessImages( const OfxRectI& procWindowRoW )
{
	using namespace boost::gil;
        const OfxRectI procWindowOutput = this->translateRoWToOutputClipCoordinates( procWindowRoW );
        const OfxRectI procWindowSrc = translateRegion( procWindowRoW, this->_srcPixelRod );

        //carver = lqr_carver_new_ext ( this->_srcView.row_begin(0) , this->_srcView.width() , this->_srcView.height(), 4/*channels*/, LQR_COLDEPTH_32F );

        //lqr_carver_init ( carver, _params._delta, _params._rigidity );

        //lqr_carver_resize ( carver, _params._width, _params._width);

        TUTTLE_COUT ("channels : " << lqr_carver_get_channels(carver));
        TUTTLE_COUT ("width : " << lqr_carver_get_width(carver));
        TUTTLE_COUT ("height : " << lqr_carver_get_height(carver));

        //lqr_carver_destroy(carver);

}

}
}
}
