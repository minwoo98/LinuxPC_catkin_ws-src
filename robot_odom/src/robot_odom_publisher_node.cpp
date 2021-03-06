#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Imu.h>

#define pi 3.1415926536
#define pulse 26
#define R 120 //2PI*r
#define dec 71

double encoder_pulse = 0.0;
//double plpha_enc=aaa; 
double ang_vel = 0;

//Subscribe encoder pulse : topic name -> "/encoder_pulse"
void encoder_pulsecallback(const std_msgs::Float64::ConstPtr& msg)
{
  encoder_pulse = msg->data;
	//ROS_INFO("Encoder pulse: %.3lf", encoder_pulse);
}

//Subscribe imu topic -> topic name -> "/imu/data"
void imu_callback(const sensor_msgs::Imu& msg)
{
	ang_vel = msg.angular_velocity.z;
	//ROS_INFO("IMU ang_vel: %.3lf", ang_vel);
}
////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_odom_publisher");

  ros::NodeHandle n;
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 10);
  tf::TransformBroadcaster odom_broadcaster;

	//subscriber 
	ros::Subscriber encoder_sub;
	ros::Subscriber imu_sub;

  double x = 0.0;
  double y = 0.0;
  double th = 0.0;

  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  ros::Rate r(20.0); //rate 20?
  while(n.ok()){

    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();

    encoder_sub = n.subscribe("/encoder_pulse", 10, encoder_pulsecallback);
    imu_sub = n.subscribe("/imu/data", 20, imu_callback);

    double vx =(56.4*encoder_pulse * pi * R) / (300*pulse * dec );
    if(ang_vel>-0.045&&ang_vel<0.045)
	    ang_vel=0;
    double vth = ang_vel;

    //compute odometry in a typical way given the velocities of the robot
    double dt = (current_time - last_time).toSec();
    double delta_x = vx * cos(th) * dt;
    double delta_y = vx * sin(th) * dt;
    double delta_th = vth * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";
		odom.child_frame_id = "base_link";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = 0;
    odom.twist.twist.angular.z = vth;

    //publish the message
    odom_pub.publish(odom);

    last_time = current_time;
    r.sleep();
  }
}
