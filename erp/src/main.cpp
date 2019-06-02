#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <string> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include "Database.h"

#define PORT    54321
#define MAXLINE 1024

void printMenu(WINDOW* win){
    wclear(win);
    int x = 0;
    int y = 0;

    getmaxyx(win, y, x);

    mvprintw(2, (x-25)/2, " ______   _____    _____  ");
    mvprintw(3, (x-25)/2, "|  ____| |  __ \\  |  __ \\ ");
    mvprintw(4, (x-25)/2, "| |__    | |__) | | |__) |");
    mvprintw(5, (x-25)/2, "|  __|   |  _  /  |  ___/ ");
    mvprintw(6, (x-25)/2, "| |____  | | \\ \\  | |     ");
    mvprintw(7, (x-25)/2, "|______| |_|  \\_\\ |_|     ");

    mvprintw(10, (x-10)/2, "1: Orders");
    mvprintw(11, (x-10)/2, "2: Machines");
    mvprintw(12, (x-10)/2, "3: Pushers");
    mvprintw(13, (x-10)/2, "4: Send xml");
    mvprintw(y-1, x-17, "Press 'q' to exit");
}

void printOrders(WINDOW* win){
    int x = 0;
    int y = 0;

    getmaxyx(win, y, x);

    mvprintw(2, (x-44)/2, "   ____  _____  _____  ______ _____   _____ ");
    mvprintw(3, (x-44)/2, "  / __ \\|  __ \\|  __ \\|  ____|  __ \\ / ____|");
    mvprintw(4, (x-44)/2, " | |  | | |__) | |  | | |__  | |__) | (___  ");
    mvprintw(5, (x-44)/2, " | |  | |  _  /| |  | |  __| |  _  / \\___ \\ ");
    mvprintw(6, (x-44)/2, " | |__| | | \\ \\| |__| | |____| | \\ \\ ____) |");
    mvprintw(7, (x-44)/2, "  \\____/|_|  \\_\\_____/|______|_|  \\_\\_____/ ");

    mvprintw(10, (x-115)/2, "ID\tState\t\t# Done\t# Prod\t# Pend\tTime In\t\t\tTime Start\t\tTime End");

    mvprintw(y-1, x-17, "Press 'q' to exit");
}

void printMachines(WINDOW* win){
    int x = 0;
    int y = 0;

    getmaxyx(win, y, x);

    mvprintw(2, (x-57)/2, "  __  __          _____ _    _ _____ _   _ ______  _____ ");
    mvprintw(3, (x-57)/2, " |  \\/  |   /\\   / ____| |  | |_   _| \\ | |  ____|/ ____|");
    mvprintw(4, (x-57)/2, " | \\  / |  /  \\ | |    | |__| | | | |  \\| | |__  | (___  ");
    mvprintw(5, (x-57)/2, " | |\\/| | / /\\ \\| |    |  __  | | | | . ` |  __|  \\___ \\ ");
    mvprintw(6, (x-57)/2, " | |  | |/ ____ \\ |____| |  | |_| |_| |\\  | |____ ____) |");
    mvprintw(7, (x-57)/2, " |_|  |_/_/    \\_\\_____|_|  |_|_____|_| \\_|______|_____/ ");

    mvprintw(10, (x-95)/2, "ID\t\t\tT Op\t# N1\t# N2\t# N3\t# N4\t# N5\t# N6\t# N7\t# N8\t# N9");

    mvprintw(y-1, x-17, "Press 'q' to exit");
}

void printPushers(WINDOW* win){
    int x = 0;
    int y = 0;

    getmaxyx(win, y, x);

    mvprintw(2, (x-51)/2, "  _____  _    _  _____ _    _ ______ _____   _____ ");
    mvprintw(3, (x-51)/2, " |  __ \\| |  | |/ ____| |  | |  ____|  __ \\ / ____|");
    mvprintw(4, (x-51)/2, " | |__) | |  | | (___ | |__| | |__  | |__) | (___  ");
    mvprintw(5, (x-51)/2, " |  ___/| |  | |\\___ \\|  __  |  __| |  _  / \\___ \\ ");
    mvprintw(6, (x-51)/2, " | |    | |__| |____) | |  | | |____| | \\ \\ ____) |");
    mvprintw(7, (x-51)/2, " |_|     \\____/|_____/|_|  |_|______|_|  \\_\\_____/ ");

    mvprintw(10, (x-75)/2, "ID\t# N1\t# N2\t# N3\t# N4\t# N5\t# N6\t# N7\t# N8\t# N9");

    mvprintw(y-1, x-17, "Press 'q' to exit");
}

void printOrderList(WINDOW* win, vector<vector<string>> orders){
    int x = 0;
    int y = 0;

    getmaxyx(win, y, x);
    int i = 0;

    for(vector<string> order : orders){
        std::string state;
        if(order.at(1) == "0")
            state = "Pending\t";
        else if (order.at(1) == "1")
            state = "Process\t";
        else
            state = "Complete";
        
        mvprintw(11+i, (x-115)/2, (std::string(4 - order.at(0).length(), '0') + order.at(0) + "\t" + state + "\t"+ order.at(4) +"\t"+ order.at(3) +"\t"+ order.at(2) +"\t"+ order.at(5) +"\t"+ order.at(6) +"\t"+ order.at(7)).c_str());
        i++;
    }
}

