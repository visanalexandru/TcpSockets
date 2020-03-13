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
		Packet received=socket.receivePacket();
		string message;
		int ans;
		received>>message>>ans;
		cout<<message<<" "<<ans;

	}
	else{


		TcpListener listener;
		listener.setPort(8080);
		TcpSocket client=listener.acceptNewClient();
		int a;
		cin>>a;
		//std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		packet<<"hello world!!!!The answer to life is"<<42;
		client.sendPacket(packet);	

	}

	return 0;
}



