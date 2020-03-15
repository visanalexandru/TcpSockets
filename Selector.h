#ifndef SELECTOR_H
#define SELECTOR_H


#include"Socket.h"
#include<set>


class Selector{

	private:
		fd_set socket_set;
		std::set<int> descriptors;


	public:
		void add(const Socket&sock);
		void remove(const Socket&sock);
		void clear();
		bool wait();//waits until sock is ready
		bool isReady(const Socket&sock);

};

#endif
