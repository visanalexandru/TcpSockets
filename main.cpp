#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>

#include "Packet.h"
#include "TcpListener.h"
#include "TcpSocket.h"
#include"Selector.h"
using namespace std;


ifstream in("input");



int main(int argc,char*argv[]){

	Packet packet;
	Selector selector;




	if(argc==2){

		TcpSocket socket;
		socket.connectToAdress("192.168.0.189",8080);


		std::cout<<"connected to"<<socket.getAdress().address<<std::endl;

		socket.receivePacket(packet);
		string message;
		int ans;
		packet>>message>>ans;
		cout<<message<<" "<<ans;

	}
	else{



		TcpListener listener;
		listener.listenToPort(8080);


		TcpSocket client;



		listener.acceptNewClient(&client);
		int a;
		cin>>a;
		//std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		packet<<"hello world!!!!The answer to life is"<<42;
		client.sendPacket(packet);	


	}

	return 0;
}



