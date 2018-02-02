#include "pcloudcreator.h" 
#include <boost/algorithm/string.hpp>

using namespace std;

CameraReader::CameraReader(const string& fileName)
{
	CameraReader::camParams = new map<string, string>;

	ifstream fin(fileName.c_str());

	if(!fin)
	{
		cerr << "Camera file does not exist." << endl;
		return;
	}

	string str;
	vector<string> params;

	while(fin.peek() != EOF)
	{
		getline(fin, str);
		//cout << str << endl;
		if (str[0] == '#' || str[0] == '%' || str == "")
			continue;
		//cout << str << endl;
		boost::split(params, str, boost::is_any_of(":"));
		boost::trim(params[0]);
		boost::trim(params[1]);
		(*CameraReader::camParams)[params[0]] = params[1];

		//cout << params[0] << " " << params[1] << endl;
	}

	fin.close();

	cout << "Camera file loaded..." << endl;
}

CameraReader::~CameraReader()
{
	delete CameraReader::camParams;
}

double::CameraReader::get_data(const string& paramName)
{
	return atof((*CameraReader::camParams)[paramName].c_str());
}

void::CameraReader::get_camera(CameraParameters& cp)
{
	cp.cx = CameraReader::get_data("Camera.cx");
	cp.cy = CameraReader::get_data("Camera.cy");
	cp.fx = CameraReader::get_data("Camera.fx");
	cp.fy = CameraReader::get_data("Camera.fy");
	cp.scale = CameraReader::get_data("DepthMapFactor");
}