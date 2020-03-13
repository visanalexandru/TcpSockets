#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>

#include "Packet.h"
#include "TcpListener.h"
#include "TcpSocket.h"
using namespace std;


ifstream in("input");



int main(int argc,char*argv[]){

	Packet packet;



	if(argc==2){

		TcpSocket socket;
		socket.connectToAdress("192.168.0.189",8080);
		std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		packet<<content;
		socket.sendPacket(packet);
	}
	else{


		TcpListener listener;
		listener.setPort(8080);
		TcpSocket client=listener.acceptNewClient();
		Packet received=client.receivePacket();

		string message;
		received>>message;

		cout<<message;


	}

	return 0;
}



