#include <iostream>
#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

void password(){
    system("cls");
    cout<<"\n\n\t\t\tYou are registered as Admin!\n";
    cout<<"\n\t\t\tUsername: Admin";
    int flag = 0, count = 3;
    string pass;
    do{
        cout<<"\n\t\t\tEnter password: ";
        cin>>pass;
        if(pass != "PASSWORD") {
            cout<<"\n\t\t\tTry again ("<<count-1<<" tries remaining)."<<endl;
            count--;
            }
        else{
            cout<<"\n\t\t\tYou are logged in!\n\n";
            flag = 1;
            system("pause");
            break;
        }
    }while(flag == 0 && count > 0);

    if(count == 0) exit(0);
}

int main()
{
    FILE *fp, *ft;
    char choice, yn;

    struct student
    {
        char fName[50], lName[50], course[50];
        int section;
    }sdnt;
    char xfName[50], xlName[50];
    long int r_size;

    fp=fopen("users.txt","rb+");

    if (fp == NULL)
    {
        fp = fopen("users.txt","wb+");

        if (fp==NULL)
        {
            puts("Cannot open file");
            return 0;
        }
    }


    r_size = sizeof(sdnt);
    password();
    while(1)
    {
        system("cls");

        cout << "\t\t====== STUDENT DATABASE MANAGEMENT SYSTEM ======";
        cout <<"\n\n                                          ";
        cout << "\n\n";
        cout << "\n \t\t\t 1. Add    Records";
        cout << "\n \t\t\t 2. List   Records";
        cout << "\n \t\t\t 3. Modify Records";
        cout << "\n \t\t\t 4. Delete Records";
        cout << "\n \t\t\t 5. Exit   Program";
        cout << "\n\n";
        cout << "\t\t\t Select Your Choice :=> ";
        fflush(stdin);
        cin>>choice;
        switch(choice)
        {
        case '1' :
            fseek(fp,0,SEEK_END);
            yn ='Y';
            while(yn == 'Y' || yn == 'y')
            {
                system("cls");
                cout << "Enter the First Name : ";
                cin >> sdnt.fName;
                cout << "Enter the Last Name : ";
                cin >> sdnt.lName;
                cout << "Enter the Course    : ";
                cin >> sdnt.course;
                cout << "Enter the Section   : ";
                cin >> sdnt.section;
                fwrite(&sdnt,r_size,1,fp);
                cout << "\n Add yn Record (Y/N) ";
                fflush(stdin);
                cin>>yn;
            }
            break;
        case '2':
            system("cls");
            rewind(fp);
            cout << "=== View the Records in the Database ===";
            cout << "\n";
            while (fread(&sdnt,r_size,1,fp) == 1)
            {
                cout << "\n";
                cout <<"\n" << sdnt.fName << setw(10)  << sdnt.lName;
                cout << "\n";
                cout <<"\n" <<sdnt.course <<  setw(8)  << sdnt.section;
            }
            cout << "\n\n";
            system("pause");
            break;

        case '3' :
            system("cls");
            yn = 'Y';
            while (yn == 'Y'|| yn == 'y')
            {
                cout << "\n Enter the last name of the student : ";
                cin >> xlName;

                rewind(fp);
                while (fread(&sdnt,r_size,1,fp) == 1)
                {
                    if (strcmp(sdnt.lName,xlName) == 0)
                    {
                        cout << "Enter new the Firt Name : ";
                        cin >> sdnt.fName;
                        cout << "Enter new the Last Name : ";
                        cin >> sdnt.lName;
                        cout << "Enter new the Course    : ";
                        cin >> sdnt.course;
                        cout << "Enter new the Section   : ";
                        cin >> sdnt.section;
                        fseek(fp, - r_size, SEEK_CUR);
                        fwrite(&sdnt,r_size,1,fp);
                        break;
                    }
                    else
                        cout<<"record not found";
                }
                cout << "\n Modify yn Record (Y/N) ";
                fflush(stdin);
                cin>>yn;
            }
            break;


        case '4':
            system("cls");
            yn = 'Y';
            while (yn == 'Y'|| yn == 'y')
            {
                cout << "\n Enter the last name of the student to delete : ";
                cin >> xlName;

                ft = fopen("temp.dat", "wb");

                rewind(fp);
                while (fread (&sdnt, r_size,1,fp) == 1)

                    if (strcmp(sdnt.lName,xlName) != 0)
                    {
                        fwrite(&sdnt,r_size,1,ft);
                    }
                fclose(fp);
                fclose(ft);
                remove("users.txt");
                rename("temp.dat","users.txt");

                fp=fopen("users.txt","rb+");

                cout << "\n Delete more Records (Y/N)?"<<endl;
                fflush(stdin);
                cin>>yn;
            }

            break;

        case '5':
            fclose(fp);
            exit(0);
        }
    }


    system("pause");
    return 0;
}
