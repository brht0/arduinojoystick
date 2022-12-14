#define DEVICE "/dev/ttyACM0"

#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

class ArduinoInterface{
public:
	ArduinoInterface():
		output_(DEVICE)
	{
		system("stty -F " DEVICE " cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
	}
	~ArduinoInterface(){
	}

	void Send(std::string command){
		std::cout << "Seding command to Arduino: \"" << command << "\"\n";
		output_ << (command + '\n') << std::flush;
	}

	void Send(uint8_t value){
		output_ << value << std::flush;
	}

private:
	std::ofstream output_;

};

void handleEvent(const sf::Event& event, ArduinoInterface& arduino){
	if (event.type == sf::Event::JoystickDisconnected){
		unsigned int joystickId = event.joystickConnect.joystickId;
		std::cout << "Joystick disconnected " << joystickId << "\n";
	}
	if (event.type == sf::Event::JoystickButtonPressed){
		unsigned int joystickId = event.joystickButton.joystickId;
		unsigned int button     = event.joystickButton.button;
		arduino.Send("B " + std::to_string(button));
	}
	if (event.type == sf::Event::JoystickMoved){
		sf::Joystick::Axis axis = event.joystickMove.axis; //X, Y, R
		int position = event.joystickMove.position; //Position is between -100 and 100
		if(axis == sf::Joystick::X) arduino.Send("X " + std::to_string(position));
		if(axis == sf::Joystick::Y) arduino.Send("Y " + std::to_string(position));
		if(axis == sf::Joystick::R) arduino.Send("R " + std::to_string(position));
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Space){
		arduino.Send("HALT");
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return){
		arduino.Send("CONTINUE");
	}
}

int main(){
	sf::RenderWindow window(sf::VideoMode(300, 300), "Control joystick");
	ArduinoInterface arduino;
	
	if(sf::Joystick::isConnected(0)){
		std::cout << "Joystick is connected\n";
	}
	else{
		std::cout << "Joystick not found\n";
		exit(1);
	}

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			handleEvent(event, arduino);
		}

		usleep(3000);
	}

  return 0;
}
