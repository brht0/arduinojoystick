#ifndef __ARDUINOINTERFACE_H__
#define __ARDUINOINTERFACE_H__

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<unistd.h>

class ArduinoInterface{
public:
	ArduinoInterface():
		output_("/dev/ttyACM0")
	{
		system("stty -F " DEVICE " cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
	}
	~ArduinoInterface(){
	}

	void Send(std::string command){
		std::cout << "Seding to Arduino: " << command << "\n";
		output_ << (command + '\n') << std::flush;
		usleep(20000);
	}

	void Send(uint8_t value){
		output_ << value << std::flush;
	}

private:
	std::ofstream output_;

};

#endif // __ARDUINOINTERFACE_H__