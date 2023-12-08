#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

// Function to generate a random date between two given dates
string randomDate(const string& startDate, const string& endDate) {
    // Convert string dates to tm
    tm start_tm = {};
    tm end_tm = {};

    istringstream start_ss(startDate);
    start_ss >> get_time(&start_tm, "%m/%d/%Y");

    istringstream end_ss(endDate);
    end_ss >> get_time(&end_tm, "%m/%d/%Y");

    time_t start_time = mktime(&start_tm);
    time_t end_time = mktime(&end_tm);

    // Generate a random time_t value between start_time and end_time
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<time_t> distribution(start_time, end_time);
    time_t random_time = distribution(generator);

    // Convert the random time_t value back to a string date
    tm* random_tm = localtime(&random_time);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%m/%d/%Y", random_tm);

    return string(buffer);
}

int main() {
    // Number of data entries
    const int numEntries = 200;

    // Create and open the file
    ofstream outputFile("data.txt");

    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return 1;
    }

    // Generate and write 200 rows of data with random birthdates and end dates
    for (int i = 1; i <= numEntries; ++i) {
        string birthDate = randomDate("01/01/1980", "12/31/2000");
        string endDate = randomDate("01/01/2001", "12/31/2022");

        outputFile << i << ",employe" << i << ",employe" << i << "," << birthDate << "," << endDate << "," << i * 100 << "\n";
    }

    // Close the file
    outputFile.close();

    cout << "Data has been written to data.txt." << endl;

    return 0;
}
