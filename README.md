# team-mixtape-OSV
The codebase for ENES100 Team MIXTAPE's OSV

## How to Navigate the Codebase
All of the OSV logic is stored in the `OSV/` directory. The `OSVSimulation/` directory stores a version of the code that was converted using the [ENES100SimulationTranslator](https://github.com/zbreit/ENES100SimulationTranslator). The code is structured as follows:
 - All `*.h` files provide forward declarations for functions and classes
 - **Convenience Classes**
   - `Constants`: Stores all configuration info (e.g., pin mappings, PID constants, OSV dimensions)
   - `LocationManager`: Has static methods to determine the location of the OSV in relation to the field and the obstacles
   - `utils`: Has convenience methods for various math and angle calculations
 - **Components**
   - `FlameSensor`: Wrapper class for the IR flame sensor. Uses median filtering of the results
   - `DCMotor`: Wrapper class to control motors on the Arduino Romeo. Provides methods to reverse motor polarity, set min and max output. 
 - **Subsystems** 
   - `DriveTrain`: Provides high-level control for the OSV's locomotion
   - `ExtinguishingArm`: Provides high-level control of the OSV's arm. 
   - `Navigator`: Contains all obstacle and mission navigation functionality
