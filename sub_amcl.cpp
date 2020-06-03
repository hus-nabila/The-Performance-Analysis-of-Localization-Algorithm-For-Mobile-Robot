#include "ros/ros.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <fstream> 

double poseAMCLx, poseAMCLy, poseAMCLa;
void poseAMCLCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msgAMCL)
{
    poseAMCLx = msgAMCL->pose.pose.position.x;
    poseAMCLy = msgAMCL->pose.pose.position.y;
    poseAMCLa = msgAMCL->pose.pose.orientation.w;   
    //ROS_INFO(msgAMCL);
  
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "amcl_pose");
    ros::NodeHandle n;
    ros::Subscriber sub_amcl = n.subscribe("amcl_pose", 100, poseAMCLCallback);
    ros::Rate loop_rate(10);
    ros::spinOnce();

    int counter, data;
    std::cin;
    counter = 0;

    std::ofstream amclPose ("amcl_pose.txt"); //open file to read

    while (ros::ok())
    {

        geometry_msgs::Pose error;
        error.position.x = poseAMCLx;
        error.position.y = poseAMCLy;
        error.orientation.w = poseAMCLa;
	counter++;
        std::cout << counter << '\n';
        ROS_INFO("position.x=%f" , poseAMCLx);
    	ROS_INFO("position.y=%f" , poseAMCLy);
    	ROS_INFO("orientation.w=%f" , poseAMCLa);
	//pub.publish(error);
       amclPose << counter <<"\t\t"<< poseAMCLx <<"\t\t"<< poseAMCLy <<"\t\t"<< poseAMCLa <<"\n"; //write data to file
        ros::spinOnce();
        loop_rate.sleep();
    }
    amclPose.close();
    return 0;
}

