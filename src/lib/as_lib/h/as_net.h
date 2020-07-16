/*
 * Copyright (C) 2020-2025 ASHINi corp. 
 * 
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version. 
 * 
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * Lesser General Public License for more details. 
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA 
 * 
 */

#ifndef _AS_NET_H_
#define _AS_NET_H_

#define ASI_DFT_GET_NETIFACE_CNT			20


extern char *inet_ntoa(struct in_addr in, char *buf, int len);
extern int get_ipaddr_by_url(char *url, char *ipaddr, int len);
extern void get_ipaddr_by_sock(int sock, char *buf, int buf_len);
extern int get_ipaddr_by_netiface(char *netiface, unsigned int *ipaddr);
extern int get_macaddr_by_netiface(char *netiface, unsigned char *macaddr);
extern int get_netiface_by_ipaddr(unsigned int ipaddr, 
		char *iface, int iface_len);
extern int get_netiface_by_macaddr(unsigned char *mac_addr, 
		char *iface, int iface_len);
extern int get_first_macaddr(unsigned char *macaddr);


#endif /* _AS_NET_H_ */


