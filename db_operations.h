#ifndef DB_OPERATIONS_H
#define DB_OPERATIONS_H

#include <mysql/mysql.h>

#define MAX_IP_SIZE 15
#define MAX_MASK_SIZE 15
#define MAX_LINE_SIZE (MAX_IP_SIZE + MAX_MASK_SIZE + 2)

void load_ip_addresses(MYSQL *conn);
void list_ip_addresses();
void add_ip_address(MYSQL *conn);
void delete_ip_address(MYSQL *conn);
int validate_ip_address(char *ipAddress);
int validate_subnet_mask(char *subnetMask);
void filterBySubnet(MYSQL* conn);
void ip_to_binary();

#endif
