# include "pcloudcreator.h"

using namespace std;

int main(int argc, char** argv)
{
	static CameraTrackReader ctr(argv[1]);
	static AssociationReader ar(argv[2]);

	KeyFrameParameters kfp;
	string depthTimeStamp;

	for (size_t i = 0; i < ctr.data_size(); i++)
	{
		ctr.get_frame(i, kfp);
		ar.get_depth_timestamp(kfp.timeStamp, depthTimeStamp);
		cout << "rgb: " << kfp.timeStamp << ".png "
			 << "depth: " << depthTimeStamp << ".png" << endl;
		
		/*cout <<"frame: " << i <<" "<<kfp.timeStamp<<" "
    				 			   <<kfp.x_c<<" "
    				               <<kfp.y_c<<" "
    				               <<kfp.z_c<<" "
    				               <<kfp.x<<" "
    				               <<kfp.y<<" "
    				               <<kfp.z<<" "
    				               <<kfp.w<<" " << endl;*/

    }

	return 0;
}