#include "WProgram.h"

#include "motorcontrol.h"
#include "pwm.h"
#include "robot.h"

#include <ros.h>

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>


ros::NodeHandle nh;

ROS_CALLBACK(cmd_vel_cb, geometry_msgs::Twist, cmd_vel)

	int theta_v = cmd_vel.angular.z* 13.1/2;
	int f_v = cmd_vel.linear.x *100;
	setLeftMotorSpeed(	f_v - theta_v);
	setRightMotorSpeed( f_v + theta_v);
}
ros::Subscriber sub_vel("cmd_vel", &cmd_vel, cmd_vel_cb);

nav_msgs::Odometry odom_msg;
ros::Publisher pub_odom("odom", &odom_msg);


void setup(){
	nh.initNode();
	nh.advertise(pub_odom);
	nh.subscribe(sub_vel);

	RobotInit();
	initEncoders();
	
setLeftMotorSpeed(0);
setRightMotorSpeed(0);

}

void updateOdom(int r_enc, int l_enc, nav_msgs::Odometry& odom ){

}

void adk_spin();
long odom_timer=0;
void loop(){

		if (odom_timer< millis()){
			updateOdom(Robot.leftWheel.encoder.count(),
					Robot.rightWheel.encoder.count(), odom_msg);
			pub_odom.publish( &odom_msg);
			odom_timer = millis() + 70;
		}

		nh.spinOnce();
		adk_spin();
}
