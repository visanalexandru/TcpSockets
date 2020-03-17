#ifndef PACKET_H
#define PACKET_H

#include<vector>
#include<cstring>
#include<string>
#include<iostream>
#include <netinet/in.h>
#include <endian.h>


class Packet{
	private:
		std::vector<char> buffer;
		std::uint32_t readPosition;
		void append(const void*data,unsigned sizeInBytes);
	public:
		Packet();
		Packet&operator <<(std::int8_t toAdd);
		Packet&operator >>(std::int8_t&destination);

		Packet&operator <<(std::uint8_t toAdd);
		Packet&operator >>(std::uint8_t&destination);

		Packet&operator <<(std::int16_t toAdd);
		Packet&operator >>(std::int16_t&destination);

		Packet&operator <<(std::uint16_t toAdd);
		Packet&operator >>(std::uint16_t&destination);


		Packet&operator <<(std::int32_t toAdd);
		Packet&operator >>(std::int32_t&destination);

	
		Packet&operator <<(std::uint32_t toAdd);
		Packet&operator >>(std::uint32_t &destination);

		Packet&operator <<(std::int64_t  toAdd);
		Packet&operator >>(std::int64_t  &destination);	

		Packet&operator <<(std::uint64_t toAdd);
		Packet&operator >>(std::uint64_t &destination);	

		Packet&operator <<(const std::string &toAdd);
		Packet&operator >>(std::string &destination);

		const void* getData() const;
		std::uint32_t getNumBytes() const;

		friend class TcpSocket;
		
};
#endif
