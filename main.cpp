#define DEVICE "/dev/ttyACM0"

#include "ArduinoInterface.hpp"
#include "SFML/Graphics.hpp"


/*

Collection of pieces of the internet. Don't sue me

*/


void handleEvent(const sf::Event& event, ArduinoInterface& arduino)
{
	if (event.type == sf::Event::MouseButtonPressed){
		arduino.Send("-- mouse 300 200\n");
	}
	else if (event.type == sf::Event::JoystickDisconnected){
			unsigned int joystickId = event.joystickConnect.joystickId;
	}
	if (event.type == sf::Event::JoystickButtonPressed){
			unsigned int joystickId = event.joystickButton.joystickId; //Ids are numbered from 0 to 7
			unsigned int button     = event.joystickButton.button; //Button are numbered from 0 to 31
		std::cout << "Button: " << (button) << "\n";
		arduino.Send((unsigned char)button);
	}
	if (event.type == sf::Event::JoystickButtonReleased)
	{
			unsigned int joystickId = event.joystickButton.joystickId; //Ids are numbered from 0 to 7
			unsigned int button     = event.joystickButton.button; //Button are numbered from 0 to 31
	}
	if (event.type == sf::Event::JoystickMoved)
	{
		unsigned int joystickId = event.joystickMove.joystickId; //Ids are numbered from 0 to 7
		sf::Joystick::Axis axis = event.joystickMove.axis; //X, Y, Z, R, U, V, POV X and POV Y
		float position          = event.joystickMove.position; //Position is between -100 and 100
		//Axes depend on your GamePad and OS System, but here is an example
		//Axis POV X and POV y  = DPad (Directional Pad)    ,first axis is horizontal (left-right), second is vertical (up-down)
		//Axis X and Y          = First Analog              ,first axis is horizontal (left-right), second is vertical (up-down)
		//Axis Z and R          = Second Analog             ,first axis is horizontal (left-right), second is vertical (up-down)
		//Axis U and V          = Shoulder (L2, R2)         ,first axis is L2, second is R2

	}
}

int main(){
	sf::RenderWindow window(sf::VideoMode(100, 100), "Control joystick");
	
	bool connected = sf::Joystick::isConnected(0);
	std::cout << "connected: " << connected << "\n";

	ArduinoInterface arduino;

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			handleEvent(event, arduino);
		}

		usleep(10000);
	}

  return 0;
}
