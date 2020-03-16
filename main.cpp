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



void server(TcpListener&server){
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
				std::cout<<"new client connected "<<newsock->getHandle()<<std::endl;
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

void client(TcpSocket&sock){
	string to_send;
	std::cout<<"started client to"<<sock.getAdress().address<<" "<<sock.getAdress().port<<std::endl;

	while(1){
		cin>>to_send;
		Packet newpacket;
		newpacket<<to_send;
		sock.sendPacket(newpacket);
	}
}


int main(int argc,char*argv[]){

	Packet packet;
	Selector selector;




	if(argc==2){

		TcpSocket socket;
		socket.connectToAdress("192.168.0.189",8080);
		client(socket);
	}
	else{



		TcpListener listener;
		listener.listenToPort(8080);


		server(listener);

	}

	return 0;
}



