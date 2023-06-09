# kogrobhf

Az AR tag olvasóhoz töltsétek le ezt az aruco_ros packaget:

https://github.com/pal-robotics/aruco_ros
Majd a saját repo-n lévő Aruco mappából másoljátok át a launch és src fájlokat felülírva az aruco_ros/aruco_ros/src és launch alatt található fájlokat. 

Használata:
Elsőként a turtlebot kameráját vízszintesbe kell tenni. Ezt a robot .xacro fájljának módosításával lehet megtenni. Valahol a camera leírásánál van egy rpy = kettő nulla meg egy 45 fok radban nagyságrendű szám, azt is nullára kell írni.

A navigációs csomagokhoz töltsétek le a tárgyhoz tartozó git repot:

https://github.com/MOGI-ROS/Week-7-8-Navigation.git
Szintént be kell másolni a saját repo-ból a launch és az src fileokat a most leklónozott repó megfelelő helyire.

1. roslaunch bme_ros_navigation spawn_robot.launch
2. roslaunch bme_ros_navigation navigation.launch
3. roslaunch aruco_ros marker_publisher.launch indítása
4. teleop-pal a kicsit megmozgatni a robotot, hogy megtalálja magát a térképen
5. helyezzünk egy kockát a robot látóterébe
        Megj.: -Megjelenítés: Rviz-ben katt arra, hogy add és utána topic alapján hozzá tudod adni az imaget aruco_marker_publisher/result/image/raw
               -Ha nem akarja felismerni, vagy néha igen-néha nem, akkor egy fényt kell berakni gazeboba, hogy kontrasztosabb legyen az ar tag
6.roslaunch bme_ros_navigation manual_waypoints.launch

a node újraindításáva

AR tag generátor:

https://chev.me/arucogen/



