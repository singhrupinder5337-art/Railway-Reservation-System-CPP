#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>  // Required for std::isfinite()
#include <algorithm>
#include <cstdio>

using namespace std;
struct BookingNode
{
    string bookingId;
    string passengerId;
    string trainNumber;
    string journeyDate;

    int seatNumber;
    string status;

    BookingNode* next;

    BookingNode(string id,
                string passenger,
                string train,
                string date,
                int seat,
                string bookingStatus)
    {
        bookingId = id;
        passengerId = passenger;
        trainNumber = train;
        journeyDate = date;
        seatNumber = seat;
        status = bookingStatus;

        next = nullptr;
    }
};
class BookingLinkedList
{
private:
    BookingNode* head;
    BookingNode* tail;

public:
BookingNode* findFirstWaiting(
    const string& trainNumber,
    const string& journeyDate
);

void displayPassengerBookings(const string& passengerId) const;
BookingNode* findBooking(const string& bookingId);
int countWaitingBookings(
    const string& trainNumber,
    const string& journeyDate
) const;
bool isSeatTaken(const string& trainNumber,
                 const string& journeyDate,
                 int seatNumber) const;

string generateBookingId() const;
    BookingLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void addBooking(string id,
                    string passenger,
                    string train,
                    string date,
                    int seat,
                    string status);

    void displayBookings();
    void displayStatistics() const;

    ~BookingLinkedList();

    // Prevent accidental copying of owning pointers.
    BookingLinkedList(const BookingLinkedList&) = delete;
    BookingLinkedList& operator=(const BookingLinkedList&) = delete;
};
bool BookingLinkedList::isSeatTaken(
    const string& trainNumber,
    const string& journeyDate,
    int seatNumber) const
{
    BookingNode* current = head;

    while(current != nullptr)
    {
        if(current->trainNumber == trainNumber &&
           current->journeyDate == journeyDate &&
           current->seatNumber == seatNumber &&
           current->status == "CONFIRMED")
        {
            return true;
        }

        current = current->next;
    }

    return false;
}
string BookingLinkedList::generateBookingId() const
{
    BookingNode* current = head;

    int maxId = 1000;

    while(current != nullptr)
    {
        string id = current->bookingId;

        if(id.length() > 2 && id.substr(0, 2) == "BK")
        {
            try
            {
                int number = stoi(id.substr(2));

                if(number > maxId)
                {
                    maxId = number;
                }
            }
            catch(...)
            {
                // Ignore invalid booking IDs
            }
        }

        current = current->next;
    }

    return "BK" + to_string(maxId + 1);
}
void BookingLinkedList::addBooking(
    string id,
    string passenger,
    string train,
    string date,
    int seat,
    string status)
{
    // Step 1: Create new booking node
    BookingNode* newNode = new BookingNode(
        id,
        passenger,
        train,
        date,
        seat,
        status
    );

    // Step 2: Check whether list is empty
    if(head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        // Step 3: Connect last node to new node
        tail->next = newNode;

        // Step 4: Update tail
        tail = newNode;
    }

    cout << "\nBooking inserted into Linked List!\n";
}
void BookingLinkedList::displayBookings()
{
    if(head == nullptr)
    {
        cout << "\nNo Bookings Available!\n";
        return;
    }

    BookingNode* current = head;

    cout << "\n========================================";
    cout << "\n          BOOKING LINKED LIST";
    cout << "\n========================================";

    while(current != nullptr)
    {
        cout << "\nBooking ID   : " << current->bookingId;
        cout << "\nPassenger ID : " << current->passengerId;
        cout << "\nTrain Number : " << current->trainNumber;
        cout << "\nJourney Date : " << current->journeyDate;
        if(current->status == "WAITING")
{
    cout << "\nSeat Number  : Not Allocated";
}
else
{
    cout << "\nSeat Number  : " << current->seatNumber;
}
        cout << "\nStatus       : " << current->status;

        cout << "\n----------------------------------------";

        current = current->next;
    }

    cout << "\n";
}
// ============== BOOKING STATISTICS ==============

void BookingLinkedList::displayStatistics() const
{
    int total = 0;
    int confirmed = 0;
    int waiting = 0;
    int cancelled = 0;

    BookingNode* current = head;

    // Traverse the Linked List
    while(current != nullptr)
    {
        total++;

        if(current->status == "CONFIRMED")
        {
            confirmed++;
        }
        else if(current->status == "WAITING")
        {
            waiting++;
        }
        else if(current->status == "CANCELLED")
        {
            cancelled++;
        }

        current = current->next;
    }

    cout << "\n========================================";
    cout << "\n         BOOKING STATISTICS";
    cout << "\n========================================";

    cout << "\nTotal Bookings      : " << total;
    cout << "\nConfirmed Tickets   : " << confirmed;
    cout << "\nWaiting Tickets     : " << waiting;
    cout << "\nCancelled Tickets   : " << cancelled;

    cout << "\n========================================\n";
}
BookingLinkedList::~BookingLinkedList()
{
    BookingNode* current = head;

    while(current != nullptr)
    {
        BookingNode* nextNode = current->next;

        delete current;

        current = nextNode;
    }

    head = nullptr;
    tail = nullptr;
}
// ================= ACTIVITY STACK NODE =================

struct ActivityNode
{
    string passengerId;
    string activity;

    ActivityNode* next;

    ActivityNode(string id, string message)
    {
        passengerId = id;
        activity = message;
        next = nullptr;
    }
};
// ================= ACTIVITY STACK =================

class ActivityStack
{
private:
    ActivityNode* top;

public:

    ActivityStack()
    {
        top = nullptr;
    }

    void push(string passengerId, string message);

void displayActivities(const string& passengerId) const;

    ~ActivityStack();

    // Prevent accidental copying
    ActivityStack(const ActivityStack&) = delete;
    ActivityStack& operator=(const ActivityStack&) = delete;
};
void ActivityStack::push(string passengerId, string message)
{
    // Create new activity node
    ActivityNode* newNode = new ActivityNode(
        passengerId,
        message
    );

    // Connect new node to current top
    newNode->next = top;

    // Update top pointer
    top = newNode;
}
void ActivityStack::displayActivities(
    const string& passengerId) const
{
    ActivityNode* current = top;

    int count = 0;

    cout << "\n========================================";
    cout << "\n          RECENT ACTIVITIES";
    cout << "\n========================================";

    while(current != nullptr)
    {
        // Show only the logged-in passenger's activities
        if(current->passengerId == passengerId)
        {
            count++;

            cout << "\n"
                 << count << ". "
                 << current->activity;
        }

        current = current->next;
    }

    if(count == 0)
    {
        cout << "\nNo Recent Activities Available!";
    }

    cout << "\n========================================\n";
}
ActivityStack::~ActivityStack()
{
    ActivityNode* current = top;

    while(current != nullptr)
    {
        ActivityNode* nextNode = current->next;

        delete current;

        current = nextNode;
    }

    top = nullptr;
}
class RailwaySystem
{
private:
    string name;
    string email;
    string phone;
    string password;

    string currentUserId;
    string currentUserName;
    string currentUserEmail;
    BookingLinkedList bookingList;
bool bookingsLoaded = false;
ActivityStack activityStack;
bool activitiesLoaded = false;

public:
    void mainMenu();
    void signup();
    void login();

    void passengerDashboard();
    void viewProfile();
    void changePassword();
    void forgotPassword();

    void adminLogin();
    void adminDashboard();

    // Train management
    void initializeTrains();
    void viewTrains();
    void addTrain();
    void searchTrain();
    void updateTrain();
    void removeTrain();
    bool loadBookings();
    void viewMyBookings();
    void checkSeatAvailability();
    // Booking Management

void bookTicket();
void cancelTicket();
void viewRecentActivities();

bool trainExists(const string& trainNumber);

    bool emailExists(string searchEmail);
    string generatePassengerId();

