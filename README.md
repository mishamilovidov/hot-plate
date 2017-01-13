# Hot Plate

A console program that computes the steady state temperature distribution over a piece of metal. This type of steady state analysis is used in solving many physics problems, such as analyzing the wind speed and pressure over each part of an airplane wing or car. Although the full analysis may be complicated, it can be broken down to much simpler pieces. Here, you will break down a square sheet of metal into 400 discrete sections, and calculate the temperature of each section over time until you arrive at a steady state.

##Local Dev Setup
* git clone repo
* running on Mac (reference http://www.dvc.edu/academics/mcsd/computer-science/pdfs/UsingAppleXCode.pdf)
    * ensure latest Xcode and Xcode Command Line Tools are installed
    * open Terminal
    * navigate to directory with main.cpp
    * run: g++ main.cpp -o hot-plate
    * run: ./hot-plate
