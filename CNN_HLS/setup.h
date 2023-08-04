#ifndef ENV_SETUP_H_
#define ENV_SETUP_H_

#include <string>
#include <vector>
#include "packet_size.h"
#include "galapagos_net_udp.hpp"
#include "galapagos_node.hpp"

typedef ap_uint<PACKET_DATA_LENGTH> T;

#define IP_ADDR_1 "127.0.0.1"
#define IP_ADDR_2 "127.0.0.1"


void setupEnvironment()
{

//     std::vector <std::string> kern_info;

//     std::string source_ip_str;
//     std::string dest_ip_str;

//     source_ip_str=IP_ADDR_1;
//     dest_ip_str=IP_ADDR_2;

//     kern_info.push_back(source_ip_str);
//     kern_info.push_back(dest_ip_str);

// #if LOG_LEVEL > 0    
//     std::shared_ptr<spdlog::logger> my_logger;
//     my_logger = spdlog::basic_logger_mt("basic_logger", "CNN_HLS_log.txt"); 
// #endif

//     std::vector < galapagos::external_driver<T> * > ext_drivers;
//     std::unique_ptr<galapagos::net::udp <T> > net_ptr;
//     std::unique_ptr<galapagos::node <T> > node_ptr;

// #if LOG_LEVEL > 0    
//         net_ptr = std::make_unique<galapagos::net::udp <T> > (
//                         4567, 
//                         kern_info, 
//                         source_ip_str, 
//                         my_logger
//                         );
// #else
//         net_ptr = std::make_unique<galapagos::net::udp <T> > (
//                         4567, 
//                         kern_info, 
//                         source_ip_str
//                         );
// #endif

}

#endif