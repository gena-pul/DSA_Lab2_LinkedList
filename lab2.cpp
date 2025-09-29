#include <iostream>
#include <vector>
using namespace std;

struct User{
   string username;
   string password;
   vector<string> permissions;
   User* next;

   User(const string& u, const string& p, const vector<string>& pm = {"view"}){
	username = u;
	password = p;
	permissions = pm;
	next = nullptr;

  }
};

bool insertUser(User*& head, const string& username, const string& password, const vector< string>& permissions = {"view"});
User* findUser(User* head, const string& username);
bool authorize(User* head, const string& username, const string& action);

int main() {

	User* head = nullptr;

	insertUser(head, "Gemma Ross", "gross0987!",{"view", "edit", "create", "delete"});
	insertUser(head, "John Moralez", "Jkmlo382", {"view", "edit", "create"});
	insertUser(head, "Kaylee Pott", "pottheFlower2323^", {"view"});

	cout << "\nAuthorization requested: Gemma Ross, delete " << authorize(head, "Gemma Ross", "delete") << endl;
	cout << "\nAuthorization requested: John Moralez, edit " << authorize(head, "John Moralez", "edit") << endl;
	cout << "\nAuthorization requested: John Moralez, delete " << authorize(head, "John Moralez", "delete") << endl;
	cout << "\nAuthorization requested: Kaylee Pott, grant " << authorize(head, "Kaylee Pott", "create") << endl;
	cout << "\nAuthorization requested: Kaylee Pott, grant " << authorize(head, "Kaylee Pott", "edit") << endl;

	return  0;
}

bool insertUser(User*& head, const string& username, const string& password, const vector<string>& permissions){
	if(!head){
	head = new User(username, password, permissions);
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
	current->next = new User(username, password, permissions);
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

	for(const string& perm : u->permissions){
	 if(perm == action){
	   return true;
          }
	}

	return false;
}
