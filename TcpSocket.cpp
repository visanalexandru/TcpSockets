#include "TcpSocket.h"


void TcpSocket::connectToAdress(const std::string&address,unsigned port){

	socketId=SocketUtils::createNewSocket();
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr)<=0)
	{
		std::cout<<"invalid adress"<<'\n';
	}

	if (connect(socketId, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout<<"connection to "<<address<<":"<<port<<" failed\n";
	}
}


void TcpSocket::sendPacket(const Packet&packet){

	//we send packet size first and then packet raw data
	//TODO size_t is implementation defined and should be changed!!!!!!
	std::uint32_t size=packet.getNumBytes();
	std::uint32_t total_size=size+sizeof(size);
	

	//we need to add the size of the packet in the raw data
	std::vector<char> data;
	data.resize(total_size);


	memcpy(&data[0],&size,sizeof(size));
	memcpy(&data[sizeof(size)],packet.getData(),size);

	std::uint32_t total_sent=0;
	while(total_sent<total_size){
		std::uint32_t chunk_size=send(socketId,&data[total_sent],total_size-total_sent,0);

		if(chunk_size<0){
			std::cout<<"could not send packet \n";
			return;
		}

		std::cout<<"sent chunk of "<<chunk_size<<" bytes \n";
		total_sent+=chunk_size;
		std::cout<<"total sent is "<<total_sent<<"out of"<<total_size<<'\n';
	}


}

Packet TcpSocket::receivePacket(){

	std::uint32_t packet_size;//this is the pending packet size
	std::uint32_t size=recv(socketId,&packet_size,sizeof(uint32_t),0);//TODO fix this (uint32_t may be received in multiple calls


	std::cout<<"Need to receive a packet of size"<<packet_size<<'\n';

	std::vector<char> buffer;
	buffer.resize(packet_size);

	std::uint32_t total_received=0;
	
	while(total_received<packet_size){
		std::uint32_t received=recv(socketId,&buffer[total_received],packet_size-total_received,0);
		total_received+=received;
		std::cout<<"received new chunk of "<<received<<" bytes "<<"total received:"<<total_received<<'\n';
	}



	Packet to_return;
	to_return.buffer=buffer;

	return to_return;
}

