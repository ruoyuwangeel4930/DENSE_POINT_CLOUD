# include "pcloudcreator.h"

using namespace std;

int main(int argc, char** argv)
{
	CameraTrackReader ctr(argv[1]);
	AssociationReader ar(argv[2]);
	CameraReader cr(argv[3]);

	KeyFrameParameters kfp;
	string depthTimeStamp;
	CameraParameters cp;

	cr.get_camera(cp);
	cout << "cx: " << cp.cx << " cy: " << cp.cy 
		 << " fx: " << cp.fx << " fy: " << cp.fy <<" scale: " << cp.scale << endl;

	for (size_t i = 0; i < ctr.data_size(); i++)
	{
		ctr.get_frame(i, kfp);
		ar.get_depth_timestamp(kfp.timeStamp, depthTimeStamp);
		
		
		cout <<"frame: " << i <<" "<<kfp.timeStamp<<" "
    				 			   <<kfp.x_c<<" "
    				               <<kfp.y_c<<" "
    				               <<kfp.z_c<<" "
    				               <<kfp.x<<" "
    				               <<kfp.y<<" "
    				               <<kfp.z<<" "
    				               <<kfp.w<<" " << endl;

		cout << "rgb: " << kfp.timeStamp << ".png "
			 << "depth: " << depthTimeStamp << ".png" << endl;

		

    }

	return 0;
}