#define DEVICE "/dev/ttyACM0"

#include "ArduinoInterface.hpp"
#include "SFML/Graphics.hpp"

void handleEvent(const sf::Event& event, ArduinoInterface& arduino){
	if (event.type == sf::Event::MouseButtonPressed){
		// arduino.Send("Mouse 300 200\n");
	}
	else if (event.type == sf::Event::JoystickDisconnected){
		unsigned int joystickId = event.joystickConnect.joystickId;
	}
	if (event.type == sf::Event::JoystickButtonPressed){
		unsigned int joystickId = event.joystickButton.joystickId; //Ids are numbered from 0 to 7
		unsigned int button     = event.joystickButton.button; //Button are numbered from 0 to 31
		arduino.Send("B " + std::to_string(button));
	}
	if (event.type == sf::Event::JoystickButtonReleased){
		unsigned int joystickId = event.joystickButton.joystickId; //Ids are numbered from 0 to 7
		unsigned int button     = event.joystickButton.button; //Button are numbered from 0 to 31
	}
	if (event.type == sf::Event::JoystickMoved){
		unsigned int joystickId = event.joystickMove.joystickId; //Ids are numbered from 0 to 7
		sf::Joystick::Axis axis = event.joystickMove.axis; //X, Y, Z, R, U, V, POV X and POV Y
		float position2          = event.joystickMove.position; //Position is between -100 and 100
		int position = position2;
		if(axis == sf::Joystick::X)
			arduino.Send("X " + std::to_string(position));
		if(axis == sf::Joystick::Y)
			arduino.Send("Y " + std::to_string(position));
		if(axis == sf::Joystick::R)
			arduino.Send("R " + std::to_string(position));
	}
}

int main(){
	sf::RenderWindow window(sf::VideoMode(300, 300), "Control joystick");
	
	bool connected = sf::Joystick::isConnected(0);
	std::cout << "connected: " << connected << "\n";

	ArduinoInterface arduino;

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			handleEvent(event, arduino);
		}

		usleep(3000);
	}

  return 0;
}
