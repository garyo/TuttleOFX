#ifndef _TUTTLE_PLUGIN_SEAM_CARVING_PROCESS_HPP_
#define _TUTTLE_PLUGIN_SEAM_CARVING_PROCESS_HPP_

#include <tuttle/plugin/ImageGilFilterProcessor.hpp>
#include <tuttle/plugin/global.hpp>
#include <tuttle/plugin/exceptions.hpp>

#include <lqr.h>

namespace tuttle {
namespace plugin {
namespace seamcarving {

/**
 * @brief Base class
 *
 */
template<class View>
class SeamCarvingProcess : public ImageGilFilterProcessor<View>
{
public:
	typedef typename View::value_type Pixel;

protected:
        SeamCarvingPlugin&          _plugin;        ///< Rendering plugin
        SeamCarvingProcessParams<Pixel>    _params;        ///< process parameters

public:
        SeamCarvingProcess<View>( SeamCarvingPlugin & instance );

	void setup( const OFX::RenderArguments& args );

	void multiThreadProcessImages( const OfxRectI& procWindowRoW );


private:
        LqrCarver* carver;
};

}
}
}

#include "SeamCarvingProcess.tcc"

#endif

