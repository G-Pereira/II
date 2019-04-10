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


#include <sys/time.h>
#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "const.h"
#include "client.h"


extern int errno;
extern char* sys_errlist[];


client :: client () : tcpip ()
{
  recived = NULL;
}

client :: ~client ()
{
  if (recived != NULL)
    delete recived;
}


void client :: send (char* host, char* service, char* packet)
{
  int sock;
  sock = connectUDP (host, service);
  (void) write (sock, packet, strlen (packet));
  close (sock);
}

bool client :: recive (char* host, char* service, char* packet)
{
  char buff[2048];
  buff[1] = '\0';
  int sock;
  int length;
  sock = connectUDP (host, service);
  write (sock, packet, strlen (packet));
/*
  fd_set rfds;
  struct timeval tv;
  tv.tv_sec = 3;
  tv.tv_usec = 0;
  FD_ZERO (&rfds);
  FD_SET (sock, &rfds);
  int a = select (1, &rfds, NULL, NULL, &tv);
  if (a == 0)
    {
      cerr << _NET_ERR_ << "read failed: Socket Timeout\n";
      return false;
    }
  if (a < 0)
    {
      cerr << _NET_ERR_ << "select failed: " << sys_errlist [errno] << "\n";
      return false;
    }
*/
  length = read (sock, buff, sizeof (buff));
  close (sock);
  if (length < 0)
    {
      cerr << _NET_ERR_ << "read failed: " << sys_errlist [errno] << "\n";
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

char* client :: get_recived ()
{
  return recived;
}

