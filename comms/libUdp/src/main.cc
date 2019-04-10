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


#include <iostream.h>
#include <unistd.h>
#include "serverDemo.h"
#include "clientDemo.h"


/**
  Main function.
  \author Borys Wisniewski
  \date   Fri Feb  8 23:52:03 2002
  \todo   make possibility to chat with other clients (now it can talk with %server - the %server
          can not talk to more than one %client - every connected %client talks with %server only)
  \todo   change the program to use TCP/IP, now it uses UDP/IP
  \todo   make a better user interface
*/
int main(int argc, char* argv[])
{
/*
  //  char *command;
  char command[1024];
  int i = 1;

  cout << "Starting Super Experimental X (SEX) Messaging program\n";
  sleep (2);
  cout << "Type 'help' for help\n";
  while (i == 1)
  {
    cout << ":) > ";
//    cin >> command;
    cin.getline ( command, 1024 );
    if ( ! strcmp ( command, "send" ) )
    {
      cout << "Enter user name:";
      cin.getline ( command, 1024 );
      cout << "Enter message:";
      cin.getline ( command, 1024 );
      cout << "Sending\n";
    }
    
    if ( ! strcmp ( command, "read" ) )
      cout << "Reading\n";
    if ( ! strcmp ( command, "help" ) )
    {
      cout << "send - send a message\n";
      cout << "read - read recived message\n";
      cout << "quit - quit program\n";
      cout << "help - display this help\n";
    }
    if ( ! strcmp ( command, "quit" ) )
    {
      cout << "Bye Bye\n";
      break;
    }
  }
*/
  switch (argc)
  {
    case 2:
      if (strcmp(argv[1],"server") == 0)
      {
        serverDemo server ("3999");
        server.start();
      }
      else
      {
        clientDemo client ("3999",argv[1]);
        client.start();
      }
      break;
    default:
      cout << "RTFM!\n";
      break;
  }
  return (0);
}

