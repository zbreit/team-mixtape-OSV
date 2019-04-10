#ifndef OSV_MANAGER
#define OSV_MANAGER

class LocationManager {
private:
  LocationManager() {}
  static Coordinate* MISSION_LOCATION;
  static const NewPing frontRightSensor;
  static const SharpDistSensor frontLeftSensor;
  static void waitForLocationUpdate();
  static Coordinate* getMissionLocation();
public:

  // OSV Vision system info
  static Coordinate getCurrentLocation();
  static double getX();
  static double getY();
  static double getHeading();
  static double getFrontX();
  static double getTopY();
  static double getBottomY();
  static double getBackY();
  static double getBackX();
  static double getSideX();

  // OSV Sensor Info
  static double getFrontRightDistance();
  static double getFrontLeftDistance();
  static bool obstaclesBlockingTheFront();
  static bool obstaclesBlockingTheFrontLeft();
  static bool obstaclesBlockingTheFrontRight();

  // Mission information
  static double getMissionX();
  static double getMissionY();
  static double getMissionCenterX();
  static double getMissionCenterY();
  static double getMissionBottomY();
  static double getMissionBackX();
};

#endif
