# kogrobhf

Az AR tag olvasóhoz töltsétek le ezt az aruco_ros packaget:

https://github.com/pal-robotics/aruco_ros

Majd az ezen a repo-n lévő Aruco mappából másoljátok át a launch és src fájlokat felülírva az aruco_ros/aruco_ros/src vagy launch alatt található fájlokat. 

Használata:
1. Gazebos szimuláció indít
2. Rviz indít
3. roslaunch aruco_ros marker_publisher.launch indítása
4. Megjelenítés: Rviz-ban katt arra, hogy add és utána topic alapján hozzá tudod adni az aruco_ros/result imaget
5. Koordiníták: rqr-ben az aruco_ros/markers alatt jönnek szépen az éppen látott ar tagek koordinátái
6. Ha nem akarja felismerni, vagy néha igen-néha nem, akkor egy fényt kell berakni gazeboba, hogy kontrasztosabb legyen az ar tag

AR tag generátor:

https://chev.me/arucogen/

MOGI-s projekt:

https://github.com/dudasdavid/mogi_chess_ros_framework/blob/main/mogi_chess_vision/scripts/aruco_detector.py
