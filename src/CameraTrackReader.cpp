#include "pcloudcreator.h" 
#include <boost/algorithm/string.hpp>

using namespace std;

CameraTrackReader::CameraTrackReader(const string& fileName)
{
	CameraTrackReader::data = new vector<KeyFrameParameters>;

	ifstream fin(fileName.c_str());

	if (!fin)
	{
		cerr << "Camera trajectory file does not exist." << endl;
		return;
	}

	cout << "Trajectory loaded..." << endl; 

	string str;
	vector<string> params;
	KeyFrameParameters kfp;

	while(fin.peek() != EOF)
	{
		getline(fin, str);
		boost::split(params, str, boost::is_any_of("\t "));

		//assign values
		kfp.timeStamp = params[0];
		kfp.x_c = atof(params[1].c_str());
    	kfp.y_c = atof(params[2].c_str());
    	kfp.z_c = atof(params[3].c_str());
    	kfp.x = atof(params[4].c_str());
    	kfp.y = atof(params[5].c_str());
    	kfp.z = atof(params[6].c_str());
    	kfp.w = atof(params[7].c_str());		

    	CameraTrackReader::data->push_back(kfp); 
	}

	fin.close();

	cout << "Key frames loaded..." << endl;
}

CameraTrackReader::~CameraTrackReader()
{
	delete CameraTrackReader::data; 
}

void::CameraTrackReader::get_frame(const int i, KeyFrameParameters& kfp)
{
	kfp = (*CameraTrackReader::data)[i];

	return;
}

int::CameraTrackReader::data_size()
{
	return CameraTrackReader::data->size();
}


