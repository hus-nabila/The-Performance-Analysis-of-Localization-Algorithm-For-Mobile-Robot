#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include <fstream> 

double poseGRNDx, poseGRNDy, poseGRNDa;
void poseGRNDCallback(const nav_msgs::Odometry::ConstPtr& msgGRND)
{
    poseGRNDx = msgGRND->pose.pose.position.x;
    poseGRNDy = msgGRND->pose.pose.position.y;
    poseGRNDa = msgGRND->pose.pose.orientation.w;   
    //ROS_INFO(msgGRND);
  
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "grnd_truth");
    ros::NodeHandle n;
    ros::Subscriber sub_amcl = n.subscribe("ground_truth/state", 100, poseGRNDCallback);
    ros::Rate loop_rate(10);
    ros::spinOnce();

    int counter, data;
    std::cin;
    counter = 0;

    std::ofstream groundPose ("ground_truth.txt"); //open file to read

    while (ros::ok())
    {

        geometry_msgs::Pose error;
        error.position.x = poseGRNDx;
        error.position.y = poseGRNDy;
        error.orientation.w = poseGRNDa;
	counter++;
        std::cout << counter << '\n';
        ROS_INFO("position.x=%f" , poseGRNDx);
    	ROS_INFO("position.y=%f" , poseGRNDy);
    	ROS_INFO("orientation.w=%f" , poseGRNDa);
	//pub.publish(error);
       groundPose << counter <<"\t\t"<< poseGRNDx <<"\t\t"<< poseGRNDy <<"\t\t"<< poseGRNDa <<"\n"; //write data to file
        ros::spinOnce();
        loop_rate.sleep();
    }
    groundPose.close();
    return 0;
}

