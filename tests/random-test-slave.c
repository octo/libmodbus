/*
 * Copyright © 2008 Stéphane Raimbault <stephane.raimbault@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "modbus.h"

#define SLAVE 0x11

int main(void)
{
        int socket;
        modbus_param_t mb_param;
        modbus_mapping_t mb_mapping;
        int ret;

        modbus_init_tcp(&mb_param, "127.0.0.1", 1502, SLAVE);
        /* modbus_set_debug(&mb_param, TRUE); */

        ret = modbus_mapping_new(&mb_mapping, 500, 500, 500, 500);
        if (ret < 0) {
                printf("Memory allocation failed\n");
                exit(1);
        }

        socket = modbus_slave_listen_tcp(&mb_param, 1);
        modbus_slave_accept_tcp(&mb_param, &socket);

        while (1) {
                uint8_t query[MAX_MESSAGE_LENGTH];
                int ret;

                ret = modbus_slave_receive(&mb_param, -1, query);
                if (ret >= 0) {
                        /* ret is the query size */
                        modbus_slave_manage(&mb_param, query, ret, &mb_mapping);
                } else if (ret == CONNECTION_CLOSED) {
                        /* Connection closed by the client, end of server */
                        break;
                } else {
                        printf("Error in modbus_listen (%d)\n", ret);
                }
        }

        close(socket);
        modbus_mapping_free(&mb_mapping);
        modbus_close(&mb_param);

        return 0;
}
