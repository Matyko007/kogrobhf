#include <ros/ros.h>
#include <aruco_msgs/MarkerArray.h>
#include <gazebo_msgs/LinkStates.h>

// Global variables to store marker and state positions
double markerPositionx = 0.0;
double markerPositiony = 0.0;
double markerPositionz = 0.0;
double markerOrientationz=0.0;
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
    markerOrientationz = marker.pose.pose.orientation.z;
  }
  //ROS_INFO("Marker Position: x = %f, y = %f, z = %f, Oriz=%f", markerPositionx, markerPositiony, markerPositionz, markerOrientationz);
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
  //ROS_INFO("State Position: x = %f, y = %f, z = %f, Oriz = %f", statePositionx, statePositiony, statePositionz, stateOrientationz);
}

int main(int argc, char** argv)
{
  // Initialize the ROS node
  ros::init(argc, argv, "marker_subscriber");

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
  // Access marker position and state position in the main function
  
  ROS_INFO("Szög=%f",szog);
  }
  return 0;

  
}
