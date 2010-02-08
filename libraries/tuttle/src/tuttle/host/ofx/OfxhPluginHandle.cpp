#include "OfxhPluginHandle.hpp"
#include "OfxhPlugin.hpp"
#include "OfxhPluginBinary.hpp"

#include <boost/lexical_cast.hpp>

namespace tuttle {
namespace host {
namespace ofx {


OfxhPluginHandle::OfxhPluginHandle( OfxhPlugin* p, OfxhHost* host ) : _p( p )
{
	_b = p->getBinary();
	_b->_binary.ref();
	_op                          = 0;
	OfxPlugin* ( *getPlug )(int) = ( OfxPlugin * ( * )( int ) )_b->_binary.findSymbol( "OfxGetPlugin" );
	_op                          = getPlug( p->getIndex() );
	if( !_op )
	{
		throw core::exception::LogicError( "Can't found plugin at index '"+boost::lexical_cast<std::string>(p->getIndex())+"' in plugin '" + _p->getIdentifier() + "'" );
	}
	_op->setHost( host->getHandle() );
}

OfxhPluginHandle::~OfxhPluginHandle()
{
	_b->_binary.unref();
}

}
}
}

