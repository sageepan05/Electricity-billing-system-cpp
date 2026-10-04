/*
   C++ code for automated electricity meter reading entries and billing procedures
*/


#include <iostream>     //Library for input output operations
#include <string>       //Library for string class and manipulation function
#include <ctime>        //Library for time
#include <vector>       //Library for creating dynamic array - Vector
#include <limits>       //Library for error handling due to buffers
using namespace std; 

/*Define structure for store user information*/
struct user
{
	string name;
	string username;
	string password;
	string role;
};   

/*Create a structure/template for the data type - meterreading*/
struct meterreading
{
	string customerID;
	string readingdate;
	long double previousreading;
	long double currentreading;
	long double unitsused; 
	long double amountdue;
	long double amountforunitsused;
	long double totalamounttopay;
};   

/*Declaration of global variables*/
vector <user> Users;                    //Create vector to store all users
user current_user;                      //Create object of type user for currently logged in user 
vector <meterreading> Meter_Readings;   //Create vector to store all meter reading data
meterreading readingentryofcustomer;    //Create object - new reading of type meter reading

const double RATE_PER_UNIT = 12.75;     //Fixed rate for one unit

/* Function prototype declaration - To avoid interuption in function calling order */
void display_Startup_Message();
bool login();
void display_Main_Menu();
void meter_Reading_Entry();
void view_Billing_Summary();
void energy_Saving_Tips();
void logout();
void initialize_Users();
void initialize_Meter_Readings();
void display_Date_Time();
void yes_or_no();
void press_Enter_to_continue();

int main()
{
	initialize_Users();          //To load predefined users into the system
    display_Startup_Message();   //To show startup message
    
  	if (login())                 //If login success
	{
        cout<<"Sucessfully logged in..."<<endl;
        cout<<"Welcome! " <<current_user.name <<" (" <<current_user.role <<")" <<endl;
        cout<<"==================================================" << endl;
        cout<<endl;
        press_Enter_to_continue();
        
        system("cls");
        initialize_Meter_Readings();   //To load predefined(stored) meter reading data into the system
        display_Main_Menu();           //To show main menu
	}	
}

/* Function to display startup message */
void display_Startup_Message() 
{
    system("cls");
    cout<<"==================================================" <<endl;
    cout<<"               CEYLON POWER COMPANY               " <<endl;
    cout<<"==================================================" <<endl;
    cout<<"             CPCCPC   CPCPCPC   CPCCPC            " <<endl;
    cout<<"             C        C     P   P                 " <<endl;
    cout<<"             P      * CPCPCPC * C                 " <<endl;
    cout<<"             C        C         P                 " <<endl;
    cout<<"             CPCCPC   C         CPCCPC            " <<endl;  
    cout<<"            #Reliable Energy Solutions#           " <<endl;
    cout<<"--------------------------------------------------" <<endl;
    cout<<"                Colombo Main Branch               " <<endl;
    cout<<"--------------------------------------------------" <<endl;
	display_Date_Time();                                                 //To show time 
    cout<<"==================================================" <<endl;
    cout<<"Initializing System... Please wait..." <<endl;
    press_Enter_to_continue();                                           //Press enter to continue further  
}

/* Function for login */
bool login() 
{
	int attempt = 0;
	int max_attempt = 3;
	
	while (attempt < max_attempt)   //For max. no.of attempts 3
	{
		system("cls");
    	cout<<"==================================================" << endl;
    	cout<<"                  LOGIN PORTAL                    " << endl;
		cout<<"==================================================" << endl;
		
		string username, password;
		
		cout<<"Username: ";
    	cin>>username;                              //Get username from user 
    	cout<<"Password: ";
    	cin>>password;                              //Get password from user
    	
		bool login_success = false;                 //Initial login status
    
		for (size_t u = 0; u < Users.size(); u++)   //Check each users one by one in users vector
		{
        	if (Users[u].username == username && Users[u].password == password)   //Compare username and password with stored value
			{
                current_user = Users[u];            //Assign current user if match found
                login_success = true;               //Set login status as successful
                break;                              //Exit loop
        	}
		}
		
		if (login_success) 
		{
            return true;   //Return login as success to calling function
        }
		
		attempt++;         //Increment attempt by one if login fail
		cout<<"--------------------------------------------------" << endl;
		cout<<"Incorrect username/password..." <<endl;
		cout<<"Attempts remaining: " <<max_attempt - attempt <<endl;
		
		if (attempt < max_attempt)
		{		
			cout<<endl;                  //To get a full line spacing
			press_Enter_to_continue();	 //Press enter for next login attempt	
		}
	}
	cout<<"==================================================" <<endl;   //To display information after all login attempts failed
	cout<<"Maximum login attempts exceeded. System exiting..." <<endl;
	cout<<"Please contact IT Services for assistance..." <<endl;
	cout<<"==================================================" <<endl;
    return false;   ////Return login as fail to calling function
}

