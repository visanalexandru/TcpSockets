#include "Packet.h"

Packet::Packet():readPosition(0){
	

}

void Packet::append(const void*data,unsigned sizeInBytes){
	int starting=buffer.size();
	buffer.resize(starting+sizeInBytes);
	memcpy(&buffer[starting],data,sizeInBytes);
}




Packet& Packet::operator <<(char toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(char &destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}




Packet& Packet::operator <<(short toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(short&destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}






Packet& Packet::operator <<(unsigned short toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(unsigned short&destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}







Packet& Packet::operator <<(int toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(int&destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}



Packet& Packet::operator <<(unsigned toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(unsigned&destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}


Packet& Packet::operator <<(long toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(long &destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}


Packet& Packet::operator <<(unsigned long toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(unsigned long &destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}




Packet& Packet::operator <<(long long toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(long long &destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}



Packet& Packet::operator <<(unsigned long long toAdd){
	append(&toAdd,sizeof(toAdd));
	return *this;
}


Packet& Packet::operator >>(unsigned long long &destination){
	memcpy(&destination,&buffer[readPosition],sizeof(destination));
	readPosition+=sizeof(destination);
	return *this;
}





Packet& Packet::operator <<(const std::string&toAdd){
	*this<<toAdd.length();


	for(int i=0;i<toAdd.length();i++){
		*this<<toAdd[i];
	}

	return *this;
}


Packet& Packet::operator >>(std::string&destination){
	
	size_t length;

	*this>>length;

	destination.assign(&buffer[readPosition],length);


	readPosition+=length;
	return *this;
}

const void* Packet::getData() const {
	return &buffer[0];
}


size_t Packet::getNumBytes() const{
	return buffer.size();
}


