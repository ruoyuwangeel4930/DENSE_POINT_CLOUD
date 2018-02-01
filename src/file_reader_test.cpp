# include "pcloudcreator.h"

using namespace std;

int main(int argc, char** argv)
{
	static CameraTrackReader ctr(argv[1]);

	KeyFrameParameters kfp;

	int i = 1;

	while(ctr.fin->peek() != EOF)		
	{
		cout << i << " " << ctr.fin->eof() << " ";
		ctr.getframe(kfp);
		i++;
	}

	ctr.clear();

	return 0;
}