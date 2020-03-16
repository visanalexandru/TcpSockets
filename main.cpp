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



void server(){
	TcpListener server;
	server.listenToPort(8080);


	Selector selector;
	selector.add(server);
	vector<TcpSocket*> clients;


	while(1){
		if(selector.wait()){
			if(selector.isReady(server)){
				TcpSocket*newsock=new TcpSocket;
				server.acceptNewClient(newsock);
				selector.add(*newsock);
				clients.push_back(newsock);
				std::cout<<"new client connected "<<std::endl;
			}
			else{
				for(int i=0;i<clients.size();i++){
					TcpSocket*a=clients[i];


					if(selector.isReady(*a)){
						Packet received;
						Socket::Status status=a->receivePacket(received);
						if(status==Socket::Status::Done){
							string message;
							received>>message;
							std::cout<<a->getAdress().address<<":"<<message<<std::endl;
						}
						else if(status==Socket::Status::Disconnected){
							selector.remove(*a);
							clients.erase(clients.begin()+i);
							std::cout<<a->getAdress().address<<" disconnected"<<std::endl;
						}
					}						
				}
			}

		}
	}

}

void client(){
	string to_send;
	TcpSocket socket;
	Socket::Status status=socket.connectToAdress("192.168.0.189",8080);

	if(status!=Socket::Status::Done){
		std::cout<<"cannot connect to server"<<std::endl;
		return;
	}


	std::cout<<"started client to"<<socket.getAdress().address<<" "<<socket.getAdress().port<<std::endl;

	while(1){
		std::getline (std::cin,to_send);

		Packet newpacket;
		newpacket<<to_send;

		Socket::Status status=socket.sendPacket(newpacket);
		if(status==Socket::Disconnected){
			std::cout<<"server disconnected"<<std::endl;
			break;
		}
	}
}


int main(int argc,char*argv[]){




	if(argc==2){
		client();
	}
	else{
		server();
	}

	return 0;
}



