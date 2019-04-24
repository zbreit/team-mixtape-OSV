#ifndef NAVIGATOR
#define NAVIGATOR

class Navigator {
private:
  static Navigator* instance;
  DriveTrain* driveTrain;
  ExtinguishingArm* extinguishingArm;
  Lane lane;

  // Navigating to Mission Site
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
public:
  void navigate();
  void countAndExtinguishFlames();
  static Navigator* getInstance();
};

#endif
