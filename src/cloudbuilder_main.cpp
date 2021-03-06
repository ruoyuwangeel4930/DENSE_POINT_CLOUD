#include <iostream>
#include <pcl/io/pcd_io.h>
#include <cloudbuilder.h>

using namespace std;

int main(int argc, char** argv)
{
    float near = atof(argv[4]);
    float far = atof(argv[5]);
    float leaf_sz = atof(argv[6]);
    int start = atoi(argv[7]);
    int end = atoi(argv[8]);
    int step = atoi(argv[9]);

    dec::PointCloud::Ptr cloud(new dec::PointCloud); 
    
    dec::CloudBuilder cbr = dec::CloudBuilder(argv[1], argv[2], argv[3]);
    cloud = cbr.buildPointCloud(near, far, leaf_sz, start, end, step);
    pcl::io::savePCDFileASCII ("dense_map.pcd", *cloud);
    cout << "dense_map.pcd has been saved." << endl;

    return 0;
}