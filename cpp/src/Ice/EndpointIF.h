// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_ENDPOINT_I_F_H
#define ICE_ENDPOINT_I_F_H

#include <IceUtil/Shared.h>
#include <Ice/Handle.h>

namespace IceInternal
{

class EndpointI;
class TcpEndpointI;
class UdpEndpointI;
class WSEndpoint;
class EndpointI_connectors;

#ifdef ICE_CPP11_MAPPING // C++11 mapping

typedef ::std::shared_ptr<EndpointI> EndpointIPtr;
typedef ::std::shared_ptr<TcpEndpointI> TcpEndpointIPtr;
typedef ::std::shared_ptr<UdpEndpointI> UdpEndpointIPtr;
typedef ::std::shared_ptr<WSEndpoint> WSEndpointPtr;
typedef ::std::shared_ptr<EndpointI_connectors> EndpointI_connectorsPtr;

#else // C++98 mapping

ICE_API IceUtil::Shared* upCast(EndpointI*);
typedef Handle<EndpointI> EndpointIPtr;

ICE_API IceUtil::Shared* upCast(TcpEndpointI*);
typedef Handle<TcpEndpointI> TcpEndpointIPtr;

ICE_API IceUtil::Shared* upCast(UdpEndpointI*);
typedef Handle<UdpEndpointI> UdpEndpointIPtr;

ICE_API IceUtil::Shared* upCast(WSEndpoint*);
typedef Handle<WSEndpoint> WSEndpointPtr;

ICE_API IceUtil::Shared* upCast(EndpointI_connectors*);
typedef Handle<EndpointI_connectors> EndpointI_connectorsPtr;

#endif

}

#endif