    bool validateEmail(string email);
    bool validatePassword(string password);
    bool validatePhone(string phone);
    bool loadActivities();

bool recordActivity(
    const string& passengerId,
    const string& message
);
};
bool RailwaySystem::loadBookings()
{
     cout << "\nDEBUG: loadBookings() function called!\n";

    ifstream file("bookings.txt");

    // First execution: create an empty booking file
    if(!file.is_open())
    {
        ofstream createFile("bookings.txt", ios::app);

        if(!createFile)
        {
            cout << "\nError accessing booking database!\n";
            return false;
        }

        createFile.close();

        bookingsLoaded = true;
        return true;
    }

    string line;

    while(getline(file, line))
    {
        if(line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string bookingId;
        string passengerId;
        string trainNumber;
        string journeyDate;
        string seatString;
        string status;

        if(!getline(ss, bookingId, '|') ||
           !getline(ss, passengerId, '|') ||
           !getline(ss, trainNumber, '|') ||
           !getline(ss, journeyDate, '|') ||
           !getline(ss, seatString, '|') ||
           !getline(ss, status))
        {
            cout << "\nInvalid booking record found!\n";
            return false;
        }

        int seatNumber;

        try
        {
            seatNumber = stoi(seatString);
        }
        catch(...)
        {
            cout << "\nInvalid seat number in booking file!\n";
            return false;
        }

        bookingList.addBooking(
            bookingId,
            passengerId,
            trainNumber,
            journeyDate,
            seatNumber,
            status
        );
    }

    if(file.bad())
    {
        cout << "\nError reading booking database!\n";
        return false;
    }

    bookingsLoaded = true;

    cout << "\nBooking records loaded successfully!\n";

    return true;
}
// ================= MAIN MENU =================

void RailwaySystem::mainMenu()
{
    string choice;

    while (true)
    {
        cout << "\n========================================";
        cout << "\n       RAILWAY RESERVATION SYSTEM";
        cout << "\n========================================";

        cout << "\n\n1. Passenger Login";
        cout << "\n2. Passenger Registration";
        cout << "\n3. Admin Login";
        cout << "\n4. Forgot Password";
        cout << "\n5. Exit";

        cout << "\n\n========================================";

        cout << "\nEnter your choice: ";
getline(cin, choice);

cout << "\nYou entered: " << choice << endl;

        if (choice == "1")
{
    login();
}

        else if (choice == "2")
        {
            signup();
        }

        else if (choice == "3")
        {
           adminLogin();
        }

        else if(choice == "4")
{
    forgotPassword();
}

        else if (choice == "5")
        {
            cout << "\nThank you for using our Railway System!\n";
            break;
        }

        else
        {
            cout << "\nInvalid choice! Please try again.\n";
        }
    }
}


// ================= EMAIL VALIDATION =================

bool RailwaySystem::validateEmail(string email)
{
    if (email.empty())
    {
        return false;
    }

    size_t atPosition = email.find('@');

    // Check @ symbol
    if (atPosition == string::npos || atPosition == 0)
    {
        return false;
    }

    // Prevent multiple @ symbols
    if (email.find('@', atPosition + 1) != string::npos)
    {
        return false;
    }

    // Check domain
    size_t dotPosition = email.find('.', atPosition + 1);

    if (dotPosition == string::npos ||
        dotPosition <= atPosition + 1 ||
        dotPosition == email.length() - 1)
    {
        return false;
    }

    // Reject whitespace and file separator
    for (char ch : email)
    {
        unsigned char c = static_cast<unsigned char>(ch);

        if (isspace(c) || ch == '|')
        {
            return false;
        }
    }

    return true;
}


// ================= PASSWORD VALIDATION =================

bool RailwaySystem::validatePassword(string password)
{
    if (password.length() < 8)
    {
        return false;
    }

    bool upper = false;
    bool lower = false;
    bool digit = false;
    bool special = false;

    for (char ch : password)
    {
        unsigned char c = static_cast<unsigned char>(ch);

        if (isupper(c))
        {
            upper = true;
        }

        else if (islower(c))
        {
            lower = true;
        }

        else if (isdigit(c))
        {
            digit = true;
        }

        else if (ispunct(c) && ch != '|')
        {
            special = true;
        }

        if (isspace(c) || ch == '|')
        {
            return false;
        }
    }

    return upper && lower && digit && special;
}


// ================= PHONE VALIDATION =================

bool RailwaySystem::validatePhone(string phone)
{
    if (phone.length() != 10)
    {
        return false;
    }

    for (char ch : phone)
    {
        if (!isdigit(static_cast<unsigned char>(ch)))
        {
            return false;
        }
    }

    return true;
}


// ================= CHECK DUPLICATE EMAIL =================

bool RailwaySystem::emailExists(string searchEmail)
{
    ifstream file("users.txt");

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id;
        string username;
        string useremail;

        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, useremail, '|');

        if (useremail == searchEmail)
        {
            return true;
        }
    }

    return false;
}


// ================= GENERATE PASSENGER ID =================

string RailwaySystem::generatePassengerId()
{
    ifstream file("users.txt");

    string line;

    int maxId = 1000;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id;

        getline(ss, id, '|');

        if (id.length() > 1 && id[0] == 'U')
        {
            try
            {
                int number = stoi(id.substr(1));

                if (number > maxId)
                {
                    maxId = number;
                }
            }

            catch (...)
            {
                // Ignore invalid ID
            }
        }
    }

    return "U" + to_string(maxId + 1);
}


// ================= PASSENGER SIGNUP =================

void RailwaySystem::signup()
{
    cout << "\n========================================";
    cout << "\n         PASSENGER REGISTRATION";
    cout << "\n========================================";

    // Name
    cout << "\nEnter Full Name: ";
    getline(cin, name);

    if (name.find_first_not_of(" \t") == string::npos ||
        name.find('|') != string::npos)
    {
        cout << "\nInvalid Name!\n";
        return;
    }

    // Email
    cout << "Enter Email: ";
    getline(cin, email);

    if (!validateEmail(email))
    {
        cout << "\nInvalid Email Address!";
        cout << "\nExample: rupinder@gmail.com\n";
        return;
    }

    // Duplicate email
    if (emailExists(email))
    {
        cout << "\nThis Email Is Already Registered!\n";
        return;
    }

    // Phone
    cout << "Enter Phone Number: ";
    getline(cin, phone);

    if (!validatePhone(phone))
    {
        cout << "\nInvalid Phone Number!";
        cout << "\nPhone number must contain exactly 10 digits.\n";
        return;
    }

    // Password
    cout << "Enter Password: ";
    getline(cin, password);

    if (!validatePassword(password))
    {
        cout << "\nWeak Password!";

        cout << "\nPassword must contain:";
        cout << "\n1. Minimum 8 characters";
        cout << "\n2. One uppercase letter";
        cout << "\n3. One lowercase letter";
        cout << "\n4. One number";
        cout << "\n5. One special character";
        cout << "\n6. No spaces\n";

        return;
    }

    // Confirm Password
    string confirmPassword;

    cout << "Confirm Password: ";
    getline(cin, confirmPassword);

    if (password != confirmPassword)
    {
        cout << "\nPasswords Do Not Match!\n";
        return;
    }

    // Generate ID
    string passengerId = generatePassengerId();

    // Save details
    ofstream file("users.txt", ios::app);

    if (!file.is_open())
    {
        cout << "\nError Opening File!\n";
        return;
    }

    // Prototype only: uses plaintext passwords
    file << passengerId << "|"
         << name << "|"
         << email << "|"
         << phone << "|"
         << password << "\n";

    if (!file)
    {
        cout << "\nError Saving Passenger Details!\n";
        return;
    }

    file.close();

    if (!file)
    {
        cout << "\nError Closing Passenger File!\n";
        return;
    }

    // Success
    cout << "\n========================================";
    cout << "\n       REGISTRATION SUCCESSFUL!";
    cout << "\n========================================";

    cout << "\nPassenger ID : " << passengerId;
    cout << "\nName         : " << name;
    cout << "\nEmail        : " << email;
    cout << "\nPhone        : " << phone;

    cout << "\n\nPlease Login To Continue.\n";
}
void RailwaySystem::login()
{
    string searchEmail, searchPassword;

    cout << "\n========================================";
    cout << "\n           PASSENGER LOGIN";
    cout << "\n========================================";

    cout << "\nEnter Email: ";
    getline(cin, searchEmail);

    cout << "Enter Password: ";
    getline(cin, searchPassword);

    ifstream file("users.txt");

    if(!file.is_open())
    {
        cout << "\nNo registered passengers found!\n";
        return;
    }

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string id, username, useremail;
        string userphone, userpassword;

        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, useremail, '|');
        getline(ss, userphone, '|');
        getline(ss, userpassword);

        if(searchEmail == useremail &&
           searchPassword == userpassword)
        {
            currentUserId = id;
            currentUserName = username;
            currentUserEmail = useremail;

            file.close();

            cout << "\n========================================";
            cout << "\n          LOGIN SUCCESSFUL!";
            cout << "\n========================================";

            cout << "\nWelcome, " << currentUserName << "!\n";

            passengerDashboard();

            return;
        }
    }

    cout << "\nInvalid Email or Password!\n";
}
void RailwaySystem::viewProfile()
{
    if(currentUserId.empty())
    {
        cout << "\nPlease login first!\n";
        return;
    }

    ifstream file("users.txt");

    if(!file.is_open())
    {
        cout << "\nUnable to open passenger records!\n";
        return;
    }

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string id, username, useremail;
        string userphone, userpassword;

        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, useremail, '|');
        getline(ss, userphone, '|');
        getline(ss, userpassword);

        if(id == currentUserId)
        {
            cout << "\n========================================";
            cout << "\n             MY PROFILE";
            cout << "\n========================================";

            cout << "\nPassenger ID : " << id;
            cout << "\nFull Name    : " << username;
            cout << "\nEmail        : " << useremail;
            cout << "\nPhone Number : " << userphone;

            cout << "\n========================================\n";

            return;
        }
    }

    cout << "\nPassenger profile not found!\n";
}
// ================= FORGOT PASSWORD =================

