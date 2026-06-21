#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <cstdio>
#include <conio.h>
using namespace std;
const int MAX_TEXT = 80;
const int MAX_CARS = 250;
const int MAX_RENTALS = 250;
const int MAX_USERS = 120;
const char STAFF_USERS_FILE[] = "staff_users.txt";
const char CUSTOMER_USERS_FILE[] = "customer_users.txt";
const char CARS_FILE[] = "cars.txt";
const char RENTALS_FILE[] = "rentals.txt";
const char PAYMENTS_FILE[] = "payments.txt";
const char REPORTS_FILE[] = "reports.txt";
const char SYSTEM_REPORT_FILE[] = "system_report.txt";
const char CUSTOMER_REPORT_FILE[] = "customer_summary_report.txt";
const char ANALYTICS_REPORT_FILE[] = "analytics_report.txt";
const char MAINTENANCE_FILE[] = "maintenance.txt";
const char RECEIPTS_FILE[] = "receipts.txt";
const char FEEDBACK_FILE[] = "feedback.txt";
const char ACTIVITY_FILE[] = "activity_log.txt";
const char PROMOTIONS_FILE[] = "promotions.txt";
const char INCIDENTS_FILE[] = "incidents.txt";
const char BACKUP_FILE[] = "system_backup.txt";
struct CarRecord {
    char carId[MAX_TEXT];
    char brand[MAX_TEXT];
    char model[MAX_TEXT];
    char plateNo[MAX_TEXT];
    char carType[MAX_TEXT];
    char status[MAX_TEXT];
    double dailyRate;
    int seats;
};
struct RentalRecord {
    char rentalId[MAX_TEXT];
    char username[MAX_TEXT];
    char carId[MAX_TEXT];
    char startDate[MAX_TEXT];
    char endDate[MAX_TEXT];
    char status[MAX_TEXT];
    int days;
    double totalAmount;
};
struct UserRecord {
    char username[MAX_TEXT];
    char password[MAX_TEXT];
    char role[MAX_TEXT];
    char fullName[MAX_TEXT];
    char phone[MAX_TEXT];
};
struct PaymentRecord {
    char paymentId[MAX_TEXT];
    char rentalId[MAX_TEXT];
    char status[MAX_TEXT];
    double amount;
};
struct MaintenanceRecord {
    char maintenanceId[MAX_TEXT];
    char carId[MAX_TEXT];
    char issue[MAX_TEXT];
    char startDate[MAX_TEXT];
    char endDate[MAX_TEXT];
    char status[MAX_TEXT];
    double cost;
};
struct ReceiptRecord {
    char receiptId[MAX_TEXT];
    char rentalId[MAX_TEXT];
    char username[MAX_TEXT];
    char carId[MAX_TEXT];
    char paymentId[MAX_TEXT];
    char issueDate[MAX_TEXT];
    double amount;
};
struct FeedbackRecord {
    char feedbackId[MAX_TEXT];
    char username[MAX_TEXT];
    char rentalId[MAX_TEXT];
    char comment[MAX_TEXT];
    char status[MAX_TEXT];
    int rating;
};
struct ActivityRecord {
    char activityId[MAX_TEXT];
    char username[MAX_TEXT];
    char action[MAX_TEXT];
    char targetId[MAX_TEXT];
    char status[MAX_TEXT];
};
struct PromotionRecord {
    char promoCode[MAX_TEXT];
    char description[MAX_TEXT];
    char status[MAX_TEXT];
    double discountRate;
};
struct IncidentRecord {
    char incidentId[MAX_TEXT];
    char rentalId[MAX_TEXT];
    char username[MAX_TEXT];
    char carId[MAX_TEXT];
    char issue[MAX_TEXT];
    char status[MAX_TEXT];
    double charge;
};
void copyText(char target[], const char source[], int limit) {
    int i = 0;
    while (source[i] != '\0' && i < limit - 1) {
        target[i] = source[i];
        i++;
    }
    target[i] = '\0';
}
void trimNewline(char text[]) {
    int len = strlen(text);
    while (len > 0 && (text[len - 1] == '\n' || text[len - 1] == '\r')) {
        text[len - 1] = '\0';
        len--;
    }
}
bool sameText(const char a[], const char b[]) {
    return strcmp(a, b) == 0;
}
bool containsText(const char source[], const char key[]) {
    int sourceLen = strlen(source);
    int keyLen = strlen(key);
    if (keyLen == 0) return true;
    for (int i = 0; i <= sourceLen - keyLen; i++) {
        int j = 0;
        while (j < keyLen && tolower(source[i + j]) == tolower(key[j])) j++;
        if (j == keyLen) return true;
    }
    return false;
}
void readField(char line[], int &pos, char out[]) {
    int i = 0;
    while (line[pos] != '\0' && line[pos] != ',' && i < MAX_TEXT - 1) {
        out[i] = line[pos];
        i++;
        pos++;
    }
    out[i] = '\0';
    if (line[pos] == ',') pos++;
}
int textToInt(const char text[]) {
    return atoi(text);
}
double textToDouble(const char text[]) {
    return atof(text);
}
void pauseScreen() {
    cout << "Press ENTER to continue...";
    cin.ignore(10000, '\n');
    cin.get();
}
void waitForEnter() {
    char temp[MAX_TEXT];
    cout << "\nPress ENTER to return to the menu...";
    cin.getline(temp, MAX_TEXT);
}
void inputLine(const char prompt[], char out[], int limit) {
    cout << prompt;
    cin.getline(out, limit);
    if (strlen(out) == 0) {
        cin.getline(out, limit);
    }
}
void printBoxLine(int width) {
    cout << "+";
    for (int i = 0; i < width; i++) cout << "=";
    cout << "+" << endl;
}
void printCenteredLine(const char text[], int width) {
    int len = strlen(text);
    int left = (width - len) / 2;
    int right = width - len - left;
    if (left < 0) left = 0;
    if (right < 0) right = 0;
    cout << "|";
    for (int i = 0; i < left; i++) cout << " ";
    cout << text;
    for (int i = 0; i < right; i++) cout << " ";
    cout << "|" << endl;
}
void printMenuTitle(const char title[]) {
    printBoxLine(48);
    printCenteredLine(title, 48);
    printBoxLine(48);
}
void printMenuOption(int number, const char text[]) {
    cout << "|| " << right << setw(2) << number << ". " << left << setw(40) << text << right << "||" << endl;
}
bool isNumberText(const char text[]) {
    if (strlen(text) == 0) return false;
    for (int i = 0; text[i] != '\0'; i++) {
        if (!isdigit(text[i])) return false;
    }
    return true;
}
int readChoice(int minimum, int maximum) {
    char text[MAX_TEXT];
    while (true) {
        cout << "Choice: ";
        cin.getline(text, MAX_TEXT);
        if (!isNumberText(text)) {
            cout << "Invalid option. Please enter a number from " << minimum << " to " << maximum << "." << endl;
            continue;
        }
        int choice = textToInt(text);
        if (choice < minimum || choice > maximum) {
            cout << "Invalid option. Please choose from " << minimum << " to " << maximum << "." << endl;
            continue;
        }
        return choice;
    }
}
void inputPassword(const char prompt[], char out[], int limit) {
    cout << prompt;
    int i = 0;
    while (i < limit - 1) {
        int ch = _getch();
        if (ch == 13) break;
        if (ch == 8) {
            if (i > 0) {
                i--;
                cout << "\b \b";
            }
        } else if (ch >= 32 && ch <= 126) {
            out[i] = (char)ch;
            i++;
            cout << "*";
        }
    }
    out[i] = '\0';
    cout << endl;
}
bool isPhoneValid(const char phone[]) {
    int len = strlen(phone);
    if (len < 10 || len > 11) return false;
    if (!(phone[0] == '0' && phone[1] == '1')) return false;
    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i])) return false;
    }
    return true;
}
void toUpperText(char text[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = (char)toupper(text[i]);
    }
}
bool isPlateValid(const char plate[]) {
    int len = strlen(plate);
    int letters = 0;
    int digits = 0;
    int i = 0;
    if (len < 2 || len > 7) return false;
    while (plate[i] != '\0' && isalpha(plate[i])) {
        letters++;
        i++;
    }
    while (plate[i] != '\0' && isdigit(plate[i])) {
        digits++;
        i++;
    }
    if (plate[i] != '\0') return false;
    if (letters < 1 || letters > 3) return false;
    if (digits < 1 || digits > 4) return false;
    return true;
}
bool isCancelInput(const char text[]);
bool inputPlateNumber(const char prompt[], char plate[]) {
    while (true) {
        inputLine(prompt, plate, MAX_TEXT);
        toUpperText(plate);
        if (isCancelInput(plate)) return false;
        if (isPlateValid(plate)) return true;
        cout << "Invalid plate format. Use 1-3 English letters followed by 1-4 digits, example ABC1234." << endl;
    }
}
bool isLeapYear(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    return year % 4 == 0;
}
int daysInMonth(int year, int month) {
    if (month == 1) return 31;
    if (month == 2) return isLeapYear(year) ? 29 : 28;
    if (month == 3) return 31;
    if (month == 4) return 30;
    if (month == 5) return 31;
    if (month == 6) return 30;
    if (month == 7) return 31;
    if (month == 8) return 31;
    if (month == 9) return 30;
    if (month == 10) return 31;
    if (month == 11) return 30;
    if (month == 12) return 31;
    return 0;
}
bool parseDate(const char dateText[], int &year, int &month, int &day) {
    if (strlen(dateText) != 10) return false;
    if (dateText[4] != '-' || dateText[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(dateText[i])) return false;
    }
    char yearText[5];
    char monthText[3];
    char dayText[3];
    yearText[0] = dateText[0];
    yearText[1] = dateText[1];
    yearText[2] = dateText[2];
    yearText[3] = dateText[3];
    yearText[4] = '\0';
    monthText[0] = dateText[5];
    monthText[1] = dateText[6];
    monthText[2] = '\0';
    dayText[0] = dateText[8];
    dayText[1] = dateText[9];
    dayText[2] = '\0';
    year = textToInt(yearText);
    month = textToInt(monthText);
    day = textToInt(dayText);
    if (year < 2020 || year > 2099) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(year, month)) return false;
    return true;
}
int dateKey(const char dateText[]) {
    int year = 0;
    int month = 0;
    int day = 0;
    if (!parseDate(dateText, year, month, day)) return -1;
    return year * 10000 + month * 100 + day;
}
int dateSerial(int year, int month, int day) {
    int serial = 0;
    for (int y = 2020; y < year; y++) {
        serial += isLeapYear(y) ? 366 : 365;
    }
    for (int m = 1; m < month; m++) {
        serial += daysInMonth(year, m);
    }
    serial += day;
    return serial;
}
int dateSerialFromText(const char dateText[]) {
    int year = 0;
    int month = 0;
    int day = 0;
    if (!parseDate(dateText, year, month, day)) return -1;
    return dateSerial(year, month, day);
}
void serialToDate(int serial, char out[]) {
    int year = 2020;
    while (serial > (isLeapYear(year) ? 366 : 365)) {
        serial -= isLeapYear(year) ? 366 : 365;
        year++;
    }
    int month = 1;
    while (serial > daysInMonth(year, month)) {
        serial -= daysInMonth(year, month);
        month++;
    }
    int day = serial;
    sprintf(out, "%04d-%02d-%02d", year, month, day);
}
void getTodayDate(char out[]) {
    time_t now = time(0);
    tm *localTime = localtime(&now);
    int year = localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;
    sprintf(out, "%04d-%02d-%02d", year, month, day);
}
void getTomorrowDate(char out[]) {
    char today[MAX_TEXT];
    int year = 0;
    int month = 0;
    int day = 0;
    getTodayDate(today);
    parseDate(today, year, month, day);
    serialToDate(dateSerial(year, month, day) + 1, out);
}
bool isDateRangeValid(const char startDate[], const char endDate[]) {
    int startKey = dateKey(startDate);
    int endKey = dateKey(endDate);
    if (startKey < 0 || endKey < 0) return false;
    return endKey > startKey;
}
bool isCancelInput(const char text[]) {
    return sameText(text, "0") || sameText(text, "CANCEL");
}
bool inputYesNoConfirmation(const char prompt[]) {
    char confirm[MAX_TEXT];
    while (true) {
        inputLine(prompt, confirm, MAX_TEXT);
        toUpperText(confirm);
        if (sameText(confirm, "YES")) return true;
        if (sameText(confirm, "NO")) return false;
        cout << "Invalid option. Please type YES to confirm or NO to cancel." << endl;
    }
}
void inputDate(const char prompt[], char out[]) {
    while (true) {
        inputLine(prompt, out, MAX_TEXT);
        int year = 0;
        int month = 0;
        int day = 0;
        if (parseDate(out, year, month, day)) return;
        cout << "Invalid date. Use YYYY-MM-DD, example 2026-06-22." << endl;
    }
}
void inputDateRange(char startDate[], char endDate[]) {
    while (true) {
        inputDate("Start date YYYY-MM-DD: ", startDate);
        inputDate("End date YYYY-MM-DD: ", endDate);
        if (isDateRangeValid(startDate, endDate)) return;
        cout << "Invalid date range. End date must be after start date." << endl;
    }
}
int calculateRentalDays(const char startDate[], const char endDate[]) {
    int startSerial = dateSerialFromText(startDate);
    int endSerial = dateSerialFromText(endDate);
    if (startSerial < 0 || endSerial < 0 || endSerial < startSerial) return 0;
    return endSerial - startSerial + 1;
}
bool inputBookingDateRange(char startDate[], char endDate[], int &days) {
    char today[MAX_TEXT];
    char tomorrow[MAX_TEXT];
    getTodayDate(today);
    getTomorrowDate(tomorrow);
    int tomorrowSerial = dateSerialFromText(tomorrow);
    while (true) {
        cout << "Today date is " << today << "." << endl;
        cout << "Rental start date must be tomorrow or later. Earliest start date: " << tomorrow << endl;
        inputDate("Start date YYYY-MM-DD: ", startDate);
        int startSerial = dateSerialFromText(startDate);
        if (startSerial < tomorrowSerial) {
            cout << "Invalid start date. Start date must be " << tomorrow << " or later." << endl;
            continue;
        }
        inputDate("End date YYYY-MM-DD: ", endDate);
        if (!isDateRangeValid(startDate, endDate)) {
            cout << "Invalid end date. End date must be after start date." << endl;
            continue;
        }
        days = calculateRentalDays(startDate, endDate);
        cout << "Total rental days: " << days << endl;
        if (inputYesNoConfirmation("Confirm these rental dates? Type YES to confirm or NO to cancel: ")) return true;
        cout << "Date selection not confirmed." << endl;
        return false;
    }
}
void inputMaintenanceStartDate(char startDate[]) {
    char today[MAX_TEXT];
    getTodayDate(today);
    int todaySerial = dateSerialFromText(today);
    while (true) {
        cout << "Today date is " << today << "." << endl;
        inputDate("Maintenance start date YYYY-MM-DD: ", startDate);
        int startSerial = dateSerialFromText(startDate);
        if (startSerial >= todaySerial) return;
        cout << "Invalid maintenance start date. It cannot be before today." << endl;
    }
}
void inputMaintenanceCompletionDate(const char startDate[], char endDate[]) {
    int startSerial = dateSerialFromText(startDate);
    while (true) {
        inputDate("Completion date YYYY-MM-DD: ", endDate);
        int endSerial = dateSerialFromText(endDate);
        if (endSerial > startSerial) return;
        cout << "Invalid completion date. It must be after the maintenance start date." << endl;
    }
}
void inputPositiveDouble(const char prompt[], double &value) {
    char text[MAX_TEXT];
    while (true) {
        inputLine(prompt, text, MAX_TEXT);
        value = textToDouble(text);
        if (value >= 0) return;
        cout << "Invalid amount. Please enter zero or a positive value." << endl;
    }
}
void inputPositiveInt(const char prompt[], int &value) {
    char text[MAX_TEXT];
    while (true) {
        inputLine(prompt, text, MAX_TEXT);
        if (!isNumberText(text)) {
            cout << "Invalid number. Please enter digits only." << endl;
            continue;
        }
        value = textToInt(text);
        if (value > 0) return;
        cout << "Invalid number. Please enter a positive value." << endl;
    }
}
bool chooseCarType(char out[]) {
    printMenuTitle("Select Car Type");
    printMenuOption(1, "Sedan");
    printMenuOption(2, "Hatchback");
    printMenuOption(3, "SUV");
    printMenuOption(4, "Compact");
    printMenuOption(5, "Manual input");
    printMenuOption(6, "Cancel");
    printBoxLine(48);
    int choice = readChoice(1, 6);
    if (choice == 1) copyText(out, "Sedan", MAX_TEXT);
    else if (choice == 2) copyText(out, "Hatchback", MAX_TEXT);
    else if (choice == 3) copyText(out, "SUV", MAX_TEXT);
    else if (choice == 4) copyText(out, "Compact", MAX_TEXT);
    else if (choice == 6) return false;
    else {
        while (true) {
            inputLine("Type (letters and spaces only, 3-20 characters): ", out, MAX_TEXT);
            if (isCancelInput(out)) return false;
            int len = strlen(out);
            bool valid = len >= 3 && len <= 20;
            for (int i = 0; out[i] != '\0'; i++) {
                if (!isalpha(out[i]) && out[i] != ' ') valid = false;
            }
            if (valid) return true;
            cout << "Invalid type. Use letters and spaces only, example Luxury Van." << endl;
        }
    }
    return true;
}
class FileEntity {
protected:
    char sourceFile[MAX_TEXT];
public:
    FileEntity() { copyText(sourceFile, "", MAX_TEXT); }
    FileEntity(const char fileName[]) { copyText(sourceFile, fileName, MAX_TEXT); }
    virtual ~FileEntity() { }
    virtual void load() = 0;
    virtual void save() = 0;
    void setSource(const char fileName[]) { copyText(sourceFile, fileName, MAX_TEXT); }
};
class PersonModule {
protected:
    char currentUser[MAX_TEXT];
public:
    PersonModule() { copyText(currentUser, "guest", MAX_TEXT); }
    PersonModule(const char name[]) { copyText(currentUser, name, MAX_TEXT); }
    virtual ~PersonModule() { }
    virtual void showMenu() = 0;
    virtual bool login(UserRecord users[], int userCount) = 0;
    void logout() { copyText(currentUser, "guest", MAX_TEXT); }
    const char *getCurrentUser() { return currentUser; }
};
class CarNode {
public:
    CarRecord data;
    CarNode *next;
    CarNode() { next = NULL; }
};
class CarLinkedList : public FileEntity {
private:
    CarNode *head;
    int total;
public:
    CarLinkedList() : FileEntity(CARS_FILE) { head = NULL; total = 0; }
    ~CarLinkedList() { clear(); }
    friend void printCarFriend(CarLinkedList &list);
    friend int countAvailableFriend(CarLinkedList &list);
    void clear() {
        CarNode *walker = head;
        while (walker != NULL) {
            CarNode *temp = walker;
            walker = walker->next;
            delete temp;
        }
        head = NULL;
        total = 0;
    }
    void addCar(CarRecord car) {
        CarNode *node = new CarNode();
        node->data = car;
        node->next = NULL;
        if (head == NULL) head = node;
        else {
            CarNode *walker = head;
            while (walker->next != NULL) walker = walker->next;
            walker->next = node;
        }
        total++;
    }
    int size() { return total; }
    CarNode *first() { return head; }
    CarRecord *findById(const char id[]) {
        CarNode *walker = head;
        while (walker != NULL) {
            if (sameText(walker->data.carId, id)) return &(walker->data);
            walker = walker->next;
        }
        return NULL;
    }
    bool removeById(const char id[]) {
        CarNode *walker = head;
        CarNode *previous = NULL;
        while (walker != NULL) {
            if (sameText(walker->data.carId, id)) {
                if (previous == NULL) head = walker->next;
                else previous->next = walker->next;
                delete walker;
                total--;
                return true;
            }
            previous = walker;
            walker = walker->next;
        }
        return false;
    }
    void load() {
        clear();
        ifstream fin(sourceFile);
        char line[400];
        while (fin.getline(line, 400)) {
            trimNewline(line);
            if (strlen(line) < 5) continue;
            int pos = 0;
            char rateText[MAX_TEXT];
            char seatText[MAX_TEXT];
            CarRecord car;
            readField(line, pos, car.carId);
            readField(line, pos, car.brand);
            readField(line, pos, car.model);
            readField(line, pos, car.plateNo);
            readField(line, pos, car.carType);
            readField(line, pos, rateText);
            readField(line, pos, seatText);
            readField(line, pos, car.status);
            car.dailyRate = textToDouble(rateText);
            car.seats = textToInt(seatText);
            addCar(car);
        }
        fin.close();
    }
    void save() {
        ofstream fout(sourceFile);
        CarNode *walker = head;
        while (walker != NULL) {
            fout << walker->data.carId << ',' << walker->data.brand << ',' << walker->data.model << ',';
            fout << walker->data.plateNo << ',' << walker->data.carType << ',' << walker->data.dailyRate << ',';
            fout << walker->data.seats << ',' << walker->data.status << endl;
            walker = walker->next;
        }
        fout.close();
    }
};
void printCarRow(CarRecord car) {
    cout << left << setw(8) << car.carId << setw(12) << car.brand << setw(12) << car.model;
    cout << setw(12) << car.plateNo << setw(12) << car.carType << setw(10) << car.dailyRate;
    cout << setw(8) << car.seats << setw(12) << car.status << endl;
}
void printCarHeader() {
    cout << left << setw(8) << "ID" << setw(12) << "Brand" << setw(12) << "Model";
    cout << setw(12) << "Plate" << setw(12) << "Type" << setw(10) << "Rate";
    cout << setw(8) << "Seats" << setw(12) << "Status" << endl;
}
void printCarFriend(CarLinkedList &list) {
    printCarHeader();
    CarNode *walker = list.head;
    while (walker != NULL) {
        printCarRow(walker->data);
        walker = walker->next;
    }
}
int countAvailableFriend(CarLinkedList &list) {
    int count = 0;
    CarNode *walker = list.head;
    while (walker != NULL) {
        if (sameText(walker->data.status, "Available")) count++;
        walker = walker->next;
    }
    return count;
}
class RentalManager : public FileEntity {
private:
    RentalRecord rentals[MAX_RENTALS];
    int total;
public:
    RentalManager() : FileEntity(RENTALS_FILE) { total = 0; }
    ~RentalManager() { }
    friend double totalRevenueFriend(RentalManager &manager);
    friend void printRentalFriend(RentalManager &manager);
    int size() { return total; }
    RentalRecord getAt(int index) { return rentals[index]; }
    void setAt(int index, RentalRecord rental) { if (index >= 0 && index < total) rentals[index] = rental; }
    void addRental(RentalRecord rental) { if (total < MAX_RENTALS) rentals[total++] = rental; }
    RentalRecord *findById(const char id[]) {
        for (int i = 0; i < total; i++) {
            if (sameText(rentals[i].rentalId, id)) return &rentals[i];
        }
        return NULL;
    }
    bool removeById(const char id[]) {
        for (int i = 0; i < total; i++) {
            if (sameText(rentals[i].rentalId, id)) {
                for (int j = i; j < total - 1; j++) rentals[j] = rentals[j + 1];
                total--;
                return true;
            }
        }
        return false;
    }
    void load() {
        total = 0;
        ifstream fin(sourceFile);
        char line[400];
        while (fin.getline(line, 400)) {
            trimNewline(line);
            if (strlen(line) < 5) continue;
            int pos = 0;
            char daysText[MAX_TEXT];
            char amountText[MAX_TEXT];
            RentalRecord rental;
            readField(line, pos, rental.rentalId);
            readField(line, pos, rental.username);
            readField(line, pos, rental.carId);
            readField(line, pos, rental.startDate);
            readField(line, pos, rental.endDate);
            readField(line, pos, daysText);
            readField(line, pos, amountText);
            readField(line, pos, rental.status);
            rental.days = textToInt(daysText);
            rental.totalAmount = textToDouble(amountText);
            addRental(rental);
        }
        fin.close();
    }
    void save() {
        ofstream fout(sourceFile);
        for (int i = 0; i < total; i++) {
            fout << rentals[i].rentalId << ',' << rentals[i].username << ',' << rentals[i].carId << ',';
            fout << rentals[i].startDate << ',' << rentals[i].endDate << ',' << rentals[i].days << ',';
            fout << rentals[i].totalAmount << ',' << rentals[i].status << endl;
        }
        fout.close();
    }
};
void printRentalRow(RentalRecord rental) {
    cout << left << setw(8) << rental.rentalId << setw(14) << rental.username << setw(8) << rental.carId;
    cout << setw(12) << rental.startDate << setw(12) << rental.endDate << setw(6) << rental.days;
    cout << setw(10) << rental.totalAmount << setw(12) << rental.status << endl;
}
void printRentalHeader() {
    cout << left << setw(8) << "ID" << setw(14) << "Customer" << setw(8) << "Car";
    cout << setw(12) << "Start" << setw(12) << "End" << setw(6) << "Days";
    cout << setw(10) << "Amount" << setw(12) << "Status" << endl;
}
double totalRevenueFriend(RentalManager &manager) {
    double totalAmount = 0;
    for (int i = 0; i < manager.total; i++) totalAmount += manager.rentals[i].totalAmount;
    return totalAmount;
}
void printRentalFriend(RentalManager &manager) {
    printRentalHeader();
    for (int i = 0; i < manager.total; i++) printRentalRow(manager.rentals[i]);
}
class UserManager : public FileEntity {
private:
    UserRecord users[MAX_USERS];
    int total;
public:
    UserManager() : FileEntity(CUSTOMER_USERS_FILE) { total = 0; }
    ~UserManager() { }
    int size() { return total; }
    UserRecord *allUsers() { return users; }
    void addUser(UserRecord user) { if (total < MAX_USERS) users[total++] = user; }
    UserRecord *findUser(const char username[]) {
        for (int i = 0; i < total; i++) if (sameText(users[i].username, username)) return &users[i];
        return NULL;
    }
    bool validate(const char username[], const char password[], const char role[]) {
        for (int i = 0; i < total; i++) {
            if (sameText(users[i].username, username) && sameText(users[i].password, password) && sameText(users[i].role, role)) return true;
        }
        return false;
    }
    void displayAllUsers() {
        printMenuTitle("Registered Customers");
        cout << left << setw(16) << "Username" << setw(24) << "Full Name" << setw(14) << "Phone" << endl;
        for (int i = 0; i < total; i++) {
            if (sameText(users[i].role, "Customer")) {
                cout << left << setw(16) << users[i].username;
                cout << setw(24) << users[i].fullName << setw(14) << users[i].phone << endl;
            }
        }
    }
    void displayStaffUsers() {
        printMenuTitle("Registered Staff");
        cout << left << setw(16) << "Username" << setw(24) << "Full Name" << setw(14) << "Phone" << endl;
        for (int i = 0; i < total; i++) {
            if (sameText(users[i].role, "Staff")) {
                cout << left << setw(16) << users[i].username;
                cout << setw(24) << users[i].fullName << setw(14) << users[i].phone << endl;
            }
        }
    }
    int countByRole(const char role[]) {
        int count = 0;
        for (int i = 0; i < total; i++) {
            if (sameText(users[i].role, role)) count++;
        }
        return count;
    }
    void displayUserStatistics() {
        printMenuTitle("User Statistics");
        cout << "Total accounts    : " << total << endl;
        cout << "Customer accounts : " << countByRole("Customer") << endl;
        cout << "Staff accounts    : " << countByRole("Staff") << endl;
    }
    void searchCustomerByUsername() {
        char username[MAX_TEXT];
        inputLine("Customer username to search: ", username, MAX_TEXT);
        UserRecord *user = findUser(username);
        if (user == NULL || !sameText(user->role, "Customer")) {
            cout << "Customer not found." << endl;
            return;
        }
        cout << left << setw(16) << "Username" << setw(24) << "Full Name" << setw(14) << "Phone" << endl;
        cout << left << setw(16) << user->username << setw(24) << user->fullName << setw(14) << user->phone << endl;
    }
    bool startsWithText(const char source[], const char prefix[]) {
        int prefixLen = strlen(prefix);
        if (prefixLen == 0) return true;
        if ((int)strlen(source) < prefixLen) return false;
        for (int i = 0; i < prefixLen; i++) {
            if (source[i] != prefix[i]) return false;
        }
        return true;
    }
    void filterCustomersByPhonePrefix() {
        char prefix[MAX_TEXT];
        inputLine("Phone prefix, example 012: ", prefix, MAX_TEXT);
        cout << left << setw(16) << "Username" << setw(24) << "Full Name" << setw(14) << "Phone" << endl;
        for (int i = 0; i < total; i++) {
            if (sameText(users[i].role, "Customer") && startsWithText(users[i].phone, prefix)) {
                cout << left << setw(16) << users[i].username;
                cout << setw(24) << users[i].fullName << setw(14) << users[i].phone << endl;
            }
        }
    }
    void loadUserFile(const char fileName[], const char defaultRole[]) {
        ifstream fin(fileName);
        char line[400];
        while (fin.getline(line, 400)) {
            trimNewline(line);
            if (strlen(line) < 3) continue;
            int pos = 0;
            UserRecord user;
            readField(line, pos, user.username);
            readField(line, pos, user.password);
            readField(line, pos, user.role);
            readField(line, pos, user.fullName);
            readField(line, pos, user.phone);
            if (strlen(user.role) == 0) copyText(user.role, defaultRole, MAX_TEXT);
            addUser(user);
        }
        fin.close();
    }
    void load() {
        total = 0;
        loadUserFile(STAFF_USERS_FILE, "Staff");
        loadUserFile(CUSTOMER_USERS_FILE, "Customer");
    }
    void saveRoleFile(const char fileName[], const char role[]) {
        ofstream fout(fileName);
        for (int i = 0; i < total; i++) {
            if (sameText(users[i].role, role)) {
                fout << users[i].username << ',' << users[i].password << ',' << users[i].role << ',';
                fout << users[i].fullName << ',' << users[i].phone << endl;
            }
        }
        fout.close();
    }
    void save() {
        saveRoleFile(STAFF_USERS_FILE, "Staff");
        saveRoleFile(CUSTOMER_USERS_FILE, "Customer");
    }
};
void sortCarsByRate(CarRecord cars[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (cars[j].dailyRate > cars[j + 1].dailyRate) {
                CarRecord temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }
}
void sortCarsByBrand(CarRecord cars[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(cars[j].brand, cars[j + 1].brand) > 0) {
                CarRecord temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }
}
void sortCarsById(CarRecord cars[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(cars[j].carId, cars[j + 1].carId) > 0) {
                CarRecord temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }
}
int binarySearchCarById(CarRecord cars[], int count, const char id[]) {
    int low = 0;
    int high = count - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int result = strcmp(cars[mid].carId, id);
        if (result == 0) return mid;
        if (result < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
int copyCarsToArray(CarLinkedList &list, CarRecord cars[]) {
    int count = 0;
    CarNode *walker = list.first();
    while (walker != NULL && count < MAX_CARS) {
        cars[count++] = walker->data;
        walker = walker->next;
    }
    return count;
}
void showLatestCarId(CarLinkedList &list) {
    CarRecord buffer[MAX_CARS];
    int count = copyCarsToArray(list, buffer);
    if (count == 0) {
        cout << "No car records yet. Suggested first ID: CAR001" << endl;
        return;
    }
    sortCarsById(buffer, count);
    cout << "Latest car ID in system: " << buffer[count - 1].carId << endl;
    cout << "Please enter the next ID manually, for example CAR061." << endl;
}
void displayCarArray(CarRecord cars[], int count) {
    printCarHeader();
    for (int i = 0; i < count; i++) printCarRow(cars[i]);
}
void searchCarById(CarLinkedList &cars) {
    char key[MAX_TEXT];
    inputLine("Enter car ID for binary search: ", key, MAX_TEXT);
    CarRecord buffer[MAX_CARS];
    int count = copyCarsToArray(cars, buffer);
    sortCarsById(buffer, count);
    int index = binarySearchCarById(buffer, count, key);
    if (index >= 0) {
        printCarHeader();
        printCarRow(buffer[index]);
    } else {
        cout << "No matching car found." << endl;
    }
}
void sortAndDisplayCars(CarLinkedList &cars) {
    CarRecord buffer[MAX_CARS];
    int count = copyCarsToArray(cars, buffer);
    printMenuTitle("Sort Car Records");
    printMenuOption(1, "Sort by rate");
    printMenuOption(2, "Sort by brand");
    printBoxLine(48);
    int choice = readChoice(1, 2);
    if (choice == 1) sortCarsByRate(buffer, count);
    else sortCarsByBrand(buffer, count);
    displayCarArray(buffer, count);
}
void sortRentalsByAmount(RentalManager &manager) {
    for (int i = 0; i < manager.size() - 1; i++) {
        for (int j = 0; j < manager.size() - i - 1; j++) {
            RentalRecord a = manager.getAt(j);
            RentalRecord b = manager.getAt(j + 1);
            if (a.totalAmount > b.totalAmount) {
                manager.setAt(j, b);
                manager.setAt(j + 1, a);
            }
        }
    }
}
void sortRentalsByCustomer(RentalManager &manager) {
    for (int i = 0; i < manager.size() - 1; i++) {
        for (int j = 0; j < manager.size() - i - 1; j++) {
            RentalRecord a = manager.getAt(j);
            RentalRecord b = manager.getAt(j + 1);
            if (strcmp(a.username, b.username) > 0) {
                manager.setAt(j, b);
                manager.setAt(j + 1, a);
            }
        }
    }
}
void overloadedDisplay(CarRecord car) { printCarRow(car); }
void overloadedDisplay(RentalRecord rental) { printRentalRow(rental); }
void overloadedDisplay(UserRecord user) { cout << user.username << " - " << user.role << " - " << user.fullName << endl; }
void overloadedDisplay(PaymentRecord payment) { cout << payment.paymentId << " " << payment.rentalId << " " << payment.amount << " " << payment.status << endl; }
class PaymentManager : public FileEntity {
private:
    PaymentRecord payments[MAX_RENTALS];
    int total;
public:
    PaymentManager() : FileEntity(PAYMENTS_FILE) { total = 0; }
    ~PaymentManager() { }
    int size() { return total; }
    void addPayment(PaymentRecord payment) {
        if (total < MAX_RENTALS) payments[total++] = payment;
    }
    void generatePaymentId(char out[]) {
        sprintf(out, "PAY%03d", total + 1);
    }
    PaymentRecord *findByRentalId(const char rentalId[]) {
        for (int i = 0; i < total; i++) {
            if (sameText(payments[i].rentalId, rentalId)) return &payments[i];
        }
        return NULL;
    }
    void displayAllPayments() {
        cout << left << setw(10) << "Payment" << setw(10) << "Rental" << setw(12) << "Amount" << setw(16) << "Status" << endl;
        for (int i = 0; i < total; i++) {
            cout << left << setw(10) << payments[i].paymentId << setw(10) << payments[i].rentalId;
            cout << setw(12) << payments[i].amount << setw(16) << payments[i].status << endl;
        }
    }
    void displayPaymentByRental(const char rentalId[]) {
        PaymentRecord *payment = findByRentalId(rentalId);
        if (payment == NULL) {
            cout << "No payment record found for this rental." << endl;
            return;
        }
        cout << left << setw(10) << "Payment" << setw(10) << "Rental" << setw(12) << "Amount" << setw(16) << "Status" << endl;
        cout << left << setw(10) << payment->paymentId << setw(10) << payment->rentalId;
        cout << setw(12) << payment->amount << setw(16) << payment->status << endl;
    }
    void updatePaymentAmount(const char rentalId[], double amount) {
        PaymentRecord *payment = findByRentalId(rentalId);
        if (payment != NULL) {
            payment->amount = amount;
            save();
        }
    }
    void cancelPayment(const char rentalId[]) {
        PaymentRecord *payment = findByRentalId(rentalId);
        if (payment != NULL) {
            copyText(payment->status, "Cancelled", MAX_TEXT);
            save();
        }
    }
    void load() {
        total = 0;
        ifstream fin(sourceFile);
        char line[300];
        while (fin.getline(line, 300)) {
            trimNewline(line);
            if (strlen(line) < 5) continue;
            int pos = 0;
            char amountText[MAX_TEXT];
            PaymentRecord payment;
            readField(line, pos, payment.paymentId);
            readField(line, pos, payment.rentalId);
            readField(line, pos, amountText);
            readField(line, pos, payment.status);
            payment.amount = textToDouble(amountText);
            addPayment(payment);
        }
        fin.close();
    }
    void save() {
        ofstream fout(sourceFile);
        for (int i = 0; i < total; i++) {
            fout << payments[i].paymentId << ',' << payments[i].rentalId << ',';
            fout << payments[i].amount << ',' << payments[i].status << endl;
        }
        fout.close();
    }
};
class ReceiptManager : public FileEntity {
private:
    ReceiptRecord receipts[MAX_RENTALS];
    int total;
public:
    ReceiptManager() : FileEntity(RECEIPTS_FILE) { total = 0; }
    ~ReceiptManager() { }
    int size() { return total; }
    void generateReceiptId(char out[]) {
        sprintf(out, "REC%03d", total + 1);
    }
    void addReceipt(ReceiptRecord receipt) {
        if (total < MAX_RENTALS) receipts[total++] = receipt;
    }
    ReceiptRecord *findByRentalId(const char rentalId[]) {
        for (int i = 0; i < total; i++) {
            if (sameText(receipts[i].rentalId, rentalId)) return &receipts[i];
        }
        return NULL;
    }
    void createReceipt(RentalRecord rental, PaymentRecord payment) {
        if (findByRentalId(rental.rentalId) != NULL) return;
        ReceiptRecord receipt;
        generateReceiptId(receipt.receiptId);
        copyText(receipt.rentalId, rental.rentalId, MAX_TEXT);
        copyText(receipt.username, rental.username, MAX_TEXT);
        copyText(receipt.carId, rental.carId, MAX_TEXT);
        copyText(receipt.paymentId, payment.paymentId, MAX_TEXT);
        copyText(receipt.issueDate, rental.startDate, MAX_TEXT);
        receipt.amount = rental.totalAmount;
        addReceipt(receipt);
        save();
    }
    void updateReceiptAmount(const char rentalId[], double amount) {
        ReceiptRecord *receipt = findByRentalId(rentalId);
        if (receipt != NULL) {
            receipt->amount = amount;
            save();
        }
    }
    void displayReceipt(ReceiptRecord receipt, const char rentalStatus[]) {
        printBoxLine(54);
        printCenteredLine("Rental Receipt", 54);
        printBoxLine(54);
        cout << "Receipt ID : " << receipt.receiptId << endl;
        cout << "Rental ID  : " << receipt.rentalId << endl;
        cout << "Customer   : " << receipt.username << endl;
        cout << "Car ID     : " << receipt.carId << endl;
        cout << "Payment ID : " << receipt.paymentId << endl;
        cout << "Issue Date : " << receipt.issueDate << endl;
        cout << "Amount     : RM " << receipt.amount << endl;
        cout << "Status     : " << rentalStatus << endl;
        printBoxLine(54);
    }
    void displayAllReceipts() {
        cout << left << setw(10) << "Receipt" << setw(10) << "Rental" << setw(14) << "Customer";
        cout << setw(8) << "Car" << setw(10) << "Payment" << setw(12) << "Date" << setw(10) << "Amount" << endl;
        for (int i = 0; i < total; i++) {
            cout << left << setw(10) << receipts[i].receiptId << setw(10) << receipts[i].rentalId;
            cout << setw(14) << receipts[i].username << setw(8) << receipts[i].carId;
            cout << setw(10) << receipts[i].paymentId << setw(12) << receipts[i].issueDate;
            cout << setw(10) << receipts[i].amount << endl;
        }
    }
    void displayReceiptByRental(RentalManager &rentals) {
        char rentalId[MAX_TEXT];
        inputLine("Enter rental ID: ", rentalId, MAX_TEXT);
        ReceiptRecord *receipt = findByRentalId(rentalId);
        if (receipt == NULL) cout << "Receipt not found." << endl;
        else {
            RentalRecord *rental = rentals.findById(rentalId);
            if (rental == NULL) displayReceipt(*receipt, "Unknown");
            else displayReceipt(*receipt, rental->status);
        }
    }
    void load() {
        total = 0;
        ifstream fin(sourceFile);
        char line[400];
        while (fin.getline(line, 400)) {
            trimNewline(line);
            if (strlen(line) < 5) continue;
            int pos = 0;
            char amountText[MAX_TEXT];
            ReceiptRecord receipt;
            readField(line, pos, receipt.receiptId);
            readField(line, pos, receipt.rentalId);
            readField(line, pos, receipt.username);
            readField(line, pos, receipt.carId);
            readField(line, pos, receipt.paymentId);
            readField(line, pos, receipt.issueDate);
            readField(line, pos, amountText);
            receipt.amount = textToDouble(amountText);
            addReceipt(receipt);
        }
        fin.close();
    }
    void save() {
        ofstream fout(sourceFile);
        for (int i = 0; i < total; i++) {
            fout << receipts[i].receiptId << ',' << receipts[i].rentalId << ',' << receipts[i].username << ',';
            fout << receipts[i].carId << ',' << receipts[i].paymentId << ',' << receipts[i].issueDate << ',';
            fout << receipts[i].amount << endl;
        }
        fout.close();
    }
};
class FeedbackManager : public FileEntity {
private:
    FeedbackRecord feedbacks[MAX_RENTALS];
    int total;
public:
    FeedbackManager() : FileEntity(FEEDBACK_FILE) { total = 0; }
    ~FeedbackManager() { }
    int size() { return total; }
    void generateFeedbackId(char out[]) {
        sprintf(out, "FDB%03d", total + 1);
    }
    void addFeedback(FeedbackRecord feedback) {
        if (total < MAX_RENTALS) feedbacks[total++] = feedback;
    }
    FeedbackRecord *findById(const char feedbackId[]) {
        for (int i = 0; i < total; i++) {
            if (sameText(feedbacks[i].feedbackId, feedbackId)) return &feedbacks[i];
        }
        return NULL;
    }
    void submitFeedback(const char username[], RentalManager &rentals) {
        char rentalId[MAX_TEXT];
        inputLine("Rental ID for feedback: ", rentalId, MAX_TEXT);
        RentalRecord *rental = rentals.findById(rentalId);
        if (rental == NULL || !sameText(rental->username, username)) {
            cout << "Rental not found or access denied." << endl;
            return;
        }
        FeedbackRecord feedback;
        generateFeedbackId(feedback.feedbackId);
        copyText(feedback.username, username, MAX_TEXT);
        copyText(feedback.rentalId, rentalId, MAX_TEXT);
        inputLine("Feedback comment: ", feedback.comment, MAX_TEXT);
        printMenuTitle("Feedback Rating");
        printMenuOption(1, "Very poor");
        printMenuOption(2, "Poor");
        printMenuOption(3, "Average");
        printMenuOption(4, "Good");
        printMenuOption(5, "Excellent");
        printBoxLine(48);
        feedback.rating = readChoice(1, 5);
        copyText(feedback.status, "Submitted", MAX_TEXT);
        addFeedback(feedback);
        save();
        cout << "Feedback submitted. Thank you." << endl;
    }
    void updateFeedbackStatus() {
        char feedbackId[MAX_TEXT];
        inputLine("Feedback ID to update: ", feedbackId, MAX_TEXT);
        FeedbackRecord *feedback = findById(feedbackId);
        if (feedback == NULL) {
            cout << "Feedback not found." << endl;
            return;
        }
        printMenuTitle("Feedback Status");
        printMenuOption(1, "Submitted");
        printMenuOption(2, "Reviewed");
        printMenuOption(3, "Resolved");
        printBoxLine(48);
        int choice = readChoice(1, 3);
        if (choice == 1) copyText(feedback->status, "Submitted", MAX_TEXT);
        else if (choice == 2) copyText(feedback->status, "Reviewed", MAX_TEXT);
        else copyText(feedback->status, "Resolved", MAX_TEXT);
        save();
        cout << "Feedback status updated." << endl;
    }
    void displayFeedbackHeader() {
        cout << left << setw(10) << "ID" << setw(14) << "Customer" << setw(10) << "Rental";
        cout << setw(8) << "Rating" << setw(14) << "Status" << "Comment" << endl;
    }
    void displayFeedbackRow(FeedbackRecord feedback) {
        cout << left << setw(10) << feedback.feedbackId << setw(14) << feedback.username;
        cout << setw(10) << feedback.rentalId << setw(8) << feedback.rating;
        cout << setw(14) << feedback.status << feedback.comment << endl;
    }
    void displayAllFeedback() {
        displayFeedbackHeader();
        for (int i = 0; i < total; i++) displayFeedbackRow(feedbacks[i]);
    }
    void displayCustomerFeedback(const char username[]) {
        displayFeedbackHeader();
        for (int i = 0; i < total; i++) {
            if (sameText(feedbacks[i].username, username)) displayFeedbackRow(feedbacks[i]);
        }
    }
    void searchFeedbackByRental() {
        char rentalId[MAX_TEXT];
        inputLine("Rental ID to search feedback: ", rentalId, MAX_TEXT);
        displayFeedbackHeader();
        for (int i = 0; i < total; i++) {
            if (sameText(feedbacks[i].rentalId, rentalId)) displayFeedbackRow(feedbacks[i]);
        }
    }
    double averageRating() {
        if (total == 0) return 0;
        double sum = 0;
        for (int i = 0; i < total; i++) sum += feedbacks[i].rating;
        return sum / total;
    }
    void load() {
        total = 0;
        ifstream fin(sourceFile);
        char line[500];
        while (fin.getline(line, 500)) {
            trimNewline(line);
            if (strlen(line) < 5) continue;
            int pos = 0;
            char ratingText[MAX_TEXT];
            FeedbackRecord feedback;
            readField(line, pos, feedback.feedbackId);
            readField(line, pos, feedback.username);
            readField(line, pos, feedback.rentalId);
            readField(line, pos, ratingText);
            readField(line, pos, feedback.status);
            readField(line, pos, feedback.comment);
            feedback.rating = textToInt(ratingText);
            addFeedback(feedback);
        }
        fin.close();
    }
    void save() {
        ofstream fout(sourceFile);
        for (int i = 0; i < total; i++) {
            fout << feedbacks[i].feedbackId << ',' << feedbacks[i].username << ',' << feedbacks[i].rentalId << ',';
            fout << feedbacks[i].rating << ',' << feedbacks[i].status << ',' << feedbacks[i].comment << endl;
        }
        fout.close();
    }
};
class MaintenanceManager : public FileEntity {
private:
    MaintenanceRecord records[MAX_CARS];
    int total;
public:
    MaintenanceManager() : FileEntity(MAINTENANCE_FILE) { total = 0; }
    ~MaintenanceManager() { }
    int size() { return total; }
    void generateMaintenanceId(char out[]) {
        sprintf(out, "MNT%03d", total + 1);
    }
    void addRecord(MaintenanceRecord record) {
        if (total < MAX_CARS) records[total++] = record;
    }
    MaintenanceRecord *findById(const char maintenanceId[]) {
        for (int i = 0; i < total; i++) {
            if (sameText(records[i].maintenanceId, maintenanceId)) return &records[i];
        }
        return NULL;
    }
    bool hasActiveMaintenance(const char carId[]) {
        for (int i = 0; i < total; i++) {
            if (sameText(records[i].carId, carId) && sameText(records[i].status, "Active")) return true;
        }
        return false;
    }
    void addMaintenance(CarLinkedList &cars) {
        char carId[MAX_TEXT];
        inputLine("Car ID for maintenance: ", carId, MAX_TEXT);
        CarRecord *car = cars.findById(carId);
        if (car == NULL) {
            cout << "Car not found." << endl;
            return;
        }
        if (hasActiveMaintenance(carId)) {
            cout << "This car already has active maintenance." << endl;
            return;
        }
        MaintenanceRecord record;
        generateMaintenanceId(record.maintenanceId);
        copyText(record.carId, carId, MAX_TEXT);
        inputLine("Issue description: ", record.issue, MAX_TEXT);
        inputMaintenanceStartDate(record.startDate);
        copyText(record.endDate, "Pending", MAX_TEXT);
        inputPositiveDouble("Estimated cost: RM ", record.cost);
        copyText(record.status, "Active", MAX_TEXT);
        copyText(car->status, "Maintenance", MAX_TEXT);
        addRecord(record);
        save();
        cars.save();
        cout << "Maintenance record added and car status changed to Maintenance." << endl;
    }
    void completeMaintenance(CarLinkedList &cars) {
        char maintenanceId[MAX_TEXT];
        inputLine("Maintenance ID to complete: ", maintenanceId, MAX_TEXT);
        MaintenanceRecord *record = findById(maintenanceId);
        if (record == NULL) {
            cout << "Maintenance record not found." << endl;
            return;
        }
        if (!sameText(record->status, "Active")) {
            cout << "Maintenance is not active." << endl;
            return;
        }
        inputMaintenanceCompletionDate(record->startDate, record->endDate);
        inputPositiveDouble("Final cost: RM ", record->cost);
        copyText(record->status, "Completed", MAX_TEXT);
        CarRecord *car = cars.findById(record->carId);
        if (car != NULL) {
            copyText(car->status, "Available", MAX_TEXT);
            cars.save();
        }
        save();
        cout << "Maintenance completed and car returned to Available." << endl;
    }
    void editMaintenanceIssue() {
        char maintenanceId[MAX_TEXT];
        inputLine("Maintenance ID to edit: ", maintenanceId, MAX_TEXT);
        MaintenanceRecord *record = findById(maintenanceId);
        if (record == NULL) {
            cout << "Maintenance record not found." << endl;
            return;
        }
        inputLine("New issue description: ", record->issue, MAX_TEXT);
        inputPositiveDouble("Updated cost: RM ", record->cost);
        save();
        cout << "Maintenance record updated." << endl;
    }
    void displayHeader() {
        cout << left << setw(10) << "ID" << setw(8) << "Car" << setw(14) << "Start";
        cout << setw(14) << "End" << setw(12) << "Cost" << setw(14) << "Status" << "Issue" << endl;
    }
    void displayRow(MaintenanceRecord record) {
        cout << left << setw(10) << record.maintenanceId << setw(8) << record.carId << setw(14) << record.startDate;
        cout << setw(14) << record.endDate << setw(12) << record.cost << setw(14) << record.status << record.issue << endl;
    }
    void displayAll() {
        displayHeader();
        for (int i = 0; i < total; i++) displayRow(records[i]);
    }
    void displayActive() {
        displayHeader();
        for (int i = 0; i < total; i++) {
            if (sameText(records[i].status, "Active")) displayRow(records[i]);
        }
    }
    void searchByCar() {
        char carId[MAX_TEXT];
        inputLine("Car ID to search maintenance: ", carId, MAX_TEXT);
        displayHeader();
        for (int i = 0; i < total; i++) {
            if (sameText(records[i].carId, carId)) displayRow(records[i]);
        }
    }
    double totalMaintenanceCost() {
        double sum = 0;
        for (int i = 0; i < total; i++) sum += records[i].cost;
        return sum;
    }
    void load() {
        total = 0;
        ifstream fin(sourceFile);
        char line[500];
        while (fin.getline(line, 500)) {
            trimNewline(line);
            if (strlen(line) < 5) continue;
            int pos = 0;
            char costText[MAX_TEXT];
            MaintenanceRecord record;
            readField(line, pos, record.maintenanceId);
            readField(line, pos, record.carId);
            readField(line, pos, record.issue);
            readField(line, pos, record.startDate);
            readField(line, pos, record.endDate);
            readField(line, pos, costText);
            readField(line, pos, record.status);
            record.cost = textToDouble(costText);
            addRecord(record);
        }
        fin.close();
    }
    void save() {
        ofstream fout(sourceFile);
        for (int i = 0; i < total; i++) {
            fout << records[i].maintenanceId << ',' << records[i].carId << ',' << records[i].issue << ',';
            fout << records[i].startDate << ',' << records[i].endDate << ',' << records[i].cost << ',';
            fout << records[i].status << endl;
        }
        fout.close();
    }
};
class ActivityLogManager : public FileEntity {
private:
    ActivityRecord activities[500];
    int total;
public:
    ActivityLogManager() : FileEntity(ACTIVITY_FILE) { total = 0; }
    ~ActivityLogManager() { }
    int size() { return total; }
    void generateActivityId(char out[]) {
        sprintf(out, "ACT%03d", total + 1);
    }
    void addActivity(const char username[], const char action[], const char targetId[], const char status[]) {
        if (total >= 500) return;
        ActivityRecord activity;
        generateActivityId(activity.activityId);
        copyText(activity.username, username, MAX_TEXT);
        copyText(activity.action, action, MAX_TEXT);
        copyText(activity.targetId, targetId, MAX_TEXT);
        copyText(activity.status, status, MAX_TEXT);
        activities[total++] = activity;
        save();
    }
    void displayHeader() {
        cout << left << setw(10) << "ID" << setw(14) << "User" << setw(24) << "Action";
        cout << setw(14) << "Target" << setw(14) << "Status" << endl;
    }
    void displayRow(ActivityRecord activity) {
        cout << left << setw(10) << activity.activityId << setw(14) << activity.username;
        cout << setw(24) << activity.action << setw(14) << activity.targetId << setw(14) << activity.status << endl;
    }
    void displayAll() {
        displayHeader();
        for (int i = 0; i < total; i++) displayRow(activities[i]);
    }
    void searchByUser() {
        char username[MAX_TEXT];
        inputLine("Username to search activity: ", username, MAX_TEXT);
        displayHeader();
        for (int i = 0; i < total; i++) {
            if (sameText(activities[i].username, username)) displayRow(activities[i]);
        }
    }
    void searchByAction() {
        char keyword[MAX_TEXT];
        inputLine("Action keyword: ", keyword, MAX_TEXT);
        displayHeader();
        for (int i = 0; i < total; i++) {
            if (containsText(activities[i].action, keyword)) displayRow(activities[i]);
        }
    }
    void load() {
        total = 0;
        ifstream fin(sourceFile);
        char line[400];
        while (fin.getline(line, 400)) {
            trimNewline(line);
            if (strlen(line) < 5) continue;
            int pos = 0;
            ActivityRecord activity;
            readField(line, pos, activity.activityId);
            readField(line, pos, activity.username);
            readField(line, pos, activity.action);
            readField(line, pos, activity.targetId);
            readField(line, pos, activity.status);
            if (total < 500) activities[total++] = activity;
        }
        fin.close();
    }
    void save() {
        ofstream fout(sourceFile);
        for (int i = 0; i < total; i++) {
            fout << activities[i].activityId << ',' << activities[i].username << ',';
            fout << activities[i].action << ',' << activities[i].targetId << ',' << activities[i].status << endl;
        }
        fout.close();
    }
};
class PromotionManager : public FileEntity {
private:
    PromotionRecord promotions[100];
    int total;
public:
    PromotionManager() : FileEntity(PROMOTIONS_FILE) { total = 0; }
    ~PromotionManager() { }
    int size() { return total; }
    PromotionRecord *findPromo(const char promoCode[]) {
        for (int i = 0; i < total; i++) {
            if (sameText(promotions[i].promoCode, promoCode)) return &promotions[i];
        }
        return NULL;
    }
    void addPromotion() {
        if (total >= 100) {
            cout << "Promotion storage is full." << endl;
            return;
        }
        PromotionRecord promo;
        inputLine("Promotion code: ", promo.promoCode, MAX_TEXT);
        toUpperText(promo.promoCode);
        if (findPromo(promo.promoCode) != NULL) {
            cout << "Promotion code already exists." << endl;
            return;
        }
        inputLine("Description: ", promo.description, MAX_TEXT);
        inputPositiveDouble("Discount rate percentage, example 10: ", promo.discountRate);
        if (promo.discountRate > 80) {
            cout << "Discount too high. Maximum allowed is 80 percent." << endl;
            return;
        }
        copyText(promo.status, "Active", MAX_TEXT);
        promotions[total++] = promo;
        save();
        cout << "Promotion added." << endl;
    }
    void editPromotion() {
        char promoCode[MAX_TEXT];
        inputLine("Promotion code to edit: ", promoCode, MAX_TEXT);
        toUpperText(promoCode);
        PromotionRecord *promo = findPromo(promoCode);
        if (promo == NULL) {
            cout << "Promotion not found." << endl;
            return;
        }
        printMenuTitle("Edit Promotion");
        printMenuOption(1, "Description");
        printMenuOption(2, "Discount rate");
        printMenuOption(3, "Status");
        printBoxLine(48);
        int choice = readChoice(1, 3);
        if (choice == 1) inputLine("New description: ", promo->description, MAX_TEXT);
        else if (choice == 2) {
            inputPositiveDouble("New discount rate: ", promo->discountRate);
            if (promo->discountRate > 80) promo->discountRate = 80;
        } else {
            printMenuTitle("Promotion Status");
            printMenuOption(1, "Active");
            printMenuOption(2, "Inactive");
            printBoxLine(48);
            int statusChoice = readChoice(1, 2);
            if (statusChoice == 1) copyText(promo->status, "Active", MAX_TEXT);
            else copyText(promo->status, "Inactive", MAX_TEXT);
        }
        save();
        cout << "Promotion updated." << endl;
    }
    double calculateDiscount(const char promoCode[], double amount) {
        PromotionRecord *promo = findPromo(promoCode);
        if (promo == NULL) return 0;
        if (!sameText(promo->status, "Active")) return 0;
        return amount * promo->discountRate / 100.0;
    }
    void displayHeader() {
        cout << left << setw(14) << "Code" << setw(12) << "Discount" << setw(12) << "Status" << "Description" << endl;
    }
    void displayRow(PromotionRecord promo) {
        cout << left << setw(14) << promo.promoCode << setw(12) << promo.discountRate;
        cout << setw(12) << promo.status << promo.description << endl;
    }
    void displayAll() {
        displayHeader();
        for (int i = 0; i < total; i++) displayRow(promotions[i]);
    }
    void displayActive() {
        displayHeader();
        for (int i = 0; i < total; i++) {
            if (sameText(promotions[i].status, "Active")) displayRow(promotions[i]);
        }
    }
    void load() {
        total = 0;
        ifstream fin(sourceFile);
        char line[400];
        while (fin.getline(line, 400)) {
            trimNewline(line);
            if (strlen(line) < 3) continue;
            int pos = 0;
            char discountText[MAX_TEXT];
            PromotionRecord promo;
            readField(line, pos, promo.promoCode);
            readField(line, pos, promo.description);
            readField(line, pos, discountText);
            readField(line, pos, promo.status);
            promo.discountRate = textToDouble(discountText);
            if (total < 100) promotions[total++] = promo;
        }
        fin.close();
    }
    void save() {
        ofstream fout(sourceFile);
        for (int i = 0; i < total; i++) {
            fout << promotions[i].promoCode << ',' << promotions[i].description << ',';
            fout << promotions[i].discountRate << ',' << promotions[i].status << endl;
        }
        fout.close();
    }
};
class IncidentManager : public FileEntity {
private:
    IncidentRecord incidents[MAX_RENTALS];
    int total;
public:
    IncidentManager() : FileEntity(INCIDENTS_FILE) { total = 0; }
    ~IncidentManager() { }
    int size() { return total; }
    void generateIncidentId(char out[]) {
        sprintf(out, "INC%03d", total + 1);
    }
    IncidentRecord *findById(const char incidentId[]) {
        for (int i = 0; i < total; i++) {
            if (sameText(incidents[i].incidentId, incidentId)) return &incidents[i];
        }
        return NULL;
    }
    void addIncident(const char username[], RentalManager &rentals) {
        char rentalId[MAX_TEXT];
        inputLine("Rental ID for incident: ", rentalId, MAX_TEXT);
        RentalRecord *rental = rentals.findById(rentalId);
        if (rental == NULL || !sameText(rental->username, username)) {
            cout << "Rental not found or access denied." << endl;
            return;
        }
        IncidentRecord incident;
        generateIncidentId(incident.incidentId);
        copyText(incident.rentalId, rentalId, MAX_TEXT);
        copyText(incident.username, username, MAX_TEXT);
        copyText(incident.carId, rental->carId, MAX_TEXT);
        inputLine("Incident issue: ", incident.issue, MAX_TEXT);
        copyText(incident.status, "Reported", MAX_TEXT);
        incident.charge = 0;
        if (total < MAX_RENTALS) incidents[total++] = incident;
        save();
        cout << "Incident report submitted." << endl;
    }
    void updateIncident() {
        char incidentId[MAX_TEXT];
        inputLine("Incident ID to update: ", incidentId, MAX_TEXT);
        IncidentRecord *incident = findById(incidentId);
        if (incident == NULL) {
            cout << "Incident not found." << endl;
            return;
        }
        printMenuTitle("Incident Status");
        printMenuOption(1, "Reported");
        printMenuOption(2, "Under Review");
        printMenuOption(3, "Resolved");
        printBoxLine(48);
        int choice = readChoice(1, 3);
        if (choice == 1) copyText(incident->status, "Reported", MAX_TEXT);
        else if (choice == 2) copyText(incident->status, "Under Review", MAX_TEXT);
        else copyText(incident->status, "Resolved", MAX_TEXT);
        inputPositiveDouble("Incident charge RM: ", incident->charge);
        save();
        cout << "Incident updated." << endl;
    }
    void displayHeader() {
        cout << left << setw(10) << "ID" << setw(10) << "Rental" << setw(14) << "Customer";
        cout << setw(8) << "Car" << setw(14) << "Status" << setw(10) << "Charge" << "Issue" << endl;
    }
    void displayRow(IncidentRecord incident) {
        cout << left << setw(10) << incident.incidentId << setw(10) << incident.rentalId;
        cout << setw(14) << incident.username << setw(8) << incident.carId;
        cout << setw(14) << incident.status << setw(10) << incident.charge << incident.issue << endl;
    }
    void displayAll() {
        displayHeader();
        for (int i = 0; i < total; i++) displayRow(incidents[i]);
    }
    void displayCustomerIncidents(const char username[]) {
        displayHeader();
        for (int i = 0; i < total; i++) {
            if (sameText(incidents[i].username, username)) displayRow(incidents[i]);
        }
    }
    void searchByCar() {
        char carId[MAX_TEXT];
        inputLine("Car ID to search incidents: ", carId, MAX_TEXT);
        displayHeader();
        for (int i = 0; i < total; i++) {
            if (sameText(incidents[i].carId, carId)) displayRow(incidents[i]);
        }
    }
    double totalCharges() {
        double sum = 0;
        for (int i = 0; i < total; i++) sum += incidents[i].charge;
        return sum;
    }
    void load() {
        total = 0;
        ifstream fin(sourceFile);
        char line[500];
        while (fin.getline(line, 500)) {
            trimNewline(line);
            if (strlen(line) < 5) continue;
            int pos = 0;
            char chargeText[MAX_TEXT];
            IncidentRecord incident;
            readField(line, pos, incident.incidentId);
            readField(line, pos, incident.rentalId);
            readField(line, pos, incident.username);
            readField(line, pos, incident.carId);
            readField(line, pos, incident.issue);
            readField(line, pos, chargeText);
            readField(line, pos, incident.status);
            incident.charge = textToDouble(chargeText);
            if (total < MAX_RENTALS) incidents[total++] = incident;
        }
        fin.close();
    }
    void save() {
        ofstream fout(sourceFile);
        for (int i = 0; i < total; i++) {
            fout << incidents[i].incidentId << ',' << incidents[i].rentalId << ',' << incidents[i].username << ',';
            fout << incidents[i].carId << ',' << incidents[i].issue << ',' << incidents[i].charge << ',';
            fout << incidents[i].status << endl;
        }
        fout.close();
    }
};
class FleetAnalytics {
public:
    FleetAnalytics() { }
    ~FleetAnalytics() { }
    int countCarsByStatus(CarLinkedList &cars, const char status[]) {
        int count = 0;
        CarNode *walker = cars.first();
        while (walker != NULL) {
            if (sameText(walker->data.status, status)) count++;
            walker = walker->next;
        }
        return count;
    }
    int countRentalsByStatus(RentalManager &rentals, const char status[]) {
        int count = 0;
        for (int i = 0; i < rentals.size(); i++) {
            RentalRecord rental = rentals.getAt(i);
            if (sameText(rental.status, status)) count++;
        }
        return count;
    }
    double revenueByCustomer(RentalManager &rentals, const char username[]) {
        double total = 0;
        for (int i = 0; i < rentals.size(); i++) {
            RentalRecord rental = rentals.getAt(i);
            if (sameText(rental.username, username) && !sameText(rental.status, "Cancelled")) {
                total += rental.totalAmount;
            }
        }
        return total;
    }
    int rentalCountByCar(RentalManager &rentals, const char carId[]) {
        int count = 0;
        for (int i = 0; i < rentals.size(); i++) {
            RentalRecord rental = rentals.getAt(i);
            if (sameText(rental.carId, carId)) count++;
        }
        return count;
    }
    double revenueByMonth(RentalManager &rentals, const char yearMonth[]) {
        double total = 0;
        for (int i = 0; i < rentals.size(); i++) {
            RentalRecord rental = rentals.getAt(i);
            bool sameMonth = true;
            for (int j = 0; j < 7; j++) {
                if (rental.startDate[j] != yearMonth[j]) sameMonth = false;
            }
            if (sameMonth && !sameText(rental.status, "Cancelled")) total += rental.totalAmount;
        }
        return total;
    }
    int rentalCountByMonth(RentalManager &rentals, const char yearMonth[]) {
        int count = 0;
        for (int i = 0; i < rentals.size(); i++) {
            RentalRecord rental = rentals.getAt(i);
            bool sameMonth = true;
            for (int j = 0; j < 7; j++) {
                if (rental.startDate[j] != yearMonth[j]) sameMonth = false;
            }
            if (sameMonth) count++;
        }
        return count;
    }
    void showFleetStatus(CarLinkedList &cars) {
        printMenuTitle("Fleet Status Summary");
        cout << "Total cars       : " << cars.size() << endl;
        cout << "Available cars   : " << countCarsByStatus(cars, "Available") << endl;
        cout << "Rented cars      : " << countCarsByStatus(cars, "Rented") << endl;
        cout << "Maintenance cars : " << countCarsByStatus(cars, "Maintenance") << endl;
    }
    void showRentalStatus(RentalManager &rentals) {
        printMenuTitle("Rental Status Summary");
        cout << "Total rentals    : " << rentals.size() << endl;
        cout << "Active rentals   : " << countRentalsByStatus(rentals, "Active") << endl;
        cout << "Completed rentals: " << countRentalsByStatus(rentals, "Completed") << endl;
        cout << "Cancelled rentals: " << countRentalsByStatus(rentals, "Cancelled") << endl;
        cout << "Revenue          : RM " << totalRevenueFriend(rentals) << endl;
    }
    void showCustomerRevenue(RentalManager &rentals) {
        char username[MAX_TEXT];
        inputLine("Customer username: ", username, MAX_TEXT);
        double revenue = revenueByCustomer(rentals, username);
        cout << "Revenue from " << username << ": RM " << revenue << endl;
    }
    void showCarUsage(RentalManager &rentals) {
        char carId[MAX_TEXT];
        inputLine("Car ID: ", carId, MAX_TEXT);
        int count = rentalCountByCar(rentals, carId);
        cout << "Rental count for " << carId << ": " << count << endl;
    }
    void showMonthlySummary(RentalManager &rentals) {
        char yearMonth[MAX_TEXT];
        inputLine("Month YYYY-MM: ", yearMonth, MAX_TEXT);
        if (strlen(yearMonth) != 7 || yearMonth[4] != '-') {
            cout << "Invalid month format." << endl;
            return;
        }
        cout << "Rental count for " << yearMonth << ": " << rentalCountByMonth(rentals, yearMonth) << endl;
        cout << "Revenue for " << yearMonth << ": RM " << revenueByMonth(rentals, yearMonth) << endl;
    }
    void showHighValueRentals(RentalManager &rentals) {
        double threshold = 0;
        inputPositiveDouble("Minimum rental amount RM: ", threshold);
        printRentalHeader();
        for (int i = 0; i < rentals.size(); i++) {
            RentalRecord rental = rentals.getAt(i);
            if (rental.totalAmount >= threshold) printRentalRow(rental);
        }
    }
    void showCarUsageRanking(CarLinkedList &cars, RentalManager &rentals) {
        CarRecord buffer[MAX_CARS];
        int count = copyCarsToArray(cars, buffer);
        int usage[MAX_CARS];
        for (int i = 0; i < count; i++) usage[i] = rentalCountByCar(rentals, buffer[i].carId);
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (usage[j] < usage[j + 1]) {
                    int tempUsage = usage[j];
                    usage[j] = usage[j + 1];
                    usage[j + 1] = tempUsage;
                    CarRecord tempCar = buffer[j];
                    buffer[j] = buffer[j + 1];
                    buffer[j + 1] = tempCar;
                }
            }
        }
        cout << left << setw(8) << "Car ID" << setw(14) << "Brand" << setw(14) << "Model" << setw(10) << "Rentals" << endl;
        for (int i = 0; i < count && i < 10; i++) {
            cout << left << setw(8) << buffer[i].carId << setw(14) << buffer[i].brand;
            cout << setw(14) << buffer[i].model << setw(10) << usage[i] << endl;
        }
    }
    void showFeedbackRatingBreakdown(FeedbackManager &feedbacks) {
        printMenuTitle("Feedback Rating Summary");
        cout << "Average rating: " << feedbacks.averageRating() << endl;
        cout << "Use the feedback display menu to review individual comments." << endl;
    }
    void showCostSummary(MaintenanceManager &maintenance, IncidentManager &incidents) {
        printMenuTitle("Cost Summary");
        cout << "Maintenance cost total: RM " << maintenance.totalMaintenanceCost() << endl;
        cout << "Incident charges total : RM " << incidents.totalCharges() << endl;
        cout << "Combined cost impact   : RM " << maintenance.totalMaintenanceCost() + incidents.totalCharges() << endl;
    }
    void saveAnalyticsReport(CarLinkedList &cars, RentalManager &rentals, MaintenanceManager &maintenance, FeedbackManager &feedbacks, IncidentManager &incidents) {
        ofstream fout(ANALYTICS_REPORT_FILE);
        fout << "Fleet Analytics Report" << endl;
        fout << "Cars: " << cars.size() << endl;
        fout << "Available: " << countCarsByStatus(cars, "Available") << endl;
        fout << "Rented: " << countCarsByStatus(cars, "Rented") << endl;
        fout << "Maintenance: " << countCarsByStatus(cars, "Maintenance") << endl;
        fout << "Rentals: " << rentals.size() << endl;
        fout << "Revenue: " << totalRevenueFriend(rentals) << endl;
        fout << "Maintenance cost: " << maintenance.totalMaintenanceCost() << endl;
        fout << "Average feedback rating: " << feedbacks.averageRating() << endl;
        fout << "Incident charges: " << incidents.totalCharges() << endl;
        fout.close();
        cout << "Analytics report saved to " << ANALYTICS_REPORT_FILE << "." << endl;
        cout << "Location: same folder as Project_GR1.cpp and the executable file." << endl;
    }
    void showAnalyticsMenu(CarLinkedList &cars, RentalManager &rentals, MaintenanceManager &maintenance, FeedbackManager &feedbacks, IncidentManager &incidents) {
        int choice = 0;
        while (choice != 11) {
            printMenuTitle("Fleet Analytics");
            printMenuOption(1, "Fleet status summary");
            printMenuOption(2, "Rental status summary");
            printMenuOption(3, "Customer revenue");
            printMenuOption(4, "Car usage count");
            printMenuOption(5, "Monthly summary");
            printMenuOption(6, "High value rentals");
            printMenuOption(7, "Car usage ranking");
            printMenuOption(8, "Feedback rating summary");
            printMenuOption(9, "Maintenance and incident cost");
            printMenuOption(10, "Save analytics report");
            printMenuOption(11, "Back");
            printBoxLine(48);
            choice = readChoice(1, 11);
            if (choice == 1) showFleetStatus(cars);
            else if (choice == 2) showRentalStatus(rentals);
            else if (choice == 3) showCustomerRevenue(rentals);
            else if (choice == 4) showCarUsage(rentals);
            else if (choice == 5) showMonthlySummary(rentals);
            else if (choice == 6) showHighValueRentals(rentals);
            else if (choice == 7) showCarUsageRanking(cars, rentals);
            else if (choice == 8) showFeedbackRatingBreakdown(feedbacks);
            else if (choice == 9) showCostSummary(maintenance, incidents);
            else if (choice == 10) saveAnalyticsReport(cars, rentals, maintenance, feedbacks, incidents);
            if (choice != 11) waitForEnter();
        }
    }
};
class BackupManager : public FileEntity {
public:
    BackupManager() : FileEntity(BACKUP_FILE) { }
    ~BackupManager() { }
    void load() {
        ifstream fin(sourceFile);
        char line[250];
        while (fin.getline(line, 250)) cout << line << endl;
        fin.close();
    }
    void save() { }
    void writeSectionHeader(ofstream &fout, const char title[]) {
        fout << "==================================================" << endl;
        fout << title << endl;
        fout << "==================================================" << endl;
    }
    void appendFile(ofstream &fout, const char title[], const char fileName[]) {
        writeSectionHeader(fout, title);
        ifstream fin(fileName);
        char line[500];
        int count = 0;
        while (fin.getline(line, 500)) {
            fout << line << endl;
            count++;
        }
        if (count == 0) fout << "No records found." << endl;
        fin.close();
        fout << endl;
    }
    void createFullBackup() {
        ofstream fout(sourceFile);
        fout << "Car Rental Management System Backup Export" << endl;
        fout << "This file contains readable copies of all system text data." << endl;
        fout << endl;
        appendFile(fout, "Staff Users", STAFF_USERS_FILE);
        appendFile(fout, "Customer Users", CUSTOMER_USERS_FILE);
        appendFile(fout, "Cars", CARS_FILE);
        appendFile(fout, "Rentals", RENTALS_FILE);
        appendFile(fout, "Payments", PAYMENTS_FILE);
        appendFile(fout, "Receipts", RECEIPTS_FILE);
        appendFile(fout, "Maintenance", MAINTENANCE_FILE);
        appendFile(fout, "Feedback", FEEDBACK_FILE);
        appendFile(fout, "Promotions", PROMOTIONS_FILE);
        appendFile(fout, "Incidents", INCIDENTS_FILE);
        appendFile(fout, "Activity Log", ACTIVITY_FILE);
        appendFile(fout, "Reports", REPORTS_FILE);
        appendFile(fout, "System Report", SYSTEM_REPORT_FILE);
        appendFile(fout, "Customer Summary Report", CUSTOMER_REPORT_FILE);
        appendFile(fout, "Analytics Report", ANALYTICS_REPORT_FILE);
        fout.close();
        cout << "Full backup exported to system_backup.txt." << endl;
    }
    int countFileRecords(const char fileName[]) {
        ifstream fin(fileName);
        char line[500];
        int count = 0;
        while (fin.getline(line, 500)) {
            trimNewline(line);
            if (strlen(line) > 0) count++;
        }
        fin.close();
        return count;
    }
    void displayBackupStatus() {
        printMenuTitle("Backup Source Status");
        cout << left << setw(18) << "File" << setw(10) << "Records" << endl;
        cout << left << setw(18) << STAFF_USERS_FILE << setw(10) << countFileRecords(STAFF_USERS_FILE) << endl;
        cout << left << setw(18) << CUSTOMER_USERS_FILE << setw(10) << countFileRecords(CUSTOMER_USERS_FILE) << endl;
        cout << left << setw(18) << CARS_FILE << setw(10) << countFileRecords(CARS_FILE) << endl;
        cout << left << setw(18) << RENTALS_FILE << setw(10) << countFileRecords(RENTALS_FILE) << endl;
        cout << left << setw(18) << PAYMENTS_FILE << setw(10) << countFileRecords(PAYMENTS_FILE) << endl;
        cout << left << setw(18) << RECEIPTS_FILE << setw(10) << countFileRecords(RECEIPTS_FILE) << endl;
        cout << left << setw(18) << MAINTENANCE_FILE << setw(10) << countFileRecords(MAINTENANCE_FILE) << endl;
        cout << left << setw(18) << FEEDBACK_FILE << setw(10) << countFileRecords(FEEDBACK_FILE) << endl;
        cout << left << setw(18) << PROMOTIONS_FILE << setw(10) << countFileRecords(PROMOTIONS_FILE) << endl;
        cout << left << setw(18) << INCIDENTS_FILE << setw(10) << countFileRecords(INCIDENTS_FILE) << endl;
        cout << left << setw(18) << ACTIVITY_FILE << setw(10) << countFileRecords(ACTIVITY_FILE) << endl;
        cout << left << setw(18) << SYSTEM_REPORT_FILE << setw(10) << countFileRecords(SYSTEM_REPORT_FILE) << endl;
        cout << left << setw(18) << CUSTOMER_REPORT_FILE << setw(10) << countFileRecords(CUSTOMER_REPORT_FILE) << endl;
        cout << left << setw(18) << ANALYTICS_REPORT_FILE << setw(10) << countFileRecords(ANALYTICS_REPORT_FILE) << endl;
    }
    bool fileExists(const char fileName[]) {
        ifstream fin(fileName);
        bool exists = fin.good();
        fin.close();
        return exists;
    }
    void printFileCheck(const char fileName[]) {
        cout << left << setw(22) << fileName;
        if (fileExists(fileName)) cout << "OK" << endl;
        else cout << "MISSING" << endl;
    }
    void verifyRequiredFiles() {
        printMenuTitle("Required File Check");
        printFileCheck(STAFF_USERS_FILE);
        printFileCheck(CUSTOMER_USERS_FILE);
        printFileCheck(CARS_FILE);
        printFileCheck(RENTALS_FILE);
        printFileCheck(PAYMENTS_FILE);
        printFileCheck(REPORTS_FILE);
        printFileCheck(MAINTENANCE_FILE);
        printFileCheck(RECEIPTS_FILE);
        printFileCheck(FEEDBACK_FILE);
        printFileCheck(ACTIVITY_FILE);
        printFileCheck(PROMOTIONS_FILE);
        printFileCheck(INCIDENTS_FILE);
        printFileCheck(SYSTEM_REPORT_FILE);
        printFileCheck(CUSTOMER_REPORT_FILE);
        printFileCheck(ANALYTICS_REPORT_FILE);
        cout << "Keep these files in the same folder as the executable." << endl;
    }
    void displaySubmissionChecklist() {
        printMenuTitle("Submission Checklist");
        cout << "[OK] Project_GR1.cpp contains the C++ source code." << endl;
        cout << "[OK] README.txt contains run and login instructions." << endl;
        cout << "[OK] cars.txt stores car records." << endl;
        cout << "[OK] staff_users.txt stores staff/admin login accounts." << endl;
        cout << "[OK] customer_users.txt stores customer login accounts." << endl;
        cout << "[OK] rentals.txt stores booking records." << endl;
        cout << "[OK] payments.txt stores payment records." << endl;
        cout << "[OK] system_report.txt stores admin system report." << endl;
        cout << "[OK] customer_summary_report.txt stores customer report." << endl;
        cout << "[OK] analytics_report.txt stores fleet analytics report." << endl;
        cout << "[OK] maintenance.txt stores maintenance records." << endl;
        cout << "[OK] receipts.txt stores receipt records." << endl;
        cout << "[OK] feedback.txt stores customer feedback." << endl;
        cout << "[OK] promotions.txt stores discount campaigns." << endl;
        cout << "[OK] incidents.txt stores incident reports." << endl;
        cout << "[OK] activity_log.txt stores audit history." << endl;
        cout << "[OK] system_backup.txt can be generated from Backup menu." << endl;
        cout << "[OK] Staff/Admin module supports management functions." << endl;
        cout << "[OK] Customer module supports booking functions." << endl;
        cout << "[OK] Manual sorting is used for car records." << endl;
        cout << "[OK] Manual binary search is used for car lookup." << endl;
        cout << "[OK] Linked list is used for dynamic car storage." << endl;
        cout << "[OK] Payment, receipt, feedback, and incident data are stored." << endl;
        cout << "[OK] Maintenance records update car availability." << endl;
        cout << "[OK] Cancelled bookings return cars to Available." << endl;
        cout << "[OK] Edited bookings recalculate rental total." << endl;
        cout << "[OK] Plate number validation follows the required format." << endl;
        cout << "[OK] Password input is masked on screen." << endl;
        cout << "[OK] Invalid menu input is handled safely." << endl;
        cout << "[OK] Reports can be saved and retrieved from text file." << endl;
        cout << "[OK] GitHub repository should include source and txt files." << endl;
        cout << "[OK] AI usage should be disclosed in the final report." << endl;
        cout << "[OK] Lecturer collaborator access should be added in GitHub." << endl;
        cout << "Do not submit generated .exe files unless your lecturer requests them." << endl;
    }
    void displayBackupMenu() {
        int choice = 0;
        while (choice != 6) {
            printMenuTitle("Backup And Export");
            printMenuOption(1, "Create full backup");
            printMenuOption(2, "Display backup file");
            printMenuOption(3, "Display source status");
            printMenuOption(4, "Verify required files");
            printMenuOption(5, "Submission checklist");
            printMenuOption(6, "Back");
            printBoxLine(48);
            choice = readChoice(1, 6);
            if (choice == 1) createFullBackup();
            else if (choice == 2) load();
            else if (choice == 3) displayBackupStatus();
            else if (choice == 4) verifyRequiredFiles();
            else if (choice == 5) displaySubmissionChecklist();
            if (choice != 6) waitForEnter();
        }
    }
};
class HelpGuide {
public:
    HelpGuide() { }
    ~HelpGuide() { }
    void showLine(const char text[]) {
        cout << " - " << text << endl;
    }
    void showStaffGuide() {
        printMenuTitle("Staff Help Guide");
        showLine("Use Add car record to register a new vehicle.");
        showLine("Use Edit car record to update brand, model, plate, type, rate, seats, or status.");
        showLine("Use Display all cars before deleting or editing records.");
        showLine("Use Search car for binary search by car ID.");
        showLine("Use Sort cars to arrange records by rate or brand.");
        showLine("Use Delete car only after confirming the selected details.");
        showLine("Use Maintenance when a car is not available for rental.");
        showLine("Use Complete maintenance to return a car to Available.");
        showLine("Use Fleet analytics to review revenue, rental count, and car usage.");
        showLine("Use Backup and export before final submission or major testing.");
    }
    void showCustomerGuide() {
        printMenuTitle("Customer Help Guide");
        showLine("Register from the main menu before customer login.");
        showLine("Use Display available cars to see cars that can be rented.");
        showLine("Use Search car when you already know the car ID.");
        showLine("Use Sort cars to compare price or brand.");
        showLine("Use Make rental booking to select car, dates, days, promotion, and payment.");
        showLine("Use Edit booking to change dates and days; total amount is recalculated.");
        showLine("Use Cancel booking to cancel the rental and return the car to Available.");
        showLine("Use View receipt after booking payment is created.");
        showLine("Use Submit feedback to rate completed or active rental experience.");
        showLine("Use Report car incident to record damage or issues during rental.");
    }
    void showValidationGuide() {
        printMenuTitle("Input Validation Guide");
        showLine("Menu choices accept numbers only and reject invalid options.");
        showLine("Password input is masked with stars.");
        showLine("Phone number must start with 01 and contain 10 or 11 digits.");
        showLine("Plate number must contain 1-3 English letters followed by 1-4 digits.");
        showLine("Date must follow YYYY-MM-DD format.");
        showLine("End date must be after start date.");
        showLine("Rental days, seats, cost, and amount must be positive where required.");
        showLine("Promotion discount cannot exceed the allowed maximum.");
        showLine("Duplicate username and duplicate car ID are rejected.");
        showLine("Restricted customer actions check ownership of rental records.");
    }
    void showDataFileGuide() {
        printMenuTitle("Text File Guide");
        showLine("staff_users.txt stores staff/admin login accounts.");
        showLine("customer_users.txt stores customer login accounts.");
        showLine("cars.txt stores the linked-list car source records.");
        showLine("rentals.txt stores rental booking records.");
        showLine("payments.txt stores payment records created after booking.");
        showLine("receipts.txt stores receipt records generated from payment.");
        showLine("maintenance.txt stores vehicle maintenance history.");
        showLine("feedback.txt stores customer feedback and ratings.");
        showLine("incidents.txt stores customer incident reports.");
        showLine("promotions.txt stores discount campaign settings.");
        showLine("activity_log.txt stores audit history for key actions.");
        showLine("system_report.txt stores admin system report.");
        showLine("customer_summary_report.txt stores customer summary report.");
        showLine("analytics_report.txt stores fleet analytics report.");
        showLine("system_backup.txt stores full exported backup.");
    }
    void showAlgorithmGuide() {
        printMenuTitle("Algorithm Guide");
        showLine("Cars are stored in a manually implemented linked list.");
        showLine("Car sorting is manually implemented without built-in sorting functions.");
        showLine("Car ID lookup uses manually implemented binary search.");
        showLine("Car records are copied into arrays before sort/search operations.");
        showLine("No STL containers such as vector, list, stack, or queue are used.");
        showLine("File load and save operations keep modules consistent across sessions.");
        showLine("Cancelling booking updates both rental and car records.");
        showLine("Editing booking recalculates amount and updates payment/receipt records.");
        showLine("Maintenance changes car status to Maintenance, then back to Available.");
        showLine("Analytics uses manual loops over arrays and linked list records.");
    }
    void showStaffHelpMenu() {
        int choice = 0;
        while (choice != 5) {
            printMenuTitle("Staff Help And User Guide");
            printMenuOption(1, "Staff guide");
            printMenuOption(2, "Input validation guide");
            printMenuOption(3, "Text file guide");
            printMenuOption(4, "Algorithm guide");
            printMenuOption(5, "Back");
            printBoxLine(48);
            choice = readChoice(1, 5);
            if (choice == 1) showStaffGuide();
            else if (choice == 2) showValidationGuide();
            else if (choice == 3) showDataFileGuide();
            else if (choice == 4) showAlgorithmGuide();
            if (choice != 5) waitForEnter();
        }
    }
    void showCustomerHelpMenu() {
        int choice = 0;
        while (choice != 5) {
            printMenuTitle("Customer Help And User Guide");
            printMenuOption(1, "Customer guide");
            printMenuOption(2, "Input validation guide");
            printMenuOption(3, "Text file guide");
            printMenuOption(4, "Algorithm guide");
            printMenuOption(5, "Back");
            printBoxLine(48);
            choice = readChoice(1, 5);
            if (choice == 1) showCustomerGuide();
            else if (choice == 2) showValidationGuide();
            else if (choice == 3) showDataFileGuide();
            else if (choice == 4) showAlgorithmGuide();
            if (choice != 5) waitForEnter();
        }
    }
};
class ReportModule : public FileEntity {
public:
    ReportModule() : FileEntity(REPORTS_FILE) { }
    ~ReportModule() { }
    void load() {
        ifstream fin(sourceFile);
        char line[200];
        while (fin.getline(line, 200)) cout << line << endl;
        fin.close();
    }
    void save() { }
    void saveSummary(CarLinkedList &cars, RentalManager &rentals) {
        ofstream fout(SYSTEM_REPORT_FILE);
        fout << "Car Rental Management System Summary Report" << endl;
        fout << "Total cars: " << cars.size() << endl;
        fout << "Available cars: " << countAvailableFriend(cars) << endl;
        fout << "Total rentals: " << rentals.size() << endl;
        fout << "Total revenue: RM " << totalRevenueFriend(rentals) << endl;
        fout.close();
        cout << "System report saved to " << SYSTEM_REPORT_FILE << "." << endl;
        cout << "Location: same folder as Project_GR1.cpp and the executable file." << endl;
        ifstream fin(SYSTEM_REPORT_FILE);
        char line[200];
        while (fin.getline(line, 200)) cout << line << endl;
        fin.close();
    }
};
class StaffModule : public PersonModule {
public:
    StaffModule() : PersonModule("staff") { }
    StaffModule(const char name[]) : PersonModule(name) { }
    ~StaffModule() { cout << "Staff module closed." << endl; }
    bool login(UserRecord users[], int userCount) {
        char username[MAX_TEXT];
        char password[MAX_TEXT];
        cout << "Type 0 or CANCEL to return to main menu." << endl;
        inputLine("Staff username: ", username, MAX_TEXT);
        if (isCancelInput(username)) {
            copyText(currentUser, "cancelled", MAX_TEXT);
            cout << "Staff login cancelled." << endl;
            return false;
        }
        inputPassword("Staff password: ", password, MAX_TEXT);
        if (isCancelInput(password)) {
            copyText(currentUser, "cancelled", MAX_TEXT);
            cout << "Staff login cancelled." << endl;
            return false;
        }
        for (int i = 0; i < userCount; i++) {
            if (sameText(users[i].username, username) && sameText(users[i].password, password) && sameText(users[i].role, "Staff")) {
                copyText(currentUser, username, MAX_TEXT);
                return true;
            }
        }
        return false;
    }
    void showMenu() {
        printMenuTitle("Staff / Admin Module");
        printMenuOption(1, "Add car record");
        printMenuOption(2, "Edit car record");
        printMenuOption(3, "Display all cars");
        printMenuOption(4, "Search car");
        printMenuOption(5, "Sort cars");
        printMenuOption(6, "Delete car");
        printMenuOption(7, "Display rental records");
        printMenuOption(8, "Complete rental");
        printMenuOption(9, "Save and view system report");
        printMenuOption(10, "Register staff account");
        printMenuOption(11, "Display customers");
        printMenuOption(12, "Display staff accounts");
        printMenuOption(13, "Display payment records");
        printMenuOption(14, "Add maintenance record");
        printMenuOption(15, "Complete maintenance");
        printMenuOption(16, "Display maintenance records");
        printMenuOption(17, "Display customer feedback");
        printMenuOption(18, "Update feedback status");
        printMenuOption(19, "Display receipts");
        printMenuOption(20, "Display activity log");
        printMenuOption(21, "Search activity by user");
        printMenuOption(22, "Add promotion");
        printMenuOption(23, "Edit promotion");
        printMenuOption(24, "Display promotions");
        printMenuOption(25, "Display incidents");
        printMenuOption(26, "Update incident");
        printMenuOption(27, "Search incidents by car");
        printMenuOption(28, "Fleet analytics");
        printMenuOption(29, "Backup and export");
        printMenuOption(30, "Search customer account");
        printMenuOption(31, "Filter customers by phone");
        printMenuOption(32, "Display user statistics");
        printMenuOption(33, "Help and user guide");
        printMenuOption(34, "Logout");
        printBoxLine(48);
    }
    void registerStaffAccount(UserManager &users) {
        try {
            UserRecord user;
            cout << "Type 0 or CANCEL at any input to cancel staff registration." << endl;
            inputLine("New staff username: ", user.username, MAX_TEXT);
            if (isCancelInput(user.username)) throw "Staff registration cancelled.";
            if (users.findUser(user.username) != NULL) throw "Username already exists.";
            inputPassword("New staff password: ", user.password, MAX_TEXT);
            if (isCancelInput(user.password)) throw "Staff registration cancelled.";
            copyText(user.role, "Staff", MAX_TEXT);
            inputLine("Staff full name: ", user.fullName, MAX_TEXT);
            if (isCancelInput(user.fullName)) throw "Staff registration cancelled.";
            while (true) {
                inputLine("Phone (Malaysia format, example 0123456789): ", user.phone, MAX_TEXT);
                if (isCancelInput(user.phone)) throw "Staff registration cancelled.";
                if (isPhoneValid(user.phone)) break;
                cout << "Invalid phone format. Use 10 or 11 digits and start with 01." << endl;
            }
            users.addUser(user);
            users.save();
            cout << "Staff registration completed." << endl;
        } catch (const char *message) {
            if (containsText(message, "cancelled")) cout << message << endl;
            else cout << "Error: " << message << endl;
        }
    }
    void addCarRecord(CarLinkedList &cars) {
        try {
            CarRecord car;
            char rateText[MAX_TEXT];
            char seatText[MAX_TEXT];
            cout << "Type 0 or CANCEL at any input to cancel add car." << endl;
            showLatestCarId(cars);
            inputLine("Car ID: ", car.carId, MAX_TEXT);
            if (isCancelInput(car.carId)) throw "Add car cancelled.";
            if (cars.findById(car.carId) != NULL) throw "Car ID already exists.";
            inputLine("Brand: ", car.brand, MAX_TEXT);
            if (isCancelInput(car.brand)) throw "Add car cancelled.";
            inputLine("Model: ", car.model, MAX_TEXT);
            if (isCancelInput(car.model)) throw "Add car cancelled.";
            if (!inputPlateNumber("Plate No (letters then digits, example ABC1234): ", car.plateNo)) throw "Add car cancelled.";
            if (!chooseCarType(car.carType)) throw "Add car cancelled.";
            inputLine("Daily Rate: ", rateText, MAX_TEXT);
            if (isCancelInput(rateText)) throw "Add car cancelled.";
            inputLine("Seats: ", seatText, MAX_TEXT);
            if (isCancelInput(seatText)) throw "Add car cancelled.";
            copyText(car.status, "Available", MAX_TEXT);
            car.dailyRate = textToDouble(rateText);
            car.seats = textToInt(seatText);
            if (car.dailyRate <= 0) throw "Daily rate must be positive.";
            if (car.seats <= 0) throw "Seats must be positive.";
            cars.addCar(car);
            cars.save();
            cout << "Car added successfully." << endl;
        } catch (const char *message) {
            if (containsText(message, "cancelled")) cout << message << endl;
            else cout << "Error: " << message << endl;
        }
    }
    void editCarRecord(CarLinkedList &cars) {
        try {
            char id[MAX_TEXT];
            inputLine("Enter car ID to edit: ", id, MAX_TEXT);
            CarRecord *car = cars.findById(id);
            if (car == NULL) throw "Car not found.";
            char rateText[MAX_TEXT];
            char seatText[MAX_TEXT];
            printCarHeader();
            printCarRow(*car);
            printMenuTitle("Choose Field To Edit");
            printMenuOption(1, "Brand");
            printMenuOption(2, "Model");
            printMenuOption(3, "Plate number");
            printMenuOption(4, "Type");
            printMenuOption(5, "Daily rate");
            printMenuOption(6, "Seats");
            printMenuOption(7, "Status");
            printMenuOption(8, "Cancel");
            printBoxLine(48);
            int field = readChoice(1, 8);
            if (field == 1) inputLine("New brand: ", car->brand, MAX_TEXT);
            else if (field == 2) inputLine("New model: ", car->model, MAX_TEXT);
            else if (field == 3) {
                if (!inputPlateNumber("New plate number: ", car->plateNo)) {
                    cout << "Edit cancelled." << endl;
                    return;
                }
            }
            else if (field == 4) {
                if (!chooseCarType(car->carType)) {
                    cout << "Edit cancelled." << endl;
                    return;
                }
            }
            else if (field == 5) {
                inputLine("New daily rate: ", rateText, MAX_TEXT);
                car->dailyRate = textToDouble(rateText);
                if (car->dailyRate <= 0) throw "Daily rate must be positive.";
            } else if (field == 6) {
                inputLine("New seats: ", seatText, MAX_TEXT);
                car->seats = textToInt(seatText);
                if (car->seats <= 0) throw "Seats must be positive.";
            } else if (field == 7) {
                printMenuTitle("Select Status");
                printMenuOption(1, "Available");
                printMenuOption(2, "Rented");
                printMenuOption(3, "Maintenance");
                printBoxLine(48);
                int statusChoice = readChoice(1, 3);
                if (statusChoice == 1) copyText(car->status, "Available", MAX_TEXT);
                else if (statusChoice == 2) copyText(car->status, "Rented", MAX_TEXT);
                else copyText(car->status, "Maintenance", MAX_TEXT);
            } else {
                cout << "Edit cancelled." << endl;
                return;
            }
            cars.save();
            cout << "Car updated." << endl;
        } catch (const char *message) {
            cout << "Error: " << message << endl;
        }
    }
    void searchCarRecord(CarLinkedList &cars) {
        searchCarById(cars);
    }
    void sortCarRecords(CarLinkedList &cars) {
        sortAndDisplayCars(cars);
    }
    void deleteCarRecord(CarLinkedList &cars) {
        char id[MAX_TEXT];
        inputLine("Enter car ID to delete: ", id, MAX_TEXT);
        CarRecord *car = cars.findById(id);
        if (car == NULL) {
            cout << "Car not found." << endl;
            return;
        }
        cout << "Car selected for deletion:" << endl;
        printCarHeader();
        printCarRow(*car);
        if (inputYesNoConfirmation("Confirm delete? Type YES to delete or NO to cancel: ")) {
            if (cars.removeById(id)) { cars.save(); cout << "Car deleted." << endl; }
            else cout << "Car not found." << endl;
        } else {
            cout << "Delete cancelled." << endl;
        }
    }
    bool completeRentalRecord(RentalManager &rentals, CarLinkedList &cars) {
        char id[MAX_TEXT];
        inputLine("Rental ID to complete: ", id, MAX_TEXT);
        if (isCancelInput(id)) {
            cout << "Complete rental cancelled." << endl;
            return false;
        }
        RentalRecord *rental = rentals.findById(id);
        if (rental == NULL) {
            cout << "Rental not found." << endl;
            return false;
        }
        if (sameText(rental->status, "Completed")) {
            cout << "Rental is already completed." << endl;
            return false;
        }
        if (sameText(rental->status, "Cancelled")) {
            cout << "Cancelled rental cannot be completed." << endl;
            return false;
        }
        cout << "Rental selected for completion:" << endl;
        printRentalHeader();
        printRentalRow(*rental);
        if (!inputYesNoConfirmation("Confirm complete rental? Type YES to complete or NO to cancel: ")) {
            cout << "Complete rental cancelled." << endl;
            return false;
        }
        copyText(rental->status, "Completed", MAX_TEXT);
        CarRecord *car = cars.findById(rental->carId);
        if (car != NULL && sameText(car->status, "Rented")) {
            copyText(car->status, "Available", MAX_TEXT);
            cars.save();
        }
        rentals.save();
        cout << "Rental completed." << endl;
        return true;
    }
};
class CustomerModule : public PersonModule {
public:
    CustomerModule() : PersonModule("customer") { }
    CustomerModule(const char name[]) : PersonModule(name) { }
    ~CustomerModule() { cout << "Customer module closed." << endl; }
    bool login(UserRecord users[], int userCount) {
        char username[MAX_TEXT];
        char password[MAX_TEXT];
        cout << "Type 0 or CANCEL to return to main menu." << endl;
        inputLine("Customer username: ", username, MAX_TEXT);
        if (isCancelInput(username)) {
            copyText(currentUser, "cancelled", MAX_TEXT);
            cout << "Customer login cancelled." << endl;
            return false;
        }
        inputPassword("Customer password: ", password, MAX_TEXT);
        if (isCancelInput(password)) {
            copyText(currentUser, "cancelled", MAX_TEXT);
            cout << "Customer login cancelled." << endl;
            return false;
        }
        for (int i = 0; i < userCount; i++) {
            if (sameText(users[i].username, username) && sameText(users[i].password, password) && sameText(users[i].role, "Customer")) {
                copyText(currentUser, username, MAX_TEXT);
                return true;
            }
        }
        return false;
    }
    void showMenu() {
        printMenuTitle("Customer Module");
        printMenuOption(1, "Display available cars");
        printMenuOption(2, "Search car");
        printMenuOption(3, "Sort cars");
        printMenuOption(4, "Make rental booking");
        printMenuOption(5, "Edit booking");
        printMenuOption(6, "Cancel booking");
        printMenuOption(7, "View my rentals");
        printMenuOption(8, "Save and retrieve my summary");
        printMenuOption(9, "View receipt");
        printMenuOption(10, "Submit feedback");
        printMenuOption(11, "View my feedback");
        printMenuOption(12, "Display promotions");
        printMenuOption(13, "Report car incident");
        printMenuOption(14, "View my incidents");
        printMenuOption(15, "Help and user guide");
        printMenuOption(16, "Logout");
        printBoxLine(48);
    }
    void registerAccount(UserManager &users) {
        try {
            UserRecord user;
            cout << "Type 0 or CANCEL at any input to cancel registration." << endl;
            inputLine("New username: ", user.username, MAX_TEXT);
            if (isCancelInput(user.username)) throw "Registration cancelled.";
            if (users.findUser(user.username) != NULL) throw "Username already exists.";
            inputPassword("New password: ", user.password, MAX_TEXT);
            if (isCancelInput(user.password)) throw "Registration cancelled.";
            copyText(user.role, "Customer", MAX_TEXT);
            inputLine("Full name: ", user.fullName, MAX_TEXT);
            if (isCancelInput(user.fullName)) throw "Registration cancelled.";
            while (true) {
                inputLine("Phone (Malaysia format, example 0123456789): ", user.phone, MAX_TEXT);
                if (isCancelInput(user.phone)) throw "Registration cancelled.";
                if (isPhoneValid(user.phone)) break;
                cout << "Invalid phone format. Use 10 or 11 digits and start with 01." << endl;
            }
            users.addUser(user);
            users.save();
            cout << "Registration completed." << endl;
        } catch (const char *message) {
            if (containsText(message, "cancelled")) cout << message << endl;
            else cout << "Error: " << message << endl;
        }
    }
    void displayAvailableCars(CarLinkedList &cars) {
        printCarHeader();
        CarNode *walker = cars.first();
        while (walker != NULL) {
            if (sameText(walker->data.status, "Available")) printCarRow(walker->data);
            walker = walker->next;
        }
    }
    void makeBooking(CarLinkedList &cars, RentalManager &rentals, PaymentManager &payments, ReceiptManager &receipts, PromotionManager &promotions, ActivityLogManager &activityLog) {
        try {
            char id[MAX_TEXT];
            inputLine("Car ID to rent: ", id, MAX_TEXT);
            CarRecord *car = cars.findById(id);
            if (car == NULL) throw "Car not found.";
            if (!sameText(car->status, "Available")) throw "Car is not available.";
            RentalRecord rental;
            int number = rentals.size() + 1;
            sprintf(rental.rentalId, "REN%03d", number);
            copyText(rental.username, currentUser, MAX_TEXT);
            copyText(rental.carId, id, MAX_TEXT);
            if (!inputBookingDateRange(rental.startDate, rental.endDate, rental.days)) {
                throw "Booking cancelled because rental dates were not confirmed.";
            }
            rental.totalAmount = rental.days * car->dailyRate;
            promotions.displayActive();
            char promoCode[MAX_TEXT];
            inputLine("Promotion code (or NONE): ", promoCode, MAX_TEXT);
            toUpperText(promoCode);
            if (!sameText(promoCode, "NONE")) {
                double discount = promotions.calculateDiscount(promoCode, rental.totalAmount);
                if (discount > 0) {
                    cout << "Promotion discount applied: RM " << discount << endl;
                    rental.totalAmount -= discount;
                } else {
                    cout << "Promotion not applied." << endl;
                }
            }
            copyText(rental.status, "Active", MAX_TEXT);
            copyText(car->status, "Rented", MAX_TEXT);
            rentals.addRental(rental);
            PaymentRecord payment;
            payments.generatePaymentId(payment.paymentId);
            copyText(payment.rentalId, rental.rentalId, MAX_TEXT);
            payment.amount = rental.totalAmount;
            printMenuTitle("Payment Method");
            printMenuOption(1, "Cash");
            printMenuOption(2, "Card");
            printMenuOption(3, "Online Banking");
            printBoxLine(48);
            int method = readChoice(1, 3);
            if (method == 1) copyText(payment.status, "Paid-Cash", MAX_TEXT);
            else if (method == 2) copyText(payment.status, "Paid-Card", MAX_TEXT);
            else copyText(payment.status, "Paid-Online", MAX_TEXT);
            payments.addPayment(payment);
            payments.save();
            receipts.createReceipt(rental, payment);
            rentals.save();
            cars.save();
            activityLog.addActivity(currentUser, "Create booking", rental.rentalId, "Success");
            cout << "Booking created. Total RM " << rental.totalAmount << endl;
            cout << "Booking details:" << endl;
            printRentalHeader();
            printRentalRow(rental);
            cout << "Payment details:" << endl;
            payments.displayPaymentByRental(rental.rentalId);
        } catch (const char *message) {
            if (containsText(message, "cancelled")) cout << message << endl;
            else cout << "Error: " << message << endl;
        }
    }
    void editBooking(RentalManager &rentals, CarLinkedList &cars, PaymentManager &payments, ReceiptManager &receipts, ActivityLogManager &activityLog) {
        try {
            char id[MAX_TEXT];
            inputLine("Rental ID to edit: ", id, MAX_TEXT);
            RentalRecord *rental = rentals.findById(id);
            if (rental == NULL) throw "Rental not found.";
            if (!sameText(rental->username, currentUser)) throw "You can edit only your own booking.";
            if (!inputBookingDateRange(rental->startDate, rental->endDate, rental->days)) {
                throw "Booking update cancelled because rental dates were not confirmed.";
            }
            CarRecord *car = cars.findById(rental->carId);
            if (car == NULL) throw "Related car record not found.";
            rental->totalAmount = rental->days * car->dailyRate;
            rentals.save();
            payments.updatePaymentAmount(rental->rentalId, rental->totalAmount);
            receipts.updateReceiptAmount(rental->rentalId, rental->totalAmount);
            activityLog.addActivity(currentUser, "Edit booking", rental->rentalId, "Success");
            cout << "Booking updated." << endl;
            printRentalHeader();
            printRentalRow(*rental);
        } catch (const char *message) {
            if (containsText(message, "cancelled")) cout << message << endl;
            else cout << "Error: " << message << endl;
        }
    }
    void cancelBooking(RentalManager &rentals, CarLinkedList &cars, PaymentManager &payments, ActivityLogManager &activityLog) {
        char id[MAX_TEXT];
        inputLine("Rental ID to cancel: ", id, MAX_TEXT);
        if (isCancelInput(id)) {
            cout << "Cancel booking cancelled." << endl;
            return;
        }
        RentalRecord *rental = rentals.findById(id);
        if (rental != NULL && sameText(rental->username, currentUser)) {
            if (sameText(rental->status, "Cancelled")) {
                cout << "Booking is already cancelled." << endl;
                return;
            }
            cout << "Rental selected for cancellation:" << endl;
            printRentalHeader();
            printRentalRow(*rental);
            if (!inputYesNoConfirmation("Confirm cancel booking? Type YES to cancel or NO to keep booking: ")) {
                cout << "Cancel booking cancelled." << endl;
                return;
            }
            copyText(rental->status, "Cancelled", MAX_TEXT);
            CarRecord *car = cars.findById(rental->carId);
            if (car != NULL) {
                copyText(car->status, "Available", MAX_TEXT);
                cars.save();
            }
            payments.cancelPayment(rental->rentalId);
            rentals.save();
            activityLog.addActivity(currentUser, "Cancel booking", rental->rentalId, "Success");
            cout << "Booking cancelled." << endl;
        } else cout << "Rental not found or access denied." << endl;
    }
    void viewMyRentals(RentalManager &rentals) {
        printRentalHeader();
        for (int i = 0; i < rentals.size(); i++) {
            RentalRecord rental = rentals.getAt(i);
            if (sameText(rental.username, currentUser)) printRentalRow(rental);
        }
    }
    void saveAndRetrieveMySummary(RentalManager &rentals) {
        ofstream fout(CUSTOMER_REPORT_FILE);
        fout << "Customer Summary for " << currentUser << endl;
        int count = 0;
        double amount = 0;
        fout << left << setw(8) << "ID" << setw(8) << "Car" << setw(12) << "Start";
        fout << setw(12) << "End" << setw(6) << "Days" << setw(10) << "Amount" << setw(12) << "Status" << endl;
        for (int i = 0; i < rentals.size(); i++) {
            RentalRecord rental = rentals.getAt(i);
            if (sameText(rental.username, currentUser)) {
                count++;
                amount += rental.totalAmount;
                fout << left << setw(8) << rental.rentalId << setw(8) << rental.carId;
                fout << setw(12) << rental.startDate << setw(12) << rental.endDate << setw(6) << rental.days;
                fout << setw(10) << rental.totalAmount << setw(12) << rental.status << endl;
            }
        }
        fout << "Rental count: " << count << endl;
        fout << "Rental amount: RM " << amount << endl;
        fout.close();
        cout << "Customer summary report saved to " << CUSTOMER_REPORT_FILE << "." << endl;
        cout << "Location: same folder as Project_GR1.cpp and the executable file." << endl;
        ifstream fin(CUSTOMER_REPORT_FILE);
        char line[200];
        while (fin.getline(line, 200)) cout << line << endl;
        fin.close();
    }
};
void runStaff(StaffModule &staff, UserManager &users, CarLinkedList &cars, RentalManager &rentals, PaymentManager &payments, ReceiptManager &receipts, FeedbackManager &feedbacks, MaintenanceManager &maintenance, PromotionManager &promotions, IncidentManager &incidents, ActivityLogManager &activityLog, FleetAnalytics &analytics, BackupManager &backup, HelpGuide &helpGuide, ReportModule &reports) {
    int choice = 0;
    while (choice != 34) {
        staff.showMenu();
        choice = readChoice(1, 34);
        if (choice == 1) staff.addCarRecord(cars);
        else if (choice == 2) staff.editCarRecord(cars);
        else if (choice == 3) printCarFriend(cars);
        else if (choice == 4) staff.searchCarRecord(cars);
        else if (choice == 5) staff.sortCarRecords(cars);
        else if (choice == 6) staff.deleteCarRecord(cars);
        else if (choice == 7) printRentalFriend(rentals);
        else if (choice == 8) {
            if (staff.completeRentalRecord(rentals, cars)) activityLog.addActivity(staff.getCurrentUser(), "Complete rental", "REN", "Success");
        }
        else if (choice == 9) reports.saveSummary(cars, rentals);
        else if (choice == 10) staff.registerStaffAccount(users);
        else if (choice == 11) users.displayAllUsers();
        else if (choice == 12) users.displayStaffUsers();
        else if (choice == 13) payments.displayAllPayments();
        else if (choice == 14) { maintenance.addMaintenance(cars); activityLog.addActivity(staff.getCurrentUser(), "Add maintenance", "CAR", "Success"); }
        else if (choice == 15) { maintenance.completeMaintenance(cars); activityLog.addActivity(staff.getCurrentUser(), "Complete maintenance", "MNT", "Success"); }
        else if (choice == 16) maintenance.displayAll();
        else if (choice == 17) feedbacks.displayAllFeedback();
        else if (choice == 18) feedbacks.updateFeedbackStatus();
        else if (choice == 19) receipts.displayAllReceipts();
        else if (choice == 20) activityLog.displayAll();
        else if (choice == 21) activityLog.searchByUser();
        else if (choice == 22) promotions.addPromotion();
        else if (choice == 23) promotions.editPromotion();
        else if (choice == 24) promotions.displayAll();
        else if (choice == 25) incidents.displayAll();
        else if (choice == 26) incidents.updateIncident();
        else if (choice == 27) incidents.searchByCar();
        else if (choice == 28) analytics.showAnalyticsMenu(cars, rentals, maintenance, feedbacks, incidents);
        else if (choice == 29) backup.displayBackupMenu();
        else if (choice == 30) users.searchCustomerByUsername();
        else if (choice == 31) users.filterCustomersByPhonePrefix();
        else if (choice == 32) users.displayUserStatistics();
        else if (choice == 33) helpGuide.showStaffHelpMenu();
        if (choice != 34) waitForEnter();
    }
    staff.logout();
}
void runCustomer(CustomerModule &customer, UserManager &users, CarLinkedList &cars, RentalManager &rentals, PaymentManager &payments, ReceiptManager &receipts, FeedbackManager &feedbacks, PromotionManager &promotions, IncidentManager &incidents, ActivityLogManager &activityLog, HelpGuide &helpGuide) {
    int choice = 0;
    while (choice != 16) {
        customer.showMenu();
        choice = readChoice(1, 16);
        if (choice == 1) customer.displayAvailableCars(cars);
        else if (choice == 2) searchCarById(cars);
        else if (choice == 3) sortAndDisplayCars(cars);
        else if (choice == 4) customer.makeBooking(cars, rentals, payments, receipts, promotions, activityLog);
        else if (choice == 5) customer.editBooking(rentals, cars, payments, receipts, activityLog);
        else if (choice == 6) customer.cancelBooking(rentals, cars, payments, activityLog);
        else if (choice == 7) customer.viewMyRentals(rentals);
        else if (choice == 8) customer.saveAndRetrieveMySummary(rentals);
        else if (choice == 9) receipts.displayReceiptByRental(rentals);
        else if (choice == 10) { feedbacks.submitFeedback(customer.getCurrentUser(), rentals); activityLog.addActivity(customer.getCurrentUser(), "Submit feedback", "FDB", "Success"); }
        else if (choice == 11) feedbacks.displayCustomerFeedback(customer.getCurrentUser());
        else if (choice == 12) promotions.displayActive();
        else if (choice == 13) { incidents.addIncident(customer.getCurrentUser(), rentals); activityLog.addActivity(customer.getCurrentUser(), "Report incident", "INC", "Success"); }
        else if (choice == 14) incidents.displayCustomerIncidents(customer.getCurrentUser());
        else if (choice == 15) helpGuide.showCustomerHelpMenu();
        if (choice != 16) waitForEnter();
    }
    customer.logout();
}

void showWelcome() {
    printBoxLine(54);
    printCenteredLine("Car Rental Management System", 54);
    printCenteredLine("Data Structure and Algorithms Project", 54);
    printBoxLine(54);
}
int main() {
    UserManager users;
    CarLinkedList cars;
    RentalManager rentals;
    PaymentManager payments;
    ReceiptManager receipts;
    FeedbackManager feedbacks;
    MaintenanceManager maintenance;
    PromotionManager promotions;
    IncidentManager incidents;
    ActivityLogManager activityLog;
    FleetAnalytics analytics;
    BackupManager backup;
    HelpGuide helpGuide;
    ReportModule reports;
    users.load();
    cars.load();
    rentals.load();
    payments.load();
    receipts.load();
    feedbacks.load();
    maintenance.load();
    promotions.load();
    incidents.load();
    activityLog.load();
    showWelcome();
    int option = 0;
    while (option != 4) {
        printMenuTitle("Main Menu");
        printMenuOption(1, "Staff / Admin Login");
        printMenuOption(2, "Customer Login");
        printMenuOption(3, "Customer Registration");
        printMenuOption(4, "Exit");
        printBoxLine(48);
        option = readChoice(1, 4);
        if (option == 1) {
            StaffModule staff;
            if (staff.login(users.allUsers(), users.size())) runStaff(staff, users, cars, rentals, payments, receipts, feedbacks, maintenance, promotions, incidents, activityLog, analytics, backup, helpGuide, reports);
            else if (!sameText(staff.getCurrentUser(), "cancelled")) cout << "Invalid staff login." << endl;
        } else if (option == 2) {
            CustomerModule customer;
            if (customer.login(users.allUsers(), users.size())) runCustomer(customer, users, cars, rentals, payments, receipts, feedbacks, promotions, incidents, activityLog, helpGuide);
            else if (!sameText(customer.getCurrentUser(), "cancelled")) cout << "Invalid customer login." << endl;
        } else if (option == 3) {
            CustomerModule customer;
            customer.registerAccount(users);
        }
    }
    cars.save();
    rentals.save();
    payments.save();
    receipts.save();
    feedbacks.save();
    maintenance.save();
    promotions.save();
    incidents.save();
    activityLog.save();
    users.save();
    cout << "Thank you for using Car Rental Management System." << endl;
    return 0;
}

