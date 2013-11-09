#include <cstdio>
#include <map>
#include <string>
#include <iostream>

using namespace std;

map<string, string> password;
map<string, bool> logged_in;

int main() {
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;

        if(cmd == "login") {
            string user, pass;
            cin >> user >> pass;

            if(password.find(user) == password.end()) {
                printf("fail: no such user\n");
            } else if(password[user] != pass) {
                printf("fail: incorrect password\n");
            } else if(logged_in[user]) {
                printf("fail: already logged in\n");
            } else {
                logged_in[user] = true;
                printf("success: user logged in\n");
            }
        } else if(cmd == "logout") {
            string user;
            cin >> user;

            if(password.find(user) == password.end()) {
                printf("fail: no such user\n");
            } else if(!logged_in[user]) {
                printf("fail: already logged out\n");
            } else {
                logged_in[user] = false;
                printf("success: user logged out\n"); 
            }
        } else {
            string user, pass;
            cin >> user >> pass;

            if(password.find(user) != password.end()) {
                printf("fail: user already exists\n");
            } else {
                password[user] = pass;
                printf("success: new user added\n");
            }
        }
    }

    return 0;
}

