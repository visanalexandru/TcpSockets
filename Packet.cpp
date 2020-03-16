#include "Packet.h"

Packet::Packet():readPosition(0){
	

}

void Packet::append(const void*data,std::uint32_t sizeInBytes){
	int starting=buffer.size();
	buffer.resize(starting+sizeInBytes);
	memcpy(&buffer[starting],data,sizeInBytes);
}




Packet& Packet::operator <<(std::int8_t toAdd){

	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(std::int8_t &destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}

Packet& Packet::operator <<(std::uint8_t toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(std::uint8_t &destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}

Packet& Packet::operator <<(std::int16_t toAdd){
	std::int16_t network_order=htons(toAdd);
	append(&network_order,sizeof(network_order));
	return *this;
}


Packet& Packet::operator >>(std::int16_t &destination){
	std::int16_t network_order;

	memcpy(&network_order,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);

	destination=ntohs(network_order);
	return *this;
}

Packet& Packet::operator <<(std::uint16_t toAdd){
	std::uint16_t network_order=htons(toAdd);
	append(&network_order,sizeof(network_order));
	return *this;
}


Packet& Packet::operator >>(std::uint16_t &destination){
	std::uint16_t network_order;

	memcpy(&network_order,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);

	destination=ntohs(network_order);
	return *this;
}

Packet& Packet::operator <<(std::int32_t toAdd){
	std::int32_t network_order=htonl(toAdd);
	append(&network_order,sizeof(network_order));
	return *this;
}


Packet& Packet::operator >>(std::int32_t &destination){
	std::int32_t network_order;

	memcpy(&network_order,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);

	destination=ntohl(network_order);
	return *this;
}

Packet& Packet::operator <<(std::uint32_t toAdd){
	std::uint32_t network_order=htonl(toAdd);
	append(&network_order,sizeof(network_order));
	return *this;
}


Packet& Packet::operator >>(std::uint32_t &destination){
	std::uint32_t network_order;

	memcpy(&network_order,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);

	destination=ntohl(network_order);
	return *this;
}




Packet& Packet::operator <<(std::int64_t toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(std::int64_t &destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}

Packet& Packet::operator <<(std::uint64_t toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(std::uint64_t &destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}




Packet& Packet::operator <<(const std::string&toAdd){

	std::uint32_t string_size=toAdd.length();
	*this<<string_size;

	for(int i=0;i<toAdd.length();i++){
		std::int8_t character=toAdd[i];
		*this<<character;
	}
	return *this;
}


Packet& Packet::operator >>(std::string&destination){
	
	std::uint32_t length;

	*this>>length;

	destination.assign(&buffer[readPosition],length);


	readPosition+=length;
	return *this;
}

const void* Packet::getData() const {
	return &buffer[0];
}


std::uint32_t Packet::getNumBytes() const{
	return buffer.size();
}


