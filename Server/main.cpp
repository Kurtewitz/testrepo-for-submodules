//
//  main.cpp
//  Server2
//
//  Created by intx on 22.09.18.
//  Copyright © 2018 intx. All rights reserved.
//

#include "TCP_Server.hpp"
//#include <mysql_driver.h>
//#include <mysql_connection.h>
//#include <cppconn/*.h>

int main(int argc, const char * argv[]) {
    try {
        boost::asio::io_service io_service;
        std::shared_ptr<Connection_Manager> c_manager(new Connection_Manager());
        TCP_Server tcp_Server(io_service, c_manager);
        io_service.run();
        std::cout << "IM AFTER .run()" << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
