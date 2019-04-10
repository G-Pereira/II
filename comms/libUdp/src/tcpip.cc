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


#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <assert.h>
#include "const.h"
#include "tcpip.h"


extern int errno;
extern char* sys_errlist[];


tcpip :: tcpip ()
{
  portbase = 0;
}

tcpip :: ~tcpip ()
{
}


int tcpip :: connectTCP (char *host, char *service)
{
  return connectsock (host, service, "tcp");
}

int tcpip :: connectUDP (char *host, char *service)
{
  return connectsock (host, service, "udp");
}

int tcpip :: passiveTCP (char *service, int qlen)
{
  return passivesock (service, "tcp", qlen);
}

int tcpip :: passiveUDP (char *service)
{
  return passivesock (service, "udp", 0);
}

int tcpip :: connectsock (char *host, char *service, char* protocol)
{
  struct hostent *phe;
  struct servent *pse;
  struct protoent *ppe;
  struct sockaddr_in sin;
  int s;
  int type;
  bzero ((char*) &sin, sizeof (sin));
  sin.sin_family = AF_INET;
  if ((pse = getservbyname (service, protocol)))
    sin.sin_port = pse -> s_port;
  else if ((sin.sin_port = htons ((ushort) atoi (service))) == 0)
    {
      cerr << _NET_ERR_ << "can't get \"" << service << "\" service entry.\n";
      exit (1);
    }
  if ((phe = gethostbyname (host)))
    bcopy (phe -> h_addr, (char*) &sin.sin_addr, phe -> h_length);
  else if ((sin.sin_addr.s_addr = inet_addr (host)) == INADDR_NONE)
    {
      cerr << _NET_ERR_ << "can't get \"" << host << "\" host entry.\n";
      exit (1);
    }
  if ((ppe = getprotobyname (protocol)) == 0)
    {
      cerr << _NET_ERR_ << "can't get \"" << protocol << "\" protocol entry.\n";
      exit (1);
    }
  if (strcmp (protocol, "udp") == 0)
    type = SOCK_DGRAM;
  else
    type = SOCK_STREAM;
  s = socket (PF_INET, type, ppe -> p_proto);
  if (s<0)
    {
      cerr << _NET_ERR_ << "can't create socket: " << sys_errlist [errno] << "\n";
      exit (1);
    }
  if (connect (s, (struct sockaddr *) &sin, sizeof (sin)) < 0)
    {
      cerr << _NET_ERR_ << "can't connect to " << host << " " << service << ": " << sys_errlist [errno] << "\n";
      exit (1);
    }
  return s;
}

int tcpip :: passivesock (char *service, char *protocol, int qlen)
{
  struct servent *pse;
  struct protoent *ppe;
  struct sockaddr_in sin;
  int s;
  int type;
  bzero ((char*) &sin, sizeof (sin));
  sin.sin_family = AF_INET;
  if ((pse = getservbyname (service, protocol)))
    sin.sin_port = htons (ntohs ((u_short) pse -> s_port) + portbase);
  else if ((sin.sin_port = htons ((ushort) atoi (service))) == 0)
    {
      cerr << _NET_ERR_ << "can't get \"" << service << "\" service entry.\n";
      exit (1);
    }
  if ((ppe = getprotobyname (protocol)) == 0)
    {
      cerr << _NET_ERR_ << "can't get \"" << protocol << "\" protocol entry.\n";
      exit (1);
    }
  if (strcmp (protocol, "udp") == 0)
    type = SOCK_DGRAM;
  else
    type = SOCK_STREAM;
  s = socket (PF_INET, type, ppe -> p_proto);
  if (s<0)
    {
      cerr << _NET_ERR_ << "can't create socket: " << sys_errlist [errno] << "\n";
      exit (1);
    }
  if (bind (s, (struct sockaddr *) &sin, sizeof (sin)) < 0)
    {
      cerr << _NET_ERR_ << "can't bind to " << service << "port: " << sys_errlist [errno] << "\n";
      exit (1);
    }
  if (type == SOCK_STREAM && listen (s, qlen) < 0)
    {
      cerr << _NET_ERR_ << "can't listen on " << service << "port: " << sys_errlist [errno] << "\n";
      exit (1);
    }
  return s;
}

