#ifndef _TUTTLE_HOST_PROCESSVERTEX_HPP_
#define _TUTTLE_HOST_PROCESSVERTEX_HPP_

#include "IVertex.hpp"
#include "UVertex.hpp"
#include "ProcessVertexData.hpp"

namespace tuttle {
namespace host {
namespace graph {

class ProcessVertex : public IVertex
{
public:
	typedef std::string Key;
public:
	ProcessVertex( const std::string& name = "Undefined" );
	ProcessVertex( const UVertex& v );
	ProcessVertex( const ProcessVertex& v );

	ProcessVertex& operator=( const ProcessVertex& v )
	{
		IVertex::operator=(v);
		_data           = v._data;
		return *this;
	}

	ProcessVertex& operator=( const UVertex& v )
	{
		IVertex::operator=(v);
		_data._apiType = v.getProcessNode().getNodeType();
		return *this;
	}

	Key getKey() const { return getName(); }

	void setProcessData( const ProcessVertexData& d ) { _data = d; }

	ProcessVertexData&       getProcessData()       { return _data; }
	const ProcessVertexData& getProcessData() const { return _data; }
	
	std::ostream& exportDotDebug( std::ostream& os ) const;
	friend std::ostream& operator<<( std::ostream& os, const ProcessVertex& v );

public:
	ProcessVertexData _data;
};

}
}
}

#endif

