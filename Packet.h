#ifndef PACKET_H
#define PACKET_H

#include<vector>
#include<cstring>
#include<string>
#include<iostream>

class Packet{
	private:
		std::vector<char> buffer;
		int readPosition;
		void append(const void*data,unsigned sizeInBytes);
	public:
		Packet();
		Packet&operator <<(char toAdd);
		Packet&operator >>(char&destination);


		Packet&operator <<(short toAdd);
		Packet&operator >>(short&destination);

		Packet&operator <<(unsigned short toAdd);
		Packet&operator >>(unsigned short&destination);


		Packet&operator <<(int toAdd);
		Packet&operator >>(int&destination);

	
		Packet&operator <<(unsigned toAdd);
		Packet&operator >>(unsigned &destination);

		Packet&operator <<(long toAdd);
		Packet&operator >>(long &destination);	

		Packet&operator <<(unsigned long toAdd);
		Packet&operator >>(unsigned long &destination);	

		Packet&operator <<(long long  toAdd);
		Packet&operator >>(long long &destination);	

		Packet&operator <<(unsigned long long  toAdd);
		Packet&operator >>(unsigned long long &destination);	

		Packet&operator <<(const std::string &toAdd);
		Packet&operator >>(std::string &destination);

		const void* getData() const;
		size_t getNumBytes() const;

		friend class TcpSocket;
		
};
#endif