/* Function for main menu */
void display_Main_Menu()
{
    cout<<"=================================================" <<endl;
    cout<<"                    MAIN MENU                    " <<endl;
    cout<<"=================================================" <<endl;
    cout<<"Logged in as: " <<current_user.name <<" (" <<current_user.role <<")" <<endl;   //To show details of current logged in user
    cout<<"-------------------------------------------------" <<endl;
    cout<<"1. Meter Reading Entry" <<endl;                                                //Option to enter meter reading entry
    cout<<"2. View Billing Summary" <<endl;                                               //Option to view billing details of customer
    cout<<"3. Energy Savings Tips" <<endl;                                                //Option to view energy saving tips
    cout<<"4. Log Out" <<endl;                                                            //Option to exit the system
    cout<<"-------------------------------------------------" <<endl;
    
    int choice;
        start:
        cout<<endl;
        cout<<"Enter your choice (1-4): ";
        cin>>choice;
        
        switch (choice) 
		{
            case 1:
                meter_Reading_Entry();
                break;
            case 2:
                view_Billing_Summary();
                break;
            case 3:
                energy_Saving_Tips();
                break;
            case 4:
                logout();
                break;
            default:
                cout<<"Invalid choice! Please try again." <<endl;   //For invalid choice entered
                goto start;                                         //Go to enter choice again
        }
}

/* Function for meter reading entry */
void meter_Reading_Entry()
{
	system("cls");
	cout<<"===================================================" <<endl;
    cout<<"               METER READING ENTRY                 " <<endl;
    cout<<"===================================================" <<endl;
    
    long double amountdue = 0;
    long double totalamounttopay =0;   
    bool customerIDfound = false;       //To check customer id found in meter reading vector
    size_t customerindex = 0;           //Index to locate customer in meter reading vector
    
    cout<<"Enter Customer ID: ";
    cin>>readingentryofcustomer.customerID;          //Get customer ID
    
    cout<<"Enter Date of Reading (YYYY-MM-DD): ";
    cin>>readingentryofcustomer.readingdate;         //Get current meter reading date
     
    cout<<"Enter Previous Meter Reading: ";
    cin>>readingentryofcustomer.previousreading;     //Get previous meter reading value
    
    cout<<"Enter Current Meter Reading: ";
    cin>>readingentryofcustomer.currentreading;      //Get new meter reading value
    
    for (size_t r = 0; r < Meter_Readings.size(); r++)   //Search for existing customer
    {
        if (Meter_Readings[r].customerID == readingentryofcustomer.customerID)   //If customer exist
        {
        	amountdue = Meter_Readings[r].amountdue;                             //Get previous stored due amount
        	totalamounttopay = 	Meter_Readings[r].totalamounttopay;              //Get previous stored total amount to pay
            customerIDfound = true;                                              //Mark customer exist status as success
            customerindex = r;                                                   //Assign location of customer in vector
            break;
        }
    }
    
    readingentryofcustomer.amountdue = amountdue + totalamounttopay;                                                            //Update new amount due
    readingentryofcustomer.readingdate = readingentryofcustomer.readingdate ;                                                   //Update new meter reading date
    readingentryofcustomer.unitsused = readingentryofcustomer.currentreading - readingentryofcustomer.previousreading;          //Calculate units used
    readingentryofcustomer.amountforunitsused = readingentryofcustomer.unitsused * RATE_PER_UNIT;                               //Calculate cost for unitsused
    readingentryofcustomer.totalamounttopay = readingentryofcustomer.amountdue + readingentryofcustomer.amountforunitsused;     //Calculate total amount to pay
    
    if (customerIDfound)
    {
    	Meter_Readings[customerindex] = readingentryofcustomer;     //Store updated meter reading data to existing customer in vector
    }
    else   //If customer not exist in vector - a new customer
    {
    	cout<<"---------------------------------------------------" <<endl;
    	cout<<"New customer detected..." <<endl;
    	Meter_Readings.push_back(readingentryofcustomer);    //Add new customer reading records to vector
	}
    
    cout<<"---------------------------------------------------" <<endl;
    cout<<"Reading Successfully Recorded..." <<endl;
    cout<<"===================================================" <<endl;
    cout<<endl;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   //Avoid errors due to buffer
    yes_or_no();                                           //Yes for return to main menu and no for logout
}

