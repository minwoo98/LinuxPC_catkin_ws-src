#include "ros/ros.h"
#include "ros_tutorials_service/SrvTutorial.h"

bool calculation(ros_tutorials_service::SrvTutorial::Request &req, ros_tutorials_service::SrvTutorial::Response &res)
{
	res.result = req.a + req.b;

	ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
	ROS_INFO("sending back response: %ld", (long int)res.result);

	return true;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "service_server");
	ros::NodeHandle nh;

	ros::ServiceServer ros_tutorials_service_server = nh.advertiseService("ros_tutorial_srv", calculation);

	ROS_INFO("ready srv server!");

	ros::spin();

	return 0;
}

