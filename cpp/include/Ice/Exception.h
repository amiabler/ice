// **********************************************************************
//
// Copyright (c) 2001
// MutableRealms, Inc.
// Huntsville, AL, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef ICE_EXCEPTION_H
#define ICE_EXCEPTION_H

#include <IceUtil/Exception.h>
#include <Ice/Config.h>

namespace IceInternal
{

class BasicStream;

}

namespace Ice
{

typedef IceUtil::Exception Exception;

class LocalException : public IceUtil::Exception
{
public:    

    ICE_API LocalException(const char*, int);
    virtual std::string _ice_name() const = 0;
    virtual Exception* _ice_clone() const = 0;
    virtual void _ice_throw() const = 0;
};

class ICE_API UserException : public IceUtil::Exception
{
public:    

    virtual std::string _ice_name() const = 0;
    virtual Exception* _ice_clone() const = 0;
    virtual void _ice_throw() const = 0;

    virtual const char** __getExceptionIds() const = 0;
    virtual void __write(::IceInternal::BasicStream*) const = 0;
    virtual void __read(::IceInternal::BasicStream*) = 0;
};

}

#include <Ice/LocalException.h>

#endif
