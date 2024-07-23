#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class Book{
    int book_id;
    string book_name;
    string author;
    float price;
    bool status;
    public:
        void acceptbook(){
            cout<<"\n\t Enter book id: ";
            cin>>book_id;
            cout<<"\t Enter book name: ";
            cin>>book_name;
            cout<<"\t Enter author name: ";
            cin>>author;
            cout<<"\t Enter price: ";
            cin>>price;
            status=false;
        }
        void display(){
            cout<<"\n\t *****************************************"<<endl;
            cout<<"\t Name   : "<<book_name<<endl;
            cout<<"\t ID     : "<<book_id<<endl;
            cout<<"\t Author : "<<author<<endl;
            cout<<"\t Price  : "<<price<<endl;
            if(status == false){
                cout<<"\t Status : Not Issued"<<endl;
            }
            else{
                cout<<"\t Status : Issued"<<endl;
            }
            cout<<"\t *****************************************"<<endl;
        }
        void addbook();
        void viewbook();
        void issuebook();
        void searchbook();
        void deletebook(string n);
};

Book obj;
void Book::addbook(){
    char op;
    do{
        fstream rd;
        rd.open("./book_data.txt",ios::in);
        string n;
        bool exists = false;
        cout<<"\n\t Enter book name to check if it exists: ";
        cin>>n;
        while (rd.read((char*)&obj, sizeof(obj))) {
            if (n == obj.book_name) {
                exists = true;
                break;
            }
        }
        rd.close();
        if (exists) {
            cout << "\t Book Already Exists!" << endl;
        }
        else{
            cout<<"\t Book is not there, You may add"<<endl;
            obj.acceptbook();
            fstream wr;
            wr.open("./book_data.txt",ios::out | ios::app);
            wr.write((char *)&obj,sizeof(obj));
            cout<<"\t ********************* Book Added Successfully ********************"<<endl;  
        }
        cout<<"\n\t Do you want to add more books, (Y/N):  ";
        cin>>op;
    }while(op=='y' || op=='Y');
}
void Book::viewbook(){
    fstream rd;
    rd.open("./book_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size = rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    if(size==0){cout<< "\t Sorry, Book is not available now."<<endl;}
    for(int i=1;i<=size;i++){
        rd.read((char*)&obj,sizeof(obj));
        obj.display();
    }
}
void Book::issuebook() {
    fstream rdwr;
    rdwr.open("./book_data.txt", ios::in | ios::out | ios::binary);
    string n;
    cout << "\n\t Enter name of the book to issue: ";
    cin >> n;
    int found = 0;
    while (rdwr.read((char*)&obj, sizeof(obj))) {
        if (n == obj.book_name && !obj.status) { 
            found = 1;
            obj.status = true; 
            cout<<"\t ********************* Book Issued Successfully ********************"<<endl;
            break;
        }
    }
    rdwr.close();
    if (!found) {
        cout << "\t Sorry, either the book is not found or it's already issued." << endl;
    }
    else{
        obj.display();
        obj.deletebook(n);
    }
}

void Book::searchbook(){
    fstream rd;
    rd.open("./book_data.txt",ios::in);
    string n;
    cout<<"\n\t Enter name of book: ";
    cin>>n;
    rd.seekg(0,ios::end);
    int size = rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    int flag = 0;
    for(int i=1;i<=size;i++){
        rd.read((char*)&obj,sizeof(obj));
        if(n==obj.book_name){
            flag = 1;
            break;
        }
    }
    if(flag == 0){
        cout<<"\t Sorry We didn't find that book !"<<endl;
    }
    else{
    	cout<<"\t ********************* Book Found ********************"<<endl;
        obj.display();
    }
}
void Book::deletebook(string n){
    fstream rd,wr;
    rd.open("./book_data.txt",ios::in);
    wr.open("./temp.txt",ios::app);
    rd.seekg(0,ios::end);
    int size = rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    int flag = 0;
    for(int i=1;i<=size;i++){
        rd.read((char*)&obj,sizeof(obj));
        if(n!=obj.book_name){
            wr.write((char *)&obj,sizeof(obj));
        }
    }
    rd.close();
    wr.close();
    remove("./book_data.txt");
    rename("./temp.txt","./book_data.txt");
}
int main(){
    int choice;
    Book b1;
    cout<<"\n\t********************* Welcome To Library Management System ********************"<<endl;
    while(1){
        cout<<"\n\t\t\t What would you want me to do ?"<<endl;
        cout<<"\t -----------------------------------------------------------------------"<<endl;
        cout<<"\t 1. Add Book"
            <<"\t 2. View Book"
            <<"\t 3. Search Book"
            <<"\t 4. Issue Book"
            <<"\t 0. Exit"<<endl;
        cout<<"\n\t Enter here: ";
        cin>>choice;
        if(choice == 1){
            b1.addbook();
        }
        else if(choice == 2){
            b1.viewbook();
        }
        else if(choice == 3){
            b1.searchbook();
        }
        else if(choice == 4){
            b1.issuebook();
        }
        else{
            break;
        }
    }
    cout<<"\n\t Thank You for using our software"<<endl<<"\t Have a Nice Day !"<<endl<<endl;
    return 0;
}