void printMachineList(WINDOW* win, vector<vector<string>> machines){
    int x = 0;
    int y = 0;

    getmaxyx(win, y, x);
    int i = 0;

    for(vector<string> machine : machines){
        std::string nm;
        if(machine.at(0)[0] == '1')
            nm = "1";
        else if (machine.at(0)[0] == '2')
            nm = "2";
        else if (machine.at(0)[0] == '3')
            nm = "3";
        else if (machine.at(0)[0] == '4')
            nm = "4";
        std::string m = "Cell " + nm + " Machine " + machine.at(0)[1] + machine.at(0)[2];
        
        mvprintw(11+i, (x-95)/2, (m + "\t" + machine.at(1) + "\t"+ machine.at(2) + "\t"+ machine.at(3) + "\t"+ machine.at(4) + "\t"+ machine.at(5) + "\t"+ machine.at(6) + "\t"+ machine.at(7) + "\t"+ machine.at(8) + "\t"+ machine.at(9) + "\t"+ machine.at(10)).c_str());
        i++;
    }
}

void printPusherList(WINDOW* win, vector<vector<string>> pushers){
    int x = 0;
    int y = 0;

    getmaxyx(win, y, x);
    int i = 0;

    for(vector<string> pusher : pushers){
        mvprintw(11+i, (x-75)/2, (std::string(4 - pusher.at(9).length(), '0') + pusher.at(9) + "\t"+ pusher.at(0) + "\t"+ pusher.at(1) + "\t"+ pusher.at(2) + "\t"+ pusher.at(3) + "\t"+ pusher.at(4) + "\t"+ pusher.at(5) + "\t"+ pusher.at(6) + "\t"+ pusher.at(7) + "\t"+ pusher.at(8)).c_str());
        i++;
    }
}

std::string printAsk(WINDOW* win, std::string toAsk){
    std::string input;

    int x = 0;
    int y = 0;

    getmaxyx(win, y, x);

    mvprintw(y-1, 0, toAsk.c_str());
    //wmove(win, y-1, 2);
    echo();
    refresh();
    cin >> input;
    return input;
}

void sayGoodbye(WINDOW* win){
    int x = 0;
    int y = 0;

    getmaxyx(win, y, x);

    char print[] = "Closing ERP";

    clear();
    mvprintw(y/2, (x-strlen(print))/2, print);
    refresh();

    usleep(2000000);
}

// funtion sending file 
string readFile(FILE* fp) 
{
    std::string fdata;
    char buf = fgetc(fp);
    while (buf != EOF){
        cout << buf;
        fdata += buf;
        buf = fgetc(fp);
    }
    return fdata; 
} 

string sendUDP(){
    int sockfd; 
    struct sockaddr_in servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("10.227.156.230"); 
    
    FILE* fp = fopen("orders.xml", "r");
    if (fp == NULL){
        beep();
        return "";
    }

    std::string data = readFile(fp);

    sendto(sockfd, data.c_str(), data.size(), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr));
    
    /*char buffer[MAXLINE];
    unsigned int n, rlen;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &rlen); 
    buffer[n] = '\0';*/
  
    close(sockfd);
    fclose(fp);
    return string("");
}

int main() {
    Database db(false);
    WINDOW* mainWin = initscr(); // init ncurses
    noecho(); // don't echo as we type
	
    while(true){
        printMenu(mainWin);

        refresh();			/* Print it on to the real screen */

        char ch = getch();
        
        if (ch == 'q')
            break;
        else if(ch == '1') {
            wclear(mainWin);
            WINDOW* ordersWin = initscr(); // init ncurses
            noecho(); // don't echo as we type
            printOrders(ordersWin);
            refresh();			/* Print it on to the real screen */
            while(true){
                std::vector<std::vector<string>> orders = db.select("orders", "true ORDER BY timein");
                printOrderList(ordersWin, orders);

                timeout(1000);
                char orderch = getch();
                if (orderch == 'q')
                break;
            }
        } else if(ch == '2') {
            wclear(mainWin);
            WINDOW* machinesWin = initscr(); // init ncurses
            noecho(); // don't echo as we type
            printMachines(machinesWin);
            refresh();			/* Print it on to the real screen */
            while(true){
                std::vector<std::vector<string>> machines = db.select("machine", "true ORDER BY id");
                printMachineList(machinesWin, machines);

                timeout(1000);
                char machinech = getch();
                if (machinech == 'q')
                break;
            }
        } else if(ch == '3') {
            wclear(mainWin);
            WINDOW* pushersWin = initscr(); // init ncurses
            noecho(); // don't echo as we type
            printPushers(pushersWin);
            refresh();			/* Print it on to the real screen */
            while(true){
                std::vector<std::vector<string>> pushers = db.select("pusher", "true ORDER BY id");
                printPusherList(pushersWin, pushers);

                timeout(1000);
                char pusherch = getch();
                if (pusherch == 'q')
                break;
            }
        }
        else if(ch == '4'){
            sendUDP();
        }
    }

    sayGoodbye(mainWin);

    endwin();			/* End curses mode		  */
    //cout << sendUDP() << endl;
    return 0;
}