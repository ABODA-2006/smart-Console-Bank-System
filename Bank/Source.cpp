// Console cpp Bank Project
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include <fstream>
#include "Header.h"
using namespace std;
using namespace Lib; 
void MainProgram();
void GoBackToMainMenu(); 
void Process();
void GoBackToTransMenu(); 
void NowUser();
void DisplayMainScreen() {
	system("cls");
	cout << "\n ******************************************************************************* \n";
	cout << "				Main Menue Screen		\n";
	cout << " ******************************************************************************* \n";
	
	cout << "\n			   (1)  ==> Display Client List.\n";
	cout << "			   (2)  ==> Add New Client.\n";
	cout << "			   (3)  ==> Delete Client.\n";
	cout << "			   (4)  ==> Update Client.\n";
	cout << "			   (5)  ==> Find Client.\n";
	cout << "			   (6)  ==> reset Clients.\n";
	cout << "			   (7)  ==> TransActions.\n";
	cout << "			   (8)  ==> Manage Users.\n";
	cout << "			   (9)  ==> Log out .\n";
	cout << "			   (10) ==> Quit .\n";
}
void ShowClientList() {
	system("cls");
	vector <string> clients = SaveFileContentToVec("clients.txt");
	int clientsize = clients.size();
	printf("\n\nClient List (%d) Client (s).\n", clientsize);
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(20) << "Account Number" << "| " << setw(10) << "Pin Code" << "| " << setw(25) << "client Name" << "| " << setw(25) << "Phone" << "| " << setw(10) << "Balance" << "\n";
	cout << "--------------------------------------------------------------------------------------------------\n\n";
	for (int i = 0; i < clients.size(); i++) {
		StClientInfo person = ConvertClientStringToStruct(clients[i]);
		cout << "| " << left << setw(20) << person.AccountName << "| " << setw(10) << person.PinCode << "| " << setw(25) << person.name << "| " << setw(25) << person.phone << "| "  << person.Balance << " $ \n";
	}
	cout << "\n--------------------------------------------------------------------------------------------------\n\n";
}
void AddNewClient(StClientInfo person) {
	system("cls");
	cout << "----------------------------------------\n";
	cout << "	  Add Client Screen \n";
	cout << "----------------------------------------\n";
	vector <string> ClientData;
	person = ReadClientData();
	ClientData = ConvertStructToVector(person);
	SaveStringToFile(ConvertVectorToString(ClientData, " () "), "clients.txt");
	cout << "\n Client Added Successfully :') \n";
	
}
void DeleteClient() {
	system("cls");
	cout << "----------------------------------------\n";
	cout << "	  Delete Client Screen \n";
	cout << "----------------------------------------\n";
	StClientInfo person;
	vector <string> clients = SaveFileContentToVec("clients.txt");
	cout << "Which Client account number you search for ? : ";
	cin >> person.AccountName;
	int ClientPos = FindClientAccountNumber(person.AccountName);
	if (!ClientExist(person.AccountName)) cout << "\nthere is no client with this Account Number to delete !!\n";
	else {
		char ans;
		DisplayVectorOnScreen(SplitStringToVector(clients[ClientPos], " () "));
		cout << "\n are you sure you want to delete ? (y,n) :";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			clients.at(ClientPos).clear();
			SaveVecToFile(clients, "clients.txt");
		cout << "\n Client has been deleted successfully :') \n";
		}
	}

}
void UpdateClient() {
	system("cls");
	cout << "----------------------------------------\n";
	cout << "	  Update Client Screen \n";
	cout << "----------------------------------------\n";
	int ClientPos;
	vector <string> clients;
	StClientInfo person = UpdateStructOfPerson(clients, ClientPos);
	if (ClientPos != -1){
		clients[ClientPos] = ConvertVectorToString(ConvertStructToVector(person), " () ");
		SaveVecToFile(clients, "clients.txt");
		cout << "\n Client Data has been Updated Successifully :') \n";
		cout << "\n\n the new client data : \n\n";
		DisplayVectorOnScreen(SplitStringToVector(clients[ClientPos], " () "));
	}
}
void FindClient() {
	system("cls");
	cout << "----------------------------------------\n";
	cout << "	  Find Client Screen \n";
	cout << "----------------------------------------\n";
	vector <string> clients = SaveFileContentToVec("clients.txt");
	string Accountnumber;
	cout << "Enter Account Number : ";
	cin >> Accountnumber;
	if (clients.size() == 0 || !ClientExist(Accountnumber)) cout << "\nit is not found !!";
	else {
		int ClientPos = FindClientAccountNumber(Accountnumber);
		DisplayVectorOnScreen(SplitStringToVector(clients[ClientPos], " () "));
	}
}
void ResetClients() {
	fstream file;
	system("cls");
	cout << "----------------------------------------\n";
	cout << "	  Reset Client Screen \n";
	cout << "----------------------------------------\n";
	char ans;
	cout << "Are you Sure ?? (y,n) ";
	cin >> ans;
	if(ans == 'y' || ans == 'Y') {
		file.open("clients.txt", ios::out);
		cout << "\nAll clients data has been deleted :')\n";
	}
	
}
void TranActionProgram() {
	TransMenu();
	switch (TransAns()) {
		case enTransActions::deposit:
			DepositScreenOrWithdrow(1);
			GoBackToTransMenu();
			break;
		case enTransActions::withdraw:
			DepositScreenOrWithdrow(0);
			GoBackToTransMenu();
			break;
		case enTransActions::mainmenue:
			MainProgram();
			break;
	}
}
void GoBackToMainMenu() {
	cout << "\npress any key for getting to Main Menue...";
	system("pause>0");
	MainProgram();
}
void GoBackToTransMenu() {
	cout << "\npress any key for getting to Main Menue...";
	system("pause>0");
	TranActionProgram();
}
void userList() {
	system("cls");
	vector <string> Users = SaveFileContentToVec("users.txt");
	int userssize = Users.size();
	printf("\nUsers List (%d) user(s).\n", userssize);
	cout << "------------------------------------------------------------------\n";
	cout << "| " << left << setw(20) << "User Name" << "| " << setw(10) << "Password" << "| " << setw(25) << "Permeision" << "\n";
	cout << "------------------------------------------------------------------\n\n";
	for (int i = 0; i < userssize; i++) {
		StUser User = ConvertUserStringToStruct(Users[i]);
		cout << "| " << left << setw(20) << User.name << "| " << setw(10) << User.Pass << "| " << setw(25) << User.permession << "\n";
	}
	cout << "\n----------------------------------------------------------------\n\n";

}
void AddUser() {
	system("cls");
	cout << "------------------------------\n";
	cout << "	Add User screen\n";
	cout << "------------------------------\n";
	SaveStringToFile(ConvertVectorToString(ReadUser(), " () "), "users.txt");
	cout << "\n User Added Successfully :') ";

}
void DeleteUser() {
	system("cls");
	cout << "------------------------------\n";
	cout << "	Delete User screen\n";
	cout << "------------------------------\n";
	string UserName;
	cout << "\nenter user name you want to delete : ";
	cin >> UserName;
	vector <string> users = SaveFileContentToVec("users.txt");
	int pos = FindUserName(UserName, users);
	if (pos == 0) cout << "you cant delete Admin User :( ";
	else if (pos == -1) cout << "\nthere are no users with this user name :(";
	else 
	{
		PrintUserString(users[pos]);
		char ans;
		cout << "\nare you sure to delete ? (y/n) ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			users.at(pos).clear();
			SaveVecToFile(users, "users.txt");
			cout << "\n user deleted successfully :')";
		}
	}
}
void FindUser() {
	string UserName;
	system("cls");
	cout << "------------------------------\n";
	cout << "	Find User screen\n";
	cout << "------------------------------\n\n";
	cout << "enter user name you want to find : ";
	cin >> UserName;
	vector <string> users = SaveFileContentToVec("users.txt");
	int pos = FindUserName(UserName, users);
	if (pos == -1) cout << "\nthere are no users with this user name :(";
	else{
		StUser user = ConvertUserStringToStruct(users.at(pos));
		cout << "\n---------------------------\n";
		cout << left << setw(18) << "User Name" << ": " << user.name << "\n";
		cout << left << setw(18) << "Password" << ": " << user.Pass << "\n";
		cout << left << setw(18) << "permession Level" << ": " << user.permession;
		cout << "\n---------------------------\n";
	}


}
void UpdateUser() {
	StUser user;
	string UserName;
	system("cls");
	cout << "------------------------------\n";
	cout << "	Update User screen\n";
	cout << "------------------------------\n\n";
	cout << "enter user name you want to Update : ";
	cin >> UserName;
	vector <string> users = SaveFileContentToVec("users.txt");
	int pos = FindUserName(UserName, users);
	if (pos == -1) cout << "\nthere are no users with this user name :(";
	else if (pos == 0) cout << "\nSorry you cant ubdate Admin Account :(";
	else 
	{
		PrintUserString(users[pos]);
		char Ans;
		user.name = UserName;
		cout << "\nenter Password : ";
		cin >> user.Pass;
		cout << "\nenter permesion access (for example to access first property and second type 12) : ";
		cin >> Ans;
		if (Ans == 'y' || Ans == 'Y') user.permession = "12345678";
		else {
			cout << "\nAccess to Clients List ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') user.permession += "1";
			cout << "\nAccess to Add New Client Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') user.permession += "2";
			cout << "\nAccess to Delete Client Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') user.permession += "3";
			cout << "\nAccess to Update Client Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') user.permession += "4";
			cout << "\nAccess to Find Client Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') user.permession += "5";
			cout << "\nAccess to Reset Clients Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') user.permession += "6";
			cout << "\nAccess to TransActions Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') user.permession += "7";
			cout << "\nAccess to Manage Users Screen ? (y, n) : ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y') user.permession += "8";
		}
		vector<string> User;
		User.push_back(user.name);
		User.push_back(user.Pass);
		User.push_back(user.permession);
		users[pos].clear();
		users[pos] = ConvertVectorToString(User);
		SaveVecToFile(users, "users.txt");
		cout << "Data has been Updated successfully :') \n";
	}
}
void ManageUser() {
	StUser user;
	system("cls");
	cout << "********************************************\n";
	cout << "	Manage Users screen\n";
	cout << "********************************************\n\n";
	cout << "(1) ==> Users List\n";
	cout << "(2) ==> Add new User\n";
	cout << "(3) ==> delete User\n";
	cout << "(4) ==> update User\n";
	cout << "(5) ==> find User\n";
	cout << "(6) ==> Main Menue\n";
	cout << "------------------------------";
	enManageUsers ManageUser = ReadManChoice();
	switch (ManageUser) {
		case enManageUsers::UserList:
			userList();
			break;
		case enManageUsers::MainMenue:
			MainProgram();
			break;
		case enManageUsers::Adduser:
			AddUser();
			break;
		case enManageUsers::deleteuser:
			DeleteUser();
			break;
		case enManageUsers::finduser:
			FindUser();
			break;
		case enManageUsers::updateuser:
			UpdateUser();
			break;
	}
	cout << "\n\npress any key to go back to Manage users screen... ";
	system("pause>0");
}
void MainProgram() {
	vector <string> Nowuser = SplitStringToVector(SaveFileContentToString("nowuser.txt"));
	StClientInfo person;
	fstream file;
	DisplayMainScreen();
	switch(ReadChoiceFromUser()) {
		case enMainChoice::ShowClientLIst:
		if(IsAllowed(Nowuser, '1')) {
			ShowClientList();
		}
		else  NotAllowed();
			GoBackToMainMenu();
			break;
		case enMainChoice::adddNewClient:
			if (IsAllowed(Nowuser, '2')) {
				AddNewClient(person);
			}
			else  NotAllowed();
				GoBackToMainMenu();
			break;
		case enMainChoice::resetClients:
			if (IsAllowed(Nowuser, '6')) {
				ResetClients();
			}
			else NotAllowed();
				GoBackToMainMenu();
			break;
		case enMainChoice::deleteClient:
			if (IsAllowed(Nowuser, '3')) {
				DeleteClient();
			}
			else  NotAllowed();
				GoBackToMainMenu();
			break;
		case enMainChoice::updateClient:
			if (IsAllowed(Nowuser, '4')) {
				UpdateClient();
			}
			else  NotAllowed();
				GoBackToMainMenu();
			break;
		case enMainChoice::findClient:
			if (IsAllowed(Nowuser, '5')) {
				FindClient();
			}
			else  NotAllowed();	
				GoBackToMainMenu();
			break;
		case enMainChoice::LogOut:
			Process();
			break;
		case enMainChoice::TransActions:
			if (IsAllowed(Nowuser, '7')) {
				while (1) {
					TranActionProgram();
				}
			}
			else {
			  NotAllowed();
			  GoBackToMainMenu();
			}
			break;
		case enMainChoice::MangeUsers:
			if (IsAllowed(Nowuser, '8')) {
				while (1) {
					ManageUser();
				}
			}
			else {
				NotAllowed();
				GoBackToMainMenu();
			}
			break;
		case enMainChoice::Quit:
			exit(0);		
	}
}
void NowUser() {
	fstream file;
	file.open("nowuser.txt", ios::out);
	vector <string>NUser;
	StNowUser Nowuser = LogInScreen();
	NUser.push_back(Nowuser.name);
	NUser.push_back(Nowuser.Pass);
	NUser.push_back(Nowuser.permession);
	SaveStringToFile(ConvertVectorToString(NUser), "nowuser.txt");

}
void Process() {
	NowUser();
	while (true) {
		MainProgram();
	}
}
int main() {
	Process();
	return 0;
}