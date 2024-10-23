#include "GlobalConfiguration.h"
#include "boost/property_tree/ptree.hpp"
#include <boost/property_tree/xml_parser.hpp>

#include <exception>
#include <locale>

#include "../Log.h"

const static char* CONFIG_WIDTH = "Root.Width";
const static char* CONFIG_HEIGHT = "Root.Height";
const static char* CONFIG_DEPTH_BITS = "Root.DepthBits";
const static char* CONFIG_STENCIL_BITS = "Root.StencilBits";
const static char* CONFIG_GRAPHICSLIB_NAME = "Root.GraphicsLib.Name";
const static char* CONFIG_GRAPHICSLIB_MAJOR = "Root.GraphicsLib.MajorVersion";
const static char* CONFIG_GRAPHICSLIB_MINOR = "Root.GraphicsLib.MinorVersion";


namespace pt = boost::property_tree;

Configuration* Configuration::mSingleConfig = nullptr;

Configuration::Configuration()
	:mWidth(DEFAULT_WIDTH), 
	mHeight(DEFAULT_HEIGHT),
	mDepthBits(0),
	mStencilBits(0),
	mMajorVersion(0),
	mMinorVersion(0)
{
}

Configuration* Configuration::Get()
{
	if (mSingleConfig == nullptr)
	{
		mSingleConfig = new Configuration;
	}
	return mSingleConfig;
}

int Configuration::Load(const char* pathName)
{
	pt::ptree tree;
	try
	{
		read_xml(pathName, tree);
		mWidth = tree.get<int>(CONFIG_WIDTH);
		mHeight = tree.get<int>(CONFIG_HEIGHT);
		mDepthBits = tree.get<int>(CONFIG_DEPTH_BITS);
		mStencilBits = tree.get<int>(CONFIG_STENCIL_BITS);
		mGraphicsLibName = tree.get<std::string>(CONFIG_GRAPHICSLIB_NAME);
		mMajorVersion = tree.get<int>(CONFIG_GRAPHICSLIB_MAJOR);
		mMinorVersion = tree.get<int>(CONFIG_GRAPHICSLIB_MINOR);
	}
	catch (const std::exception& e)
	{
		Logger::LogError(e.what());
	}
	
	return 0;
}

int Configuration::Save(const char* pathName)
{
	pt::ptree tree;
	try
	{
		tree.put<int>(CONFIG_WIDTH, mWidth);
		tree.put<int>(CONFIG_HEIGHT, mHeight);

		write_xml(pathName, tree);
	}
	catch (const std::exception& e)
	{
		Logger::LogError(e.what());
	}
	return 0;
}
