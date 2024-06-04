#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
# include <iomanip>
#include <ctime>
using namespace std;

struct Vehicle {
  string title;
  double price;
  string registration_date;
  int mileage;
  string fuel_type;
  string transmission;
  float engine_size;
  int number_of_doors;
  string color;
  string body_type;
  string URL;
  string sale_date;
  int car_number;
  bool isBooked;
};

struct Invoice {
    int invoice_number;
    int vehicle_reference_number;
    string description;
    string invoice_date;
    double sale_price;
    double discount;
    string client_name;
    string identity_number;
    float deposit_amount;
};

struct Client {
    int client_number;
    string name;
    string identity_number;
};


const string USERNAME = "salesperson";
const string PASSWORD = "password";
const string USERNAME_M = "manager";
const string PASSWORD_M = "password";



vector<Vehicle> readVehiclesFromFile(const string& file_name) {
  int number = 1;
  vector<Vehicle> vehicles;
  ifstream file(file_name);
  string line;

  // Skip the first line
  getline(file, line);

   while (getline(file, line)) {
    vector<string> fields;
    string field;
    istringstream iss(line);
    while (getline(iss, field, ',')) {
      fields.push_back(field);
    }

    Vehicle vehicle;
    vehicle.isBooked = false;
    vehicle.car_number = number;
    vehicle.title = fields[0];
    string price_str = fields[1];
    price_str = price_str.substr(2);
    vehicle.price = std::stof(price_str);
    vehicle.registration_date = fields[2];
    vehicle.mileage = std::stoi(fields[3]);
    vehicle.fuel_type = fields[4];
    vehicle.transmission = fields[5];
    vehicle.engine_size = std::stof(fields[6]);
    vehicle.number_of_doors = std::stoi(fields[7]);
    vehicle.color = fields[8];
    vehicle.body_type = fields[9];
    vehicle.URL = fields[10];
    vehicle.sale_date = fields[11];
    vehicles.push_back(vehicle);
    number++;

}
   return vehicles;
}

void searchVehicles(vector<Vehicle> &vehicles) {

    string bodyType;
    int numDoors;
    cout << "Enter the body type to search for: ";
    cin >> bodyType;
    cin.ignore();
    cout << "Enter the number of doors: ";
    cin >> numDoors;
    cin.ignore();

    cout << "Search results:" << endl;
    cout << left <<setw(20)<<"Car number"<< setw(109) << "Title" << setw(20) << "Price" << setw(10) << "Doors" << "Body Type" << endl;

    bool found = false;
    for (const auto &v : vehicles) {
        if (v.body_type == bodyType && v.number_of_doors == numDoors) {
            found = true;
            cout << left <<setw(20)<<v.car_number<< setw(109) << v.title << setw(20) << v.price << setw(10) << v.number_of_doors << v.body_type << endl;
        }
    }



    if (!found) {
        cout << "No cars matches the search criteria." << endl;
    }
}

vector<Invoice> createInvoice(vector<Invoice> &invoices,vector<Vehicle> &vehicles,float depositAmount) {

    int invoice_number;
    int vehicle_reference_number;
    string description;
    string invoice_date;
    double sale_price;
    double discount;
    string client_name;
    string identity_number;

    cout << "Enter invoice number: ";
    cin >> invoice_number;
    cin.ignore();
    cout << "Enter vehicle reference number: ";
    cin >> vehicle_reference_number;
    cin.ignore();

    for (int i = 0;i<vehicles.size();i++){
        if (vehicles[i].car_number == vehicle_reference_number){
            description = vehicles[i].title;
            sale_price = vehicles[i].price;
        }
    }

    cout << "Enter invoice date: ";
    getline(cin, invoice_date);
    cout << "Enter discount: ";
    cin >> discount;
    cin.ignore();
    cout << "Enter client name: ";
    getline(cin, client_name);
    cout << "Enter identity number: ";
    getline(cin, identity_number);

    sale_price = sale_price - ((discount/100)*sale_price);
    Invoice invoice;
    invoice.deposit_amount = depositAmount;
    invoice.invoice_number = invoice_number;
    invoice.vehicle_reference_number = vehicle_reference_number;
    invoice.description = description;
    invoice.invoice_date = invoice_date;
    invoice.sale_price = sale_price;
    invoice.discount = discount;
    invoice.client_name = client_name;
    invoice.identity_number = identity_number;

    invoices.push_back(invoice);

    return invoices;
}

