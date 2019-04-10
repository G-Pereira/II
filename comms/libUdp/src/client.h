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


/**
  Class for sending/reciving data from/to %server.
  Implements network %client.
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
class client : public tcpip
{
 public:
/**
  Default constructor.
  Initialize variables.
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  client ();
/**
  Default destructor.
  Free any allocated momory.
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  ~client ();
 protected:
/**
  Returns last recived data.
  \return recived string
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  char* get_recived();
/**
  Sends data (string) to the %server.
  \param  host hostname or IP address of the %server
  \param  service port number of the %server
  \param  packet a string to send
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  void send (char* host, char* service, char* packet);
/**
  Sends data (string) to the %server, waits for response from this %server and then recives it.
  \param  host hostname or IP address of the %server
  \param  service port number of the %server
  \param  packet a string to send
  \return "true" if everything is OK or "false" if there is an error
  \bug    Timeout doesn't seem to work correctly.
  \author Marcin Caban
  \date   Thu Jan 17 01:41:18 2002
*/
  bool recive (char* host, char* service, char* packet);
 private:
/**
  Last recived string.
  Stores last recived data from a %server.
*/
  char* recived;
};

