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
		output_ << command << std::flush;
	}

private:
	std::ofstream output_;

};

#endif // __ARDUINOINTERFACE_H__