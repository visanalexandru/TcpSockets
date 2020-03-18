#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include<thread>


#include "Packet.h"
#include "TcpListener.h"
#include "TcpSocket.h"
#include"Selector.h"
using namespace std;






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
				Socket::Status status=server.acceptNewClient(newsock);


				if(status==Socket::Status::Done){
					selector.add(*newsock);
					clients.push_back(newsock);
					std::cout<<"new client connected: "<<newsock->getAdress().address<<std::endl;
				}
				else delete newsock;
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
							string to_send=a->getAdress().address+": "+message;
							Packet packet_to_send;
							packet_to_send<<to_send;

							std::cout<<a->getAdress().address<<":"<<message<<std::endl;
							for(int i=0;i<clients.size();i++){
								clients[i]->sendPacket(packet_to_send);
							}
						}
						else if(status==Socket::Status::Disconnected){
							selector.remove(*a);
							clients.erase(clients.begin()+i);
							std::cout<<a->getAdress().address<<" disconnected"<<std::endl;
							delete a;
						}
					}						
				}
			}

		}
	}

}


void serverListener(bool*isRunning,TcpSocket*socket){
	Selector selector;
	selector.add(*socket);
	while(*isRunning){
		if(selector.wait(1000000)){//wait 1 second

			Packet received;
			Socket::Status status=socket->receivePacket(received);

			if(status==Socket::Status::Done){
				string message;
				received>>message;
				std::cout<<message<<std::endl;
			}
			else if(status==Socket::Status::Disconnected){
				std::cout<<"SERVER LISTENER:server disconnected"<<std::endl;
				break;
			}
			else std::cout<<"SERVER LISTENER:error while receiving packet"<<std::endl;
		}
	}

	std::cout<<"SERVER LISTENER:stopped"<<std::endl;
}

void client(){
	string to_send;
	TcpSocket socket;
	Socket::Status status=socket.connectToAdress("192.168.0.189",8080);

	if(status!=Socket::Status::Done){
		std::cout<<"cannot connect to server"<<std::endl;
		return;
	}
	bool running=true;

	std::thread server_listener_thread(serverListener,&running,&socket);


	std::cout<<"started client to"<<socket.getAdress().address<<" "<<socket.getAdress().port<<std::endl;

	while(1){

		std::getline(std::cin,to_send);
		if(to_send=="/STOP")
			break;

		Packet newpacket;
		newpacket<<to_send;

		Socket::Status status=socket.sendPacket(newpacket);
		if(status==Socket::Disconnected){
			std::cout<<"server disconnected"<<std::endl;
			break;
		}
	}
	running=false;
	server_listener_thread.join();
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



