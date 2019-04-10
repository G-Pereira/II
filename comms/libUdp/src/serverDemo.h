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


#include "server.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


/**
  Class implements chat %server.
  \author Borys Wisniewski
  \date   Mon Jan 28 19:25:28 2002
*/
class serverDemo : public server
{
 public:
/**
  Default constructor.
  Initialize variables.
  \param  service port number
  \author Borys Wisniewski
  \date   Mon Jan 28 19:25:28 2002
*/
  serverDemo (char* service);
/**
  Default destructor.
  Frees any allocated memory.
  \param  service listen port number
  \author Borys Wisniewski
  \date   Mon Jan 28 19:25:28 2002
*/
 ~serverDemo ();
/**
  Starts the %server.
  \author Borys Wisniewski
  \date   Mon Jan 28 19:25:28 2002
*/
  void start ();
 protected:
 private:
/**
  port number
*/
  char* service;
/**
 last recived data
*/
  char* packet;
};

