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
*/


#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "const.h"
#include "server.h"


extern int errno;
extern char* sys_errlist[];


server :: server (char* service) : tcpip ()
{
  recived = NULL;
  sock = passiveUDP (service);
}

server :: ~server ()
{
  if (recived != NULL)
    delete recived;
  close (sock);
}


void server :: answer (char* packet)
{
  (void) sendto (sock, packet, strlen (packet), 0, (struct sockaddr *) &addr, addr_len);
}

bool server :: listenUDP ()
{
  char buff[2048];
  buff[1] = '\0';
  int length = recvfrom (sock, buff, sizeof (buff), 0, (struct sockaddr *) &addr, &addr_len);
  if (length < 0)
    {
      cerr << _NET_ERR_ << "listen failed: " << sys_errlist [errno] << "\n";
      return false;
    }
  buff[length] = '\0';
  if (recived != NULL)
    delete recived;
  recived = NULL;
  recived = new char [length+1];
  assert (recived != NULL);
  strcpy (recived, buff);
  return true;
}

bool server :: listenTCP ()
{
  char buff[2048];
  buff[1] = '\0';
  int length = recvfrom (sock, buff, sizeof (buff), 0, (struct sockaddr *) &addr, &addr_len);
  if (length < 0)
    {
      cerr << _NET_ERR_ << "listen failed: " << sys_errlist [errno] << "\n";
      return false;
    }
  buff[length] = '\0';
  if (recived != NULL)
    delete recived;
  recived = NULL;
  recived = new char [length+1];
  assert (recived != NULL);
  strcpy (recived, buff);
  return true;
}

char* server :: get_recived ()
{
  return recived;
}

