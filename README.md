# kogrobhf

![4](https://github.com/Matyko007/kogrobhf/assets/130318497/fc42a5fe-1f12-48d2-a770-7315f21bc9a8)

Az AR tag olvasóhoz töltsétek le ezt az aruco_ros packaget:

https://github.com/pal-robotics/aruco_ros
Majd a saját repo-n lévő Aruco mappából másoljátok át a launch és src fájlokat felülírva az aruco_ros/aruco_ros/src és launch alatt található fájlokat. 

Használata:
Elsőként a turtlebot kameráját vízszintesbe kell tenni. Ezt a robot .xacro fájljának módosításával lehet megtenni. Valahol a camera leírásánál van egy rpy = kettő nulla meg egy 45 fok radban nagyságrendű szám, azt is nullára kell írni.

A navigációs csomagokhoz töltsétek le a tárgyhoz tartozó git repot:

https://github.com/MOGI-ROS/Week-7-8-Navigation.git
![1](https://github.com/Matyko007/kogrobhf/assets/130318497/14688f53-f0a0-4bcf-bf24-f339c107f5ec)
Szintént be kell másolni a saját repo-ból a launch és az src fileokat a most leklónozott repó megfelelő helyire.

ezeket felrakni:
sudo apt install ros-$(rosversion -d)-hector-slam 

sudo apt install ros-$(rosversion -d)-map-server

sudo apt install ros-$(rosversion -d)-amcl

sudo apt install ros-$(rosversion -d)-interactive-marker-twist-server


![2](https://github.com/Matyko007/kogrobhf/assets/130318497/0b4f8c72-d42a-4ab9-99b4-6a02226e8aeb)

1. roslaunch bme_ros_navigation spawn_robot.launch
2. roslaunch bme_ros_navigation navigation.launch
3. roslaunch aruco_ros marker_publisher.launch indítása
4. teleop-pal a kicsit megmozgatni a robotot, hogy megtalálja magát a térképen
5. helyezzünk egy kockát a robot látóterébe
        Megj.: -Megjelenítés: Rviz-ben katt arra, hogy add és utána topic alapján hozzá tudod adni az imaget aruco_marker_publisher/result/image/raw
               -Ha nem akarja felismerni, vagy néha igen-néha nem, akkor egy fényt kell berakni gazeboba, hogy kontrasztosabb legyen az ar tag
6.roslaunch bme_ros_navigation manual_waypoints.launch

A node újraindításával újra ás újra navigálhatjuk a robotot egy másik tag-re.

Navigáció működése:
    A marker_publisher.launch file-ban megadjuk a kocka méretét (0.1 [m]) Fontos, hogy ezt a méretet fogja használni és úgy fogja arányosítani a távolságot a látott mérethez képest.

    Az src mappában lévő adat.cpp filet rosrun bme_ros_navigation hajra-val tudjuk elindítani, ez felsubscribolodik a marker pozició és a robot "középpontjának" a pozíciójára, így ezekkel az értékeket emg tudjuk jelenítni.
    Illetve a nav_goals.cpp-ben is jutunk hozzá az adatokhoz.
    A marker pozícióját a globális koordináta rendszerhez képes mondjuk meg, így ezz egy az egyben odaadjuk a nav_goals.cpp-nek. Illetve a szöget úgy számoljuk ki, hogy a markerbe és a robotba mutató helyvektorokat kivonjuk egymásból. És ennek a vektornak a szögét használjuk a markerre történő ráállásra. Vagyis a robotból a markerre mutató vektor irányával (globális szempontból)

    Ahhoz, hogy ne ütközzünk össze a kockával, valahogy meg kellen mondanunk, hogy az adott irányban mennyivel csökkentsük vagy éppen növeljuk az x,y koordinátákat. Ehelyett a maker_publsiher.launch-ban megadott értéket kisebbre vesszük. Így mindig kicsit nagyobbnak, vagyis közelebbinek fogja látni a taget a kamera. És így továbbra is használhatjuk az x,y koordinátákat egyyszerűen.

AR tag generátor:

https://chev.me/arucogen/



