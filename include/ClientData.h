//
// Created by aviv on 12/01/2020.
//

#ifndef UNTITLED_CLIENTDATA_H
#define UNTITLED_CLIENTDATA_H

#include <string>
#include <unordered_map>
#include <vector>
#include <condition_variable>
using namespace std;
class ClientData {
    private:
    string username;
    unordered_map<string,vector<string>*> booksPerTopic;
    unordered_map<string,string> ownersPerBook;
    vector<string> wishList;
    bool IsConnected;
    unordered_map<int,string> reciptsAndDisplays;
public:
    vector<string>* getBooksForATopic(string topic);
    unordered_map<string,string>& getOwnersPerBook();
    vector<string>& getWishList();
    string getOwnewr(string book);
    string getName();
    ClientData();
    ~ClientData();
    void connect();
    void DisConnect();
    bool isConnected();
    void setUserName(string name);
    string getUserName();
    string getDisplayByReceipt(int receiptId);
    void addDisplayForReceipt(int receiptId, string display);
    bool isBookExists(string topic, string bookName);
    void addBook(string topic, string bookName);
    void addBorrowedBook(string ownerName,string topic, string bookName);
    void removeBook(string topic, string book);
    void returnBorrowedBook(string owner, string topic, string book);
    void addBookToWishList(string bookName);
    void removeFromWishList(string bookName);

};


#endif //UNTITLED_CLIENTDATA_H
