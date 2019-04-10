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


#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#include <unistd.h>
#include "const.h"
#include "string.h"
#include "serverDemo.h"


serverDemo :: serverDemo (char* new_service) : server (new_service)
{
  service = NULL;
  packet = NULL;
  service = new char [ strlen (new_service) +1 ];
  assert (service != NULL);
  strcpy (service, new_service);
}

serverDemo :: ~serverDemo ()
{
  if (service != NULL)
    delete service;
  if (packet != NULL)
    delete packet;
}


void serverDemo :: start ()
{
  cout << "\n### Hello !\n";
  while (true)
  {
    if (listenUDP () == false)
	{
      sleep (1);
	  continue;
	}
    cout << get_recived () << "\n";
    answer ("### I'm a server. I've just recived message from You.");
  }
  cout << "\n### Goodbye !\n";
}

