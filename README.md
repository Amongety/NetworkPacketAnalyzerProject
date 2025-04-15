**Installing and running the application for Linux**

If you do not have these packages installed, please install the following:
   - `sudo apt-get update`
   - `sudo apt-get install -y build-essential`
   - `sudo apt-get install cmake`
   - `sudo apt-get install gcc`

Code compilation:
1) Put it in the right directory: `git clone https://github.com/Amongety/NetworkPacketAnalyzerProject.git`
2) On the command line of this directory, type: `cmake CMakeLists.txt`
3) At the command prompt in this directory, type: `make`
4) Run the application for a root user through the command: `./main`