void view_Billing_Summary()
{
	system("cls");
    cout<<"===================================================" <<endl;
    cout<<"               BILLING SUMMARY                     " <<endl;
    cout<<"===================================================" <<endl;
    
    string customerID;
    start:
    cout<<"Enter Customer ID: ";
    cin>>customerID;               //Get customer ID
    
    bool customerIDfound = false;  //Initial customer ID existing status is false
    
    for (size_t r = 0; r < Meter_Readings.size(); r++)     //Check customer ID in meter reading vector
    {
        if (Meter_Readings[r].customerID == customerID)    //IF customer ID matches with stores data in meter reading vector
        {
        	readingentryofcustomer = Meter_Readings[r];    //Get stored data 
            customerIDfound = true;                        //Assign customer ID found status as success
            break;
        }
    }
    
    if (customerIDfound)   //If customer ID found display below data
    {
    	
    	cout<<endl <<"Customer ID: " <<readingentryofcustomer.customerID <<endl;
        cout<<"Last Reading Date: " <<readingentryofcustomer.readingdate <<endl;
        cout<<"Units Used according to last reading: " <<readingentryofcustomer.unitsused <<" units" <<endl;
        cout<<"Amount for Units Used: Rs. " <<readingentryofcustomer.amountforunitsused <<endl;
        cout<<"Amount Due: Rs. " <<readingentryofcustomer.amountdue <<endl;
        cout<<"Amount to Pay: Rs. " <<readingentryofcustomer.totalamounttopay <<endl;
       
    }
    else    //If customer ID not found
    {
    	cout<<endl;
        cout<<"No record found for Customer ID: " << customerID << endl;
        cout<<"Please check the Customer ID and try again." << endl;
        cout<<"===================================================" <<endl;
    	cout<<endl;
        goto start;   //Agin ask to input correct Customer ID
    }
    
    cout<<"===================================================" <<endl;
    cout<<endl;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   //Avoid errors due to buffer
    yes_or_no();                                          //Yes for return to main menu and no for logout
}

/* Function for energy saving tips */
void energy_Saving_Tips()    //Display enegy saving tips
{
    system("cls");
    cout<<"===================================================" <<endl;
    cout<<"                ENERGY SAVINGS TIPS                " <<endl;
    cout<<"===================================================" <<endl;
        
    cout<<"1. LIGHTING TIPS" <<endl;
    cout<<"   - Switch to LED bulbs." <<endl;
    cout<<"   - Install motion sensors or timers in lighting." <<endl;
    cout<<endl;
    
    cout<<"2. REFRIGERATOR TIPS" <<endl;
    cout<<"   - Set temperture limit as 3-5 degree Celsius." <<endl;
    cout<<"   - Defrost regularly to improve efficiency." <<endl;
    cout<<endl;
    
    cout<<"3. AC USAGE TIPS" <<endl;
    cout<<"   - Set temperature limit as 24-26 degree Celsius." <<endl;
    cout<<"   - Clean air filters regularly." <<endl;
    cout<<endl;

    cout<<"4. WATER HEATING TIPS" <<endl;
    cout<<"   - Set water heater to 60 degree Celsius." <<endl;
    cout<<"   - Insulate hot water pipes." <<endl;
    cout<<endl;
    
    cout<<"5. APPLIANCES AND ELECTRONICS USAGE TIPS" <<endl;
    cout<<"   - Look for 5-star energy rating." <<endl;
    cout<<"   - Unplug chargers and devices when not in use." <<endl;
    cout<<endl;
    
    cout<<"6. LONG TERM SAVINGS TIPS" <<endl;
    cout<<"   - Switch to solar panels." <<endl;
    cout<<"   - Use inverter type A/C and refrigerators." <<endl;
    
    cout<<"===================================================" <<endl;
    cout<<endl;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   //Avoid errors due to buffer
    yes_or_no();                                           //Yes for return to main menu and no for logout
}

