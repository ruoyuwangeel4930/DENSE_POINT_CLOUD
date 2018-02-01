#include "pcloudcreator.h" 
#include <boost/algorithm/string.hpp>

using namespace std;

string match_depth()
{
	
}

CameraTrackReader::CameraTrackReader(string fileName)
{
	CameraTrackReader::fin = new ifstream(fileName.c_str());

	if (!*(CameraTrackReader::fin))
	{
		cerr << "Camera trajectory file does not exist." << endl;
		return;
	}

	cout << "Trajectory loaded..." << endl; 
}

void::CameraTrackReader::getframe(KeyFrameParameters& kfp)
{

	string str;
	getline(*(CameraTrackReader::fin), str);

	vector<string> params;
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

    cout <<"frame: " <<kfp.timeStamp<<" "
    				 <<kfp.x_c<<" "
    				 <<kfp.y_c<<" "
    				 <<kfp.z_c<<" "
    				 <<kfp.x<<" "
    				 <<kfp.y<<" "
    				 <<kfp.z<<" "
    				 <<kfp.w<<" " << endl;


    return;
}

void::CameraTrackReader::clear()
{
	CameraTrackReader::fin->close();
	delete CameraTrackReader::fin;
}


