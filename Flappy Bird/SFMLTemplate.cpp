#include "pch.h"
#include "tube.h"
#include <string>
#include <random>

int main()
{
	RenderWindow window(VideoMode(800, 800), "SFML"); //creates a screen the size 800 by 800

	//player
	Texture playerUpTexture; //creates atexture variable called playerUpTexture for when the bird is going up
	Texture playerDownTexture; //creates a texture variable called playerDownTexture for when the bird is falling
	Sprite player; //creates a sprite variable called player
	player.setPosition(100, 400); //sets player's position
	player.setScale(0.15,0.15); //sets players scale
	playerDownTexture.loadFromFile("Texture/flappyDown.png"); //sets playerDownTexture equal to img from a file
	playerUpTexture.loadFromFile("Texture/flappyUp.png"); //sets playerUpTexture equal to img from 
	player.setTexture(playerUpTexture); //sets the texture of the player to playerTexture's value

	//background
	Texture backgroundImg; //creates a texture variable called backgroundImg
	backgroundImg.loadFromFile("Texture/background.png");
	Sprite background; //creates a sprite variable called background
	background.setTexture(backgroundImg); //sets the texture of background to backgroundImg
	background.setScale(2, 2); //sets scale of background
	

	//time
	Clock clock; //creates a clock varible
	float timer; //creates a float variable called timer
	bool stopTime = false; //creates a boolean variable called stopTime and sets it to false

	//gameover 
	Texture gameoverTexture; //creates a texture variable called gameoverTexture
	gameoverTexture.loadFromFile("Texture/gameoverscreen.jpg"); //loads an image from a file and sets it to gameoverTexture
	Sprite gameoverSprite; //creates a sprite variable called gameoverSprite
	gameoverSprite.setTexture(gameoverTexture); //sets the texture of gameoverSprite and sets it to game
	bool gameover = false; //sets the boolean gameover to false

	
	//tube
	Texture tubeTexture; //creates a texture variable called tubeTexture
	Sprite tube; //creates a sprite called tube
	tubeTexture.loadFromFile("Texture/FlappyBirdTubes.png"); //loads a picture from a file and stores it into tubTexture
	tube.setTexture(tubeTexture); //sets the texture of the tube sprite to tubeTexture
	tube.setPosition(400, -450); //sets the position of the tube to 400x and -450y
	tube.setScale(0.5, 0.5); //sets the scale of the tube to 0.5

	//tube top collider
	RectangleShape topCollider; //creates a rectangle shape variable called topCollider
	topCollider.setSize(Vector2f(115,400)); //sets the width of the topCollider to 115 and the height to 400
	topCollider.setFillColor(Color::Transparent); //sets the color of the topCollider to transparent
	topCollider.setPosition(tube.getPosition().x , tube.getPosition().y + 350); //sets the x of the top collider to the tube's x position and sets the y position of topCollide to the y position of the tube + 350

	//tube bottom collider
	RectangleShape bottomCollider; //creates a rectangle shape variable called bottomCollider
	bottomCollider.setSize(Vector2f(115, 400)); //sets the size of the bottom collider to 115x and 400y
	bottomCollider.setFillColor(Color::Transparent); //sets the color of the bottom Collider to transparent
	bottomCollider.setPosition(tube.getPosition().x , tube.getPosition().y + 1000); //sets the position of the bottom collider to the tube's x position and sets the bottom colliders's y position to the tube's y position + 1000

	//second tube
	Sprite tube1; //creates a sprite variable called tube1
	tube1.setTexture(tubeTexture); //sets the texture of tube1 to tubeTexture
	tube1.setPosition(850, -350); //sets the position of tube 1 to 850 x and -350 y
	tube1.setScale(0.5, 0.5); //sets the scale of tube1 to 0.5

	//second tube's top collider
	RectangleShape topCollider1; //creates a rectangle shape variable called topCollider1
	topCollider1.setSize(Vector2f(115, 400)); //sets the size of topCollider1 to 115x and 400y
	topCollider1.setFillColor(Color::Transparent); //sets the color of topCollider1 to Transparent
	topCollider1.setPosition(tube1.getPosition().x + 300, tube1.getPosition().y + 350); //sets the position of topCollider1 to the tube's x position + 300 and sets the topCollider1's y to the tube's y position + 350 

	//second tube's bottom collider
	RectangleShape bottomCollider1;//creates a rectangle shape variable called bottomCollider1
	bottomCollider1.setSize(Vector2f(115, 400)); //sets the size of bottomCollider1 to 115x and 400y
	bottomCollider1.setFillColor(Color::Transparent); //sets the color of bottomCollider1 to transparent
	bottomCollider1.setPosition(tube1.getPosition().x + 350, tube1.getPosition().y + 1000); //sets the position of bottomCollider1 to the tube's x position + 350 and sets the bottomCollider1's y position to the tube's y position + 1000

	//ground
	Texture groundTexture; //creates a texture variable called groundTexture
	Sprite ground; //creates a sprite variable called ground
	groundTexture.loadFromFile("Texture/ground.png"); //gets an image from a file and sets it to groundTexture;
	ground.setTexture(groundTexture);//sets the texture of the ground to groundTexture
	ground.setScale(1.5,1.9); //sets the scale of the ground to 1.5 by x and 1.9 by y 
	ground.setPosition(-10, 730); //sets the grounds position to -10 x and 730 y


	//score
	int score = 0; //creates a integer variable called score and sets it to 0
	Font myFont; //creates a font variable and calls it myFont
	Text text; //creates a text variable and calls it text
	myFont.loadFromFile("Font/Heebo-Bold.ttf"); //gets a font from file and sets it to myFont
	text.setFont(myFont); //sets the font of text to myFont
	text.setFillColor(Color::Black); //sets the color of text to black
	text.setCharacterSize(40); //sets the font size of text to 40
	text.setPosition(320,50); //sets the position of text to 320 x and 50 y

	//gameover screen
	Text gameOverScore; //creates a text variable called gameOverScore
	Font gameOverFont; //creates a font varible called gameOverFont
	gameOverFont.loadFromFile("Font/Arimo-Bold.ttf"); //gets a font from the file and sets it equal to gameOverFont
	gameOverScore.setFont(gameOverFont); //sets the font of gameOverScore to gameOverFont
	gameOverScore.setFillColor(Color::Black); //sets the color of gameOverScore to black
	gameOverScore.setCharacterSize(30); //sets the font size of gameOverScore to 30
	gameOverScore.setPosition(290, 480);  //sets the position of gameOverScore to 290 x and 480y
	gameOverScore.setString("Score"); //sets the characters of gameOverScore to Score

	bool jumping = false; //creates a boolean variable and sets it to false

	while (window.isOpen()) { //while the window is open

		Event event; //creates a event variable called event
		while (window.pollEvent(event)) { //while their is a event
			if (event.type == Event::Closed) //to close the window
				window.close(); //closes the window

			if (event.type == Event::KeyPressed) //when their is a key pressed
				if (event.key.code == Keyboard::Escape) //if the escape key is pressed
					window.close();	// close the window


			if (event.type == Event::KeyPressed) { //when  their is a key pressed
				if (event.key.code == Keyboard::Space) { //when the space key is pressed
					jumping = true; //sets jumping to true (this makes the bird jump)
				}
			}

			if (event.type == Event::KeyReleased) { //when the person playing the game releases a key
				if (event.key.code == Keyboard::Space) { //when the person playing the game releases the space key
					jumping = false; //sets jumping  to false (doesnt make the bird jump anymore)
				}
			
			}

		} 

		if (player.getPosition().y > 690 || player.getPosition().y < -80) { //if the bird's y is greater than 690 or if the bird's y is less than -80 (if the bird goes too high that its off the screen or if the bird goes too low that its off the screen)
			gameover = true; //sets gameover to true (ends the game)
		}
		player.move(0, 0.34); //constanly changes the bird's y position by 0.34 (gives the bird gravity)
		Vector2f movement(0, 0); 

		//time stuff
		if (stopTime == false){ //if stopTIme is equal to false (if the game is still going on)
		timer = clock.getElapsedTime().asSeconds(); //sets the variable timer to to the elapsed amount of seconds on clock

		if (timer > 1.f) { //if the seconds is greater than 1 second
			text.setString(std::to_string(timer)); //makes the seconds into a string 
			gameOverScore.setString("Time: " + std::to_string(timer)); //sets the character's of gameOverScore to Time: + the amount of seconds
		}
	}


		if (jumping == true) { //if jumping is equal to true (if the bird is jumping)
			movement.y -= 0.8;  //subtracts 0.8 from the y position of the bird
			player.setTexture(playerUpTexture); //sets the bird's texture to playerUpTexture (sets the bird's costume that is looking down into the bird's costume that is looking up)
		}

		else { //else (if the bird is falling and not jumping)
			player.setTexture(playerDownTexture); //sets the bird's texture to playerDownTexture (sets the bird's costume that is looking down to the bird's costume that is looking up)
		}


		//bird
		player.move(movement);//moves the bird by the varible movement (makes the bird jump)
		//first tube
		topCollider.move(-0.1, 0); //moves the x position of the topCollider by -0.1 (makes the topCollider of the tube move left)
		bottomCollider.move(-0.1, 0); //moves the x positon of the bottom Collider by -0.1 (makes the bottomCollider of the tube move left)
		tube.move(-0.1, 0); //moves the x position of the first tube by -0.1 (makes the tube move left)
		//second tube
		topCollider1.move(-0.1, 0); //moves the x position of topCollider by -0.1 (makes the top collider of the second tube move left)
		bottomCollider1.move(-0.1, 0);//moves the x position of bottomCollider by -0.1 (makes the bottom collider of the second tube move left)
		tube1.move(-0.1, 0);  //moves the x position of the second tube by -0.1 (makes the second tube move left)

		if (player.getGlobalBounds().intersects(topCollider.getGlobalBounds()) ||
			player.getGlobalBounds().intersects(bottomCollider.getGlobalBounds()) ||
			player.getGlobalBounds().intersects(topCollider1.getGlobalBounds()) ||
			player.getGlobalBounds().intersects(bottomCollider1.getGlobalBounds())) //if the bird intersects with the first tube's top collider OR if the bord intersects with the bottom collider of the first tube OR if the forst colllider of the second tube intersects with the player OR if the player intersects with the bottom collider of the second tube sets gameover to true (if the bird hits the top tube or the bottom tube ends the game)
		{
			gameover = true; //sets gameover to true
		}

		random_device rd; //creates a random_device variable to rd
		int num = rd() % 5; //creates a integer variable called num and makes it have 5 possibilities
		float randY; //creates a float variable called randY
		//creates a switch with num
		switch (num) { 
		case 0: //if the num is equal to 0
			randY = -150; //sets randY to -150
			break;

		case 1://if the num is equal to 1
			randY = -200;//sets randY to -200
			break;

		case 2://if the num is equal to 2
			randY = 90;//sets randY to 90
			break;

		case 3://if the num is equal to 3
			randY = -80;//sets randY to -80
			break;

		default: //default
			randY = 0; //sets randY to 0
			break;
		}

		

		if (tube.getPosition().x < -120) { //if the first tube's x position if equal to -120 (if the first tube gets off the screen to the left)
			tube.setPosition(820, tube.getPosition().y + randY);  //sets the positon of the first tube to 820 x and sets the y positon to the tube's y positon + randY (respawns the first tube with a random y position)
			bottomCollider.setPosition(tube.getPosition().x, tube.getPosition().y + 1000); //does the same thing above with the first tube's bottom collider 
			topCollider.setPosition(tube.getPosition().x, tube.getPosition().y + 350); //does the same thing above but with the first tube's top collider 
		}

		if (tube1.getPosition().x < -120) { //if the second tube's x position if equal to -120 (if the second tube gets off the screen to the left)
			tube1.setPosition(820, tube1.getPosition().y + randY);//sets the positon of the second tube to 820 x and sets the y positon to the tube's y positon + randY (respawns the second tube with a random y position)
			bottomCollider1.setPosition(tube1.getPosition().x, tube1.getPosition().y + 1000);//does the same thing above with the second tube's bottom collider 
			topCollider1.setPosition(tube1.getPosition().x, tube1.getPosition().y + 350);//does the same thing above but with the second tube's top collider 
		}

		window.clear(); //clears the window

		if (!gameover) { //if the game is not equal to gameover (if the game is still going on)
			window.draw(background); //draws the background
			window.draw(player); //draws the player(bird)
			window.draw(topCollider); //draws the top collider of the first tube
			window.draw(bottomCollider); //draws the bottom collider of the first tube
			window.draw(tube); //draws the first tube
			window.draw(tube1);//draws the second tube
			window.draw(topCollider1); //draws the top collider of the second tube
			window.draw(bottomCollider1); //draws the bottom collider of the second tube
			window.draw(ground); //draws the ground
			window.draw(text); //draws the text (time)
		}

		else {
			stopTime = true; //sets stopTime to true (stops the time)
			window.draw(gameoverSprite); //draws the gameoverSprite
			window.draw(gameOverScore); //draws the gameOverScore
		}
		
		window.display(); //displays the window
	}
}