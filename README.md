# OS-lab-project
# Deadlock Detection and Recovery Tool

This project is a Windows application that implements a basic deadlock detection and recovery tool using the Banker's Algorithm. The tool allows users to add processes, add resources, allocate resources, detect deadlocks, and recover from deadlocks.

## How to Run

1. Setup Development Environment:
     Ensure you have a C++ development environment set up. This typically includes:
         A C++ compiler (like GCC or MSVC)
         An IDE (like Visual Studio) or a text editor (like VSCode)
     Make sure the Windows SDK is installed for creating Windows applications.

2. Create a New Project:
     Open your IDE (e.g., Visual Studio).
     Create a new Win32 Project.
     Copy and paste the provided source code into the main `.cpp` file.

3. Build and Run the Application:
     Build the project to compile the code. Ensure there are no compilation errors.
     Run the application. A window will appear with buttons to add processes, add resources, allocate resources, detect deadlock, and recover from deadlock.

4. Using the Application:
     Add Process: Click the "Add Process" button to add a new process.
     Add Resource: Click the "Add Resource" button to add a new resource.
     Allocate Resource: Click the "Allocate Resource" button to simulate resource allocation.
     Detect Deadlock: Click the "Detect Deadlock" button to run the deadlock detection algorithm. The result will be displayed in the output text box.
     Recover: Click the "Recover" button to simulate recovering from a deadlock.

## Dependencies

 Windows OS: This application is designed to run on Windows.
 C++ Compiler: Required to compile the source code.
 Windows SDK: Necessary for developing Windows applications.

## Additional Notes

 The application uses the Banker's Algorithm for deadlock detection.
 The code includes basic user interface components created using the Windows API.
 This is a simplified example for educational purposes and may need additional features and error handling for production use.