void createBillReceipt(vector<Vehicle> &vehicles,vector<Invoice> &invoices,int invoiceNumber) {
    Invoice selectedInvoice;
    Vehicle selectedVehicle;
    time_t now = time(0);
     char* dt = ctime(&now);

    for (int i = 0;i<invoices.size();i++){
        if (invoices[i].invoice_number == invoiceNumber){
            selectedInvoice = invoices[i];
        }
        else{
            cout<<"Invoice not found"<<endl;
        }
    }

    for (int i = 0;i<vehicles.size();i++){
        if (vehicles[i].car_number == selectedInvoice.vehicle_reference_number){
            selectedVehicle = vehicles[i];
        }
    }
    cout << "---------------------------------------" << endl;
    cout << "           BILL RECEIPT                " << endl;
    cout << "---------------------------------------" << endl;
    cout << "Invoice Number: " << selectedInvoice.invoice_number << endl;
    cout << "Vehicle Reference Number: " << selectedInvoice.vehicle_reference_number << endl;
    cout << "Description: " << selectedVehicle.title << endl;
    cout << "Invoice Date: " << dt << endl;
    cout << "Price: " << selectedInvoice.sale_price << endl;
    cout << "Discount: " << selectedInvoice.discount << endl;
    cout << "Client Name: " << selectedInvoice.client_name << endl;
    cout << "Identity Number: " << selectedInvoice.identity_number << endl;
    cout << "Deposit Amount: " << selectedInvoice.deposit_amount << endl;
    cout << "Balance Due: " << selectedInvoice.sale_price - selectedInvoice.deposit_amount << endl;
    cout << "---------------------------------------" << endl;
    cout << "Thank you for your business!" << endl;
    cout << "---------------------------------------" << endl;
}

void bookVehicle(vector<Vehicle> &vehicles) {
    int vehicle_reference_number;
    cout << "Enter vehicle reference number: ";
    cin >> vehicle_reference_number;
    cin.ignore();

    for (int i = 0;i<vehicles.size();i++){
        if (vehicles[i].car_number == vehicle_reference_number){
            if (vehicles[i].isBooked == false){
                vehicles[i].isBooked = true;
                cout << "Vehicle with reference number " << vehicle_reference_number << " has been booked." << endl;
            } else {
                cout << "Vehicle with reference number " << vehicle_reference_number << " is already booked." << endl;
            }
        }
    }
}

vector <Client> getClients(vector<Invoice> &invoices){
    vector <Client> clients;
    for (int i = 0;i<invoices.size();i++){
        Client client;
        client.client_number = i;
        client.identity_number = invoices[i].identity_number;
        client.name = invoices[i].client_name;
        clients.push_back(client);
    }

    return clients;

}

void updateClient(vector<Client> &clients, int clientNumber) {
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i].client_number == clientNumber) {
            cout << "Enter new client name: ";
            getline(cin, clients[i].name);
            cout << "Enter new identity number: ";
            getline(cin, clients[i].identity_number);
            cout << "Client information updated successfully!" << endl;
            return;
        }
    }
    cout << "Client not found" << endl;
}

void viewClient(vector<Client> &clients) {
    for (int i = 0; i < clients.size(); i++) {
            cout << "Client Number: " << clients[i].client_number << endl;
            cout << "Client Name: " << clients[i].name << endl;
            cout << "Identity Number: " << clients[i].identity_number << endl;


    }
}

