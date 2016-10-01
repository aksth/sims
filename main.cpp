#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include "global_obj.h" //HANDLE (object) declared globally
#include <fstream>  // header file for file
 
using namespace std;

//Function prototypes

void BlankSpace(int n);
void CharDisplay(int charID, int w); //CharID = Character Set's No, W=Width
void DisplayHeader();
void CategoryHeader(char s []);
void CenterText(char s[]);

void CursorPos(int x, int y);
int GetCursorPosX();
int GetCursorPosY();
string LimitBuffer(int w);

void DisplayMainMenu(int & ChoiceSelected);
void MenuItems(char *a, char*b, char *c, char *d, char *e, char *f, int & selected);

//END of Funciton prototypes

// Class Definitions

class product
{
      protected:
           
           int id;
           char description[25];
           float price;
           //brand, category
                
      public:
             void get_data(int indent)
             {
                    
                    BlankSpace(indent);
                    cout<<"Enter ID: ";
                    cin>>id;
                    cin.clear(); //clear the error bits for the cin input stream
                    cin.sync(); //synchronize the input buffer, discarding any leftover characters in the buffer
                    cout<<endl;
                    BlankSpace(indent);
                    cout<<"Enter Description: ";
                    cin.getline(description,25); 
                    cout<<endl;
                    BlankSpace(indent);
                    cout<<"Enter Price: ";
                    cin>>price;
             }
             void show_data(int indent){
                    BlankSpace(indent);
                    cout.width(10);
                    cout<<id;
                    cout.setf(ios::left);
                    cout<<"       ";
                    cout.width(25);
                    cout<<description;
                    cout.unsetf(ios::left);
                    cout.width(15);
                    cout<<price<<endl;
                }
                
