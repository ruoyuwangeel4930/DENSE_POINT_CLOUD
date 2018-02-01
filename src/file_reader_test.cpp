# include "pcloudcreator.h"

using namespace std;

int main(int argc, char** argv)
{
	static CameraTrackReader ctr(argv[1]);

	KeyFrameParameters kfp;

	for (size_t i = 0; i < ctr.data_size(); i++)
	{
		ctr.get_frame(i, kfp);
		
		cout <<"frame: " << i <<" "<<kfp.timeStamp<<" "
    				 			   <<kfp.x_c<<" "
    				               <<kfp.y_c<<" "
    				               <<kfp.z_c<<" "
    				               <<kfp.x<<" "
    				               <<kfp.y<<" "
    				               <<kfp.z<<" "
    				               <<kfp.w<<" " << endl;

    }

	return 0;
}