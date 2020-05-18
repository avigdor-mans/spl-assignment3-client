//
// Created by aviv on 12/01/2020.
//

#include <algorithm>
#include "../include/ClientData.h"
#include <vector>

string ClientData::getOwnewr(string book) {
    string theOwner = "";
    for(auto owner: ownersPerBook)
    {
        if (owner.first.compare(book)==0){
            theOwner = owner.second;
        }
    }
    return theOwner;
}
ClientData::ClientData() : username(""),booksPerTopic(),ownersPerBook(),wishList(),IsConnected(false),
reciptsAndDisplays(){

}
ClientData::~ClientData() {
    for (pair<string,vector<string>*> pair : booksPerTopic)
    {
        pair.second->clear();
        delete pair.second;
    }
    booksPerTopic.clear();
}

string ClientData::getName() {
    return username;
}
void ClientData::connect() {
    IsConnected = true;
}
void ClientData::DisConnect() {
    IsConnected = false;
}

bool ClientData::isConnected() {
    return  IsConnected;
}

void ClientData::setUserName(string name) {
    username = name;
}

string ClientData::getUserName() {
    return username;
}

string ClientData::getDisplayByReceipt(int receiptId) {
    return reciptsAndDisplays[receiptId];
}

bool ClientData::isBookExists(string topic, string book) {
    bool answer = false;
    for (pair<string,vector<string>*> pair : booksPerTopic)
    {
        if (topic.compare(pair.first) == 0)
        {
            if (!booksPerTopic[topic]->empty()) {
                for (string b : (*booksPerTopic[topic])) {
                    if (b.compare(book) == 0)
                        answer = true;
                }
            }
        }
    }
    return answer;
}
void ClientData::addBook(string topic, string bookName) {
    bool isTopicExist = false;
    for (pair<string,vector<string>*> pair : booksPerTopic)
    {
        if (topic.compare(pair.first) == 0)
        {
            isTopicExist = true;
            booksPerTopic[topic]->push_back(bookName);
        }
    }
    if (!isTopicExist)
    {
        vector<string> *a = new vector<string>();
        booksPerTopic.insert(pair<string,vector<string>*>(topic,a));
        booksPerTopic[topic]->push_back(bookName);
    }
}

vector<string> &ClientData::getWishList() {
    return wishList;
}
vector<string>* ClientData::getBooksForATopic(string topic) {
    vector<string>* temp = new vector<string>();
    for (pair<string,vector<string>*> pair : booksPerTopic)
    {
        if (topic.compare(pair.first) == 0)
        {
            temp = booksPerTopic[topic];
        }
    }
    return temp;
}

void ClientData::addDisplayForReceipt(int receiptId, string display) {
    reciptsAndDisplays.insert(pair<int,string>(receiptId,display));
}


void ClientData::addBorrowedBook(string ownerName,string topic, string bookName) {
    ownersPerBook.insert(pair<string,string>(bookName,ownerName));
    addBook(topic,bookName);

}

void ClientData::removeBook(string topic, string book) {
    int tmp = 0;
    int toErase = 0;
    for(string b : (*booksPerTopic[topic]))
    {
        if (b.compare(book) == 0)
        {
            toErase = tmp;
        }
        tmp++;
    }
    booksPerTopic[topic]->erase (booksPerTopic[topic]->begin()+toErase);
    if (booksPerTopic[topic]->size()==0){
       delete booksPerTopic[topic];
       booksPerTopic.erase(topic);
    }
}

void ClientData::returnBorrowedBook(string owner, string topic, string book) {

    for (pair<string,string> pair : ownersPerBook)
    {
        if (pair.first.compare(book) == 0)
        {
            removeBook(topic,book);
        }
    }
    ownersPerBook.erase(book);

}

void ClientData::addBookToWishList(string bookName) {
    wishList.push_back(bookName);
}
void ClientData::removeFromWishList(string bookName) {
    int tmp = 0;
    int toErase = 0;
    for(string b : wishList)
    {
        if (b.compare(bookName) == 0)
        {
            toErase=tmp;
        }
        tmp++;
    }
    wishList.erase (wishList.begin()+toErase);
}