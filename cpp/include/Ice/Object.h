// **********************************************************************
//
// Copyright (c) 2001
// MutableRealms, Inc.
// Huntsville, AL, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef ICE_OBJECT_H
#define ICE_OBJECT_H

#include <IceUtil/Shared.h>
#include <Ice/ObjectF.h>
#include <Ice/ProxyF.h>

namespace IceInternal
{

class Incoming;
class BasicStream;

enum DispatchStatus
{
    DispatchOK,
    DispatchUserException,
    DispatchLocationForward,
    DispatchObjectNotExist,
    DispatchFacetNotExist,
    DispatchOperationNotExist,
    DispatchUnknownLocalException,
    DispatchUnknownUserException,
    DispatchUnknownException
};

}

namespace Ice
{

class ICE_API LocationForward
{
public:

    LocationForward(const LocationForward&);
    LocationForward(const ObjectPrx&);

protected:

    ObjectPrx _prx;
    friend class ::IceProxy::Ice::Object;
    friend class ::IceInternal::Incoming;
};

class ICE_API Object : virtual public ::IceUtil::Shared
{
public:

    Object();

    bool operator==(const Object&) const;
    bool operator<(const Object&) const;
    ::Ice::Int _ice_hash() const;

    virtual bool _ice_isA(const std::string&);
    virtual void _ice_ping();
    ::IceInternal::DispatchStatus ____ice_isA(::IceInternal::Incoming&);
    ::IceInternal::DispatchStatus ____ice_ping(::IceInternal::Incoming&);
    virtual const char** __getClassIds() = 0;

    static const char* __all[];
    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const std::string&);
    virtual bool __isMutating(const std::string&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*);

    void _ice_addFacet(const ObjectPtr&, const ::std::string&);
    void _ice_removeFacet(const ::std::string&);
    void _ice_removeAllFacets();
    ObjectPtr _ice_findFacet(const ::std::string&);

private:

    std::map<std::string, ObjectPtr> _activeFacetMap;
    std::map<std::string, ObjectPtr>::iterator _activeFacetMapHint;
    JTCMutex _activeFacetMapMutex;
};

}

#endif