             void record_header(int indent){
                    BlankSpace(indent);
                    SetConsoleTextAttribute(hConsole, 14);
                    cout.width(10);
                    cout<<"ID";
                    cout.setf(ios::left);
                    cout<<"       ";
                    cout.width(25);
                    cout<<"DESCRIPTION";
                    cout.unsetf(ios::left);
                    cout.width(15);
                    cout<<"PRICE"<<endl<<endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                int IDCheck(int IDRead)
                {
                    if(id==IDRead)  // if ID is matched it returns 1
                        return 1;
                    
                    return 0;
                }
                
                char* get_description()
                {
                     return description;
                }
                float get_price()
                {
                     return price;
                }
                
                void DisplayProductsMenu(int & PMSelected)
                {
                     DisplayHeader(); // ========= Header
                     cout<<endl;
                     CategoryHeader("PRODUCTS");
                     cout<<endl<<endl<<endl;
                     MenuItems("ADD PRODUCTS","VIEW PRODUCTS","EDIT PRODUCTS","SEARCH PRODUCTS","DELETE PRODUCTS","BACK",PMSelected); 
                }
                
                int AddRecord()
                {
                        char FileName[20], MenuHeader[20], EnterHeader[40];
                        
                             strcpy(FileName,"products.dat");
                             strcpy(MenuHeader,"ADD PRODUCTS");
                             strcpy(EnterHeader,"Enter the data of product:");
                        
                        
                        product p;
                        
                        ofstream ifile; // object of ofstream class is created
                        ifile.open(FileName,ios::app | ios::binary);   // file is opened in binary as well as append mode
                        if (!ifile){    // if file is not created the error message is displayed and program terminates
                            
                            SetConsoleTextAttribute(hConsole, 12);
                            CenterText("Error Creating File");
                            SetConsoleTextAttribute(hConsole, 15);
                            
                            return 0;
                            
                        }
                        
                        //Cursor Activate
                        CONSOLE_CURSOR_INFO CursoInfo;
                        CursoInfo.dwSize = 2;         /* The size of caret */
                        CursoInfo.bVisible = true;   /* Caret is visible? */
                        SetConsoleCursorInfo(hConsole, &CursoInfo);
                        //End of Cursor Code
                        
                        AddRecord: 
                        system("cls");
                        
                        DisplayHeader(); // ========= Header
                        cout<<endl;
                        
                        CategoryHeader(MenuHeader);
                        
                        cout<<endl<<endl<<endl;
                        
                        
                            
                            SetConsoleTextAttribute(hConsole, 14);
                            CenterText(EnterHeader);
                            cout<<endl;
                            SetConsoleTextAttribute(hConsole, 15);
                            
                            cout<<endl;
                            
                            
                                p.get_data(25);  // Function call to get information of student
                                ifile.write((char*)(&p),sizeof(p));   // object containing inforamation of student is written in file
                            
                            
                            cout<<endl;
                          
                            
                            SetConsoleTextAttribute(hConsole, 12);
                            CenterText("Enter Another Record (y/n)");
                            SetConsoleTextAttribute(hConsole, 15);
                            
                            int YesNo;
                            
                            while(1){
                               if(kbhit()){
                                 YesNo=getch();
                                 //cin.getline(str,5);
                                    if(YesNo==110){ //110 = n
                                        ifile.close(); //File is closed.
                                        //Cursor Deactivate
                                        CursoInfo.dwSize = 1;         /* The size of caret */
                                        CursoInfo.bVisible = false;   /* Caret is visible? */
                                        SetConsoleCursorInfo(hConsole, &CursoInfo);
                                        //End of Cursor Code
                                        
                                        return 0;
                                        
                                    }
                                    else
                                    {
                                        cout<<endl<<endl;
                                        goto AddRecord;
                                    }
                               }
                            }   // loop continues until the user presses n
                }
                
                int ViewRecord()
                {
                       char FileName[20], MenuHeader[20];
                        
                        
                             strcpy(FileName,"products.dat");
                             strcpy(MenuHeader,"VIEW PRODUCTS");
                         
                        
                        product p;
                       
                       
                       system("cls");
                       
                       DisplayHeader(); // ========= Header
                       cout<<endl;
                       
                       CategoryHeader(MenuHeader);
                       
                       cout<<endl<<endl;
                  
                        fstream ofile; // object of ifstream is created
                        ofile.open(FileName,ios::in | ios::binary);  // file is opened in binary, in and out mode
                        if(!ofile){ // if file doesn't exist then error message is displayed and contro goes out of switch
                            
                            SetConsoleTextAttribute(hConsole, 12);
                            CenterText("File Doesn't Exist!");
                            SetConsoleTextAttribute(hConsole, 15);
                            
                            Sleep(1000); //in milliseconds
                            return 0;
                        }
                        ofile.seekg(0); // cursor position is set to the starting of file
                        
                        
                             p.record_header(10);  // function call to make title bar of the list
                        
                        
                        int RecordCount=0;
                        while(1){
                            
                                 ofile.read((char*)(&p),sizeof(p));    // One object is read at a time
                                 
                            
                            
                            if(ofile.eof())// if cursor position reaches end of file then control goes out of loop
                                  break;
                            
                            if(RecordCount==12){
                                 
                                 cout<<endl;
                                 BlankSpace(51);
                                 SetConsoleTextAttribute(hConsole, 12);
                                 cout<<"...Continued >>>";
                                 SetConsoleTextAttribute(hConsole, 15);
                                 
                                 getch();
                                 
                                 system("cls");
                                 DisplayHeader(); // ========= Header
                                   cout<<endl;
                                   CategoryHeader(MenuHeader);
                                   cout<<endl<<endl;
                                   
                                    
                                         p.record_header(10);  // function call to make title bar of the list
                                         
                                    
                                 RecordCount=0;
                            }
                            
                            p.show_data(10); // content of object that is read is displayed
                                 
                            
                            
                            RecordCount++;
                            
                            
                            
                        }
                        
                       ofile.close();  // File is closed
                       
                       cout<<endl;
                       SetConsoleTextAttribute(hConsole, 12);
                       CenterText("Press any key to continue");
                       SetConsoleTextAttribute(hConsole, 15);
                       
                       getch();
                }
                
                int EditRecord()
                {
                        int IDRead;
                        int i=0;
                        
                        char FileName[20], MenuHeader[20], EnterHeader[40];
                        
                        
                             strcpy(FileName,"products.dat");
                             strcpy(MenuHeader,"EDIT PRODUCTS");
                             strcpy(EnterHeader,"Enter the Product ID to Edit: ");
                        
                        
                        product p;
                        
                        system("cls");
                       
                        DisplayHeader(); // ========= Header
                        cout<<endl;
                        CategoryHeader(MenuHeader);
                        cout<<endl<<endl;
                        
                        fstream ofile;  // object of fstream is created
                        ofile.open(FileName,ios::in | ios::out | ios::binary); // file is opened in binary, in and out mode
                        if(!ofile){ // if file doesnt exist then error is displayed and control flows out of switch
                            SetConsoleTextAttribute(hConsole, 12);
                            CenterText("File Doesn't Exist!");
                            SetConsoleTextAttribute(hConsole, 15);
                            
                            Sleep(1000); //in milliseconds
                            return 0;
                        }
                        //Cursor Activate
                             CONSOLE_CURSOR_INFO CursoInfo;
                             CursoInfo.dwSize = 2;         /* The size of caret */
                             CursoInfo.bVisible = true;   /* Caret is visible? */
                             SetConsoleCursorInfo(hConsole, &CursoInfo);
                        //End of Cursor Code
                        
                        BlankSpace(26);
                        SetConsoleTextAttribute(hConsole, 14);                
                        cout<<EnterHeader;
                        cin>>IDRead;    // taking ID from user to edit
                        SetConsoleTextAttribute(hConsole, 15);
                        cout<<endl;
                        ofile.seekg(0); // cursor position is set to starting of file
                        while(1){
                            
                            
                                ofile.read((char*)(&p),sizeof(p));    // One object is read at a time
                                if (ofile.eof())    // if cursor reaches end of file then control flows out of loop
                                    break;
                                if(p.IDCheck(IDRead)==1){  // function to check the ID entered by user and ID of object in file
                                    ofile.seekg(i*sizeof(p));// if ID matches then cursor positon is set to initial position of object containing that ID
                                    p.get_data(25);  // Function call to get information of products
                                    ofile.write((char*)(&p),sizeof(p));   // the object containing that ID is overwriten by object p which contains the information of products
                                    SetConsoleTextAttribute(hConsole, 12);
                                    cout<<endl;
                                    CenterText("Record Edited!");
                                    SetConsoleTextAttribute(hConsole, 15);
                                    goto EditSuccess;
                                }
                            
                            
                            i++;
                        }
                        
                        
                            if(p.IDCheck(IDRead)==0){
                                    SetConsoleTextAttribute(hConsole, 12);
                                    CenterText("Record Not Found!");
                                    SetConsoleTextAttribute(hConsole, 15);                        
                                }
                        
                        
                       EditSuccess:
                       //Cursor Deactivate
                             CursoInfo.dwSize = 1;         /* The size of caret */
                             CursoInfo.bVisible = false;   /* Caret is visible? */
                             SetConsoleCursorInfo(hConsole, &CursoInfo);
                        //End of Cursor Code
                       
                       
                       ofile.close(); //File is closed
                       
                       cout<<endl<<endl;
                       SetConsoleTextAttribute(hConsole, 12);
                       CenterText("Press Any Key to Continue");
                       SetConsoleTextAttribute(hConsole, 15);
                       getch();
                }
                
                int SearchRecord()
                {
                        int IDRead;
                        char FileName[20], MenuHeader[20], EnterHeader[40];
                        
                        
                             strcpy(FileName,"products.dat");
                             strcpy(MenuHeader,"SEARCH PRODUCTS");
                             strcpy(EnterHeader,"Enter the Product ID to Search: ");
                        
                        
                        product p;
                        
                        
                        system("cls");
                       
                        DisplayHeader(); // ========= Header
                        cout<<endl;
                        CategoryHeader(MenuHeader);
                        cout<<endl<<endl;
                        
                        ifstream ofile; // object of ifstraem class is created
                        ofile.open(FileName,ios::in | ios::binary); // file is opened in binary, in and out mode
                        if(!ofile){ // if file doesnt exist then error is displayed and control goes out of switch
                            SetConsoleTextAttribute(hConsole, 12);
                            CenterText("File Doesn't Exist!");
                            SetConsoleTextAttribute(hConsole, 15);
                            Sleep(1500);
                            return 0;
                        }
                        
                        //Cursor Activate
                             CONSOLE_CURSOR_INFO CursoInfo;
                             CursoInfo.dwSize = 2;         /* The size of caret */
                             CursoInfo.bVisible = true;   /* Caret is visible? */
                             SetConsoleCursorInfo(hConsole, &CursoInfo);
                        //End of Cursor Code
                        
                        BlankSpace(26);
                        SetConsoleTextAttribute(hConsole, 14);                
                        cout<<EnterHeader;
                        cin>>IDRead;    // taking ID from user to edit
                        SetConsoleTextAttribute(hConsole, 15);
                        cout<<endl;
                        ofile.seekg(0); // cursor position is set to starting of file
                        while(1){
                                 
                            
                                 ofile.read((char*)&p,sizeof(p));  // One object is read at a time
                            
                            
                            if (ofile.eof()){   // if cursor reaches to end of file then control goes out of loop
                            
                                     SetConsoleTextAttribute(hConsole, 12);
                                     CenterText("No match for this ID!");
                                     cout<<endl<<endl;
                                     CenterText("Press any key to continue");
                                     SetConsoleTextAttribute(hConsole, 15);
                                     //Cursor Deactivate
                                     CursoInfo.dwSize = 1;         /* The size of caret */
                                     CursoInfo.bVisible = false;   /* Caret is visible? */
                                     SetConsoleCursorInfo(hConsole, &CursoInfo);
                                     //End of Cursor Code
                                     getch();
                                     return 0;
                            }
                           
                           
                              if(p.IDCheck(IDRead))
                                    {
                                         p.record_header(10);
                                         p.show_data(10);
                                         goto SearchSuccess;
                                    }
                            
                        } // end of while
                        
                        SearchSuccess:
                                      
                            //Cursor Deactivate
                             CursoInfo.dwSize = 1;         /* The size of caret */
                             CursoInfo.bVisible = false;   /* Caret is visible? */
                             SetConsoleCursorInfo(hConsole, &CursoInfo);
                            //End of Cursor Code
                            
                            ofile.close(); 
                            
                            cout<<endl;
                            SetConsoleTextAttribute(hConsole, 12);
                            CenterText("Press any key to continue");
                            SetConsoleTextAttribute(hConsole, 15);
                           
                            getch();
                }
                
                int DeleteRecord()
                {
                        int IDRead;
                        int RecordStatus=0;
                        
                        char FileName[20], TempFileName[20], MenuHeader[20], EnterHeader[40];
                        
                        
                             strcpy(FileName,"products.dat");
                             strcpy(TempFileName,"products_temp.dat");
                             strcpy(MenuHeader,"DELETE PRODUCTS");
                             strcpy(EnterHeader,"Enter the Product ID to Delete: ");
                        
                        
                        product p;
                        
                        
                        system("cls");
                       
                        DisplayHeader(); // ========= Header
                        cout<<endl;
                        CategoryHeader(MenuHeader);
                        cout<<endl<<endl;
                        
                        fstream ofile; // object of ifstream is created
                        ofile.open(FileName,ios::in | ios::binary);  // file is opened in binary, in and out mode
                        if(!ofile){ // if file doesn't exist then error message is displayed and contro goes out of switch
                            
                            SetConsoleTextAttribute(hConsole, 12);
                            CenterText("File Doesn't Exist!");
                            SetConsoleTextAttribute(hConsole, 15);
                            
                            Sleep(1000); //in milliseconds
                            return 0;
                        }
                        
                        //Cursor Activate
                             CONSOLE_CURSOR_INFO CursoInfo;
                             CursoInfo.dwSize = 2;         /* The size of caret */
                             CursoInfo.bVisible = true;   /* Caret is visible? */
                             SetConsoleCursorInfo(hConsole, &CursoInfo);
                        //End of Cursor Code
                        
                        BlankSpace(26);
                        SetConsoleTextAttribute(hConsole, 14);                
                        cout<<EnterHeader;
                        cin>>IDRead;    // taking productID from user to edit
                        SetConsoleTextAttribute(hConsole, 15);
                        cout<<endl;
                        
                        ofile.seekg(0); // cursor position is set to the starting of file
                        
                        while(1){
                            
                            
                                 ofile.read((char*)&p,sizeof(p));  // One object is read at a time
                                 if (ofile.eof()){   // if cursor reaches to end of file then control goes out of loop
                            
                                     RecordStatus=0; //not found
                                     break;
                                 }
                                 if(p.IDCheck(IDRead))
                                    {
                                         //found
                                         RecordStatus=1;
                                         break;
                                    }
                                 
                            
                        }
                        
                
                        ofile.seekg(0); // cursor position is set to the starting of file
                        
                        if(RecordStatus==1){
                                            
                             ofstream ifile; // object of ofstream class is created
                             ifile.open(TempFileName,ios::app | ios::binary);   // file is opened in binary as well as append mode
                                
                                if (!ifile){    // if file is not created the error message is displayed and program terminates
                                    
                                    SetConsoleTextAttribute(hConsole, 12);
                                    CenterText("Error Creating File");
                                    SetConsoleTextAttribute(hConsole, 15);
                                    Sleep(1500);
                                    return 0;
                                }
                                            
                            while(1){
                                
                                
                                    ofile.read((char*)(&p),sizeof(p));    // object created using original file
                                    
                                    if(ofile.eof())// if cursor position reaches end of file then control goes out of loop
                                          break;
                                    
                                    if(p.IDCheck(IDRead)==0) //Entered ID not matched, so it is copied to temp file.
                                    {  
                                        ifile.write((char*)(&p),sizeof(p));   // object containing inforamation of student is written in temp file
                                        
                                    }
                                
                            } //end of while
                
                            ifile.close(); // Temporary File is closed.
                            
                            ofile.close();  // Original File is closed
                            
                            remove ( FileName ); //removing original file.
                            rename ( TempFileName , FileName ); //now making temp to original.
                       
                            SetConsoleTextAttribute(hConsole, 12);
                            CenterText("Record Deleted!");
                            cout<<endl<<endl;
                        }
                        else
                        {
                            ofile.close();  // Original File is closed
                            
                            SetConsoleTextAttribute(hConsole, 12);
                            CenterText("Record Not Found!");  
                            cout<<endl<<endl; 
                        }
                       
                        
                       //Cursor Deactivate
                             CursoInfo.dwSize = 1;         /* The size of caret */
                             CursoInfo.bVisible = false;   /* Caret is visible? */
                             SetConsoleCursorInfo(hConsole, &CursoInfo);
                        //End of Cursor Code
                        
                       CenterText("Press any key to continue");
                       SetConsoleTextAttribute(hConsole, 15);
                       
                       getch();
                
                }
                
                
};

class person
{
      protected:
           
           char name[25];
           char address[25];
           long long phone;
                
      public:
};

class customer:public person
{
      protected:
           
           int id;
                
      public:
             void get_data(int indent)
             {
                    BlankSpace(indent);
                    cout<<"Enter ID: ";
                    cin>>id;
                    cin.clear(); //clear the error bits for the cin input stream
                    cin.sync(); //synchronize the input buffer, discarding any leftover characters in the buffer
                    cout<<endl;
                    BlankSpace(indent);
                    cout<<"Enter Name: ";
                    cin.getline(name,25);
                    cout<<endl;
                    BlankSpace(indent);
                    cout<<"Enter Address: ";
                    cin.getline(address,25);
                    cout<<endl;
                    BlankSpace(indent);
                    cout<<"Enter Phone: ";
                    cin>>phone;
             }
             
