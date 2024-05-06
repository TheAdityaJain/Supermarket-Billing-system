/*-----------------------=SUPERMARKET BILLING SYSTEM=------------------------------*/
/****************************START OF PROJECT************************************/ 
#include<conio.h>
#include<iostream>
#include<fstream>

using namespace std;

#define clrscr(); system("cls");
//Class Declaration
class product {     
    int pid;
    char name[50];
    float price, qty, tax, dis;
    public:
        void create_product() {
                cout << "\nEnter The Name of The Product : ";
                cin >> name;
                cout << "\nEnter The Product ID : ";
                cin >> pid;
                cout << "\nEnter The Price of The Product : ";
                cin >> price;
                cout << "\nEnter The Discount (%) : ";
                cin >> dis;
            }
        void show_product() {
            cout << "\nName of The Product : " << name;
            cout << "\nProduct ID : " << pid;
            cout << "\nPrice : " << price;
            cout << "\nDiscount : " << dis;

        }
        int retpid() {
            return pid;
        }
        float retprice() {
            return price;
        }
        char * retname() {
            return name;
        }
        int retdis() {
            return dis;
        }
    };
//Global Declaration of stream object and class object
fstream fp;
product pr;
//Function to Create Product
void write_product() {
    fp.open("list.txt", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();
    cout << "\n\nThe Product Has Been Created ";
    getch();
}
//Function to Display Product
void display_all() {
    clrscr();
    cout << "====================================\n\n";
    cout << "\t  INVENTORY\n\n";
    cout << "====================================\n";
    fp.open("list.txt", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product))) {
        pr.show_product();
        cout << "\n\n====================================\n";
        getch();
    }
    fp.close();
    getch();
}
//Function to Display List of Product
void menu() {
    clrscr();
    fp.open("list.txt", ios:: in );
    if (!fp) {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n";
        cout << "Go To Inventory to create File ";
        cout << "\n\n\nProgram is closing ....";
        getch();
        exit(0);
    }
    cout << "====================================================\n";
    cout << "------------------LIST OF ITEMS---------------------\n";
    cout << "====================================================\n";
    cout << "P.ID.\t\tNAME\t\t\tPRICE\n";
    cout << "====================================================\n";

    while (fp.read((char * ) & pr, sizeof(product))) {
        cout << pr.retpid() << "\t\t" << pr.retname() 
        << "\t\t" << pr.retprice() << endl;
    }
    fp.close();
    cout << "====================================================\n";
}
//Function to Place Order and Generate Bill
void place_order() {
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\nPLACE YOUR ORDER";
    do {
        cout << "\n\nEnter The Product ID : ";
        cin >> order_arr[c];
        cout << "\nQuantity : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n)" << endl;
        cin >> ch;
    } 
    while (ch == 'y' || ch == 'Y');
    cout << "\n====================================================\n";
    cout << "Thank You For Placing The Order\n";
    cout << "====================================================\n";
    getch();
    clrscr();
    cout << "=====================================================================================================\n";
    cout << "\nPr Id.\t\tPr Name\t\tQuantity\t\tPrice\t\tAmount\t\tFinal Amount\n ";
    cout << "\n=====================================================================================================\n";
    for (int x = 0; x <= c; x++) {
        fp.open("list.txt", ios:: in );
        fp.read((char * ) & pr, sizeof(product));
        while (!fp.eof()) {
            if (pr.retpid() == order_arr[x]) {
                amt = pr.retprice() * quan[x];
                damt = amt - (amt * pr.retdis() / 100);
                cout << "\n" << order_arr[x] << "\t\t" << pr.retname() 
                <<"\t" << quan[x] << "\t\t\t" << pr.retprice() 
                << "\t\t" << amt << "\t\t" << damt;
                total += damt;
            }
            fp.read((char * ) & pr, sizeof(product));
        }
        fp.close();
    }
    cout << "\n\n=====================================================================================================";
    cout << "\n\t\t\t\t\tTotal Amount : " << total;
    cout << "\n=====================================================================================================\n";
    getch();
}
//Function for Introduction
void intro() {
    clrscr();
    cout << "\n\n\n\t====================================================\n";
    cout << "\n\t\t  SUPER MARKET BILLING SYSTEM";
    cout << "\n\n\t====================================================\n";
    cout << "\a";
    getch();
}
//Function for Inventory
void admin_menu() {
    clrscr();
    char ch2;
    cout << "\n\n\n\tINVENTORY";
    cout << "\n\n\t1.Create Product in Inventory";
    cout << "\n\n\t2.Display Products in Inventory";
    cout << "\n\n\t3.Main Menu";
    cout << "\n\n\tPlease Enter Your Choice (1-3) ";
    ch2 = getche();
    switch (ch2) {
    case '1':
        clrscr();
        write_product();
        break;
    case '2':
        display_all();
        break;
    case '3':
        break;
    default:
        cout << "\a";
        admin_menu();
    }
}
//The Main Menu of Billing System
int main() {
    char ch;
    intro();
    do {
        clrscr();
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. Billing Section";
        cout << "\n\n\t02. Inventory";
        cout << "\n\n\t03. Exit";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        ch = getche();
        switch (ch) {
        case '1':
            clrscr();
            place_order();
            getch();
            break;
        case '2':
            admin_menu();
            break;
        case '3':
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != '3');

    return 0;
}
/****************************END OF PROJECT************************************/ 