/* Function for logout */
void logout() 
{
    system("cls");
    cout<<"=============================================================" <<endl;
    cout<<"                            LOGOUT                           " <<endl;
    cout<<"=============================================================" <<endl;
    cout<<"User: " <<current_user.name <<" (" <<current_user.role <<")" <<" has been logged out." <<endl;   //Loggedout user details
    cout<<"Session ended... " <<endl; 
	display_Date_Time();                                                                                    //Logged out time
	cout<<"=============================================================" <<endl;
}

/* Function for initialize user vector data */
void initialize_Users() 
{
    user u1;                          //u1 - Name of object of vector
    u1.name = "Jeyakumar Sageepan";   //name,username,password,role - Properties of object
    u1.username = "Admin";
    u1.password = "Admin123";
    u1.role = "Administrator";
    Users.push_back(u1);              //u1 stores in user vector
    
    user u2;
    u2.name = "Frank Abagnale";
    u2.username = "FrankA"; 
    u2.password = "CPC@#123";
    u2.role = "Meter Reader";
    Users.push_back(u2);
    
    user u3;
    u3.name = "Roger Strong";
    u3.username = "RogerS";
    u3.password = "RS#$678";
    u3.role = "Cashier";
    Users.push_back(u3);
    
    user u4;
    u4.name = "Paul Morgan";
    u4.username = "Morgan";
    u4.password = "Paul268";
    u4.role = "Manager";
    Users.push_back(u4);
}

/* Function for initialize meter readings vector data */
void initialize_Meter_Readings()
{
    meterreading r1;                  //r1 - Name of object of vector
    r1.customerID = "CUST001";        //customerID,readingdate,previousreading,currentreading-Properties of object
    r1.readingdate = "2025-10-01";    //amountdue,unitsused,amountforunitsused,totalamounttopay-Properties of object
    r1.previousreading = 1345.5;
    r1.currentreading = 1550.5;
    r1.unitsused = 205.0;
    r1.amountdue = 554.65;
    r1.amountforunitsused = 2613.75;
	r1.totalamounttopay = 3168.4;
    Meter_Readings.push_back(r1);     //r1 stores in meter reading vector 
    
    meterreading r2;
    r2.customerID = "CUST002";
    r2.readingdate = "2025-10-01";
    r2.previousreading = 890.2;
    r2.currentreading = 1020.5;
    r2.unitsused = 130.3;
    r2.amountdue = 219.65;
    r2.amountforunitsused = 1661.325;
	r2.totalamounttopay = 1880.975;
    Meter_Readings.push_back(r2);
    
    meterreading r3;
    r3.customerID = "CUST003";
    r3.readingdate = "2025-10-01";
    r3.previousreading = 300.2;
    r3.currentreading = 476.5;
    r3.unitsused = 176.3;
    r3.amountdue = 1290.65;
    r3.amountforunitsused = 2247.825;
	r3.totalamounttopay = 3538.475;
    Meter_Readings.push_back(r3);
}

/* Function to display time | week | date */
void display_Date_Time() 
{
    time_t now = time(0);   //Get current time in seconds         
    tm *timeinfo = localtime(&now);   //Convert into readable structure
    
    const string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};              //Array for days
    
    cout<<"Time: "<<timeinfo->tm_hour<< ":" <<timeinfo->tm_min << ":" << timeinfo->tm_sec;                             //Set time format
	cout<<" | Day: " <<days[timeinfo->tm_wday];                                                                        //Week
    cout<<" | Date: " <<timeinfo->tm_mday <<"/" <<(timeinfo->tm_mon + 1) <<"/" <<(timeinfo->tm_year + 1900) << endl;   //Set date format
}

/* Function for asking yes or no from user */
void yes_or_no() 
{
    char option;
    cout << "Return to Main Menu? (Y/N): ";
    cin >> option;                                         //Get in option
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   //Avoid errors due to buffer
    
    if (option == 'Y' || option == 'y')                    //If option is yes return to mainmenu
    {
        system("cls");
        display_Main_Menu();
    }
    else if (option == 'N' || option == 'n')               //If option is no logout the system
    {
        system("cls");
        logout();
    }
    else 
    {
    	system("cls");
        cout << "Invalid input! Please enter Y or N." << endl;     //If invalid optiom
        yes_or_no();                                               //Again ask to get correct option
    }
}

/* Function to continue program by press enter */
void press_Enter_to_continue()
{
    cout<<"Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   //Avoid errors due to buffer
    cin.get();                                             //Receive enter key entered by user
}