             void record_header(int indent)
             {
                    BlankSpace(indent);
                    SetConsoleTextAttribute(hConsole, 14);
                    cout.unsetf(ios::left);
                    cout.width(8);
                    cout<<"ID";
                    cout.setf(ios::left);
                    cout<<"       ";
                    cout.width(25);
                    cout<<"NAME";
                    //cout.unsetf(ios::left);
                    cout.width(25);
                    cout<<"ADDRESS";
                    cout.width(15);
                    cout<<"PHONE"<<endl<<endl;
                    SetConsoleTextAttribute(hConsole, 15);
             }
             void show_data(int indent)
             {
                    BlankSpace(indent);
                    cout.unsetf(ios::left);
                    cout.width(8);
                    cout<<id;
                    cout.setf(ios::left);
                    cout<<"       ";
                    cout.width(25);
                    cout<<name;
                    //cout.unsetf(ios::left);
                    cout.width(25);
                    cout<<address;
                    cout.width(15);
                    cout<<phone<<endl;
             }
             
             int IDCheck(int IDRead)
                {
                    if(id==IDRead)  // if ID is matched it returns 1
                        return 1;
                    
                    return 0;
                }
             
             void DisplayCustomersMenu(int & CMSelected)
             {
                 DisplayHeader(); // ========= Header
                 cout<<endl;
                 CategoryHeader("CUSTOMERS");
                 cout<<endl<<endl<<endl;
                 MenuItems("ADD CUSTOMERS","VIEW CUSTOMERS","EDIT CUSTOMERS","SEARCH CUSTOMERS","DELETE CUSTOMERS","BACK",CMSelected); 
             }
                
             int AddRecord()
             {
                    char FileName[20], MenuHeader[20], EnterHeader[40];
                    
                    
                         strcpy(FileName,"customers.dat");
                         strcpy(MenuHeader,"ADD CUSTOMERS");
                         strcpy(EnterHeader,"Enter the data of customer:");
                    
                    
                    customer c;
                    
                    
                    ofstream ifile; // object of ofstream class is created
                    ifile.open(FileName,ios::app | ios::binary);   // file is opened in binary as well as append mode
                    if (!ifile){    // if file is not created the error message is displayed and program terminates
                        
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("Error Creating File");
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        return 0;
                        
                    }
                    
                    //Cursor Activate
                    CONSOLE_CURSOR_INFO CursoInfo;
                    CursoInfo.dwSize = 2;         /* The size of caret */
                    CursoInfo.bVisible = true;   /* Caret is visible? */
                    SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                    
                    AddRecord: 
                    system("cls");
                    
                    DisplayHeader(); // ========= Header
                    cout<<endl;
                    
                    CategoryHeader(MenuHeader);
                    
                    cout<<endl<<endl<<endl;
                    
                        SetConsoleTextAttribute(hConsole, 14);
                        CenterText(EnterHeader);
                        cout<<endl;
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        cout<<endl;
                        
                            c.get_data(25);  // Function call to get information of student
                            ifile.write((char*)(&c),sizeof(c));   // object containing inforamation of student is written in file
                        
                        cout<<endl;
                      
                        
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("Enter Another Record (y/n)");
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        int YesNo;
                        
                        while(1){
                           if(kbhit()){
                             YesNo=getch();
                             //cin.getline(str,5);
                                if(YesNo==110){ //110 = n
                                    ifile.close(); //File is closed.
                                    //Cursor Deactivate
                                    CursoInfo.dwSize = 1;         /* The size of caret */
                                    CursoInfo.bVisible = false;   /* Caret is visible? */
                                    SetConsoleCursorInfo(hConsole, &CursoInfo);
                                    //End of Cursor Code
                                    
                                    return 0;
                                    
                                }
                                else
                                {
                                    cout<<endl<<endl;
                                    goto AddRecord;
                                }
                           }
                        }   // loop continues until the user presses n
            }
            
            int ViewRecord()
            {
                   char FileName[20], MenuHeader[20];
                    
                    
                         strcpy(FileName,"customers.dat");
                         strcpy(MenuHeader,"VIEW CUSTOMERS");
                     
                   
                    customer c;
                   
                   system("cls");
                   
                   DisplayHeader(); // ========= Header
                   cout<<endl;
                   
                   CategoryHeader(MenuHeader);
                   
                   cout<<endl<<endl;
              
                    fstream ofile; // object of ifstream is created
                    ofile.open(FileName,ios::in | ios::binary);  // file is opened in binary, in and out mode
                    if(!ofile){ // if file doesn't exist then error message is displayed and contro goes out of switch
                        
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("File Doesn't Exist!");
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        Sleep(1000); //in milliseconds
                        return 0;
                    }
                    ofile.seekg(0); // cursor position is set to the starting of file
                    
                    
                         c.record_header(3);  // function call to make title bar of the list
                    
                    int RecordCount=0;
                    while(1){
                        
                             ofile.read((char*)(&c),sizeof(c));    // One object is read at a time
                             
                        
                        if(ofile.eof())// if cursor position reaches end of file then control goes out of loop
                              break;
                        
                        if(RecordCount==12){
                             
                             cout<<endl;
                             BlankSpace(51);
                             SetConsoleTextAttribute(hConsole, 12);
                             cout<<"...Continued >>>";
                             SetConsoleTextAttribute(hConsole, 15);
                             
                             getch();
                             
                             system("cls");
                             DisplayHeader(); // ========= Header
                               cout<<endl;
                               CategoryHeader(MenuHeader);
                               cout<<endl<<endl;
                               
                                
                                     c.record_header(3);  // function call to make title bar of the list
                               
                             
                             RecordCount=0;
                        }
                        
                        
                        c.show_data(3); // content of object that is read is displayed
                        
                        
                        RecordCount++;
                        
                        
                        
                    }
                    
                   ofile.close();  // File is closed
                   
                   cout<<endl;
                   SetConsoleTextAttribute(hConsole, 12);
                   CenterText("Press any key to continue");
                   SetConsoleTextAttribute(hConsole, 15);
                   
                   getch();
            }
            
            int EditRecord()
            {
                    int IDRead;
                    int i=0;
                    
                    char FileName[20], MenuHeader[20], EnterHeader[40];
                    
                    
                         strcpy(FileName,"customers.dat");
                         strcpy(MenuHeader,"EDIT CUSTOMERS");
                         strcpy(EnterHeader,"Enter the Customer ID to Edit: ");
                    
                    customer c;
                    
                    system("cls");
                   
                    DisplayHeader(); // ========= Header
                    cout<<endl;
                    CategoryHeader(MenuHeader);
                    cout<<endl<<endl;
                    
                    fstream ofile;  // object of fstream is created
                    ofile.open(FileName,ios::in | ios::out | ios::binary); // file is opened in binary, in and out mode
                    if(!ofile){ // if file doesnt exist then error is displayed and control flows out of switch
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("File Doesn't Exist!");
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        Sleep(1000); //in milliseconds
                        return 0;
                    }
                    //Cursor Activate
                         CONSOLE_CURSOR_INFO CursoInfo;
                         CursoInfo.dwSize = 2;         /* The size of caret */
                         CursoInfo.bVisible = true;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                    
                    BlankSpace(26);
                    SetConsoleTextAttribute(hConsole, 14);                
                    cout<<EnterHeader;
                    cin>>IDRead;    // taking ID from user to edit
                    SetConsoleTextAttribute(hConsole, 15);
                    cout<<endl;
                    ofile.seekg(0); // cursor position is set to starting of file
                    while(1){
                        
                        
                            ofile.read((char*)(&c),sizeof(c));    // One object is read at a time
                            if (ofile.eof())    // if cursor reaches end of file then control flows out of loop
                                break;
                            if(c.IDCheck(IDRead)==1){  // function to check the ID entered by user and ID of object in file
                                ofile.seekg(i*sizeof(c));// if ID matches then cursor positon is set to initial position of object containing that ID
                                c.get_data(25);  // Function call to get information of products
                                ofile.write((char*)(&c),sizeof(c));   // the object containing that ID is overwriten by object which contains the information of products
                                SetConsoleTextAttribute(hConsole, 12);
                                cout<<endl;
                                CenterText("Record Edited!");
                                SetConsoleTextAttribute(hConsole, 15);
                                goto EditSuccess;
                            }
                        
                        i++;
                    }
                    
                    
                        if(c.IDCheck(IDRead)==0){
                                SetConsoleTextAttribute(hConsole, 12);
                                CenterText("Record Not Found!");
                                SetConsoleTextAttribute(hConsole, 15);                        
                            }
                    
                   
                   //Cursor Deactivate
                         CursoInfo.dwSize = 1;         /* The size of caret */
                         CursoInfo.bVisible = false;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                   
                   EditSuccess:
                   ofile.close(); //File is closed
                   
                   cout<<endl<<endl;
                   SetConsoleTextAttribute(hConsole, 12);
                   CenterText("Press Any Key to Continue");
                   SetConsoleTextAttribute(hConsole, 15);
                   getch();
            }
            
