Authors:					Andy Busch and Yahel Nachum
Date:						10/8/2015
Project ID:					Project 3 alpha
CS Class:					IMGD 3000
Programming Language:				C++
OS/Hardware dependencies:			This Program is designed to run on the Windows platform.

Program Source:			
						Ball.h
						Block.h
						Box.h
						Bullet.h
						Bus.h
						Button.h
						Car.h
						Clock.h
						Enemy.h
						Event.h
						EventCollision.h
						EventHeroPosition.h
						EventKeyboard.h
						EventMouse.h
						EventOut.h
						EventPower.h
						EventStep.h
						EventView.h
						Floor.h
						Frame.h
						GameManager.h
						GraphicsManager.h
						Hero.h
						InputManager.h
						Ladder.h
						LogManager.h
						Manager.h
						MapManager.h
						MapObject.h
						Music.h
						Object.h
						ObjectList.h
						ObjectListIterator.h
						PlayerControlledCar.h
						Points.h
						Position.h
						Power.h
						ResourceManager.h
						Reticle.h
						Saucer.h
						Shelf.h
						Shield.h
						Sound.h
						SpecularObject.h
						Sprite.h
						StartScreen.h
						TreeNode.h
						Utility.h
						ViewObject.h
						Wall.h
						WorldManager.h

						Ball.cpp
						Block.cpp
						Box.cpp
						Bullet.cpp
						Bus.cpp
						Button.cpp
						Car.cpp
						Clock.cpp
						Enemy.cpp
						Event.cpp
						EventCollision.cpp
						EventHeroPosition.cpp
						EventKeyboard.cpp
						EventMouse.cpp
						EventOut.cpp
						EventPower.cpp
						EventStep.cpp
						EventView.cpp
						Floor.cpp
						Frame.cpp
						GameManager.cpp
						GraphicsManager.cpp
						Hero.cpp
						InputManager.cpp
						Ladder.cpp
						LogManager.cpp
						Manager.cpp
						MapManager.cpp
						MapObject.cpp
						Music.cpp
						Object.cpp
						ObjectList.cpp
						ObjectListIterator.cpp
						PlayerControlledCar.cpp
						Points.cpp
						Position.cpp
						Power.cpp
						ResourceManager.cpp
						Reticle.cpp
						Saucer.cpp
						Shelf.cpp
						Shield.cpp
						Sound.cpp
						SpecularObject.cpp
						Sprite.cpp
						StartScreen.cpp
						TreeNode.cpp
						Utility.cpp
						ViewObject.cpp
						Wall.cpp
						WorldManager.cpp
Additional Files:		
						README.txt
						"DragonFlyEngine\yahel_nachum_dragonfly\dragonfly.txt" - Output file
						"DragonFlyEngine\yahel_nachum_dragonfly\df-font.ttf" - Font file for GraphicsManaager
						sprites "DragonFlyEngine\sprites\*" - taken from my saucer implementation and some originals
						audio "DragonFlyEngine\audio\*" - taken from my saucer implementation

Code Structure:

	Header files:
						The header files are organized similarly with the #ifndef/#define/#endif 
						encapsulating the while file contents. Then there are the includes at the 
						top separating the system includes and the game engine includes. Lastly 
						most of the header files have the namespace defined. Then are the private attributes of 
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
						Open up the yahel_nachum_dragonfly.sln solution under "DragonFlyEngine\
						yahel_nachum_dragonfly\yahel_nachum_dragonfly.sln" with microsoft visual studio 
						and hit F5 to run game.cpp.

What to look for in log files for each test:
	
	NOTE:				All tests push output to the logfile

	Test 0: IHOP Simulator:
		This tests a simple map output onto the screen.
	Test 1: test:
		This tests simple map objects drawing to the screen.
	Test 2: hero tests:
		This test simple hero and enemy manipulation. The hero can touch the pancakes and make them fall down. If the hero stacks four pancakes on top of each other they get 50 extra points.
	Test 3: Path finding tests:
		This test the path finding functions in the TreeNode class. It uses an A* algorithm to produce the best path that the enemy can take on the map.
	Test 4: Start menu tests:
		This just displays the start menu without any functionality.
	Test 5: power ups test
		This test is for testing walls, buttons, and powerups.