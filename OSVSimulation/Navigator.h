#ifndef NAVIGATOR
#define NAVIGATOR

class Navigator {
private:
  static Navigator* instance;
  DriveTrain* driveTrain;
  void driveOverRockyTerrain();
  boolean findPathToMissionSite();
  Navigator();
public:
  void navigate();
  static Navigator* getInstance();
};

#endif
