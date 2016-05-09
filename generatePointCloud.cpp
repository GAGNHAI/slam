// C++ standard library
#include <iostream>
#include <string>
using namespace std;

// OpenCV library
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// PCL library
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>


// Define ponit cloud type
typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;

// Camera interior orientation parameter
const double camera_factor = 1000;
const double camera_cx = 325.5;
const double camera_cy = 253.3;
const double camera_fx = 518.0;
const double camera_fy = 519.0;

// Main function
int main( int argc, char** argv )
{
	// Read ./data/rgb.png and ./data/depth.png
	// , and transform them to point cloud

	// Image matrix
	cv::Mat rgb,depth;
	rgb = cv::imread(".data/rgb.png");
	// rgb is a colorful image of 8UC3
	// depth is a image of single channel 
	depth = cv::imread(".data/depth.png", -1);

	// point cloud variable
	// use intelligent pointer to create an empty ponit cloud
	PointCloud::Ptr cloud ( new PointCloud );
	// Traverse depth image
	for ( int m = 0; m < depth.rows: m++)
		for ( int n = 0; n < depth.cols; n++)
		{
			ushort d = depth.ptr<ushort>(m)[n];
			if (d == 0)
				continue;
			PonitT p;
			
			p.z = double(d) /camera_factor;
			p.x = (n - camera_cx) * p.z / camera_fx;
			p.y = (m - camera_cy) * p.z / camera_fy;
			
			p.b = rgb.ptr<uchar>(m)[n*3];
			p.g = rgb.ptr<uchar>(m)[n*3+1];
			p.r = rgb.ptr<uchar>(m)[n(3+2];
			
			cloud->points.push_back( p );

		}
	// Setting and save point cloud
	cloud->height = 1;
	cloud->width = cloud->points.size();
	cout << "point cloud size = " << cloud->points.size() << endl;
	cloud->is_dense = false;
	pcl::io::savePCDFile( "./data/pointcloud.pcd", *cloud );

	cloud->ponits.clear();
	cout << "Point cloud saved." << endl;
	return 0;
}






