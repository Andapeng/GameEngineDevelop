#include "GlobalConfiguration.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <exception>
#include <locale>

#include "../Log.h"

namespace pt = boost::property_tree;

Configuration* Configuration::mSingleConfig = nullptr;

Configuration::Configuration()
	:mWidth(DEFAULT_WIDTH), 
	mHeight(DEFAULT_HEIGHT)
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
		mWidth = tree.get<int>("root.width");
		mHeight = tree.get<int>("root.height");
		mDepthBits = tree.get<int>("root.depthBits");
		mStencilBits = tree.get<int>("root.stencilBits");
		mMajorVersion = tree.get<int>("root.graphicsLib.majorVersion");
		mMinorVersion = tree.get<int>("root.graphicsLib.minorVersion");
	}
	catch (const std::exception& e)
	{
		BOOST_LOG_TRIVIAL(error) << e.what();
	}
	
	return 0;
}

int Configuration::Save(const char* pathName)
{
	pt::ptree tree;
	try
	{
		tree.put<int>("root.width", mWidth);
		tree.put<int>("root.height", mHeight);

		write_xml(pathName, tree);
	}
	catch (const std::exception& e)
	{
		BOOST_LOG_TRIVIAL(error) << e.what();
	}
	return 0;
}