            int SearchRecord()
            {
                    int IDRead;
                    char FileName[20], MenuHeader[20], EnterHeader[40];
                    
                    
                         strcpy(FileName,"customers.dat");
                         strcpy(MenuHeader,"SEARCH CUSTOMERS");
                         strcpy(EnterHeader,"Enter the Customer ID to Search: ");
                    
                    customer c;
                    
                    system("cls");
                   
                    DisplayHeader(); // ========= Header
                    cout<<endl;
                    CategoryHeader(MenuHeader);
                    cout<<endl<<endl;
                    
                    ifstream ofile; // object of ifstraem class is created
                    ofile.open(FileName,ios::in | ios::binary); // file is opened in binary, in and out mode
                    if(!ofile){ // if file doesnt exist then error is displayed and control goes out of switch
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("File Doesn't Exist!");
                        SetConsoleTextAttribute(hConsole, 15);
                        Sleep(1500);
                        return 0;
                    }
                    
                    //Cursor Activate
                         CONSOLE_CURSOR_INFO CursoInfo;
                         CursoInfo.dwSize = 2;         /* The size of caret */
                         CursoInfo.bVisible = true;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                    
                    BlankSpace(26);
                    SetConsoleTextAttribute(hConsole, 14);                
                    cout<<EnterHeader;
                    cin>>IDRead;    // taking ID from user to edit
                    SetConsoleTextAttribute(hConsole, 15);
                    cout<<endl;
                    ofile.seekg(0); // cursor position is set to starting of file
                    while(1){
                             
                        
                             ofile.read((char*)&c,sizeof(c));  // One object is read at a time
                        
                        if (ofile.eof()){   // if cursor reaches to end of file then control goes out of loop
                        
                                 SetConsoleTextAttribute(hConsole, 12);
                                 CenterText("No match for this ID!");
                                 cout<<endl<<endl;
                                 CenterText("Press any key to continue");
                                 SetConsoleTextAttribute(hConsole, 15);
                                 //Cursor Deactivate
                                 CursoInfo.dwSize = 1;         /* The size of caret */
                                 CursoInfo.bVisible = false;   /* Caret is visible? */
                                 SetConsoleCursorInfo(hConsole, &CursoInfo);
                                 //End of Cursor Code
                                 getch();
                                 return 0;
                        }
                       
                       
                        
                            if(c.IDCheck(IDRead))
                                {
                                     c.record_header(0);
                                     c.show_data(0);
                                     goto SearchSuccess;
                                }
                                                        
                    } // end of while
                    
                    SearchSuccess:
                                  
                        //Cursor Deactivate
                         CursoInfo.dwSize = 1;         /* The size of caret */
                         CursoInfo.bVisible = false;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                        //End of Cursor Code
                        
                        ofile.close(); 
                        
                        cout<<endl;
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("Press any key to continue");
                        SetConsoleTextAttribute(hConsole, 15);
                       
                        getch();
            }
            
            int DeleteRecord()
            {
                    int IDRead;
                    int RecordStatus=0;
                    
                    char FileName[20], TempFileName[20], MenuHeader[20], EnterHeader[40];
                    
                    
                         strcpy(FileName,"customers.dat");
                         strcpy(TempFileName,"customers_temp.dat");
                         strcpy(MenuHeader,"DELETE CUSTOMERS");
                         strcpy(EnterHeader,"Enter the Customer ID to Delete: ");
                    
                    
                    customer c;
                    
                    system("cls");
                   
                    DisplayHeader(); // ========= Header
                    cout<<endl;
                    CategoryHeader(MenuHeader);
                    cout<<endl<<endl;
                    
                    fstream ofile; // object of ifstream is created
                    ofile.open(FileName,ios::in | ios::binary);  // file is opened in binary, in and out mode
                    if(!ofile){ // if file doesn't exist then error message is displayed and contro goes out of switch
                        
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("File Doesn't Exist!");
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        Sleep(1000); //in milliseconds
                        return 0;
                    }
                    
                    //Cursor Activate
                         CONSOLE_CURSOR_INFO CursoInfo;
                         CursoInfo.dwSize = 2;         /* The size of caret */
                         CursoInfo.bVisible = true;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                    
                    BlankSpace(26);
                    SetConsoleTextAttribute(hConsole, 14);                
                    cout<<EnterHeader;
                    cin>>IDRead;    // taking productID from user to edit
                    SetConsoleTextAttribute(hConsole, 15);
                    cout<<endl;
                    
                    ofile.seekg(0); // cursor position is set to the starting of file
                    
                    while(1){
                        
                        
                             ofile.read((char*)&c,sizeof(c));  // One object is read at a time
                             if (ofile.eof()){   // if cursor reaches to end of file then control goes out of loop
                        
                                 RecordStatus=0; //not found
                                 break;
                             }
                             if(c.IDCheck(IDRead))
                                {
                                     //found
                                     RecordStatus=1;
                                     break;
                                }
                        
                    }
                    
            
                    ofile.seekg(0); // cursor position is set to the starting of file
                    
                    if(RecordStatus==1){
                                        
                         ofstream ifile; // object of ofstream class is created
                         ifile.open(TempFileName,ios::app | ios::binary);   // file is opened in binary as well as append mode
                            
                            if (!ifile){    // if file is not created the error message is displayed and program terminates
                                
                                SetConsoleTextAttribute(hConsole, 12);
                                CenterText("Error Creating File");
                                SetConsoleTextAttribute(hConsole, 15);
                                Sleep(1500);
                                return 0;
                            }
                                        
                        while(1){
                            
                            
                                ofile.read((char*)(&c),sizeof(c));    // object created using original file
                                
                                if(ofile.eof())// if cursor position reaches end of file then control goes out of loop
                                      break;
                                
                                if(c.IDCheck(IDRead)==0) //Entered ID not matched, so it is copied to temp file.
                                {  
                                    ifile.write((char*)(&c),sizeof(c));   // object containing inforamation of student is written in temp file
                                    
                                }
                            
                        } //end of while
            
                        ifile.close(); // Temporary File is closed.
                        
                        ofile.close();  // Original File is closed
                        
                        remove ( FileName ); //removing original file.
                        rename ( TempFileName , FileName ); //now making temp to original.
                   
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("Record Deleted!");
                        cout<<endl<<endl;
                    }
                    else
                    {
                        ofile.close();  // Original File is closed
                        
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("Record Not Found!");  
                        cout<<endl<<endl; 
                    }
                   
                    
                   //Cursor Deactivate
                         CursoInfo.dwSize = 1;         /* The size of caret */
                         CursoInfo.bVisible = false;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                    
                   CenterText("Press any key to continue");
                   SetConsoleTextAttribute(hConsole, 15);
                   
                   getch();
            
            }
             
};

class employee:public person
{
      protected:
           
           int id;
           float salary;
           //dept
                
      public:
             void get_data(int indent)
             {
                    BlankSpace(indent);
                    cout<<"Enter ID: ";
                    cin>>id;
                    cin.clear(); //clear the error bits for the cin input stream
                    cin.sync(); //synchronize the input buffer, discarding any leftover characters in the buffer
                    cout<<endl;
                    BlankSpace(indent);
                    cout<<"Enter Name: ";
                    cin.getline(name,25);
                    cout<<endl;
                    BlankSpace(indent);
                    cout<<"Enter Address: ";
                    cin.getline(address,25);
                    cout<<endl;
                    BlankSpace(indent);
                    cout<<"Enter Phone: ";
                    cin>>phone;
                    cout<<endl;
                    BlankSpace(indent);
                    cout<<"Enter Salary: ";
                    cin>>salary;
                    
             }
             
             void record_header(int indent)
             {
                    SetConsoleTextAttribute(hConsole, 14);
                    BlankSpace(indent);
                    cout.unsetf(ios::left);
                    cout.width(8);
                    cout<<"ID";
                    cout.setf(ios::left);
                    cout<<"      ";
                    cout.width(25);
                    cout<<"NAME";
                    cout.width(18);
                    cout<<"ADDRESS";
                    cout.unsetf(ios::left);
                    cout.width(8);
                    cout<<"SALARY";
                    cout<<"     ";
                    cout.setf(ios::left);
                    cout.width(15);
                    cout<<"PHONE"<<endl<<endl;
                    SetConsoleTextAttribute(hConsole, 15);
                    
             }
             void show_data(int indent)
             {
                    BlankSpace(indent);
                    cout.unsetf(ios::left);
                    cout.width(8);
                    cout<<id;
                    cout.setf(ios::left);
                    cout<<"      ";
                    cout.width(25);
                    cout<<name;
                    cout.width(18);
                    cout<<address;
                    cout.unsetf(ios::left);
                    cout.width(8);
                    cout<<salary;
                    cout<<"     ";
                    cout.setf(ios::left);
                    cout.width(15);
                    cout<<phone<<endl;;
             }
             
             int IDCheck(int IDRead)
                {
                    if(id==IDRead)  // if ID is matched it returns 1
                        return 1;
                    
                    return 0;
                }
             
             void DisplayEmployeesMenu(int & EMSelected)
             {
                 DisplayHeader(); // ========= Header
                 cout<<endl;
                 CategoryHeader("EMPLOYEES");
                 cout<<endl<<endl<<endl;
                 MenuItems("ADD EMPLOYEES","VIEW EMPLOYEES","EDIT EMPLOYEES","SEARCH EMPLOYEES","DELETE EMPLOYEES","BACK",EMSelected); 
             }
             
             int AddRecord()
             {
                    char FileName[20], MenuHeader[20], EnterHeader[40];
                    
                         strcpy(FileName,"employees.dat");
                         strcpy(MenuHeader,"ADD EMPLOYEES");
                         strcpy(EnterHeader,"Enter the data of employee:");
                   
                    employee e;
                    
                    
                    ofstream ifile; // object of ofstream class is created
                    ifile.open(FileName,ios::app | ios::binary);   // file is opened in binary as well as append mode
                    if (!ifile){    // if file is not created the error message is displayed and program terminates
                        
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("Error Creating File");
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        return 0;
                        
                    }
                    
                    //Cursor Activate
                    CONSOLE_CURSOR_INFO CursoInfo;
                    CursoInfo.dwSize = 2;         /* The size of caret */
                    CursoInfo.bVisible = true;   /* Caret is visible? */
                    SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                    
                    AddRecord: 
                    system("cls");
                    
                    DisplayHeader(); // ========= Header
                    cout<<endl;
                    
                    CategoryHeader(MenuHeader);
                    
                    cout<<endl<<endl<<endl;
                    
                    
                        
                        SetConsoleTextAttribute(hConsole, 14);
                        CenterText(EnterHeader);
                        cout<<endl;
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        cout<<endl;
                        
                        
                            e.get_data(25);  // Function call to get information of student
                            ifile.write((char*)(&e),sizeof(e));   // object containing inforamation of student is written in file
                        
                        
                        cout<<endl;
                      
                        
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("Enter Another Record (y/n)");
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        int YesNo;
                        
                        while(1){
                           if(kbhit()){
                             YesNo=getch();
                             //cin.getline(str,5);
                                if(YesNo==110){ //110 = n
                                    ifile.close(); //File is closed.
                                    //Cursor Deactivate
                                    CursoInfo.dwSize = 1;         /* The size of caret */
                                    CursoInfo.bVisible = false;   /* Caret is visible? */
                                    SetConsoleCursorInfo(hConsole, &CursoInfo);
                                    //End of Cursor Code
                                    
                                    return 0;
                                    
                                }
                                else
                                {
                                    cout<<endl<<endl;
                                    goto AddRecord;
                                }
                           }
                        }   // loop continues until the user presses n
            }
            
