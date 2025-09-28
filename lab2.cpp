#include <iostream>
using namespace std;

struct User{
   string username;
   string password;
   string role;
   User* next;

   User(const string& u, const string& p, const string& r = "viewer"){
	username = u;
	password = p;
	role = r;
	next = nullptr;

  }
};

bool insertUser(User*& head, const string& username, const string& password, const string& role = "viewer");
User* findUser(User* head, const string& username);
bool authorize(User* head, const string& username, const string& action);

int main() {

	User* head = nullptr;

	insertUser(head, "Gemma Ross", "gross0987!","admin");
	insertUser(head, "John Moralez", "Jkmlo382", "editor");
	insertUser(head, "Kaylee Pott", "pottheFlower2323^","grant");

	cout << "\nAuthorization requested: Gemma Ross, delete " << authorize(head, "Gemma Ross", "delete") << endl;
	cout << "\nAuthorization requested: John Moralez, edit " << authorize(head, "John Moralez", "edit") << endl;
	cout << "\nAuthorization requested: John Moralez, delete " << authorize(head, "John Moralez", "delete") << endl;
	cout << "\nAuthorization requested: Kaylee Pott, grant " << authorize(head, "Kaylee Pott", "create") << endl;
	cout << "\nAuthorization requested: Kaylee Pott, grant " << authorize(head, "Kaylee Pott", "edit") << endl;

	return  0;
}

bool insertUser(User*& head, const string& username, const string& password, const string& role){
	if(!head){
	head = new User(username, password, role);
	return true;
	}

	User* current = head;
	while(current->next){
	 if(current->username == username){
	   return false;
	}
	current = current->next;
	}

	if(current->username == username){
	   return false;
	}
	current->next = new User(username, password, role);
	return true;
}
User* findUser(User* head, const string& username){
	User* current = head;
	while(current){
	    if(current->username == username){
	       return current;
	    }
	current = current->next;
	}
	return nullptr;
}
bool authorize(User* head, const string& username, const string& action){
	User* u = findUser(head, username);
	if(!u){
	 return false;
	}

	if(u->role== "admin"){
	   return true;
	}
	if(u->role== "editor"){
           return action == "view"|| action == "create" || action == "edit";
        }
	if(u->role== "viewer"){
           return action == "view";
        }

	return false;
}
