#include "pcloudcreator.h" 
#include <boost/algorithm/string.hpp>

using namespace std;

AssociationReader::AssociationReader(string fileName)
{
	AssociationReader::ptrRGB2DepthMap = new map<string, string>; 

	ifstream fin(fileName.c_str());

	if(!fin)
	{
		cerr << "Association file does not exist." << endl;
		return;
	}

	string str;
	vector<string> timeStamps;

	while(fin.peek() != EOF)
	{
		getline(fin, str);
		boost::split(timeStamps, str, boost::is_any_of("\t "));
		(*AssociationReader::ptrRGB2DepthMap)[timeStamps[0]] = timeStamps[2]; 
		//cout << timeStamps[0] << " " << (*AssociationReader::ptrRGB2DepthMap)[timeStamps[0]] << endl;
	}

	fin.close();
}

AssociationReader::~AssociationReader()
{
	delete AssociationReader::ptrRGB2DepthMap;
}

void::AssociationReader::get_depth_timestamp(const string& rgbTimeStamp, string& depthTimeStamp)
{
	depthTimeStamp = (*AssociationReader::ptrRGB2DepthMap)[rgbTimeStamp];

	return; 
}