            int ViewRecord()
            {
                   char FileName[20], MenuHeader[20], EnterHeader[40];
                    
                    
                         strcpy(FileName,"employees.dat");
                         strcpy(MenuHeader,"VIEW EMPLOYEES");
                      
                    
                    
                    employee e;

                   
                   system("cls");
                   
                   DisplayHeader(); // ========= Header
                   cout<<endl;
                   
                   CategoryHeader(MenuHeader);
                   
                   cout<<endl<<endl;
              
                    fstream ofile; // object of ifstream is created
                    ofile.open(FileName,ios::in | ios::binary);  // file is opened in binary, in and out mode
                    if(!ofile){ // if file doesn't exist then error message is displayed and contro goes out of switch
                        
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("File Doesn't Exist!");
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        Sleep(1000); //in milliseconds
                        return 0;
                    }
                    ofile.seekg(0); // cursor position is set to the starting of file
                    
                    
                         e.record_header(0);  // function call to make title bar of the list
                    
                    
                    int RecordCount=0;
                    while(1){
                        
                             ofile.read((char*)(&e),sizeof(e));    // One object is read at a time
                         
                        
                        if(ofile.eof())// if cursor position reaches end of file then control goes out of loop
                              break;
                        
                        if(RecordCount==12){
                             
                             cout<<endl;
                             BlankSpace(51);
                             SetConsoleTextAttribute(hConsole, 12);
                             cout<<"...Continued >>>";
                             SetConsoleTextAttribute(hConsole, 15);
                             
                             getch();
                             
                             system("cls");
                             DisplayHeader(); // ========= Header
                               cout<<endl;
                               CategoryHeader(MenuHeader);
                               cout<<endl<<endl;
                               
                                e.record_header(0);  // function call to make title bar of the list
                                     
                                
                             
                             RecordCount=0;
                        }
                        
                        
                             e.show_data(0); // content of object that is read is displayed
                         
                        RecordCount++;
                        
                        
                        
                    }
                    
                   ofile.close();  // File is closed
                   
                   cout<<endl;
                   SetConsoleTextAttribute(hConsole, 12);
                   CenterText("Press any key to continue");
                   SetConsoleTextAttribute(hConsole, 15);
                   
                   getch();
            }
            
            int EditRecord()
            {
                    int IDRead;
                    int i=0;
                    
                    char FileName[20], MenuHeader[20], EnterHeader[40];
                    
                    
                         strcpy(FileName,"employees.dat");
                         strcpy(MenuHeader,"EDIT EMPLOYEES");
                         strcpy(EnterHeader,"Enter the Employee ID to Edit: ");
                     
                    employee e;
                    
                    system("cls");
                   
                    DisplayHeader(); // ========= Header
                    cout<<endl;
                    CategoryHeader(MenuHeader);
                    cout<<endl<<endl;
                    
                    fstream ofile;  // object of fstream is created
                    ofile.open(FileName,ios::in | ios::out | ios::binary); // file is opened in binary, in and out mode
                    if(!ofile){ // if file doesnt exist then error is displayed and control flows out of switch
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("File Doesn't Exist!");
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        Sleep(1000); //in milliseconds
                        return 0;
                    }
                    //Cursor Activate
                         CONSOLE_CURSOR_INFO CursoInfo;
                         CursoInfo.dwSize = 2;         /* The size of caret */
                         CursoInfo.bVisible = true;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                    
                    BlankSpace(26);
                    SetConsoleTextAttribute(hConsole, 14);                
                    cout<<EnterHeader;
                    cin>>IDRead;    // taking ID from user to edit
                    SetConsoleTextAttribute(hConsole, 15);
                    cout<<endl;
                    ofile.seekg(0); // cursor position is set to starting of file
                    while(1){
                        
                        
                            ofile.read((char*)(&e),sizeof(e));    // One object is read at a time
                            if (ofile.eof())    // if cursor reaches end of file then control flows out of loop
                                break;
                            if(e.IDCheck(IDRead)==1){  // function to check the ID entered by user and ID of object in file
                                ofile.seekg(i*sizeof(e));// if ID matches then cursor positon is set to initial position of object containing that ID
                                e.get_data(25);  // Function call to get information of products
                                ofile.write((char*)(&e),sizeof(e));   // the object containing that ID is overwriten by object which contains the information of products
                                SetConsoleTextAttribute(hConsole, 12);
                                cout<<endl;
                                CenterText("Record Edited!");
                                SetConsoleTextAttribute(hConsole, 15);
                                goto EditSuccess;
                            }
                        
                        
                        i++;
                    }
                    
                    
                    if(e.IDCheck(IDRead)==0){
                            SetConsoleTextAttribute(hConsole, 12);
                            CenterText("Record Not Found!");
                            SetConsoleTextAttribute(hConsole, 15);                        
                    }
                                        
                   
                   //Cursor Deactivate
                         CursoInfo.dwSize = 1;         /* The size of caret */
                         CursoInfo.bVisible = false;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                   
                   EditSuccess:
                   ofile.close(); //File is closed
                   
                   cout<<endl<<endl;
                   SetConsoleTextAttribute(hConsole, 12);
                   CenterText("Press Any Key to Continue");
                   SetConsoleTextAttribute(hConsole, 15);
                   getch();
            }
            
            int SearchRecord()
            {
                    int IDRead;
                    char FileName[20], MenuHeader[20], EnterHeader[40];
                    
                    
                         strcpy(FileName,"employees.dat");
                         strcpy(MenuHeader,"SEARCH EMPLOYEES");
                         strcpy(EnterHeader,"Enter the Employee ID to Search: ");
                    
                    
                    
                    employee e;
                   
                    
                    system("cls");
                   
                    DisplayHeader(); // ========= Header
                    cout<<endl;
                    CategoryHeader(MenuHeader);
                    cout<<endl<<endl;
                    
                    ifstream ofile; // object of ifstraem class is created
                    ofile.open(FileName,ios::in | ios::binary); // file is opened in binary, in and out mode
                    if(!ofile){ // if file doesnt exist then error is displayed and control goes out of switch
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("File Doesn't Exist!");
                        SetConsoleTextAttribute(hConsole, 15);
                        Sleep(1500);
                        return 0;
                    }
                    
                    //Cursor Activate
                         CONSOLE_CURSOR_INFO CursoInfo;
                         CursoInfo.dwSize = 2;         /* The size of caret */
                         CursoInfo.bVisible = true;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                    
                    BlankSpace(26);
                    SetConsoleTextAttribute(hConsole, 14);                
                    cout<<EnterHeader;
                    cin>>IDRead;    // taking ID from user to edit
                    SetConsoleTextAttribute(hConsole, 15);
                    cout<<endl;
                    ofile.seekg(0); // cursor position is set to starting of file
                    while(1){
                             
                        
                             ofile.read((char*)&e,sizeof(e));  // One object is read at a time
                        
                        if (ofile.eof()){   // if cursor reaches to end of file then control goes out of loop
                        
                                 SetConsoleTextAttribute(hConsole, 12);
                                 CenterText("No match for this ID!");
                                 cout<<endl<<endl;
                                 CenterText("Press any key to continue");
                                 SetConsoleTextAttribute(hConsole, 15);
                                 //Cursor Deactivate
                                 CursoInfo.dwSize = 1;         /* The size of caret */
                                 CursoInfo.bVisible = false;   /* Caret is visible? */
                                 SetConsoleCursorInfo(hConsole, &CursoInfo);
                                 //End of Cursor Code
                                 getch();
                                 return 0;
                        }
                       
                       
                        
                            if(e.IDCheck(IDRead))
                                {
                                     e.record_header(0);
                                     e.show_data(0);
                                     goto SearchSuccess;
                                }
                        
                        
                    } // end of while
                    
                    SearchSuccess:
                                  
                        //Cursor Deactivate
                         CursoInfo.dwSize = 1;         /* The size of caret */
                         CursoInfo.bVisible = false;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                        //End of Cursor Code
                        
                        ofile.close(); 
                        
                        cout<<endl;
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("Press any key to continue");
                        SetConsoleTextAttribute(hConsole, 15);
                       
                        getch();
            }
            
