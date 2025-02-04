#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include <fstream>
using namespace std;
namespace Lib {
	struct StClientInfo {
			string name;
			string AccountName;
			string Balance;
			string phone;
			string PinCode;
	};
	enum enMainChoice {
		ShowClientLIst = 1,
		adddNewClient = 2,
		deleteClient = 3,
		updateClient = 4,
		findClient = 5,
		resetClients = 6,
		TransActions = 7,
		MangeUsers = 8,
		LogOut = 9,
		Quit = 10
	};
	enum enManageUsers {
		UserList = 1,
		Adduser = 2,
		deleteuser = 3,
		updateuser = 4,
		finduser = 5,
		MainMenue = 6
	};
	enum enTransActions {
		deposit = 1,
		withdraw = 2,
		mainmenue = 3
	};
	struct StUser {
		string name;
		string Pass;
		string permession = "";
	};
	struct StNowUser {
		string name;
		string Pass;
		string permession = "";
	};
	vector <string> SaveFileContentToVec(string FileName) {
		vector <string> clients;
		fstream file;
		file.open(FileName, ios::in);
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {

				if (line != "") {
					clients.push_back(line);
				}
			}
			file.close();
		}
		else cout << "no clients have been added yet! \n";
		return clients;
	}
	vector <string> SplitStringToVector(string input, string delim = " () ") {
		vector <string> Vword;
		int pos = 0;
		string sword;
	while ((pos = input.find(delim)) != std::string::npos) {
			sword = input.substr(0, pos);
			if (sword != "") {
				Vword.push_back(sword);
			}
			input.erase(0, pos + delim.length());
		}
		if (input != "")
			Vword.push_back(input);
		return Vword;
	}
	string ConvertVectorToString(vector <string> Words, string delim = " () ") {
			string Sentence = "";
			for (string& s : Words) {
				Sentence += s + delim;
			}
		return Sentence.substr(0, Sentence.length() - delim.length());
	}
	StClientInfo ConvertClientStringToStruct(string MonoPerson) {
		StClientInfo person;
		vector <string> Person = SplitStringToVector(MonoPerson, " () ");
		person.AccountName = Person.at(0);
		person.PinCode = Person.at(1);
		person.name = Person.at(2);
		person.phone = Person.at(3);
		person.Balance = Person.at(4);
		return person;
	}
	int FindClientAccountNumber(string NumbeAcc) {
		vector <string> clients = SaveFileContentToVec("clients.txt");
		for (int i = 0; i < clients.size(); i++) {
			StClientInfo person = ConvertClientStringToStruct(clients[i]);
			if (person.AccountName == NumbeAcc)
				return i;
		}
		return -1;
	}
	void SaveVecToFile(vector <string> clients, string name) {
		fstream file;
		file.open(name, ios::out);
		if (file.is_open()) {
			for (string s : clients) {
				file << s << "\n";
			}
			file.close();
		}
	}
	void DisplayVectorOnScreen(vector<string> data) {
			cout << left << setw(15) << "\nAccount Number" << ": " << data[0];
			cout << left << setw(15) << "\nPin code" << ": " << data[1];
			cout << left << setw(15) << "\nName" << ": " << data[2];
			cout << left << setw(15) << "\nphone number" << ": " << data[3];
			cout << left << setw(15) << "\nsalary" << ": " << data[4] << " $\n";
	}
	bool ClientExist(string AccountName) {
		int ClientPos;
		ClientPos = FindClientAccountNumber(AccountName);
		if (ClientPos == -1) return 0;
		return 1;
	}
	StClientInfo ReadClientData() {
		StClientInfo person;
		int ClientPos;
		do {
			cout << "Enter Account Name : ";
			getline(cin >> ws, person.AccountName);
			if (!ClientExist(person.AccountName)) break;
			cout << "this Account Number is already exist try another one \n";
		} while (true);

		cout << "Enter Client Name : ";
		getline(cin >> ws, person.name);
		cout << "Enter Account Balance : ";
		getline(cin >> ws, person.Balance);
		cout << "Enter Phone Number : ";
		getline(cin >> ws, person.phone);
		cout << "Enter Phone Pin Code : ";
		getline(cin >> ws, person.PinCode);
		return person;
	}
	vector <string> ConvertStructToVector(StClientInfo person) {
		vector <string> ClientData;
		ClientData.push_back(person.AccountName);
		ClientData.push_back(person.PinCode);
		ClientData.push_back(person.name);
		ClientData.push_back(person.phone);
		ClientData.push_back(person.Balance);
		return ClientData;
	}
	void SaveStringToFile(string Line, string name) {
		fstream file;
		file.open(name, ios::out | ios::app);
		if (file.is_open()) {
			if (Line != "") file << "\n" << Line;
			file.close();
		}

	}
	StClientInfo UpdateStructOfPerson(vector <string>& clients, int& ClientPos) {
		StClientInfo person;
		clients = SaveFileContentToVec("clients.txt");
		cout << "\nenter your account number : ";
		cin >> person.AccountName;
		ClientPos = FindClientAccountNumber(person.AccountName);
		if (ClientPos != -1) {
			DisplayVectorOnScreen(SplitStringToVector(clients[ClientPos], " () "));
			do {
				cout << "\n\nEnter new Account Number : ";
				getline(cin >> ws, person.AccountName);
				if (!ClientExist(person.AccountName)) {
					break;
				}
				cout << "try another, this account is already exist \n";
			} while (true);
			cout << "Enter new Client Name : ";
			getline(cin, person.name);
			cout << "Enter new Account Balance : ";
			getline(cin, person.Balance);
			cout << "Enter new Phone Number : ";
			getline(cin, person.phone);
			cout << "Enter new Phone Pin Code : ";
			getline(cin, person.PinCode);
		}
		else cout << "\nthe client is not exist\n";
		return person;
	}
	enMainChoice ReadChoiceFromUser() {
		short choice;
		cout << "\n\nWhich of these would you like to start with ? (1 : 10) : ";
		cin >> choice;

		while (cin.fail() || choice > 10 || choice < 1) {
			cin.clear();
			cin.ignore(std::numeric_limits< std::streamsize> ::max(), '\n');
			cout << "\npls enter a valid choice (1 : 10) only \n";
			cin >> choice;

		}
		return enMainChoice(choice);
	}
	void TransMenu() {
		system("cls");
		cout << "\n ******************************************************************************* \n";
		cout << "			   Transactions Menue Screen		\n";
		cout << " ******************************************************************************* \n";

		cout << "\n			   (1) ==> Deposit.\n";
		cout << "			   (2) ==> WithDrow.\n";
		cout << "			   (3) ==> Main Menue.\n";
	}
	enTransActions TransAns() {
		short choice;
		cout << "Enter a choice : (1 : 3) ";
		cin >> choice;
		while (cin.fail() || choice > 3 || choice < 1) {
			cin.clear();
			cin.ignore(std::numeric_limits< std::streamsize> ::max(), '\n');
			cout << "Enter a valid choice : (1 : 3) ";
			cin >> choice;
		}
		return enTransActions(choice);
	}
	void DepositScreenOrWithdrow(bool IsBlus) {

		system("cls");
	
				cout << "----------------------------------------\n";
	if (IsBlus) cout << "	     Deposit Screen \n";
	else		cout << "	     WithDrow Screen \n";
				cout << "----------------------------------------\n";


		int Ammount = 0;
		vector <string> clients = SaveFileContentToVec("clients.txt");
		string Accountnumber;
		cout << "Enter Account Number : ";
		cin >> Accountnumber;
		int ClientPos = FindClientAccountNumber(Accountnumber);
		if (ClientPos == -1) {
			cout << "\nthier no such account :(  ";
		}
		else {
			StClientInfo person = ConvertClientStringToStruct(clients[ClientPos]);
			DisplayVectorOnScreen(SplitStringToVector(clients[ClientPos], " () "));
			if (IsBlus) cout << "\n\nhow much money you want to deposit for this account ? : ";
			else  cout << "\n\nhow much money you want to Withdrow from this account ? : ";
			cin >> Ammount;
			char Sure;
			if (IsBlus) cout << "are you sure you want to deposit " << Ammount << " $ to " << Accountnumber << " ? (y,n) ";
			else {
				while (Ammount > stoi(person.Balance)) {
					//cin.clear();
					//cin.ignore(std::numeric_limits< std::streamsize> ::max(), '\n');
					cout << "you have the chance to withdrow only up to " << person.Balance << " try again : \n";
					cin >> Ammount;
				}
				cout << "\nare you sure you want to Withdrow " << Ammount << " $ from " << Accountnumber << " ? (y,n) ";
			}
			cin >> Sure;
			if (Sure == 'y' || Sure == 'Y') {
				if (IsBlus) {
					person.Balance = to_string(stoi(person.Balance) + Ammount);
				}
				else
				{

					person.Balance = to_string(stoi(person.Balance) - Ammount);
				}

				clients[ClientPos] = ConvertVectorToString(ConvertStructToVector(person), " () ");
				SaveVecToFile(clients, "clients.txt");
				cout << "\n";
				if (IsBlus) cout << Ammount << "$ has been deposted to " << Accountnumber << " Successfully :') ";
				else cout << Ammount << "$ has been Withdrowed from " << Accountnumber << " Successfully :') ";
			}
		}
	}
	void GoBackToManageUsersScreen(){
		cout << "press any key to get to Manage Users Screen... ";
		system("pause>0");
		//ManageUsersScreen();
	}
	StUser ConvertUserStringToStruct(string MonoPerson) {
		StUser User;
		vector <string> user = SplitStringToVector(MonoPerson, " () ");
		User.name = user.at(0);
		User.Pass = user.at(1);
		User.permession = user.at(2);
		return User;
	}
	void PrintUserString(string MonoUser) {
		StUser user = ConvertUserStringToStruct(MonoUser);
		cout << "\n----------------------\n";
		cout << "User Name  : " << user.name;
		cout << "\nPassword   : " << user.Pass;
		cout << "\nPermisions : " << user.permession;
		cout << "\n----------------------\n";
	}
	int FindUserName(string username, vector <string> Users) {
		for (int i = 0; i < Users.size(); i++) {
			StUser user = ConvertUserStringToStruct(Users[i]);
			if (user.name == username)
				return i;
		}
		return -1;
	}
	bool IsRighPass(int pos, string pass) {
		vector <string> Users = SaveFileContentToVec("users.txt");
		StUser user = ConvertUserStringToStruct(Users[pos]);
		return (user.Pass == pass);
	}
	enManageUsers ReadManChoice() {
		int ch;
		cout << "\nyour choice : ";
		cin >> ch;
		return enManageUsers(ch);
	}
	vector <string> ReadUser(){
		char Ans;
		StUser uSer;
		vector <string> user;
		while(true){
			cout << "\nenter UserName : ";
			getline(cin >> ws, uSer.name);
			if (FindUserName(uSer.name, SaveFileContentToVec("users.txt")) == -1) {
			user.push_back(uSer.name);
				 break;
			}
			cout << "this is account already exist !, try again...\n\n";
		}
		cout << "\nenter Password : ";
		getline(cin >> ws, uSer.Pass);
		user.push_back(uSer.Pass);
		cout << "\nare you want to give him full access ? (y, n) : ";
		cin >> Ans;
		if (Ans == 'y' || Ans == 'Y') uSer.permession = "12345678";
		else {
			cout << "\nAccess to Clients List ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') uSer.permession += "1";
			cout << "\nAccess to Add New Client Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') uSer.permession += "2";
			cout << "\nAccess to Delete Client Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') uSer.permession += "3";
			cout << "\nAccess to Update Client Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') uSer.permession += "4";
			cout << "\nAccess to Find Client Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') uSer.permession += "5";
			cout << "\nAccess to Reset Clients Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') uSer.permession += "6";
			cout << "\nAccess to TransActions Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') uSer.permession += "7";
			cout << "\nAccess to Manage Users Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') uSer.permession += "8";
			if(uSer.permession == "" || uSer.permession == " ") uSer.permession = "0";
		}
		user.push_back(uSer.permession);
		return user;
	}
	StNowUser LogInScreen() {
		StUser user;
		StNowUser NowUser;
		system("cls");
		cout << "------------------------------\n";
		cout << "	Log in screen\n";
		cout << "------------------------------\n";
		int pos;
		while (true) {
			cout << "\n\nenter username : ";
			cin >> user.name;
			vector<string>Users = SaveFileContentToVec("users.txt");
			pos = FindUserName(user.name, Users);
			if (pos != -1)
			{
				NowUser.permession = ConvertUserStringToStruct(Users[pos]).permession;
				NowUser.name = user.name;
				break;
			}
			cout << "\nthere is no user with this user name !, try again ! \n\n";
		}
		cout << "\nenter password : ";
		while (true) {
			cin >> user.Pass;
			if (IsRighPass(pos, user.Pass)) {
				NowUser.Pass = user.Pass;
				break;
			}
			cout << "\nwrong password, try again : ";
		}
		return NowUser;

	}
	void NotAllowed() {
		system("cls");
		cout << "| you have no Access to this option :( \n";
		cout << "| Contact Your Admin..\n";
	}
	bool IsAllowed(vector<string> NowUser, char num) {
		for (char c : NowUser[2]) {
			if (c == num) return 1;
		}
		return 0;
	}
	string SaveFileContentToString(string filename = "nowuser.txt") {
		fstream file;
		file.open(filename, ios::in);
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				if (line != "") break;
			}
			return line;
			file.close();
		}
	}

}