void RailwaySystem::forgotPassword()
{
    string passengerId, email, phone;
    string newPassword, confirmPassword;

    cout << "\n========================================";
    cout << "\n            FORGOT PASSWORD";
    cout << "\n========================================";

    cout << "\nEnter Passenger ID: ";
    getline(cin, passengerId);

    cout << "Enter Registered Email: ";
    getline(cin, email);

    cout << "Enter Registered Phone: ";
    getline(cin, phone);

    ifstream file("users.txt");

    if(!file.is_open())
    {
        cout << "\nPassenger database not found!\n";
        return;
    }

    string line;
    bool found = false;
    int matches = 0;
    string oldPassword;

    // Verify passenger details
    while(getline(file, line))
    {
        stringstream ss(line);

        string id, name, userEmail;
        string userPhone, password;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, userEmail, '|');
        getline(ss, userPhone, '|');
        getline(ss, password);

        if(id == passengerId)
        {
            matches++;

            if(userEmail == email &&
               userPhone == phone)
            {
                found = true;
                oldPassword = password;
            }
        }
    }

    bool readOk = file.eof();
    file.close();

    if(!readOk || matches != 1 || !found)
    {
        cout << "\nAccount verification failed!\n";
        return;
    }

    cout << "\nAccount Verified Successfully!\n";

    // New password
    cout << "\nEnter New Password: ";
    getline(cin, newPassword);

    if(!validatePassword(newPassword))
    {
        cout << "\nWeak Password!";
        cout << "\nUse at least 8 characters with";
        cout << "\nuppercase, lowercase, digit and special character.\n";
        return;
    }

    if(newPassword == oldPassword)
    {
        cout << "\nNew password must be different!\n";
        return;
    }

    cout << "Confirm New Password: ";
    getline(cin, confirmPassword);

    if(newPassword != confirmPassword)
    {
        cout << "\nPasswords Do Not Match!\n";
        return;
    }

    // Protect existing backup
    ifstream backup("users_backup.txt");

    if(backup.is_open())
    {
        cout << "\nExisting backup found!";
        cout << "\nCheck users_backup.txt before continuing.\n";
        return;
    }

    backup.close();

    // Rewrite passenger database
    ifstream input("users.txt");
    ofstream output("users_temp.txt", ios::trunc);

    if(!input.is_open() || !output.is_open())
    {
        cout << "\nError opening passenger files!\n";
        return;
    }

    int updated = 0;

    while(getline(input, line))
    {
        stringstream ss(line);

        string id, name, userEmail;
        string userPhone, password;

        if(!getline(ss, id, '|') ||
           !getline(ss, name, '|') ||
           !getline(ss, userEmail, '|') ||
           !getline(ss, userPhone, '|') ||
           !getline(ss, password))
        {
            cout << "\nInvalid passenger record!\n";

            input.close();
            output.close();

            std::remove("users_temp.txt");
            return;
        }

        if(id == passengerId)
        {
            updated++;

            // Preserve all details except password
            output << id << "|"
                   << name << "|"
                   << userEmail << "|"
                   << userPhone << "|"
                   << newPassword << "\n";
        }
        else
        {
            output << line << "\n";
        }
    }

    bool inputOk = input.eof();
    bool outputOk = output.good();

    input.close();
    output.close();

    if(!inputOk || !outputOk || !output || updated != 1)
    {
        cout << "\nError updating password!\n";

        std::remove("users_temp.txt");
        return;
    }

    // Backup original database
    if(std::rename("users.txt", "users_backup.txt") != 0)
    {
        cout << "\nUnable to back up passenger database!\n";

        std::remove("users_temp.txt");
        return;
    }

    // Replace with updated database
    if(std::rename("users_temp.txt", "users.txt") != 0)
    {
        cout << "\nPassword reset failed!\n";

        if(std::rename("users_backup.txt", "users.txt") != 0)
        {
            cout << "\nCRITICAL: Restoration failed!";
            cout << "\nCheck users_backup.txt manually.\n";
        }
        else
        {
            cout << "\nOriginal database restored.\n";
        }

        return;
    }

    // Remove backup
    if(std::remove("users_backup.txt") != 0)
    {
        cout << "\nWarning: Backup cleanup failed.";
        cout << "\nCheck users_backup.txt manually.\n";
    }

    cout << "\n========================================";
    cout << "\n       PASSWORD RESET SUCCESSFULLY!";
    cout << "\n========================================";

    // Record activity without storing passwords
    if(!recordActivity(
        passengerId,
        "Account Password Reset"
    ))
    {
        cout << "\nWarning: Activity history could not be saved.\n";
    }

    cout << "\nPlease login using your new password.\n";
}
// ================= CHANGE PASSWORD =================