bool compareByDate(const Invoice &a, const Invoice &b) {
  return a.invoice_date < b.invoice_date;
}

void generateReport(vector<Invoice> Invoices, string startDate, string endDate) {
  sort(Invoices.begin(), Invoices.end(), compareByDate);

  double totalAmount = 0.0;
  int count = 0;

  for (const auto &invoice : Invoices) {
    if (invoice.invoice_date >= startDate && invoice.invoice_date <= endDate) {
      totalAmount += invoice.sale_price;
      count++;
    }
  }

  cout << "Number of invoices: " << count <<endl;
  cout << "Total amount: $" << totalAmount <<endl;
}

void printReportForClient(vector <Invoice> Invoices ,vector <Client> clients,string name) {
    Client selectedClient;
    for (int i = 0;i<clients.size();i++){
        if (clients[i].name == name){
            selectedClient = clients[i];
        }
    }
  cout << "Report for client " << selectedClient.name << ":" << std::endl;

  double totalAmount = 0.0;
  for (const auto &invoice : Invoices) {
    if (invoice.client_name == selectedClient.name) {
      cout << invoice.invoice_date << " " << invoice.description << " " << invoice.sale_price << std::endl;
      totalAmount += invoice.sale_price;
    }
  }

  std::cout << "Total amount: " << totalAmount << std::endl;
}

void managerMenu(vector<Vehicle> &vehicles,vector<Invoice> &Invoices,vector <Client> clients){
    float depositNumber;
    int command;
    int invoiceNumber;
    int choice;
    int client_no;
    string name;
    string start_date;
    string end_date;
    cout<<"Enter 1 if you like to search a vehicles:"<<endl;
    cout<<"Enter 2 if you like to create an invoice:"<<endl;
    cout<<"Enter 3 if you like to print bill receipt:"<<endl;
    cout<<"Enter 4 if you would like to generate report by date range:"<<endl;
    cout<<"Enter 5 if you would like to print report for a customer:"<<endl;
    cout<<"Enter 6 if you would like to quit :"<<endl;

    cout<<"Enter your choice:";
    cin>>command;
    cin.ignore();

    while (command != 6){
        if (command == 1){
            searchVehicles(vehicles);
    }
        else if (command == 2){
            cout<<"Please enter the amount deposited by the client:";
            cin>>depositNumber;
            cout<<endl;
            Invoices = createInvoice(Invoices,vehicles,depositNumber);
        }
        else if (command == 3){
            cout<<"Please enter the invoice number: ";
            cin>>invoiceNumber;
            cout<<endl;
            createBillReceipt(vehicles,Invoices,invoiceNumber);
        }

        else if (command == 4){
            cout<<"Please enter start date:";
            cin>>start_date;
            cin.ignore();
            cout<<"Please enter end date:";
            cin>>end_date;
            cin.ignore();
            generateReport(Invoices,start_date,end_date);
        }

        else if (command == 5){
            cout<<"Please enter the name of the client that you wish to generate a report for:";
            getline(cin,name);
            printReportForClient(Invoices,clients,name);
        }
        else{
            cout<<"Invalid Input. Please try again";
            cin>>command;
        }


    cout<<"Enter 1 if you like to search a vehicles:"<<endl;
    cout<<"Enter 2 if you like to create an invoice:"<<endl;
    cout<<"Enter 3 if you like to print bill receipt:"<<endl;
    cout<<"Enter 4 if you would like to generate report by date range:"<<endl;
    cout<<"Enter 5 if you would like to print report for a customer:"<<endl;
    cout<<"Enter 6 if you would like to quit :"<<endl;

    cout<<"Enter your choice:";
    cin>>command;
}



}


