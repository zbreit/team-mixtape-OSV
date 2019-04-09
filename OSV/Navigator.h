#ifndef NAVIGATOR
#define NAVIGATOR

class Navigator {
private:
  static Navigator* instance;
  DriveTrain* driveTrain;
  void driveOverRockyTerrain();
  void verticallyAlignToMissionSite();
  Direction chooseDirectionOfTravel();
  void shiftInDirectionOfTravel(Direction direction);
  boolean findPathToMissionSite();
  void driveToMissionSite();
  Navigator();
public:
  void navigate();
  static Navigator* getInstance();
};

#endif