            int DeleteRecord()
            {
                    int IDRead;
                    int RecordStatus=0;
                    
                    char FileName[20], TempFileName[20], MenuHeader[20], EnterHeader[40];
                    
                    
                         strcpy(FileName,"employees.dat");
                         strcpy(TempFileName,"employees_temp.dat");
                         strcpy(MenuHeader,"DELETE EMPLOYEES");
                         strcpy(EnterHeader,"Enter the Employee ID to Delete: ");
                    
                    
                    
                    employee e;
                    
                    system("cls");
                   
                    DisplayHeader(); // ========= Header
                    cout<<endl;
                    CategoryHeader(MenuHeader);
                    cout<<endl<<endl;
                    
                    fstream ofile; // object of ifstream is created
                    ofile.open(FileName,ios::in | ios::binary);  // file is opened in binary, in and out mode
                    if(!ofile){ // if file doesn't exist then error message is displayed and contro goes out of switch
                        
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("File Doesn't Exist!");
                        SetConsoleTextAttribute(hConsole, 15);
                        
                        Sleep(1000); //in milliseconds
                        return 0;
                    }
                    
                    //Cursor Activate
                         CONSOLE_CURSOR_INFO CursoInfo;
                         CursoInfo.dwSize = 2;         /* The size of caret */
                         CursoInfo.bVisible = true;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                    
                    BlankSpace(26);
                    SetConsoleTextAttribute(hConsole, 14);                
                    cout<<EnterHeader;
                    cin>>IDRead;    // taking productID from user to edit
                    SetConsoleTextAttribute(hConsole, 15);
                    cout<<endl;
                    
                    ofile.seekg(0); // cursor position is set to the starting of file
                    
                    while(1){
                        
                        
                             ofile.read((char*)&e,sizeof(e));  // One object is read at a time
                             if (ofile.eof()){   // if cursor reaches to end of file then control goes out of loop
                        
                                 RecordStatus=0; //not found
                                 break;
                             }
                             if(e.IDCheck(IDRead))
                                {
                                     //found
                                     RecordStatus=1;
                                     break;
                                }
                        
                    }
                    
            
                    ofile.seekg(0); // cursor position is set to the starting of file
                    
                    if(RecordStatus==1){
                                        
                         ofstream ifile; // object of ofstream class is created
                         ifile.open(TempFileName,ios::app | ios::binary);   // file is opened in binary as well as append mode
                            
                            if (!ifile){    // if file is not created the error message is displayed and program terminates
                                
                                SetConsoleTextAttribute(hConsole, 12);
                                CenterText("Error Creating File");
                                SetConsoleTextAttribute(hConsole, 15);
                                Sleep(1500);
                                return 0;
                            }
                                        
                        while(1){
                            
                            
                                ofile.read((char*)(&e),sizeof(e));    // object created using original file
                                
                                if(ofile.eof())// if cursor position reaches end of file then control goes out of loop
                                      break;
                                
                                if(e.IDCheck(IDRead)==0) //Entered ID not matched, so it is copied to temp file.
                                {  
                                    ifile.write((char*)(&e),sizeof(e));   // object containing inforamation of student is written in temp file
                                    
                                }
                            
                        } //end of while
            
                        ifile.close(); // Temporary File is closed.
                        
                        ofile.close();  // Original File is closed
                        
                        remove ( FileName ); //removing original file.
                        rename ( TempFileName , FileName ); //now making temp to original.
                   
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("Record Deleted!");
                        cout<<endl<<endl;
                    }
                    else
                    {
                        ofile.close();  // Original File is closed
                        
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("Record Not Found!");  
                        cout<<endl<<endl; 
                    }
                   
                    
                   //Cursor Deactivate
                         CursoInfo.dwSize = 1;         /* The size of caret */
                         CursoInfo.bVisible = false;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                    
                   CenterText("Press any key to continue");
                   SetConsoleTextAttribute(hConsole, 15);
                   
                   getch();
            
            }

};

class bill
{
      protected:
             
             int id;
             
                
      public:
             
             void bill_header(int indent)
             {
                    SetConsoleTextAttribute(hConsole, 14);
                    BlankSpace(indent);
                    cout<<"S.N";
                    cout<<"      ";
                    cout.width(10);
                    cout<<"PRODUCT ID";
                    cout<<"     ";
                    cout.setf(ios::left);
                    cout.width(22);
                    cout<<"DESCRIPTION";
                    cout.unsetf(ios::left);
                    
                    //cout.setf(ios::left);
                    cout.width(10);
                    cout<<"RATE"; cout<<"   ";
                    cout.width(5);
                    cout<<"QTY";
                    cout.width(10);
                    cout<<"AMOUNT"<<endl<<endl;
                    SetConsoleTextAttribute(hConsole, 15);
             }
             
             void DisplayBillMenu(int & BMSelected)
             {
                 DisplayHeader(); // ========= Header
                 cout<<endl;
                 CategoryHeader("BILLING");
                 cout<<endl<<endl<<endl;
                 MenuItems("CREATE BILL","VIEW BILLS","SEARCH BILLS","BACK","","",BMSelected);
             }
             
