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


#include "tcpip.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


/**
  Class for communicating with clients.
  Implements network %server.
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
class server : public tcpip
{
 public:
/**
  Default constructor.
  Initialize variables.
  Opens UDP socket for listening.
  \param  service listen port number
  \todo   Make availability to open TCP as well as UDP socket.
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  server (char* service);
/**
  Default destructor.
  Free any allocated momory. Closes any open sockets.
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  ~server ();
 protected:
/**
  Returns last recived data.
  \return recived string
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  char* get_recived();
/**
  Sends data (string) to the %client.
  \param  packet a string to send
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  void answer (char* packet);
/**
  Starts listening for %client, recives data from %client on UDP port.
  \return "true" if everything is OK or "false" if there is an error
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  bool listenUDP ();
/**
  Starts listening for %client, recives data from %client on TCP port.
  \return "true" if everything is OK or "false" if there is an error
  \todo   implenent this function (now it is just a copy of listenUDP)
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  bool listenTCP (); private:
/**
  Last recived string.
  Stores last recived data from a %server.
*/
  char* recived;
/**
  Server socket.
  Stores %server socket.
*/
  int sock;
  struct sockaddr_in addr;
  socklen_t addr_len;
};

