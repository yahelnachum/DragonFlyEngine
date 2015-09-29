Author:						Yahel Nachum
Date:						9/28/2015
Project ID:					Project 2c
CS Class:					IMGD 3000
Programming Language:		C++
OS/Hardware dependencies:	This Program is designed to run on the Windows platform.

Program Source:			
						Ball.h
						Box.h
						Bullet.h
						Bus.h
						Car.h
						Clock.h
						Event.h
						EventCollision.h
						EventKeyboard.h
						EventMouse.h
						EventOut.h
						EventStep.h
						EventView.h
						GameManager.h
						GraphicsManager.h
						InputManager.h
						LogManager.h
						Manager.h
						Music.h
						Object.h
						ObjectList.h
						ObjectListIterator.h
						PlayerControlledCar.h
						Points.h
						Position.h
						ResourceManager.h
						Reticle.h
						Saucer.h
						SpecularObject.h
						Sprite.h
						Utility.h
						ViewObject.h
						WorldManager.h

						Ball.cpp
						Box.cpp
						Bullet.cpp
						Bus.cpp
						Car.cpp
						Clock.cpp
						Event.cpp
						EventCollision.cpp
						EventKeyboard.cpp
						EventMouse.cpp
						EventOut.cpp
						EventStep.cpp
						EventView.cpp
						game.cpp
						GameManager.cpp
						GraphicsManager.cpp
						InputManager.cpp
						LogManager.cpp
						Manager.cpp
						Music.cpp
						Object.cpp
						ObjectList.cpp
						ObjectListIterator.cpp
						PlayerControlledCar.cpp
						Points.cpp
						Position.cpp
						ResourceManager.cpp
						Reticle.cpp
						Saucer.cpp
						SpecularObject.cpp
						Sprite.cpp
						Utility.cpp
						ViewObject.cpp
						WorldManager.cpp

Additional Files:		
						README.txt
						"yahel_nachum_dragonfly\yahel_nachum_dragonfly\dragonfly.txt" - Output file
						"yahel_nachum_dragonfly\yahel_nachum_dragonfly\df-font.ttf" - Font file for GraphicsManaager
						sprites "yahel_nachum_dragonfly\sprites\*" - taken from my saucer implementation
						audio "yahel_nachum_dragonfly\audio\*" - taken from my saucer implementation

Code Structure:

	Header files:
						The header files are organized similarly with the #ifndef/#define/#endif 
						encapsulating the while file contents. Then there are the includes at the 
						top seperating the system includes and the game engine includes. Lastly 
						most of the header files with the exception of the extended Object classes, 
						Ball, Bullet, Bus, Car, Reticle, and PlayerControlledCar have the namespace 
						defined. Then are the private attributes of 
						the class followed by the public attributes. The constructor is usually in 
						the public attributes unless it is a singleton to control the creation of an 
						instance of that class.

	C plus plus files:
						The .cpp files are organized similarly to the .h files that they have the 
						system includes listed first and then the game engine includes. The order 
						of the functions defined is very similar to the .h file.

	Game.cpp:
						The game.cpp file has the system includes first followed by the game engine 
						includes just like the rest of the files included in this project. Then in 
						the main the first few lines of code display the menu of tests to the user. 
						After the menu is a list of if/else if statements that allow the input from 
						the menu to decide what test to run. Within each if/else if block is the test 
						that corresponds to the menu which runs the code and provides output through 
						the log file of the project and a visual representation of the world on the 
						screen produced by the GraphicsManager.

How to compile:
						Open up the yahel_nachum_dragonfly.sln solution under "yahel_nachum_dragonfly\
						yahel_nachum_dragonfly\yahel_nachum_dragonfly.sln" with microsoft visual studio 
						and hit F5 to run game.cpp.

What to look for in log files for each test:
	
	NOTE:				All tests push output to the logfile

	Test 1: Frame and Sprite tests:
		This test goes through the frame and sprite get / set methods to make 
		sure they are all operable and working as expected. Look at logs for
		actual vs expected comparisons.

	Test 2: ResourceManager Tests:
		This test goes through some basic loading tests. It will load a file 
		and check the sprite / frame objects it instantiated and will compare 
		the expected values with the actual values. Look at logs for actual 
		vs expected comparisons.

	Test 3: Frame Drawing tests:
		This test will draw different sprites based on the input taken from 
		the user. This demonstrates the loading of sprites in the ResourceManager 
		and the animation handled by the WorldManager. The sprites will 
		travel across the screen from right to left and reappear on the right
		after an out of bounds event is sent to the object.

	Test 4: Box class and boxIntersects function tests:
		This test goes through the usual actual vs expected results of gets and 
		sets method. It also tests the utility function to see if the box 
		intersects. Look at logs for expected vs actual values.

	Test 5: Views and Audio tests:
		This test will allow the user to have a lot of input. It tests the view 
		by letting the user use the wasd keys to travel across the world. When 
		the user presses down on the left mouse button a fire sound will play 
		testing the sound class. If the user releases the right mouse button 
		the music from saucer shoot will play. In the top right a view object 
		was created to keep track of psuedo points. Each step it increments by 
		1 to update its value.

	Test 6: Audio tests:
		This tests the ResourceManagers loading of sounds and music. It will 
		load and play a fire sound and then load and play a music sound.
