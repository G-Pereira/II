/**

C++ tcp/ip and udp/ip library and example programm
Copyright (C) 2002  Marcin Caban 'Cabko' and Borys Wisniewski 'Boria'

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
http://www.gnu.org/

Marcin Caban
e-mail: cabko@polsl.gliwice.pl
phone: +48 501 452 123

Borys Wisniewski
e-mail: boria@polsl.gliwice.pl
phone: +48 503 065 996

*/


/**
  TCP/IP and UDP/IP connection class.
  Class for openning sockets to connect somewhere or to listening for a connections.
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
#if !defined tcpip_exists
#define tcpip_exists
class tcpip
{
 public:
/**
  Default constructor.
  Does nothing special.
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  tcpip ();
/**
  Default destructor.
  Does nothing special.
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  ~tcpip ();
 protected:
/**
  Opens socket for communicating with TCP %server.
  \param  host hostname or IP address of the %server
  \param  service port number of the %server
  \return network socket descriptor
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  int connectTCP (char* host, char* service);
/**
  Opens socket for communicating with UDP %server.
  \param  host hostname or IP address of the %server
  \param  service port number of the %server
  \return network socket descriptor
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  int connectUDP (char* host, char* service);
/**
  Opens socket for listening for TCP connections from clients.
  \param  service port number for listening
  \param  qlen maximal length of requests queue
  \return network socket descriptor
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  int passiveTCP (char* service, int qlen);
/**
  Opens socket for listening for UDP packages from clients.
  \param  service port number of the %server
  \return network socket descriptor
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  int passiveUDP (char* service);
 private:
/**
  PortBase.
  Every port number in this class is incremented by value of this variable.
  \todo   Make availability to change value of this variable, now it is always equal to 0.
*/
  unsigned short int  portbase;
/**
  Opens socket for communicating with TCP or UDP %server.
  \param  host hostname or IP address of the %server
  \param  service port number of the %server
  \param  protocol "TCP" or "UDP"
  \return network socket descriptor
  \author Marcin Caban (based on examples from "Internetworking with TCP/IP" written by Douglas E. Comer and David L. Stevens)
  \date   Thu Jan 17 01:41:18 2002
*/
  int connectsock (char* host, char* service, char* protocol);
/**
  Opens socket for listening for TCP or UDP clients.
  \param  service port number of the %server
  \param  protocol "TCP" or "UDP"
  \param  qlen maximal length of requests queue (for UDP qlen = 0)
  \return network socket descriptor
  \author Marcin Caban (based on examples from "Internetworking with TCP/IP" written by Douglas E. Comer and David L. Stevens)
  \date   Thu Jan 17 01:41:18 2002
*/
  int passivesock (char* service, char* protocol, int qlen);
};
#endif

