// **********************************************************************
//
// Copyright (c) 2001
// MutableRealms, Inc.
// Huntsville, AL, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef ICE_UTIL_EXCEPTION_H
#define ICE_UTIL_EXCEPTION_H

#include <IceUtil/Config.h>

namespace IceUtil
{

class ICE_UTIL_API Exception
{
public:

    Exception();
    Exception(const char*, int);
    virtual ~Exception();
    virtual std::string _ice_name() const;
    virtual void _ice_print(std::ostream&) const;
    virtual Exception* _ice_clone() const;
    virtual void _ice_throw() const;
    const char* _ice_file() const;
    int _ice_line() const;
    
private:
    
    const char* _file;
    int _line;
};

ICE_UTIL_API std::ostream& operator<<(std::ostream&, const Exception&);

class ICE_UTIL_API NullHandleException : public Exception
{
public:
    
    NullHandleException(const char*, int);
    virtual std::string _ice_name() const;
    virtual std::string _ice_description() const;
    virtual Exception* _ice_clone() const;
    virtual void _ice_throw() const;
};

}

#endif
