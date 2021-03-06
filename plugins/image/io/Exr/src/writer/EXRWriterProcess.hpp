#ifndef _EXRWRITER_PROCESS_HPP_
#define _EXRWRITER_PROCESS_HPP_

#include "../half/gilHalf.hpp"

#include <tuttle/plugin/ImageGilFilterProcessor.hpp>
#include <tuttle/plugin/exceptions.hpp>
#include <terry/globals.hpp>

#include <ImfOutputFile.h>
#include <ImfRgba.h>
#include <ImfChannelList.h>
#include <ImfArray.h>
#include <ImathVec.h>

#include <boost/scoped_ptr.hpp>

namespace tuttle {
namespace plugin {
namespace exr {
namespace writer {

/**
 * @brief Exr writer
 */
template<class View>
class EXRWriterProcess : public ImageGilFilterProcessor<View>
{
public:
	typedef typename View::value_type Pixel;

public:
	EXRWriterProcess( EXRWriterPlugin& instance );

	void setup( const OFX::RenderArguments& args );
	void multiThreadProcessImages( const OfxRectI& procWindowRoW );

protected:
	EXRWriterPlugin&      _plugin;        ///< Rendering plugin
	EXRWriterProcessParams _params;

	template<class WPixel>
	void writeImage( View& src, std::string& filepath, Imf::PixelType pixType );

};

}
}
}
}

#include "EXRWriterProcess.tcc"

#endif