void salespersonMenu(vector<Vehicle> &vehicles,vector<Invoice> &Invoices,vector <Client> clients){
    float depositNumber;
    int command;
    int invoiceNumber;
    int choice;
    int client_no;
    cout<<"Enter 1 if you like to search a vehicles:"<<endl;
    cout<<"Enter 2 if you like to create an invoice:"<<endl;
    cout<<"Enter 3 if you like to print bill receipt:"<<endl;
    cout<<"Enter 4 if you would like to book a car:"<<endl;
    cout<<"Enter 5 if you would like to manage clients :"<<endl;
    cout<<"Enter 6 if you would like to quit :"<<endl;

    cout<<"Enter your choice:";
    cin>>command;
    cin.ignore();

    while (command != 6){
        if (command == 1){
            searchVehicles(vehicles);
    }
        else if (command == 2){
            cout<<"Please enter the amount deposited by the client:";
            cin>>depositNumber;
            cout<<endl;
            Invoices = createInvoice(Invoices,vehicles,depositNumber);
        }
        else if (command == 3){
            cout<<"Please enter the invoice number: ";
            cin>>invoiceNumber;
            cout<<endl;
            createBillReceipt(vehicles,Invoices,invoiceNumber);
        }

        else if (command == 4){
            bookVehicle(vehicles);
        }

        else if (command == 5){
            clients = getClients(Invoices);
            cout<<"Enter 1 if you would like to view all client"<<endl;
            cout<<"Enter 2 if you would like to update the client information"<<endl;
            cout<<"Enter 3 to quit"<<endl;
            cout<<"Enter your choice:";
            cin>>choice;

            while (choice != 3){
                if (choice == 1){
                    viewClient(clients);

                }
                else if (choice == 2){
                    cout<<"Please enter the client number that you wish to update:";
                    cin>>client_no;
                    cin.ignore();
                    updateClient(clients,client_no);
                }

                else{
                    cout<<"Invalid response. Please try again";
                    cin>>choice;
                }

            cout<<"Enter 1 if you would like to view all client"<<endl;
            cout<<"Enter 2 if you would like to update the client information"<<endl;
            cout<<"Enter 3 to quit"<<endl;
            cout<<"Enter your choice:";
            cin>>choice;
        }


        }
        else{
            cout<<"Invalid Input. Please try again";
            cin>>command;
        }


    cout<<"Enter 1 if you like to search a vehicles:"<<endl;
    cout<<"Enter 2 if you like to create an invoice:"<<endl;
    cout<<"Enter 3 if you like to print bill receipt:"<<endl;
    cout<<"Enter 4 if you would like to book a car:"<<endl;
    cout<<"Enter 5 if you would like to manage clients :"<<endl;
    cout<<"Enter 6 if you would like to quit :"<<endl;

    cout<<"Enter your choice:";
    cin>>command;
}



}

int main() {
   int choice;
   int command;
   string username;
   string password;
   string manager_username;
   string manager_password;
   vector<Vehicle> vehicles = readVehiclesFromFile("carlist.csv");
   vector<Invoice> invoices;
   vector <Client> clients;


   while (true){

    cout<<"Enter 1 if you want if you are a salesperson"<<endl;
    cout<<"Enter 2 if you are a manager"<<endl;
    cout<<"Enter 3 to quit"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;
    cin.ignore();
    if (choice == 1){
        cout<<"Please login by entering your username and password:"<<endl;
        cout<<"Enter your username:";
        cin>>username;
        cin.ignore();
        cout<<"Enter your password:";
        cin>>password;
        cin.ignore();

        if (username == USERNAME && password == PASSWORD){

            cout<<"Welcome"<<endl;
            salespersonMenu()
        }
    }

    else if (choice == 2){
        cout<<"Please login by entering your username and password:"<<endl;
        cout<<"Enter your username:";
        cin>>manager_username;
        cin.ignore();
        cout<<"Enter your password:";
        cin>>manager_password;
        cin.ignore();

        if (username == USERNAME_M && password == PASSWORD_M){

            cout<<"Welcome"<<endl;
            managerMenu();
        }
    }
}


  return 0;
}
