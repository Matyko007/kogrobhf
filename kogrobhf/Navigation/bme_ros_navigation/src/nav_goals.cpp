#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "ros/ros.h"
#include "tf/tf.h"
#include <aruco_msgs/MarkerArray.h>
#include <gazebo_msgs/LinkStates.h>

double markerPositionx = 0.0;
double markerPositiony = 0.0;
double markerPositionz = 0.0;
double markerOrientationx=0.0;
double markerOrientationy=0.0;
double markerOrientationz=0.0;
double markerOrientationw=0.0;
double statePositionx = 0.0;
double statePositiony = 0.0;
double statePositionz = 0.0;
double stateOrientationz = 0.0;
double x=0.0;
double y=0.0;


bool markerPositionUpdated = false;



// Callback function to handle incoming marker array messages
void markerCallback(const aruco_msgs::MarkerArray::ConstPtr& msg)
{
  // Process the received marker array
  for (const auto& marker : msg->markers)
  {
    // Access individual markers using 'marker' variable
    // Example: Store the position of the first marker
    markerPositionx = marker.pose.pose.position.x;
    markerPositiony = marker.pose.pose.position.y;
    markerPositionz = marker.pose.pose.position.z;
    markerOrientationz = marker.pose.pose.orientation.x;
    markerOrientationz = marker.pose.pose.orientation.y;
    markerOrientationz = marker.pose.pose.orientation.z;
    markerOrientationz = marker.pose.pose.orientation.w;
  }
  ROS_INFO("Marker Position: x = %f, y = %f, z = %f, Oriz=%f", markerPositionx, markerPositiony, markerPositionz, markerOrientationz);
  // Set the marker position updated flag to true
  markerPositionUpdated = true;
}

// Callback function to handle incoming state array messages
void stateCallback(const gazebo_msgs::LinkStates::ConstPtr& msg)
{
  // Store the position of the desired state (e.g., index 26)
  statePositionx = msg->pose[26].position.x;
  statePositiony = msg->pose[26].position.y;
  statePositionz = msg->pose[26].position.z;
  stateOrientationz = msg->pose[26].orientation.z;

  // Print the updated state position
  ROS_INFO("State Position: x = %f, y = %f, z = %f, Oriz = %f", statePositionx, statePositiony, statePositionz, stateOrientationz);
}



// Define a client for to send goal requests to the move_base server through a
// SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>
    MoveBaseClient;

int main(int argc, char **argv) {
  // Initialize the nav_goals node
  ros::init(argc, argv, "nav_goals");

    // Create a ROS node handle
  ros::NodeHandle nh;


  // Create a subscriber object for marker array
  ros::Subscriber markersub = nh.subscribe("/aruco_marker_publisher/markers", 100, markerCallback);
  ros::Subscriber statesub = nh.subscribe("/gazebo/link_states", 100, stateCallback);

  while (!markerPositionUpdated && ros::ok())
  {
    ros::spinOnce();
  }




  if (markerPositionUpdated==true){

  double o = std::sqrt(std::pow(markerPositionx - statePositionx, 2) + std::pow(markerPositiony - statePositiony, 2));
  x=(markerPositionx-statePositionx)/o;
  y=(markerPositiony-statePositiony)/o;
  double szog=std::atan2(y,x);

  // tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while (!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a list of positions and orientations for the robot to reach
  double waypoints[3] = {markerPositionx, markerPositiony, szog};
 


    goal.target_pose.pose.position.x = waypoints[0];
    goal.target_pose.pose.position.y = waypoints[1];
    goal.target_pose.pose.orientation =
        tf::createQuaternionMsgFromYaw(waypoints[2]);

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Goal reached!");
    else
      ROS_INFO("Failed to reach goal for some reason");
    // Wait 1 second before moving to the next goal
    ros::Duration(1.0).sleep();
  
}
  return 0;
}