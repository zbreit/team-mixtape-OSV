#ifndef NAVIGATOR
#define NAVIGATOR

class Navigator {
private:
  static Navigator* instance;
  DriveTrain* driveTrain;
  void driveToMiddleLane();
  void driveOverRockyTerrain();
  void driveToLane(Lane newLane);
  void reachMissionSiteX();
  void swapLanes();
  void driveToNextLane();
  bool obstaclesStillInTheWay();
  void turnUntilOpening();
  void goTheDistance();
  Navigator();
  Lane lane;
public:
  void navigate();
  static Navigator* getInstance();
};

#endif
