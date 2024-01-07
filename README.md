# minesweeper-raylib
This is my attempt to building a full minesweeper game using raylib: https://www.raylib.com/ </br>
I am updated the game object model to use game objects with hierarchy model.</br>
This is game object model is taken from Sanjay Madhav's book on Game Programming with C++.</br>
The code might need some more cleaning/refactoring, but I think this is a good start.</br>

If you want to try out this game, please follow the instructions below.</br>
Make sure you have Visual Studio 2022 installed along with Windows 10 SDK.</br>
Alternatively, you can also compile and run this with CLion.</br>
The CMakeList.txt file should have all the necessary dependencies.

### <u>How to build (for Windows 10):</u>
1. Install cmake for windows: https://cmake.org/download/
2. Run <code>mkdir build && cd build && cmake.exe ..</code></br>
   This will generate the visual studio files needed to build the final executable
3. Open the .sln file in Visual Studio 2022
4. Go to Linker > System under project settings and change SubSystem to Windows
5. Go to Linker > Command Line and add <code>/ENTRY:"mainCRTStartup"</code> under _Additional Options_</br>
   This will disable console when you run the executable.
6. Hit OK and select Build Solution under Build menu item

This should now build the complete project and you should be able to find the executable in the build directory</br>
under your active configuration setting folder, e.g. Debug, Release, etc.