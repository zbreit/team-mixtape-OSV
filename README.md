# team-mixtape-OSV
The codebase for ENES100 Team MIXTAPE's OSV

<p align="center"><img src="https://lh3.googleusercontent.com/Zvy0KismkjdYq5NxZCebk695uwi78ch-qY_RL0E0SpeDktxlkBek-DUeJtqyKnHdDh7ceB8FKBmc8U9Hhxd4u09B8hF0LD1lyOmtKrKgDWdTPyaFmEJxyf86THO6bB6HZrZhD7gkCW1uFrYM7X7eB6_69hrorsaerkcFYq8qfEkpYX_aKk4dNZn-vnGLuXu3hYpJ19MTwUoTE2rfZEl6g4Ny2G-Myd66JbxOt8gaumLgLUAMHp6e2Q5iLk-PZliGnNk1_gmyU8Js_f1fHRYUI9WtwJnfw5iE9v7En2R9Qph9cJEUOIF14qpgcj4PQhpqZoF515ep5Q5ZzjYXBZwVNxV2cWE8RLA5qFZ2t1ifBc9ULnFzDG0uV-n7uPFvLOdqT1DyOW6I_ZV-6iqYSUfdfPBJHX3PoCR84t4xBTXPhy4Y-Qee2urgLAmWPBFzmUT0o6TuFFqFSScZBt84n8o3QTlwVuk-8AKzuBpBHE9ZaSfH96aMG07_90iUqloDgbI6CczEbYrbmvy3omG804HBE_RaYaEko4bxwTnlCsoLBcKFbLZEgIRV1f4qco_F1Kv5d6cmiNLuaWk2kZUPNzg_Q5BVZUtCCiT0tZppu4M=w1920-h910" alt="Our OSV" height="500"/></p>

## How to Navigate the Codebase
All of the OSV logic is stored in the `OSV/` directory. The `OSVSimulation/` directory stores a version of the code that is compatible with the ENES100Simulator. The code was converted using the [ENES100SimulationTranslator](https://github.com/zbreit/ENES100SimulationTranslator). The code is structured as follows:
 - All `*.h` files provide forward declarations for functions and classes
 - **Convenience Classes**
   - `Constants`: Stores all configuration info (e.g., pin mappings, PID constants, OSV dimensions)
   - `LocationManager`: Has static methods to determine the location of the OSV in relation to the field and the obstacles
   - `utils`: Has convenience methods for various math and angle calculations
 - **Components**
   - `FlameSensor`: Wrapper class for the IR flame sensor. Uses median filtering of the results
   - `DCMotor`: Wrapper class to control motors on the [LM298N](https://diygeeks.org/shop/breakout-modules/lm298-motor-driver-breakout/). Provides configurations to reverse a motor's polarity and to set min and max output. 
 - **Subsystems** 
   - `DriveTrain`: Provides high-level control for the OSV's locomotion
   - `ExtinguishingArm`: Provides high-level control of the OSV extinguisher
   - `Navigator`: Contains all obstacle and mission navigation functionality
 - **The Important File**
   - `OSV.ino`: The main code file. Contains `void setup()` and `void loop()`
