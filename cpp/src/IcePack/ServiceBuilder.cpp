// **********************************************************************
//
// Copyright (c) 2003
// ZeroC, Inc.
// Billerica, MA, USA
//
// All Rights Reserved.
//
// Ice is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License version 2 as published by
// the Free Software Foundation.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <IcePack/ServiceBuilder.h>
#include <IcePack/ServerBuilder.h>
#include <Ice/Xerces.h>

using namespace std;
using namespace IcePack;

namespace IcePack
{

class ServiceHandler : public ComponentHandler
{
public:

    ServiceHandler(ServiceBuilder&);

    virtual void startElement(const XMLCh *const name, ICE_XERCES_NS AttributeList &attrs); 

private:

    ServiceBuilder& _builder;
};

}

IcePack::ServiceHandler::ServiceHandler(ServiceBuilder& builder) :
    ComponentHandler(builder),
    _builder(builder)
{
}

void 
IcePack::ServiceHandler::startElement(const XMLCh *const name, ICE_XERCES_NS AttributeList &attrs)
{
    ComponentHandler::startElement(name, attrs);

    if(!isCurrentTargetDeployable())
    {
	return;
    }

    string str = toString(name);

    if(str == "service")
    {
	string basedir = getAttributeValueWithDefault(attrs, "basedir", "");
	if(!basedir.empty())
	{
	    _builder.overrideBaseDir(basedir);
	}

	string kind = getAttributeValue(attrs, "kind");
	if(kind == "standard")
	{
	    _builder.setKind(ServiceBuilder::ServiceKindStandard);
	}
	else if(kind == "freeze")
	{
	    _builder.setKind(ServiceBuilder::ServiceKindFreeze);
	    _builder.setDBEnv(getAttributeValueWithDefault(attrs, "dbenv", ""));
	}
	
	_builder.createConfigFile(_builder.substitute("/config/config_${name}"));
	_builder.setEntryPoint(getAttributeValue(attrs, "entry"));
    }
    else if(str == "adapter")
    {
	assert(!_currentAdapterId.empty());
	string adapterName = getAttributeValue(attrs, "name");
	_builder.getServerBuilder().registerAdapter(adapterName, getAttributeValue(attrs, "endpoints"), _currentAdapterId);
    }
}

IcePack::ServiceBuilder::ServiceBuilder(const NodeInfoPtr& nodeInfo,
					ServerBuilder& serverBuilder,
					const map<string, string>& variables,
					const vector<string>& targets) :
    ComponentBuilder(nodeInfo->getCommunicator(), variables, targets),
    _nodeInfo(nodeInfo),
    _serverBuilder(serverBuilder)
{
    assert(_variables.find("parent") != _variables.end());
    assert(_variables.find("name") != _variables.end());
    assert(_variables.find("fqn") != _variables.end());
    assert(_variables.find("datadir") != _variables.end());

    //
    // Required for the component builder.
    //
    _objectRegistry = _nodeInfo->getObjectRegistry();
}

void
IcePack::ServiceBuilder::parse(const string& descriptor)
{
    ServiceHandler handler(*this);

    ComponentBuilder::parse(descriptor, handler);
}

ServerBuilder&
IcePack::ServiceBuilder::getServerBuilder() const
{
    return _serverBuilder;
}

void
IcePack::ServiceBuilder::setKind(ServiceKind kind)
{
    _kind = kind;
}

void
IcePack::ServiceBuilder::setEntryPoint(const string& entry)
{
    assert(!_configFile.empty());
    _serverBuilder.addProperty("IceBox.Service." + _variables["name"], entry + " --Ice.Config=" + _configFile);
}

void
IcePack::ServiceBuilder::setDBEnv(const string& dir)
{
    if(_kind != ServiceKindFreeze)
    {
	throw DeploySAXParseException("database environment is only allowed for Freeze services", _locator);
    }

    string path;

    if(dir.empty())
    {
	//
	// Provides database environment directory only if the
	// database environment attribute is not specified. If it's
	// specified, it's most likely because we share database
	// environments and then it's the responsabilility of the user
	// to manage the database environment directory.
	//
	createDirectory("/dbs/" + _variables["name"], true);
	path = _variables["datadir"] + "/dbs/" + _variables["name"];
    }
    else
    {
	path = toLocation(dir);
    }
    _serverBuilder.addProperty("IceBox.DBEnvName." + _variables["name"], path);
}

//
// Compute an adapter id for a given adapter name.
//
string
IcePack::ServiceBuilder::getDefaultAdapterId(const string& name)
{
    //
    // Concatenate the server and service name to the adapter name.
    //
    return name + "-" + _variables["parent"] + "." + _variables["name"];
}