             int CreateBill()
             {
                
                   
                fstream ofile; // object of ifstream is created
                ofile.open("products.dat",ios::in | ios::binary);  // file is opened in binary, in and out mode
                if(!ofile){ // if file doesn't exist then error message is displayed and contro goes out of switch
                    
                    SetConsoleTextAttribute(hConsole, 12);
                    CenterText("File Doesn't Exist!");
                    SetConsoleTextAttribute(hConsole, 15);
                    
                    Sleep(1000); //in milliseconds
                    return 0;
                }
                
                //================
                int sn=1;
                int StartingLine = 9;
                int cursorY;
                 
                
                string ProductID, qtySTR, description;
                int qty;
                float rate, amount, GrandTotal=0;
            
                int BillEnd=0;
                int EndInput;
                
                BillStart:
                system("cls");
                DisplayHeader(); // ========= Header
                cout<<endl;
                
                int BillID;
                
                SetConsoleTextAttribute(hConsole, 11);
                CursorPos(5,GetCursorPosY());    
                cout<<"Bill ID: ";
                cout<<BillID;
                SetConsoleTextAttribute(hConsole, 15);
                
                CursorPos(38,GetCursorPosY());
                cout<<"CREATE BILL";
                
                cout<<endl;
                
                for(int i=1;i<=((43-(16/2)));i++)
                {
                        cout<<" ";
                }
                CharDisplay(196,16);
                
                cout<<endl<<endl;
                
                //Cursor Activate
                         CONSOLE_CURSOR_INFO CursoInfo;
                         CursoInfo.dwSize = 10;         /* The size of caret */
                         CursoInfo.bVisible = true;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                    //End of Cursor Code
                
                bill b;
                
                b.bill_header(5);
                int CursorSN = 1;
                
                while(BillEnd==0)
                {
                    cursorY = StartingLine+(CursorSN-1); 
                    BlankSpace(5);
                    cout<<sn;
            
                    
                    CursorPos(14,cursorY);
                    ProductID = LimitBuffer(10);
                    
                    //Display Description & Rate automatically
                    
                    
                    product p;
            
                    ifstream ofile; // object of ifstraem class is created
                    ofile.open("products.dat",ios::in | ios::binary); // file is opened in binary, in and out mode
                    if(!ofile){ // if file doesnt exist then error is displayed and control goes out of switch
                        SetConsoleTextAttribute(hConsole, 12);
                        CenterText("File Doesn't Exist!");
                        SetConsoleTextAttribute(hConsole, 15);
                        Sleep(1500);
                        return 0;
                    }
                    
                    ofile.seekg(0); // cursor position is set to starting of file
                    
                    while(1){
                        ofile.read((char*)&p,sizeof(p));  // One object is read at a time
                            
                            
                        if (ofile.eof()){   // if cursor reaches to end of file then control goes out of loop
                        
                                 SetConsoleTextAttribute(hConsole, 12);
                                 CursorPos(29,cursorY);
                                 cout<<"Product Not Found!";
                                 SetConsoleTextAttribute(hConsole, 15);
                                 rate=0;
                                 break;
                        }
                           
                           
                        int i=0;
                        
                       
                        if(p.IDCheck(atoi(ProductID.c_str())))
                            {
                                 //FOUND
                                 CursorPos(29,cursorY);
                                 cout<<p.get_description();
                                 description=p.get_description();
                                 
                                 CursorPos(57,cursorY);
                                 cout<<p.get_price();
                                 rate=p.get_price();
                                 
                                 break;
                                 //goto SearchSuccess;
                            }
                        
                    } // end of while
                    
                    //SearchSuccess:
                        
                    ofile.close(); 
            
                    //Ask Quantity
                    CursorPos(66,cursorY);
                    qtySTR = LimitBuffer(4);
                    qty = atoi(qtySTR.c_str());
                    
                    
                    //Display Amount automatically
                    amount=rate*qty;
                    CursorPos(73,cursorY);
                    cout<<amount;
                    
                    GrandTotal=GrandTotal+amount;
                    
                    CursorPos(80,cursorY);
                    
                    /*
                    cout.width(10);
                    //cin.getline(ProductID,10);
                    cout<<"     ";
                    cout.setf(ios::left);
                    cout.width(25);
                    cin.getline(description,25);
                    cout.unsetf(ios::left);
                    cout.width(5);
                    cin.getline(qty,5);
                    //cout.setf(ios::left);
                    cout.width(10);
                    cin.getline(rate,10);
                    cout.width(10);
                    cin.getline(amount,10);
                    
                    */
                     
                     
                     while(1)
                     {
                          if(kbhit())
                          {
                               EndInput=getch();
                               
                               if(EndInput==13) //Enter
                               {
                                    if(sn%15==0)
                                    {
                                         
                                         sn++;
                                         goto BillStart;
                                              
                                         //CursorPos(20,10);                                     
                                    }
                                    
                                    sn++;
                                    CursorSN++;
                                    cout<<endl;
                                    break;
                                    
                               }
                               else if(EndInput==27) //ESC
                               {
                                    BillEnd=1;
                                    break;
                               }
                          }
                     }
                }
                
                cout<<endl<<"DONE!"<<endl;
                cout<<"Grand Total: "<<GrandTotal;
                
                //=================
                getch();
                //Cursor Deactivate
                         CursoInfo.dwSize = 0;         /* The size of caret */
                         CursoInfo.bVisible = false;   /* Caret is visible? */
                         SetConsoleCursorInfo(hConsole, &CursoInfo);
                //End of Cursor Code
                    
                
                return 0;
            }
             
             
             
};

// END of Class Definitions

int main(int argc, char *argv[])
{
  
    //Color set - Black BG, White FG
    SetConsoleTextAttribute(hConsole, 15); 
    //Cursor Hiding
    CONSOLE_CURSOR_INFO CursoInfo;
    CursoInfo.dwSize = 1;         /* The size of caret */
    CursoInfo.bVisible = false;   /* Caret is visible? */
    SetConsoleCursorInfo(hConsole, &CursoInfo);
    //End of Cursor Hiding Code
    
    //Declaration For Main Menu
    int MainChoiceSelected=1;
    int MainChoiceEntered;
    
    MainMenuLabel: //Label for BACK Navigations
                    
    //ForProductsMenu
    int PMSelected=1;
    int PMEntered;
    
    //ForEmployeesMenu
    int EMSelected=1;
    int EMEntered;
    
    //ForCustomersMenu
    int CMSelected=1;
    int CMEntered;
    
    //ForBillMenu
    int BMSelected=1;
    int BMEntered;
    

    /*
    product p;
    employee e;
    customer c;
    */
    
    // END of declarations ==============
    
    system("cls");
    DisplayMainMenu(MainChoiceSelected);
    
    while(1){
        if(kbhit()){
            MainChoiceEntered=getch();
            
            switch(MainChoiceEntered){
                
                
                /*                
                case 75:{
                     cout<<"left is pressed."<<endl;
                     break;
                } 
            
                case 77:{
                     cout<<"right is pressed."<<endl;
                     break;
                } */
                
                case 72:{ // UP Key
                     if(MainChoiceSelected!=1)
                     {
                          MainChoiceSelected--;
                          
                          system("cls");
                          DisplayMainMenu(MainChoiceSelected);
                     }else if(MainChoiceSelected==1)
                     {
                          MainChoiceSelected=6;
                          
                          system("cls");
                          DisplayMainMenu(MainChoiceSelected);
                     }
                     
                     break;
                }
                          
                case 80:{  //DOWN Key
                     if(MainChoiceSelected!=6)
                     {
                          MainChoiceSelected++;
                     
                          system("cls");
                          DisplayMainMenu(MainChoiceSelected);
                     }else if(MainChoiceSelected==6)
                     {
                          MainChoiceSelected=1;
                     
                          system("cls");
                          DisplayMainMenu(MainChoiceSelected);
                     }
                     
                     break;
                    
                }
                
                case 13:{ //ENTER Key
                     
                     switch(MainChoiceSelected){
                                                
                          case 1:{  //PRODUCTS
                               product p;
                               ProductMenu:
                               
                               system("cls");
                               p.DisplayProductsMenu(PMSelected);
                               
                               while(1){
                                  if(kbhit()){
                                     PMEntered=getch();
            
                                        switch(PMEntered){
                                           
                                           case 72:{ // UP Key
                                                 if(PMSelected!=1)
                                                 {
                                                      PMSelected--;
                                                      
                                                      system("cls");
                                                      p.DisplayProductsMenu(PMSelected);
                                                 } else if(PMSelected==1)
                                                 {
                                                      PMSelected=6;
                                                      
                                                      system("cls");
                                                      p.DisplayProductsMenu(PMSelected);
                                                 }
                                                 
                                                 break;
                                            }
                                            
                                            case 80:{  //DOWN Key
                                                 if(PMSelected!=6)
                                                 {
                                                      PMSelected++;
                                                 
                                                      system("cls");
                                                      p.DisplayProductsMenu(PMSelected);
                                                 } else if(PMSelected==6)
                                                 {
                                                      PMSelected=1;
                                                 
                                                      system("cls");
                                                      p.DisplayProductsMenu(PMSelected);
                                                 }
                                                 
                                                 break;
                                                
                                            }
                                            
                                            case 13:{ //ENTER Key
                     
                                                 switch(PMSelected){
                                                      
                                                      case 1:{ //ADD PRODUCTS
                                                           
                                                           //AddRecord(2); // 2 = ProductMenu
                                                           p.AddRecord();
                                                           goto ProductMenu;
                                                           
                                                           break;
                                                           
                                                      }
                                                      
                                                      case 2:{ //VIEW PRODUCTS
                                                      
                                                           p.ViewRecord();
                                                           
                                                           goto ProductMenu; 
                                                           break;
                                                      }
                                                      case 3:{ //EDIT PRODUCTS
                                                           
                                                           p.EditRecord(); 
                                                           goto ProductMenu; 
                                                      
                                                           break;
                                                      }
                                                      case 4:{ //SEARCH PRODUCTS
                                                      
                                                           p.SearchRecord();
                                                           goto ProductMenu;
                                                                
                                                           break;
                                                      }
                                                      
                                                      case 5:{ //DELETE PRODUCTS
                                                      
                                                           p.DeleteRecord();
                                                           goto ProductMenu; 
                                                      
                                                           break;
                                                      }
                                                      
                                                      
                                                      case 6:{ //BACK - should go to main menu
                                                           goto MainMenuLabel;
                                                           break;
                                                      }
                                                      default:{
                                                           break;
                                                      }
                                                 
                                                 }//end of switch
                                            break;
                                            }
                                            
                                            case 27:{ //Case of ESC key.
                                                            goto MainMenuLabel;
                                                            break;
                                                      }
                                        
                                        } //end of switch
                                  }//end of kbhit
                                  
                               }//end of while
                               
                               
                               break;     
                          } //end of case 1 - ie PRODUCTS
                          
                          case 2:{  //EMPLOYEES
                               employee e;
                               EmployeeMenu:
                               system("cls");
                               e.DisplayEmployeesMenu(EMSelected);
                               
                               while(1){
                                  if(kbhit()){
                                     EMEntered=getch();
            
                                        switch(EMEntered){
                                           
                                           case 72:{ // UP Key
                                                 if(EMSelected!=1)
                                                 {
                                                      EMSelected--;
                                                      
                                                      system("cls");
                                                      e.DisplayEmployeesMenu(EMSelected);
                                                 } else if(EMSelected==1)
                                                 {
                                                      EMSelected=6;
                                                      
                                                      system("cls");
                                                      e.DisplayEmployeesMenu(EMSelected);
                                                 }
                                                 
                                                 break;
                                            }
                                            
                                            case 80:{  //DOWN Key
                                                 if(EMSelected!=6)
                                                 {
                                                      EMSelected++;
                                                 
                                                      system("cls");
                                                      e.DisplayEmployeesMenu(EMSelected);
                                                 } else if(EMSelected==6)
                                                 {
                                                      EMSelected=1;
                                                 
                                                      system("cls");
                                                      e.DisplayEmployeesMenu(EMSelected);
                                                 }
                                                 
                                                 break;
                                                
                                            }
                                            
                                            case 13:{ //ENTER Key
                     
                                                 switch(EMSelected){
                                                      
                                                      case 1:{ //ADD EMPLOYEES
                                                      
                                                           //AddRecord(3); // 3 = Employee
                                                           e.AddRecord();
                                                           goto EmployeeMenu;
                                                           
                                                           break;
                                                      }
                                                      case 2:{ //VIEW EMPLOYEES
                                                           
                                                           e.ViewRecord();
                                                           goto EmployeeMenu;
                                                           
                                                           break;
                                                      }
                                                      case 3:{ //EDIT EMPLOYEES
                                                           
                                                           e.EditRecord();
                                                           goto EmployeeMenu;
                                                           break;
                                                      }
                                                      case 4:{ //SEARCH EMPLOYEES
                                                           e.SearchRecord();
                                                           goto EmployeeMenu;
                                                           break;
                                                      }
                                                      case 5:{ //DELETE EMPLOYEES
                                                           
                                                           e.DeleteRecord();
                                                           goto EmployeeMenu;
                                                           break;
                                                      }
                                                      case 6:{ //BACK - should go to main menu
                                                           goto MainMenuLabel;
                                                           break;
                                                      }
                                                      default:{
                                                           break;
                                                      }
                                                 
                                                 }//end of switch
                                            break;
                                            }
                                            case 27:{ //Case of ESC key.
                                                            goto MainMenuLabel;
                                                            break;
                                                      }
                                        
                                        } //end of switch
                                  }//end of kbhit
                                  
                               }//end of while
                               
                               
                               break;     
                          } //end of case 2 - ie EMPLOYEES
                          
                          case 3:{  //CUSTOMERS
                               customer c;
                               CustomerMenu:
                               system("cls");
                               c.DisplayCustomersMenu(CMSelected);
                               
                               while(1){
                                  if(kbhit()){
                                     CMEntered=getch();
            
                                        switch(CMEntered){
                                           
                                           case 72:{ // UP Key
                                                 if(CMSelected!=1)
                                                 {
                                                      CMSelected--;
                                                      
                                                      system("cls");
                                                      c.DisplayCustomersMenu(CMSelected);
                                                 } else if(CMSelected==1)
                                                 {
                                                      CMSelected=6;
                                                      
                                                      system("cls");
                                                      c.DisplayCustomersMenu(CMSelected);
                                                 }
                                                 
                                                 break;
                                            }
                                            
                                            case 80:{  //DOWN Key
                                                 if(CMSelected!=6)
                                                 {
                                                      CMSelected++;
                                                 
                                                      system("cls");
                                                      c.DisplayCustomersMenu(CMSelected);
                                                 } else if(CMSelected==6)
                                                 {
                                                      CMSelected=1;
                                                 
                                                      system("cls");
                                                      c.DisplayCustomersMenu(CMSelected);
                                                 }
                                                 
                                                 break;
                                                
                                            }
                                            
                                            case 13:{ //ENTER Key
                     
                                                 switch(CMSelected){
                                                      
                                                      case 1:{ //ADD CUSTOMERS
                                                      
                                                           //AddRecord(4); // 4 = Customer
                                                           c.AddRecord();
                                                           goto CustomerMenu;
                                                           
                                                           break;
                                                      }
                                                      case 2:{ //VIEW CUSTOMERS
                                                      
                                                           c.ViewRecord();
                                                           goto CustomerMenu;
                                                           
                                                           break;
                                                      }
                                                      case 3:{ //EDIT CUSTOMERS
                                                      
                                                           c.EditRecord();
                                                           goto CustomerMenu;
                                                      
                                                           break;
                                                      }
                                                      case 4:{ //SEARCH CUSTOMERS
                                                           c.SearchRecord();
                                                           goto CustomerMenu;
                                                           break;
                                                      }
                                                      case 5:{ //DELETE CUSTOMERS
                                                      
                                                           c.DeleteRecord();
                                                           goto CustomerMenu;
                                                           
                                                           break;
                                                      }
                                                      case 6:{ //BACK - should go to main menu
                                                           goto MainMenuLabel;
                                                           break;
                                                      }
                                                      default:{
                                                           break;
                                                      }
                                                 
                                                 }//end of switch
                                            break;
                                            }
                                            case 27:{ //Case of ESC key.
                                                            goto MainMenuLabel;
                                                            break;
                                                      }
                                        
                                        } //end of switch
                                  }//end of kbhit
                                  
                               }//end of while
                               
                               
                               break;     
                          } //end of case 3 - ie CUSTOMERS
                          
                          case 4:{ //TRANSACTION BILLING
                               bill b;
                               BillMenu:
                               
                                 //Cursor Deactivate
                                 CONSOLE_CURSOR_INFO CursoInfo;
                                 CursoInfo.dwSize = 1;         /* The size of caret */
                                 CursoInfo.bVisible = false;   /* Caret is visible? */
                                 SetConsoleCursorInfo(hConsole, &CursoInfo);
                                 //End of Cursor Code
                               
                               system("cls");
                               b.DisplayBillMenu(BMSelected);
                               
                               while(1){
                                  if(kbhit()){
                                     BMEntered=getch();
            
                                        switch(BMEntered){
                                           
                                           case 72:{ // UP Key
                                                 if(BMSelected!=1)
                                                 {
                                                      BMSelected--;
                                                      
                                                      system("cls");
                                                      b.DisplayBillMenu(BMSelected);
                                                 } else if(BMSelected==1)
                                                 {
                                                      BMSelected=4;
                                                      
                                                      system("cls");
                                                      b.DisplayBillMenu(BMSelected);
                                                 }
                                                 
                                                 break;
                                            }
                                            
                                            case 80:{  //DOWN Key
                                                 if(BMSelected!=4)
                                                 {
                                                      BMSelected++;
                                                 
                                                      system("cls");
                                                      b.DisplayBillMenu(BMSelected);
                                                 } else if(BMSelected==4)
                                                 {
                                                      BMSelected=1;
                                                 
                                                      system("cls");
                                                      b.DisplayBillMenu(BMSelected);
                                                 }
                                                 
                                                 break;
                                                
                                            }
                                            
                                            case 13:{ //ENTER Key
                     
                                                 switch(BMSelected){
                                                      
                                                      case 1:{ //CREATE BILL
                                                           
                                                           b.CreateBill();
                                                           
                                                           goto BillMenu;
                                                           break;
                                                           
                                                      }
                                                      
                                                      case 2:{ //VIEW BILLS
                                                           
                                                           
                                                           goto BillMenu; 
                                                           break;
                                                      }
                                                      case 3:{ //SEARCH BILLS
                                                           
                                                           
                                                           goto BillMenu; 
                                                      
                                                           break;
                                                      }
                                                      
                                                      case 4:{ //BACK - should go to main menu
                                                           goto MainMenuLabel;
                                                           break;
                                                      }
                                                      default:{
                                                           break;
                                                      }
                                                 
                                                 }//end of switch
                                            break;
                                            }
                                            
                                            case 27:{ //Case of ESC key.
                                                            goto MainMenuLabel;
                                                            break;
                                                      }
                                        
                                        } //end of switch
                                  }//end of kbhit
                                  
                               }//end of while
                               
                               break;     
                          }
                          
                          case 5:{ //SALES & STOCK
                               
                               break;     
                          }
                          
                          case 6:{  //EXIT
                               return 0;
                               break;     
                          }
                          
                          default:{
                               break;
                          }
                     
                     } //end of switch

                     break;
                }
                
                case 27:{ //Case of ESC key.
                    return 0;
                    break;
                }

                default:{
                         
                         break;
                }
                
            } // end of switch()

        } //end of kbhit()
       
	} //end of while()

    
    
    
    
    getch();
    
    return EXIT_SUCCESS;
    
} // END of Main


// Function Definitions ===============================

void BlankSpace(int n)
{
     for(int i=1;i<=n;i++)
     {
             cout<<" ";
     }
}

void CharDisplay(int charID, int w) //CharID = Character Set's No, W=Width
{
     for(int i;i<=w;i++)
     {
             cout<<(char) charID;
     }
}

void DisplayHeader()
{    
    cout<<endl;
    BlankSpace(28);

    SetConsoleTextAttribute(hConsole, 12);
    cout<<"SUPERMARKET INVENTORY MANAGEMENT";
    cout<<"\n  ";
    
    CharDisplay(205,80);
    
    cout<<endl;
    
    SetConsoleTextAttribute(hConsole, 15); //Black BG, White FG
}

void CategoryHeader(char s[])
{
    int len=strlen(s);
    BlankSpace((43-(len/2)));
    cout<<s<<endl;
    for(int i=1;i<=((43-(16/2)));i++)
    {
            cout<<" ";
    }
    CharDisplay(196,16);   
}

void CenterText(char s[])
{
    int len=strlen(s);
    BlankSpace((43-(len/2)));
    cout<<s;
}

void MenuItems(char *a, char*b, char *c, char *d, char *e, char *f, int & selected)
{
    
    /*
    if(selected)
        menu item highlight activate
            print text (products, employee...)
        menu item highlight deactivate
    */
    
    if(strcmp(a,"")!=0){
    BlankSpace((43-(strlen(a)/2)));
    if(selected==1)
         SetConsoleTextAttribute(hConsole, 240);
    cout<<a<<endl<<endl;
    if(selected==1)
         SetConsoleTextAttribute(hConsole, 15);
    }
    
    if(strcmp(b,"")!=0){
    BlankSpace((43-(strlen(b)/2)));
    if(selected==2)
         SetConsoleTextAttribute(hConsole, 240);
    cout<<b<<endl<<endl;
    if(selected==2)
         SetConsoleTextAttribute(hConsole, 15);
    }       
    
    if(strcmp(c,"")!=0){
    BlankSpace((43-(strlen(c)/2)));
    if(selected==3)
         SetConsoleTextAttribute(hConsole, 240);
    cout<<c<<endl<<endl;
    if(selected==3)
         SetConsoleTextAttribute(hConsole, 15);
    }
    
    if(strcmp(d,"")!=0){
    BlankSpace((43-(strlen(d)/2)));
    if(selected==4)
         SetConsoleTextAttribute(hConsole, 240);
    cout<<d<<endl<<endl;
    if(selected==4)
         SetConsoleTextAttribute(hConsole, 15);
    }
    
    if(strcmp(e,"")!=0){
    BlankSpace((43-(strlen(e)/2)));
    if(selected==5)
         SetConsoleTextAttribute(hConsole, 240);
    cout<<e<<endl<<endl;
    if(selected==5)
         SetConsoleTextAttribute(hConsole, 15);
    }
    
    if(strcmp(f,"")!=0){     
    BlankSpace((43-(strlen(f)/2)));
    if(selected==6)
         SetConsoleTextAttribute(hConsole, 240);
    cout<<f<<endl;
    if(selected==6)
         SetConsoleTextAttribute(hConsole, 15);
    }
    
}

void DisplayMainMenu(int & ChoiceSelected)
{
     
    DisplayHeader(); // ========= Header  
    
    cout<<endl;
    
    CategoryHeader("Select Menu");
    
    //========================================================================
    
    cout<<endl<<endl<<endl;
    
    MenuItems("PRODUCTS","EMPLOYEES","CUSTOMERS","TRANSACTION BILLING","SALES & STOCK","EXIT",ChoiceSelected);
}

void CursorPos(int x, int y)
{
     COORD position;
     position.Y = y;
     position.X = x;
     SetConsoleCursorPosition(hConsole, position);
}

string LimitBuffer(int w)
{
    string str;
    char a;
    
    int count=0;
    
    while(1)
    {
         if(kbhit())
         {
              
              a=getch();
              
              if((a>47 && a<58)||(a>64 && a<91)||(a>96 && a<123))
              {
                   if(count<w)
                   {
                      cout<<a;
                      str=str+a;
                      count++;
                   }
                   
                   
              } else if(a==8) //Backspace
              {
                     if(count!=0)
                     {
                         CursorPos(GetCursorPosX()-1,GetCursorPosY());
                         cout<<" ";
                         CursorPos(GetCursorPosX()-1,GetCursorPosY());
                         count--;
                         str.resize(count);
                     }
                     
              } else if(a==13) //Enter
              {
                   break;
              }
              
         }
         
    }
    
    return str;
}

int GetCursorPosX()
{
    int x;
    CONSOLE_SCREEN_BUFFER_INFO con;
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hcon != INVALID_HANDLE_VALUE &&
        GetConsoleScreenBufferInfo(hcon,&con)) 
    {
        x = con.dwCursorPosition.X;
    }
    
    return x;
}

int GetCursorPosY()
{
    int y;
    CONSOLE_SCREEN_BUFFER_INFO con;
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hcon != INVALID_HANDLE_VALUE &&
        GetConsoleScreenBufferInfo(hcon,&con)) 
    {
        y = con.dwCursorPosition.Y;
    }
    
    return y;
}