void RailwaySystem::changePassword()
{
    if(currentUserId.empty())
    {
        cout << "\nPlease login first!\n";
        return;
    }

    string oldPassword, newPassword, confirmPassword;

    cout << "\n========================================";
    cout << "\n           CHANGE PASSWORD";
    cout << "\n========================================";

    cout << "\nEnter Current Password: ";
    getline(cin, oldPassword);

    // Read passenger database
    ifstream file("users.txt");

    if(!file.is_open())
    {
        cout << "\nUnable to open passenger database!\n";
        return;
    }

    string line;
    string userName, userEmail, userPhone;
    bool found = false;
    int matches = 0;

    // Verify current password
    while(getline(file, line))
    {
        stringstream ss(line);

        string id, name, email, phone, pass;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, email, '|');
        getline(ss, phone, '|');
        getline(ss, pass);

        if(id == currentUserId)
        {
            matches++;

            if(pass == oldPassword &&
               email == currentUserEmail)
            {
                found = true;

                userName = name;
                userEmail = email;
                userPhone = phone;
            }
        }
    }

    bool readOk = file.eof();
    file.close();

    if(!readOk || matches != 1)
    {
        cout << "\nUnable to verify passenger account!\n";
        return;
    }

    if(!found)
    {
        cout << "\nIncorrect Current Password!\n";
        return;
    }

    // Get new password
    cout << "\nEnter New Password: ";
    getline(cin, newPassword);

    if(!validatePassword(newPassword))
    {
        cout << "\nWeak Password!";
        cout << "\nPassword must contain:";
        cout << "\n- At least 8 characters";
        cout << "\n- One uppercase letter";
        cout << "\n- One lowercase letter";
        cout << "\n- One number";
        cout << "\n- One special character";
        cout << "\n- No spaces\n";
        return;
    }

    if(newPassword == oldPassword)
    {
        cout << "\nNew Password Cannot Be Same As Old Password!\n";
        return;
    }

    cout << "Confirm New Password: ";
    getline(cin, confirmPassword);

    if(newPassword != confirmPassword)
    {
        cout << "\nPasswords Do Not Match!\n";
        return;
    }

    // Check for an existing backup
    ifstream backup("users_backup.txt");

    if(backup.is_open())
    {
        cout << "\nExisting backup detected!";
        cout << "\nCheck users_backup.txt before continuing.\n";
        return;
    }

    backup.close();

    // Create updated passenger database
    ifstream input("users.txt");
    ofstream output("users_temp.txt", ios::trunc);

    if(!input.is_open() || !output.is_open())
    {
        cout << "\nError Opening Passenger Files!\n";
        return;
    }

    int updated = 0;

    while(getline(input, line))
    {
        stringstream ss(line);
        string id;

        getline(ss, id, '|');

        if(id == currentUserId)
        {
            updated++;

            output << currentUserId << "|"
                   << userName << "|"
                   << userEmail << "|"
                   << userPhone << "|"
                   << newPassword << "\n";
        }
        else
        {
            output << line << "\n";
        }
    }

    bool inputOk = input.eof();
    bool outputOk = output.good();

    input.close();
    output.close();

    if(!inputOk || !outputOk || !output || updated != 1)
    {
        cout << "\nError Updating Password!\n";
        std::remove("users_temp.txt");
        return;
    }

    // Back up original database
    if(std::rename("users.txt", "users_backup.txt") != 0)
    {
        cout << "\nUnable to Back Up Passenger Database!\n";
        std::remove("users_temp.txt");
        return;
    }

    // Replace with updated database
    if(std::rename("users_temp.txt", "users.txt") != 0)
    {
        cout << "\nPassword Update Failed!\n";

        if(std::rename("users_backup.txt", "users.txt") != 0)
        {
            cout << "\nCRITICAL: Restore Failed!";
            cout << "\nCheck users_backup.txt manually.\n";
        }
        else
        {
            cout << "\nOriginal Database Restored.\n";
        }

        return;
    }

    // Remove backup after successful update
    if(std::remove("users_backup.txt") != 0)
    {
        cout << "\nWarning: Backup cleanup failed.";
        cout << "\nCheck users_backup.txt manually.\n";
    }

    cout << "\n========================================";
    cout << "\n       PASSWORD CHANGED SUCCESSFULLY!";
    cout << "\n========================================\n";

    // Record activity without storing passwords
    if(!recordActivity(
        currentUserId,
        "Account Password Changed"
    ))
    {
        cout << "\nWarning: Activity history could not be saved.\n";
    }
}
void RailwaySystem::passengerDashboard()
{
    string choice;

    while(true)
    {
        cout << "\n========================================";
        cout << "\n          PASSENGER DASHBOARD";
        cout << "\n========================================";

        cout << "\nWelcome, " << currentUserName << "!";

        cout << "\n\n1. View My Profile";
        cout << "\n2. Search Trains";
        cout << "\n3. Check Seat Availability";
        cout << "\n4. Book Ticket";
        cout << "\n5. View My Bookings";
        cout << "\n6. Cancel Ticket";
        cout << "\n7. View Recent Activities";
        cout << "\n8. Change Password";
        cout << "\n9. Logout";

        cout << "\n========================================";

        cout << "\nEnter Your Choice: ";
        
        if(!getline(cin, choice))
        {
            return;
        }

        if(choice == "1")
        {
            viewProfile();
        }
        else if(choice == "2")
        {
             searchTrain();
           }
       else if(choice == "3")
{
    checkSeatAvailability();
}
        else if(choice == "4")
{
    bookTicket();
}
        else if(choice == "5")
{
    viewMyBookings();
}
        else if(choice == "6")
{
    cancelTicket();
}
        else if(choice == "7")
{
    viewRecentActivities();
}
        else if(choice == "8")
{
    changePassword();
}
        else if(choice == "9")
        {
            cout << "\nLogout Successful!\n";

            currentUserId = "";
            currentUserName = "";
            currentUserEmail = "";

            return;
        }
        else
        {
            cout << "\nInvalid Choice!\n";
        }
    }
}
void RailwaySystem::adminLogin()
{
    string searchEmail;
    string searchPassword;

    cout << "\n========================================";
    cout << "\n             ADMIN LOGIN";
    cout << "\n========================================";

    cout << "\nEnter Admin Email: ";
    getline(cin, searchEmail);

    cout << "Enter Admin Password: ";
    getline(cin, searchPassword);

    ifstream file("admin.txt");

    if(!file.is_open())
    {
        cout << "\nError: Admin credentials file not found!";
        return;
    }

    string storedEmail;
    string storedPassword;

    getline(file, storedEmail, '|');
    getline(file, storedPassword);

    file.close();

    if(searchEmail == storedEmail &&
       searchPassword == storedPassword)
    {
        cout << "\n========================================";
        cout << "\n         ADMIN LOGIN SUCCESSFUL!";
        cout << "\n========================================";

        cout << "\nWelcome, Administrator!\n";

        adminDashboard();
    }
    else
    {
        cout << "\nInvalid Admin Email or Password!\n";
    }
}
void RailwaySystem::adminDashboard()
{
    string choice;

    while(true)
    {
        cout << "\n========================================";
        cout << "\n           ADMIN DASHBOARD";
        cout << "\n========================================";

        cout << "\nWelcome, Administrator!";

        cout << "\n\n1. Add New Train";
        cout << "\n2. View All Trains";
        cout << "\n3. Search Train";
        cout << "\n4. Update Train";
        cout << "\n5. Remove Train";
        cout << "\n6. View All Bookings";
        cout << "\n7. View Booking Statistics";
        cout << "\n8. Logout";

        cout << "\n========================================";

        cout << "\nEnter Your Choice: ";

        if(!getline(cin, choice))
        {
            return;
        }
if(choice == "1")
{
    addTrain();
}
        else if(choice == "2")
{
    viewTrains();
}
        else if(choice == "3")
{
    searchTrain();
}
        else if(choice == "4")
{
    updateTrain();
}
        else if(choice == "5")
{
    removeTrain();
}
        else if(choice == "6")
{
    if(bookingsLoaded)
    {
        bookingList.displayBookings();
    }
    else
    {
        cout << "\nBooking database is unavailable!\n";
    }
}
        else if(choice == "7")
{
    if(bookingsLoaded)
    {
        bookingList.displayStatistics();
    }
    else
    {
        cout << "\nBooking database is unavailable!\n";
    }
}
        else if(choice == "8")
        {
            cout << "\nAdmin Logout Successful!\n";
            return;
        }
        else
        {
            cout << "\nInvalid Choice! Try Again.\n";
        }
    }
}
void RailwaySystem::initializeTrains()
{
    // Check whether the train database already exists.
    ifstream checkFile("trains.txt");

    if(checkFile.is_open())
    {
        checkFile.close();
        return;
    }

    // Create the train database for the first time.
    ofstream file("trains.txt");

    if(!file.is_open())
    {
        cout << "\nError creating train database!\n";
        return;
    }

    // Real train names/numbers.
    // Timings, seats and fares are simulated.

    file << "12903|Golden Temple Mail|Bandra Terminus|Amritsar|18:45|23:45|50|1200\n";

    file << "12904|Golden Temple Mail|Amritsar|Bandra Terminus|20:00|05:00|50|1200\n";

    file << "12484|Amritsar Kochuveli SF Express|Amritsar|Thiruvananthapuram North|06:00|12:00|60|1800\n";

    file << "12483|Kochuveli Amritsar SF Express|Thiruvananthapuram North|Amritsar|05:00|14:00|60|1800\n";

    file << "12425|Jammu Rajdhani Express|New Delhi|Jammu Tawi|20:30|06:00|40|1500\n";

    file << "12426|Jammu Rajdhani Express|Jammu Tawi|New Delhi|19:30|05:30|40|1500\n";

    file << "12029|Swarna Shatabdi Express|New Delhi|Amritsar|07:00|13:00|45|900\n";

    file << "12030|Swarna Shatabdi Express|Amritsar|New Delhi|16:30|23:00|45|900\n";

    file << "12951|Mumbai Rajdhani Express|Mumbai Central|New Delhi|17:00|08:30|50|2000\n";

    file << "12952|Mumbai Rajdhani Express|New Delhi|Mumbai Central|16:30|08:00|50|2000\n";

    file.close();

    if(!file)
    {
        cout << "\nError saving initial train records!\n";
        return;
    }

    cout << "\nTrain database initialized successfully!\n";
}
void RailwaySystem::viewTrains()
{
    ifstream file("trains.txt");

    if(!file.is_open())
    {
        cout << "\nTrain database not found!\n";
        return;
    }

    cout << "\n========================================";
    cout << "\n           AVAILABLE TRAINS";
    cout << "\n========================================\n";

    string line;
    int count = 0;

    while(getline(file, line))
    {
        stringstream ss(line);

        string trainNumber;
        string trainName;
        string source;
        string destination;
        string departure;
        string arrival;
        string seats;
        string price;

        getline(ss, trainNumber, '|');
        getline(ss, trainName, '|');
        getline(ss, source, '|');
        getline(ss, destination, '|');
        getline(ss, departure, '|');
        getline(ss, arrival, '|');
        getline(ss, seats, '|');
        getline(ss, price);

        if(trainNumber.empty())
        {
            continue;
        }

        count++;

        cout << "\n----------------------------------------";
        cout << "\nTrain Number : " << trainNumber;
        cout << "\nTrain Name   : " << trainName;
        cout << "\nSource       : " << source;
        cout << "\nDestination  : " << destination;
        cout << "\nDeparture    : " << departure;
        cout << "\nArrival      : " << arrival;
        cout << "\nTotal Seats  : " << seats;
        cout << "\nTicket Price : Rs. " << price;
        cout << "\n----------------------------------------\n";
    }

    cout << "\nTotal Trains: " << count << endl;

    file.close();
}
bool RailwaySystem::trainExists(const string& searchNumber)
{
    ifstream file("trains.txt");

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string trainNumber;

        getline(ss, trainNumber, '|');

        if(trainNumber == searchNumber)
        {
            return true;
        }
    }

    return false;
}
void RailwaySystem::addTrain()
{
    string trainNumber;
    string trainName;
    string source;
    string destination;
    string departure;
    string arrival;

    string seatsInput;
    string priceInput;

    int totalSeats;
    double ticketPrice;

    cout << "\n========================================";
    cout << "\n             ADD NEW TRAIN";
    cout << "\n========================================";

    // Check the database before adding records
    ifstream checkFile("trains.txt");

    if(!checkFile.is_open())
    {
        cout << "\nError: Train database not found!\n";
        return;
    }

    checkFile.close();

    // Train number
    cout << "\nEnter Train Number: ";
    getline(cin, trainNumber);

    // Validate train number
    if(trainNumber.length() != 5)
    {
        cout << "\nTrain Number Must Contain 5 Digits!\n";
        return;
    }

    for(char ch : trainNumber)
    {
        if(!isdigit(static_cast<unsigned char>(ch)))
        {
            cout << "\nTrain Number Must Contain Digits Only!\n";
            return;
        }
    }

    // Check duplicate train number
    if(trainExists(trainNumber))
    {
        cout << "\nError: Train Number Already Exists!\n";
        return;
    }

    // Train name
    cout << "Enter Train Name: ";
    getline(cin, trainName);

    if(trainName.empty() ||
       trainName.find('|') != string::npos)
    {
        cout << "\nInvalid Train Name!\n";
        return;
    }

    // Source
    cout << "Enter Source Station: ";
    getline(cin, source);

    if(source.empty() ||
       source.find('|') != string::npos)
    {
        cout << "\nInvalid Source Station!\n";
        return;
    }

    // Destination
    cout << "Enter Destination Station: ";
    getline(cin, destination);

    if(destination.empty() ||
       destination.find('|') != string::npos)
    {
        cout << "\nInvalid Destination Station!\n";
        return;
    }

    if(source == destination)
    {
        cout << "\nSource and Destination Cannot Be Same!\n";
        return;
    }

    // Departure time
    cout << "Enter Departure Time (HH:MM): ";
    getline(cin, departure);

    // Arrival time
    cout << "Enter Arrival Time (HH:MM): ";
    getline(cin, arrival);

    // Validate time format and range
    auto validTime = [](const string& time)
    {
        if(time.length() != 5 || time[2] != ':')
        {
            return false;
        }

        for(int i : {0, 1, 3, 4})
        {
            if(!isdigit(static_cast<unsigned char>(time[i])))
            {
                return false;
            }
        }

        int hours = stoi(time.substr(0, 2));
        int minutes = stoi(time.substr(3, 2));

        return hours >= 0 && hours <= 23 &&
               minutes >= 0 && minutes <= 59;
    };

    if(!validTime(departure) || !validTime(arrival))
    {
        cout << "\nInvalid Time! Use HH:MM (24-hour format).\n";
        return;
    }

    // Seat capacity
    cout << "Enter Total Seats: ";
    getline(cin, seatsInput);

    try
    {
        size_t pos = 0;
        totalSeats = stoi(seatsInput, &pos);

        if(pos != seatsInput.length() || totalSeats <= 0)
        {
            cout << "\nSeats Must Be A Positive Integer!\n";
            return;
        }
    }
    catch(...)
    {
        cout << "\nInvalid Seat Capacity!\n";
        return;
    }

    // Ticket price
    cout << "Enter Ticket Price: ";
    getline(cin, priceInput);

    try
    {
        size_t pos = 0;
        ticketPrice = stod(priceInput, &pos);

        if(pos != priceInput.length() ||
   !std::isfinite(ticketPrice) ||
   ticketPrice <= 0)
{
    cout << "\nTicket Price Must Be A Positive Number!\n";
    return;
}
    }
    catch(...)
    {
        cout << "\nInvalid Ticket Price!\n";
        return;
    }

    // Save the new train
    ofstream file("trains.txt", ios::app);

    if(!file.is_open())
    {
        cout << "\nError Opening Train Database!\n";
        return;
    }

    file << trainNumber << "|"
         << trainName << "|"
         << source << "|"
         << destination << "|"
         << departure << "|"
         << arrival << "|"
         << totalSeats << "|"
         << ticketPrice << "\n";

    file.close();

    if(!file)
    {
        cout << "\nError Saving Train Details!\n";
        return;
    }

    cout << "\n========================================";
    cout << "\n       TRAIN ADDED SUCCESSFULLY!";
    cout << "\n========================================";

    cout << "\nTrain Number : " << trainNumber;
    cout << "\nTrain Name   : " << trainName;
    cout << "\nSource       : " << source;
    cout << "\nDestination  : " << destination;
    cout << "\nTotal Seats  : " << totalSeats;
    cout << "\nTicket Price : Rs. " << ticketPrice;

    cout << "\n========================================\n";
}
void RailwaySystem::searchTrain()
{
    ifstream file("trains.txt");

    if(!file.is_open())
    {
        cout << "\nTrain database not found!\n";
        return;
    }

    string choice;
    string searchNumber;
    string searchSource;
    string searchDestination;

    cout << "\n========================================";
    cout << "\n             SEARCH TRAIN";
    cout << "\n========================================";

    cout << "\n1. Search by Train Number";
    cout << "\n2. Search by Source and Destination";
    cout << "\n3. Back";

    cout << "\nEnter Choice: ";
    getline(cin, choice);

    if(choice == "1")
    {
        cout << "\nEnter Train Number: ";
        getline(cin, searchNumber);
    }
    else if(choice == "2")
    {
        cout << "\nEnter Source: ";
        getline(cin, searchSource);

        cout << "Enter Destination: ";
        getline(cin, searchDestination);

        if(searchSource.empty() || searchDestination.empty())
        {
            cout << "\nSource and destination are required!\n";
            return;
        }

        // Convert input to lowercase
        transform(searchSource.begin(), searchSource.end(),
                  searchSource.begin(),
                  [](unsigned char c) { return tolower(c); });

        transform(searchDestination.begin(), searchDestination.end(),
                  searchDestination.begin(),
                  [](unsigned char c) { return tolower(c); });
    }
    else if(choice == "3")
    {
        return;
    }
    else
    {
        cout << "\nInvalid Choice!\n";
        return;
    }

    string line;
    bool found = false;
    int count = 0;

    while(getline(file, line))
    {
        stringstream ss(line);

        string trainNumber;
        string trainName;
        string source;
        string destination;
        string departure;
        string arrival;
        string seats;
        string price;

        getline(ss, trainNumber, '|');
        getline(ss, trainName, '|');
        getline(ss, source, '|');
        getline(ss, destination, '|');
        getline(ss, departure, '|');
        getline(ss, arrival, '|');
        getline(ss, seats, '|');
        getline(ss, price);

        bool match = false;

        if(choice == "1")
        {
            if(trainNumber == searchNumber)
            {
                match = true;
            }
        }
        else if(choice == "2")
        {
            string sourceLower = source;
            string destinationLower = destination;

            transform(sourceLower.begin(), sourceLower.end(),
                      sourceLower.begin(),
                      [](unsigned char c) { return tolower(c); });

            transform(destinationLower.begin(), destinationLower.end(),
                      destinationLower.begin(),
                      [](unsigned char c) { return tolower(c); });

            if(sourceLower == searchSource &&
               destinationLower == searchDestination)
            {
                match = true;
            }
        }

        if(match)
        {
            found = true;
            count++;

            cout << "\n========================================";
            cout << "\n              TRAIN FOUND";
            cout << "\n========================================";

            cout << "\nTrain Number : " << trainNumber;
            cout << "\nTrain Name   : " << trainName;
            cout << "\nSource       : " << source;
            cout << "\nDestination  : " << destination;
            cout << "\nDeparture    : " << departure;
            cout << "\nArrival      : " << arrival;
            cout << "\nTotal Seats  : " << seats;
            cout << "\nTicket Price : Rs. " << price;

            cout << "\n========================================\n";
        }
    }

    if(!found)
    {
        cout << "\nNo Matching Train Found!\n";
    }
    else
    {
        cout << "\nTotal Matching Trains: " << count << "\n";
    }

    file.close();
}
void RailwaySystem::updateTrain()
{
    string searchNumber;

    cout << "\n========================================";
    cout << "\n          UPDATE TRAIN DETAILS";
    cout << "\n========================================";

    cout << "\nEnter Train Number: ";
    getline(cin, searchNumber);

    ifstream file("trains.txt");

    if(!file.is_open())
    {
        cout << "\nError: Train database not found!\n";
        return;
    }

    string line;
    string updatedRecord;
    bool found = false;

    // Step 1: Search for the train
    while(getline(file, line))
    {
        stringstream ss(line);
        string number;

        getline(ss, number, '|');

        if(number == searchNumber)
        {
            found = true;

            string name, source, destination;
            string departure, arrival, seats, price;

            getline(ss, name, '|');
            getline(ss, source, '|');
            getline(ss, destination, '|');
            getline(ss, departure, '|');
            getline(ss, arrival, '|');
            getline(ss, seats, '|');
            getline(ss, price);

            cout << "\nTrain Found!\n";

            cout << "\nTrain Number : " << number;
            cout << "\nTrain Name   : " << name;
            cout << "\nSource       : " << source;
            cout << "\nDestination  : " << destination;
            cout << "\nDeparture    : " << departure;
            cout << "\nArrival      : " << arrival;
            cout << "\nTotal Seats  : " << seats;
            cout << "\nTicket Price : Rs. " << price;

            cout << "\n\n1. Update Train Name";
            cout << "\n2. Update Departure Time";
            cout << "\n3. Update Arrival Time";
            cout << "\n4. Update Ticket Price";
            cout << "\n5. Back";

            string choice;
            string newValue;

            cout << "\n\nEnter Choice: ";
            getline(cin, choice);

            if(choice == "5")
            {
                return;
            }

            if(choice != "1" && choice != "2" &&
               choice != "3" && choice != "4")
            {
                cout << "\nInvalid Choice!\n";
                return;
            }

            cout << "\nEnter New Value: ";
            getline(cin, newValue);

            if(newValue.empty() ||
               newValue.find('|') != string::npos)
            {
                cout << "\nInvalid Value!\n";
                return;
            }

            // Validate HH:MM time format
            auto validTime = [](const string& time)
            {
                if(time.length() != 5 || time[2] != ':')
                    return false;

                for(int i : {0, 1, 3, 4})
                {
                    if(!isdigit(
                        static_cast<unsigned char>(time[i])))
                        return false;
                }

                int hours = stoi(time.substr(0, 2));
                int minutes = stoi(time.substr(3, 2));

                return hours >= 0 && hours <= 23 &&
                       minutes >= 0 && minutes <= 59;
            };

            if(choice == "1")
            {
                if(newValue.find_first_not_of(" \t") ==
                   string::npos)
                {
                    cout << "\nInvalid Train Name!\n";
                    return;
                }

                name = newValue;
            }
            else if(choice == "2")
            {
                if(!validTime(newValue))
                {
                    cout << "\nInvalid Departure Time!\n";
                    return;
                }

                departure = newValue;
            }
            else if(choice == "3")
            {
                if(!validTime(newValue))
                {
                    cout << "\nInvalid Arrival Time!\n";
                    return;
                }

                arrival = newValue;
            }
            else if(choice == "4")
            {
                try
                {
                    size_t pos = 0;
                    double newPrice = stod(newValue, &pos);

                    if(pos != newValue.length() ||
                       !std::isfinite(newPrice) ||
                       newPrice <= 0)
                    {
                        cout << "\nInvalid Ticket Price!\n";
                        return;
                    }

                    price = newValue;
                }
                catch(...)
                {
                    cout << "\nInvalid Ticket Price!\n";
                    return;
                }
            }

            // Construct updated record
            updatedRecord =
                number + "|" +
                name + "|" +
                source + "|" +
                destination + "|" +
                departure + "|" +
                arrival + "|" +
                seats + "|" +
                price;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nTrain Not Found!\n";
        return;
    }

    // Step 2: Open files to rewrite database
    ifstream input("trains.txt");
    ofstream output("trains_temp.txt", ios::trunc);

    if(!input.is_open() || !output.is_open())
    {
        cout << "\nError Opening Files!\n";
        return;
    }

    // Step 3: Write updated data to temporary file
    while(getline(input, line))
    {
        stringstream ss(line);
        string number;

        getline(ss, number, '|');

        if(number == searchNumber)
        {
            output << updatedRecord << "\n";
        }
        else
        {
            output << line << "\n";
        }
    }

    bool readOk = input.eof();
    bool writeOk = output.good();

    input.close();
    output.close();

    if(!readOk || !writeOk || !output)
    {
        cout << "\nError Writing Updated Data!\n";
        return;
    }

    // Step 4: Keep a backup during replacement
    // Never overwrite an existing backup automatically.
    ifstream backupCheck("trains_backup.txt");

    if(backupCheck.good())
    {
        cout << "\nExisting backup detected!";
        cout << "\nCheck trains_backup.txt before updating.\n";
        return;
    }

    backupCheck.close();

    if(std::rename("trains.txt", "trains_backup.txt") != 0)
    {
        cout << "\nCould Not Back Up Original File!\n";
        return;
    }

    if(std::rename("trains_temp.txt", "trains.txt") != 0)
    {
        // Attempt to restore the original database
        if(std::rename("trains_backup.txt", "trains.txt") != 0)
        {
            cout << "\nCritical Error: Restore failed!";
            cout << "\nCheck trains_backup.txt manually.\n";
        }
        else
        {
            cout << "\nUpdate Failed! Original File Restored.\n";
        }

        return;
    }

    // The new file is in place.
    // Remove the backup.
    if(std::remove("trains_backup.txt") != 0)
    {
        cout << "\nTrain updated, but backup cleanup failed.";
        cout << "\nCheck trains_backup.txt manually.\n";
    }

    cout << "\n========================================";
    cout << "\n       TRAIN UPDATED SUCCESSFULLY!";
    cout << "\n========================================\n";
}
void RailwaySystem::removeTrain()
{
    string searchNumber;

    cout << "\n========================================";
    cout << "\n             REMOVE TRAIN";
    cout << "\n========================================";

    cout << "\nEnter Train Number: ";
    getline(cin, searchNumber);

    ifstream file("trains.txt");

    if(!file.is_open())
    {
        cout << "\nTrain Database Not Found!\n";
        return;
    }

    string line;
    bool found = false;

    // STEP 1: Search for the train
    while(getline(file, line))
    {
        stringstream ss(line);

        string number;
        string trainName;
        string source;
        string destination;

        getline(ss, number, '|');

        if(number == searchNumber)
        {
            found = true;

            getline(ss, trainName, '|');
            getline(ss, source, '|');
            getline(ss, destination, '|');

            cout << "\nTrain Found!\n";

            cout << "\nTrain Number : " << number;
            cout << "\nTrain Name   : " << trainName;
            cout << "\nSource       : " << source;
            cout << "\nDestination  : " << destination;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nTrain Not Found!\n";
        return;
    }

    // STEP 2: Confirm deletion
    string choice;

    cout << "\n----------------------------------------";
    cout << "\nAre you sure you want to remove this train?";
    cout << "\n1. Yes";
    cout << "\n2. No";

    cout << "\nEnter Choice: ";
    getline(cin, choice);

    if(choice != "1")
    {
        cout << "\nTrain Removal Cancelled!\n";
        return;
    }

    // STEP 3: Temporary booking safety check.
    // Until booking records have a defined format,
    // block removals if any booking records exist.

    ifstream bookings("bookings.txt");

    if(bookings.is_open())
    {
        string bookingLine;

        while(getline(bookings, bookingLine))
        {
            if(!bookingLine.empty())
            {
                cout << "\nRemoval Blocked!";
                cout << "\nBooking records exist.";
                cout << "\nTrain removal requires booking verification.\n";
                return;
            }
        }

        if(bookings.bad())
        {
            cout << "\nError reading booking records!\n";
            return;
        }
    }

    bookings.close();

    // STEP 4: Avoid overwriting an existing backup.
    ifstream backupCheck("trains_backup.txt");

    if(backupCheck.is_open())
    {
        cout << "\nExisting train backup detected!";
        cout << "\nCheck trains_backup.txt before continuing.\n";
        return;
    }

    backupCheck.close();

    // STEP 5: Create a temporary file.
    ifstream input("trains.txt");
    ofstream output("trains_temp.txt", ios::trunc);

    if(!input.is_open() || !output.is_open())
    {
        cout << "\nError Opening Train Files!\n";
        return;
    }

    // STEP 6: Copy all records except selected train.
    while(getline(input, line))
    {
        stringstream ss(line);
        string number;

        getline(ss, number, '|');

        if(number != searchNumber)
        {
            output << line << "\n";
        }
    }

    bool readOk = input.eof();
    bool writeOk = output.good();

    input.close();
    output.close();

    if(!readOk || !writeOk || !output)
    {
        cout << "\nError Writing Updated Train Records!\n";
        std::remove("trains_temp.txt");
        return;
    }

    // STEP 7: Back up the original file.
    if(std::rename("trains.txt", "trains_backup.txt") != 0)
    {
        cout << "\nCould Not Back Up Original Train File!\n";
        std::remove("trains_temp.txt");
        return;
    }

    // STEP 8: Replace original with updated file.
    if(std::rename("trains_temp.txt", "trains.txt") != 0)
    {
        cout << "\nError Replacing Train Database!\n";

        if(std::rename("trains_backup.txt", "trains.txt") != 0)
        {
            cout << "\nCritical Error: Restoration Failed!";
            cout << "\nCheck trains_backup.txt manually.\n";
        }
        else
        {
            cout << "\nOriginal Train Database Restored.\n";
        }

        return;
    }

    // STEP 9: Remove backup after successful replacement.
    if(std::remove("trains_backup.txt") != 0)
    {
        cout << "\nWarning: Could not remove backup file.";
        cout << "\nCheck trains_backup.txt manually.\n";
    }

    cout << "\n========================================";
    cout << "\n       TRAIN REMOVED SUCCESSFULLY!";
    cout << "\n========================================\n";
}
void RailwaySystem::bookTicket()
{
    if(currentUserId.empty())
    {
        cout << "\nPlease login first!\n";
        return;
    }

    if(!bookingsLoaded)
    {
        cout << "\nBooking database could not be loaded.";
        cout << "\nTicket booking is temporarily disabled.\n";
        return;
    }

    string searchNumber;
    string journeyDate;

    cout << "\n========================================";
    cout << "\n              BOOK TICKET";
    cout << "\n========================================";

    cout << "\nEnter Train Number: ";
    getline(cin, searchNumber);

    cout << "Enter Journey Date (YYYY-MM-DD): ";
    getline(cin, journeyDate);

    // Basic date format validation
    if(journeyDate.length() != 10 ||
       journeyDate[4] != '-' ||
       journeyDate[7] != '-')
    {
        cout << "\nInvalid Date Format! Use YYYY-MM-DD.\n";
        return;
    }

    for(int i = 0; i < 10; i++)
    {
        if(i == 4 || i == 7)
        {
            continue;
        }

        if(!isdigit(
            static_cast<unsigned char>(journeyDate[i])))
        {
            cout << "\nInvalid Journey Date!\n";
            return;
        }
    }

    int year = stoi(journeyDate.substr(0, 4));
    int month = stoi(journeyDate.substr(5, 2));
    int day = stoi(journeyDate.substr(8, 2));

    bool leapYear =
        (year % 400 == 0) ||
        (year % 4 == 0 && year % 100 != 0);

    int daysInMonth[] =
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(month < 1 || month > 12 || year < 2026)
    {
        cout << "\nInvalid Journey Date!\n";
        return;
    }

    if(leapYear)
    {
        daysInMonth[2] = 29;
    }

    if(day < 1 || day > daysInMonth[month])
    {
        cout << "\nInvalid Journey Date!\n";
        return;
    }

    // Open train database
    ifstream file("trains.txt");

    if(!file.is_open())
    {
        cout << "\nTrain Database Not Found!\n";
        return;
    }

    string line;
    bool found = false;

    string trainName;
    string source;
    string destination;
    string departure;
    string arrival;
    string totalSeatsString;
    string price;

    while(getline(file, line))
    {
        stringstream ss(line);

        string number;

        getline(ss, number, '|');

        if(number == searchNumber)
        {
            found = true;

            getline(ss, trainName, '|');
            getline(ss, source, '|');
            getline(ss, destination, '|');
            getline(ss, departure, '|');
            getline(ss, arrival, '|');
            getline(ss, totalSeatsString, '|');
            getline(ss, price);

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nTrain Not Found!\n";
        return;
    }

    int totalSeats;

    try
    {
        totalSeats = stoi(totalSeatsString);
    }
    catch(...)
    {
        cout << "\nInvalid seat capacity in train record!\n";
        return;
    }

    if(totalSeats <= 0)
    {
        cout << "\nTrain has no available seating capacity!\n";
        return;
    }

    // Find the first available seat
    int allocatedSeat = 0;
    int availableSeats = 0;

    for(int seat = 1; seat <= totalSeats; seat++)
    {
        if(!bookingList.isSeatTaken(
            searchNumber,
            journeyDate,
            seat))
        {
            availableSeats++;

            if(allocatedSeat == 0)
            {
                allocatedSeat = seat;
            }
        }
    }
    string bookingStatus = "CONFIRMED";

int waitingPosition = 0;

int existingWaiting = bookingList.countWaitingBookings(
    searchNumber,
    journeyDate
);

if(allocatedSeat == 0 || existingWaiting > 0)
{
    bookingStatus = "WAITING";
    allocatedSeat = 0;
    waitingPosition = existingWaiting + 1;
}

// A new passenger must not jump ahead of the waiting list.

else
{
    cout << "\n\nSeat Available!";
    cout << "\nWould you like to confirm your booking?";
}

    cout << "\n========================================";
    cout << "\n             TRAIN DETAILS";
    cout << "\n========================================";

    cout << "\nTrain Number  : " << searchNumber;
    cout << "\nTrain Name    : " << trainName;
    cout << "\nSource        : " << source;
    cout << "\nDestination   : " << destination;
    cout << "\nDeparture     : " << departure;
    cout << "\nArrival       : " << arrival;
    cout << "\nJourney Date  : " << journeyDate;
    cout << "\nTotal Seats   : " << totalSeats;
    cout << "\nAvailable     : " << availableSeats;
    cout << "\nTicket Price  : Rs. " << price;
    if(bookingStatus == "WAITING")
{
    cout << "\n\n========================================";
    cout << "\n         WAITING LIST AVAILABLE";
    cout << "\n========================================";

    cout << "\nNo confirmed seats available.";
    cout << "\nYour Waiting Position: WL"
         << waitingPosition;

    cout << "\n\nWould you like to join the waiting list?";
}
else
{
    cout << "\n\nSeat Available!";
    cout << "\nWould you like to confirm your booking?";
}

    

    string choice;

cout << "\n1. Yes";
cout << "\n2. No";
cout << "\nEnter Choice: ";

getline(cin, choice);

if(choice != "1")
{
    cout << "\nBooking Cancelled!\n";
    return;
}

    // Generate unique booking ID
    string bookingId = bookingList.generateBookingId();

    // Save booking permanently
    ofstream bookingFile("bookings.txt", ios::app);

    if(!bookingFile.is_open())
    {
        cout << "\nError opening booking database!\n";
        return;
    }

    bookingFile << bookingId << "|"
            << currentUserId << "|"
            << searchNumber << "|"
            << journeyDate << "|"
            << allocatedSeat << "|"
            << bookingStatus
            << "\n";

    bookingFile.close();

    if(!bookingFile)
    {
        cout << "\nError saving booking!\n";
        return;
    }

        // Insert new booking into Linked List
    bookingList.addBooking(
        bookingId,
        currentUserId,
        searchNumber,
        journeyDate,
        allocatedSeat,
        bookingStatus
    );

    // Record booking activity permanently
    string activityMessage;

    if(bookingStatus == "CONFIRMED")
    {
        activityMessage =
            "Ticket " + bookingId + " Booked Successfully";
    }
    else
    {
        activityMessage =
            "Ticket " + bookingId + " Added to Waiting List";
    }

    if(!recordActivity(currentUserId, activityMessage))
    {
        cout << "\nWarning: Ticket was booked,";
        cout << "\nbut activity history could not be saved.\n";
    }

    // Display booking confirmation
    cout << "\n========================================";

    if(bookingStatus == "CONFIRMED")
    {
        cout << "\n          BOOKING SUCCESSFUL!";
    }
    else
    {
        cout << "\n    WAITING LIST BOOKING CREATED!";
    }

    cout << "\n========================================";

    cout << "\nBooking ID    : " << bookingId;
    cout << "\nPassenger ID  : " << currentUserId;
    cout << "\nPassenger     : " << currentUserName;
    cout << "\nTrain Number  : " << searchNumber;
    cout << "\nTrain Name    : " << trainName;
    cout << "\nJourney Date  : " << journeyDate;

    if(bookingStatus == "CONFIRMED")
    {
        cout << "\nSeat Number   : " << allocatedSeat;
    }
    else
    {
        cout << "\nSeat Number   : Not Allocated";
        cout << "\nWaiting No.   : WL" << waitingPosition;
    }

    cout << "\nStatus        : " << bookingStatus;
    cout << "\n========================================\n";

} // End of bookTicket()
void BookingLinkedList::displayPassengerBookings(
    const string& passengerId) const
{
    BookingNode* current = head;

    int count = 0;

    cout << "\n========================================";
    cout << "\n             MY BOOKINGS";
    cout << "\n========================================\n";

    while(current != nullptr)
    {
        if(current->passengerId == passengerId)
        {
            count++;

            cout << "\n----------------------------------------";
            cout << "\nBooking ID   : " << current->bookingId;
            cout << "\nPassenger ID : " << current->passengerId;
            cout << "\nTrain Number : " << current->trainNumber;
            cout << "\nJourney Date : " << current->journeyDate;

            if(current->seatNumber == 0)
            {
                cout << "\nSeat Number  : Not Allocated";
            }
            else
            {
                cout << "\nSeat Number  : "
                     << current->seatNumber;
            }

            cout << "\nStatus       : " << current->status;
            cout << "\n----------------------------------------\n";
        }

        // Move to next booking
        current = current->next;
    }

    if(count == 0)
    {
        cout << "\nNo bookings found for this passenger.\n";
    }

    cout << "\n========================================\n";
}
void RailwaySystem::viewMyBookings()
{
    if(currentUserId.empty())
    {
        cout << "\nPlease login first!\n";
        return;
    }

    if(!bookingsLoaded)
    {
        cout << "\nBooking records are unavailable!\n";
        return;
    }

    cout << "\nPassenger Name: " << currentUserName;
    cout << "\nPassenger ID  : " << currentUserId;

    bookingList.displayPassengerBookings(currentUserId);
}
void RailwaySystem::checkSeatAvailability()
{
    // Step 1: Check whether booking records are loaded
    if(!bookingsLoaded)
    {
        cout << "\nBooking database is unavailable!\n";
        return;
    }

    string searchNumber;
    string journeyDate;

    cout << "\n========================================";
    cout << "\n        CHECK SEAT AVAILABILITY";
    cout << "\n========================================";

    cout << "\nEnter Train Number: ";
    getline(cin, searchNumber);

    cout << "Enter Journey Date (YYYY-MM-DD): ";
    getline(cin, journeyDate);

    // Step 2: Validate journey date
    if(journeyDate.length() != 10 ||
       journeyDate[4] != '-' ||
       journeyDate[7] != '-')
    {
        cout << "\nInvalid Date Format! Use YYYY-MM-DD.\n";
        return;
    }

    for(int i = 0; i < 10; i++)
    {
        if(i == 4 || i == 7)
        {
            continue;
        }

        if(!isdigit(
            static_cast<unsigned char>(journeyDate[i])))
        {
            cout << "\nInvalid Journey Date!\n";
            return;
        }
    }

    int year = stoi(journeyDate.substr(0, 4));
    int month = stoi(journeyDate.substr(5, 2));
    int day = stoi(journeyDate.substr(8, 2));

    bool leapYear =
        (year % 400 == 0) ||
        (year % 4 == 0 && year % 100 != 0);

    int daysInMonth[] =
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(year < 2026 || month < 1 || month > 12)
    {
        cout << "\nInvalid Journey Date!\n";
        return;
    }

    if(leapYear)
    {
        daysInMonth[2] = 29;
    }

    if(day < 1 || day > daysInMonth[month])
    {
        cout << "\nInvalid Journey Date!\n";
        return;
    }

    // Step 3: Open the train database
    ifstream file("trains.txt");

    if(!file.is_open())
    {
        cout << "\nError: Train database not found!\n";
        return;
    }

    string line;

    bool found = false;

    string trainName;
    string source;
    string destination;
    string departure;
    string arrival;
    string totalSeatsString;
    string price;

    // Step 4: Search train by its number
    while(getline(file, line))
    {
        stringstream ss(line);

        string number;

        getline(ss, number, '|');

        if(number == searchNumber)
        {
            found = true;

            getline(ss, trainName, '|');
            getline(ss, source, '|');
            getline(ss, destination, '|');
            getline(ss, departure, '|');
            getline(ss, arrival, '|');
            getline(ss, totalSeatsString, '|');
            getline(ss, price);

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nTrain Not Found!\n";
        return;
    }

    // Step 5: Convert total seats to integer
    int totalSeats;

    try
    {
        size_t pos = 0;

        totalSeats = stoi(totalSeatsString, &pos);

        if(pos != totalSeatsString.length() ||
           totalSeats <= 0)
        {
            cout << "\nInvalid Train Seating Capacity!\n";
            return;
        }
    }
    catch(...)
    {
        cout << "\nError Reading Train Seating Capacity!\n";
        return;
    }

    // Step 6: Check booked seats using Linked List
    int bookedSeats = 0;

    for(int seat = 1; seat <= totalSeats; seat++)
    {
        if(bookingList.isSeatTaken(
            searchNumber,
            journeyDate,
            seat))
        {
            bookedSeats++;
        }
    }

    // Step 7: Calculate available seats
    int availableSeats = totalSeats - bookedSeats;

    // Step 8: Display availability
    cout << "\n========================================";
    cout << "\n           SEAT AVAILABILITY";
    cout << "\n========================================";

    cout << "\nTrain Number     : " << searchNumber;
    cout << "\nTrain Name       : " << trainName;
    cout << "\nSource           : " << source;
    cout << "\nDestination      : " << destination;
    cout << "\nDeparture        : " << departure;
    cout << "\nArrival          : " << arrival;
    cout << "\nJourney Date     : " << journeyDate;

    cout << "\n----------------------------------------";

    cout << "\nTotal Seats      : " << totalSeats;
    cout << "\nBooked Seats     : " << bookedSeats;
    cout << "\nAvailable Seats  : " << availableSeats;

    cout << "\n----------------------------------------";

    if(availableSeats > 0)
    {
        cout << "\nStatus           : SEATS AVAILABLE";
    }
    else
    {
        cout << "\nStatus           : FULLY BOOKED";
    }

    cout << "\n========================================\n";
}
BookingNode* BookingLinkedList::findBooking(
    const string& bookingId)
{
    BookingNode* current = head;

    while(current != nullptr)
    {
        if(current->bookingId == bookingId)
        {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}
int BookingLinkedList::countWaitingBookings(
    const string& trainNumber,
    const string& journeyDate
) const
{
    int count = 0;

    BookingNode* current = head;

    while(current != nullptr)
    {
        if(current->trainNumber == trainNumber &&
           current->journeyDate == journeyDate &&
           current->status == "WAITING")
        {
            count++;
        }

        current = current->next;
    }

    return count;
}
BookingNode* BookingLinkedList::findFirstWaiting(
    const string& trainNumber,
    const string& journeyDate)
{
    BookingNode* current = head;

    while(current != nullptr)
    {
        if(current->trainNumber == trainNumber &&
           current->journeyDate == journeyDate &&
           current->status == "WAITING")
        {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}
void RailwaySystem::cancelTicket()
{
    // STEP 1: Check login
    if(currentUserId.empty())
    {
        cout << "\nPlease login first!\n";
        return;
    }

    // STEP 2: Check booking database
    if(!bookingsLoaded)
    {
        cout << "\nBooking database is unavailable!\n";
        return;
    }

    cout << "\n========================================";
    cout << "\n             CANCEL TICKET";
    cout << "\n========================================";

    string bookingId;

    cout << "\nEnter Booking ID: ";
    getline(cin, bookingId);

    // STEP 3: Search booking using Linked List
    BookingNode* booking = bookingList.findBooking(bookingId);

    if(booking == nullptr)
    {
        cout << "\nBooking Not Found!\n";
        return;
    }

    // STEP 4: Check booking ownership
    if(booking->passengerId != currentUserId)
    {
        cout << "\nAccess Denied!";
        cout << "\nYou can cancel only your own bookings.\n";
        return;
    }

    // STEP 5: Check booking status
    if(booking->status == "CANCELLED")
    {
        cout << "\nThis ticket is already cancelled!\n";
        return;
    }

if(booking->status != "CONFIRMED" &&
   booking->status != "WAITING")
{
    cout << "\nInvalid booking status!\n";
    return;
}
    // Temporary safeguard until automatic WL promotion is ready
  

    // STEP 6: Display booking details
    cout << "\n----------------------------------------";
    cout << "\nBooking Found!";
    cout << "\n----------------------------------------";

    cout << "\nBooking ID   : " << booking->bookingId;
    cout << "\nPassenger ID : " << booking->passengerId;
    cout << "\nTrain Number : " << booking->trainNumber;
    cout << "\nJourney Date : " << booking->journeyDate;
if(booking->seatNumber == 0)
{
    cout << "\nSeat Number  : Not Allocated";
}
else
{
    cout << "\nSeat Number  : " << booking->seatNumber;
}
    cout << "\nStatus       : " << booking->status;

    // STEP 7: Confirm cancellation
    string choice;

    cout << "\n\nAre you sure you want to cancel?";
    cout << "\n1. Yes";
    cout << "\n2. No";
    cout << "\nEnter Choice: ";

    getline(cin, choice);

    if(choice != "1")
    {
        cout << "\nTicket Cancellation Aborted!\n";
        return;
    }
    // Check whether the cancelled ticket had a confirmed seat
bool wasConfirmed = (booking->status == "CONFIRMED");

// Initially, no waiting passenger is selected
BookingNode* waitingBooking = nullptr;

// Remember the seat number
int releasedSeat = booking->seatNumber;

// Search for the first waiting passenger
if(wasConfirmed)
{
    waitingBooking = bookingList.findFirstWaiting(
        booking->trainNumber,
        booking->journeyDate
    );
}

    // STEP 8: Check for existing backup
    ifstream backupCheck("bookings_backup.txt");

    if(backupCheck.is_open())
    {
        cout << "\nAn existing backup was found!";
        cout << "\nCheck bookings_backup.txt before continuing.\n";
        return;
    }

    backupCheck.close();

    // STEP 9: Open original booking file
    ifstream input("bookings.txt");

    if(!input.is_open())
    {
        cout << "\nError opening booking database!\n";
        return;
    }

    // STEP 10: Create temporary file
    ofstream output("bookings_temp.txt", ios::trunc);

    if(!output.is_open())
    {
        cout << "\nError creating temporary file!\n";
        return;
    }

    string line;

int matchingRecords = 0;
int promotionRecords = 0;

    // STEP 11: Rewrite all booking records
    while(getline(input, line))
{
    stringstream ss(line);

    string storedBookingId;
    getline(ss, storedBookingId, '|');

    // CASE 1: Cancel the selected booking
    if(storedBookingId == bookingId)
    {
        matchingRecords++;

        string passengerId;
        string trainNumber;
        string journeyDate;
        string seatNumber;
        string status;

        if(!getline(ss, passengerId, '|') ||
           !getline(ss, trainNumber, '|') ||
           !getline(ss, journeyDate, '|') ||
           !getline(ss, seatNumber, '|') ||
           !getline(ss, status))
        {
            cout << "\nInvalid booking record!\n";

            input.close();
            output.close();

            std::remove("bookings_temp.txt");
            return;
        }

        // Verify that the file matches the Linked List
        if(passengerId != booking->passengerId ||
           trainNumber != booking->trainNumber ||
           journeyDate != booking->journeyDate ||
           seatNumber != to_string(booking->seatNumber) ||
           status != booking->status)
        {
            cout << "\nBooking data mismatch!\n";

            input.close();
            output.close();

            std::remove("bookings_temp.txt");
            return;
        }

        // Save cancelled booking
        output << storedBookingId << "|"
               << passengerId << "|"
               << trainNumber << "|"
               << journeyDate << "|"
               << seatNumber << "|"
               << "CANCELLED"
               << "\n";
    }

    // CASE 2: Promote the first waiting passenger
    else if(waitingBooking != nullptr &&
            storedBookingId == waitingBooking->bookingId)
    {
        promotionRecords++;

        string passengerId;
        string trainNumber;
        string journeyDate;
        string seatNumber;
        string status;

        if(!getline(ss, passengerId, '|') ||
           !getline(ss, trainNumber, '|') ||
           !getline(ss, journeyDate, '|') ||
           !getline(ss, seatNumber, '|') ||
           !getline(ss, status))
        {
            cout << "\nInvalid waiting booking record!\n";

            input.close();
            output.close();

            std::remove("bookings_temp.txt");
            return;
        }

        // Verify the waiting booking
        if(passengerId != waitingBooking->passengerId ||
           trainNumber != waitingBooking->trainNumber ||
           journeyDate != waitingBooking->journeyDate ||
           seatNumber != "0" ||
           status != "WAITING")
        {
            cout << "\nWaiting booking data mismatch!\n";

            input.close();
            output.close();

            std::remove("bookings_temp.txt");
            return;
        }

        // Allocate the released seat
        output << storedBookingId << "|"
               << passengerId << "|"
               << trainNumber << "|"
               << journeyDate << "|"
               << releasedSeat << "|"
               << "CONFIRMED"
               << "\n";
    }

    // CASE 3: Preserve every other booking
    else
    {
        output << line << "\n";
    }
}

    // STEP 12: Check file operations
    bool readOk = input.eof();
    bool writeOk = output.good();

    input.close();
    output.close();

    int expectedPromotions = (waitingBooking != nullptr) ? 1 : 0;

if(!readOk || !writeOk || !output ||
   matchingRecords != 1 ||
   promotionRecords != expectedPromotions)
{
    cout << "\nError updating booking records!";
    cout << "\nOriginal database was not changed.\n";

    std::remove("bookings_temp.txt");
    return;
}

    // STEP 13: Back up original database
    if(std::rename("bookings.txt", "bookings_backup.txt") != 0)
    {
        cout << "\nCould not back up booking database!\n";

        std::remove("bookings_temp.txt");
        return;
    }

    // STEP 14: Replace original database
    if(std::rename("bookings_temp.txt", "bookings.txt") != 0)
    {
        cout << "\nError replacing booking database!\n";

        if(std::rename("bookings_backup.txt", "bookings.txt") != 0)
        {
            cout << "\nCritical Error: Restoration failed!";
            cout << "\nCheck bookings_backup.txt manually.\n";
        }
        else
        {
            cout << "\nOriginal booking database restored.\n";
        }

        return;
    }

    // STEP 15: Remove backup after successful replacement
    if(std::remove("bookings_backup.txt") != 0)
    {
        cout << "\nWarning: Backup cleanup failed.";
        cout << "\nCheck bookings_backup.txt manually.\n";
    }
// STEP 16: Update Linked List after successful file saving

// Cancel original booking
booking->status = "CANCELLED";

// Automatically confirm first waiting passenger
if(waitingBooking != nullptr)
{
    waitingBooking->seatNumber = releasedSeat;

    waitingBooking->status = "CONFIRMED";
}

// STEP 17: Record cancellation activity

if(!recordActivity(
    currentUserId,
    "Ticket " + booking->bookingId + " Cancelled"
))
{
    cout << "\nWarning: Cancellation succeeded,";
    cout << "\nbut activity history could not be saved.\n";
}

// STEP 18: Record waiting-list confirmation activity

if(waitingBooking != nullptr)
{
    if(!recordActivity(
        waitingBooking->passengerId,
        "Ticket " + waitingBooking->bookingId +
        " Confirmed from Waiting List"
    ))
    {
        cout << "\nWarning: Waiting ticket was confirmed,";
        cout << "\nbut its activity could not be saved.\n";
    }
}

    cout << "\n========================================";
    cout << "\n       TICKET CANCELLED SUCCESSFULLY!";
    cout << "\n========================================";

    cout << "\nBooking ID   : " << booking->bookingId;
    cout << "\nTrain Number : " << booking->trainNumber;
    cout << "\nJourney Date : " << booking->journeyDate;
if(booking->seatNumber == 0)
{
    cout << "\nSeat Number  : Not Allocated";
}
else
{
    cout << "\nSeat Number  : " << booking->seatNumber;
}
    cout << "\nStatus       : CANCELLED";
    // Display automatic waiting list confirmation

if(waitingBooking != nullptr)
{
    cout << "\n========================================";
    cout << "\n    WAITING LIST TICKET CONFIRMED!";
    cout << "\n========================================";

    cout << "\nBooking ID   : "
         << waitingBooking->bookingId;

    cout << "\nPassenger ID : "
         << waitingBooking->passengerId;

    cout << "\nTrain Number : "
         << waitingBooking->trainNumber;

    cout << "\nJourney Date : "
         << waitingBooking->journeyDate;

    cout << "\nSeat Number  : "
         << waitingBooking->seatNumber;

    cout << "\nStatus       : "
         << waitingBooking->status;

    cout << "\n========================================\n";
}
else if(wasConfirmed)
{
    cout << "\nNo waiting passengers.";
    cout << "\nThe cancelled seat is now available.\n";
}
else
{
    cout << "\nWaiting list booking cancelled.";
    cout << "\nNo seat was released.\n";
}

    cout << "\n========================================\n";
}
void RailwaySystem::viewRecentActivities()
{
    // Check whether passenger is logged in
    if(currentUserId.empty())
    {
        cout << "\nPlease login first!\n";
        return;
    }

    cout << "\n========================================";
    cout << "\n         PASSENGER ACTIVITIES";
    cout << "\n========================================";

    cout << "\nPassenger Name: " << currentUserName;
    cout << "\nPassenger ID  : " << currentUserId;

    // Display activities using our Stack
    activityStack.displayActivities(currentUserId);
}

bool RailwaySystem::loadActivities()
{
    // Prevent loading the same activities twice
    if(activitiesLoaded)
    {
        return true;
    }

    ifstream file("activities.txt");

    // Create the activity database if it does not exist
    if(!file.is_open())
    {
        ofstream createFile("activities.txt", ios::app);

        if(!createFile.is_open())
        {
            cout << "\nError creating activity database!\n";
            return false;
        }

        createFile.close();

        if(!createFile)
        {
            cout << "\nError initializing activity database!\n";
            return false;
        }

        activitiesLoaded = true;

        cout << "\nActivity database initialized!\n";

        return true;
    }

    string line;

    // First pass: validate records before loading
    while(getline(file, line))
    {
        if(line.empty())
        {
            continue;
        }

        size_t separator = line.find('|');

        if(separator == string::npos ||
           separator == 0 ||
           separator == line.length() - 1 ||
           line.find('|', separator + 1) != string::npos)
        {
            cout << "\nInvalid activity record found!\n";
            return false;
        }
    }

    if(file.bad())
    {
        cout << "\nError reading activity records!\n";
        return false;
    }

    // Return to beginning of file
    file.clear();
    file.seekg(0);

    if(!file)
    {
        cout << "\nError resetting activity file!\n";
        return false;
    }

    // Second pass: insert valid records into Stack
    while(getline(file, line))
    {
        if(line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string passengerId;
        string message;

        getline(ss, passengerId, '|');
        getline(ss, message);

        activityStack.push(passengerId, message);
    }

    if(file.bad())
    {
        cout << "\nError loading activity history!\n";
        return false;
    }

    file.close();

    activitiesLoaded = true;

    cout << "\nActivity history loaded successfully!\n";

    return true;
}
bool RailwaySystem::recordActivity(
    const string& passengerId,
    const string& message)
{
    if(!activitiesLoaded)
    {
        cout << "\nActivity database is unavailable!\n";
        return false;
    }

    // Prevent malformed activity records
    if(passengerId.empty() ||
       message.empty() ||
       passengerId.find('|') != string::npos ||
       message.find('|') != string::npos ||
       message.find('\n') != string::npos ||
       message.find('\r') != string::npos)
    {
        cout << "\nInvalid activity information!\n";
        return false;
    }

    // Save activity permanently
    ofstream file("activities.txt", ios::app);

    if(!file.is_open())
    {
        cout << "\nError opening activity database!\n";
        return false;
    }

    file << passengerId << "|" << message << "\n";

    file.close();

    if(!file)
    {
        cout << "\nError saving activity history!\n";
        return false;
    }

    // Insert into Stack after successful saving
    activityStack.push(passengerId, message);

    return true;
}
// ================= MAIN FUNCTION =================
int main()
{
    RailwaySystem system;

    system.initializeTrains();

    // Load booking records
    if(!system.loadBookings())
    {
        cout << "\nError loading bookings!\n";
    }

    // Load activity records
    if(!system.loadActivities())
    {
        cout << "\nError loading activities!\n";
    }

    system.mainMenu();

    return 0;
}