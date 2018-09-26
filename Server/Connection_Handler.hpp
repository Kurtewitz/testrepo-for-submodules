//
//  Connection_Handler.hpp
//  Server2
//
//  Created by intx on 23.09.18.
//  Copyright © 2018 intx. All rights reserved.
//

#ifndef Connection_Handler_hpp
#define Connection_Handler_hpp

#include "Game.hpp"

class Connection_Manager
{
public:
    Connection_Manager();
    ~Connection_Manager();
    
    void new_Connection(boost::asio::ip::tcp::socket socket);
private:
    std::multimap<std::shared_ptr<Game>, std::shared_ptr<Connection>> mmap_;
    
};

#endif /* Connection_Handler_hpp */
