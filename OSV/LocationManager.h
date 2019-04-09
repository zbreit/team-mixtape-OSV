#ifndef OSV_MANAGER
#define OSV_MANAGER

class LocationManager {
private:
  LocationManager() {}
  static Coordinate* MISSION_LOCATION;
  static const NewPing sideDistanceSensor;
  static const SharpDistSensor frontDistanceSensor;
  static void waitForLocationUpdate();
  static Coordinate* getMissionLocation();
public:

  // OSV Vision system info
  static Coordinate getCurrentLocation();
  static double getX();
  static double getY();
  static double getHeading();
  static double getFrontX();
  static double getFrontY();
  static double getBackY();
  static double getBackX();
  static double getSideX();

  // OSV Sensor Info
  static double getFrontDistance();
  static double getSideDistance();
  static bool obstaclesAreBlockingTheRight();
  static bool obstaclesAreBlockingTheFront(double distanceToMissionSite);
  static bool cantMoveInDirectionOfTravel(Direction direction);

  // Mission information
  static double getMissionX();
  static double getMissionY();
  static double getMissionCenterX();
  static double getMissionCenterY();
  static double getMissionBottomY();
  static double getMissionBackX();
};

#endif
