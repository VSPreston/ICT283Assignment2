#include "Date.h"
#include "Time.h"
#include "BST.h"
// #include "Date.cpp" // for testing purposes.
// #include "Time.cpp"  // for testing purposes.
#include "Vector.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <map>

// Compiler command:
// g++ -Wall -g -std=c++11 -ftime-report main.cpp Time.cpp Date.cpp -o main

typedef struct {
    Date d;
    Time t;
    float speed;
    float solarrad;
    float airtemp;
} RecType;

typedef Vector<RecType> LogType; 
float CalculateMean(const Vector<float>& array, int size);
float CalculateSD(const Vector<float>& array, int size);
void runtime();
void option1(LogType& inputdata);
void option2(LogType& inputdata);
void option3(LogType& inputdata);
void option4(LogType& inputdata);

void menu();

int main() {
    runtime();
    return 0;
}

void runtime() {
    std::string filename;
    LogType wind_data = LogType(5);
    std::ifstream inputFile("data/data_source.txt");

    while (std::getline(inputFile, filename)) {
        filename = "data/" + filename;
        std::ifstream infile(filename);
        // std::cout << filename << std::endl;
        if (!infile) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            continue; // Move to the next file
        }

        std::cout << "Processing file: " << filename << std::endl;
        int wastpostion = -1;
        int speedpostion = -1;
        int solarradposition = -1;
        int airtempposition = -1;
        int counter = 0;
        std::string header;
        std::string headerline;

        if (std::getline(infile, headerline)) {
            for (char c : headerline) {
                if (c == ',') {
                    // If a comma is encountered, check if the headerName matches "WAST" or "S"
                    if (header == "WAST") {
                        wastpostion = counter;
                    } else if (header == "S") {
                        speedpostion = counter;
                    } else if (header == "T") {
                        airtempposition = counter;
                    } else if (header == "SR") {
                        solarradposition = counter;
                    } 
                    header.clear(); // Clear the headerName for the next cell
                    counter++; // Move to the next column
                } else {
                    header += c; // Append the character to the headerName
                }
            }
            if (!header.empty()) {
                if (header == "WAST") {
                    wastpostion = counter;
                } else if (header == "S") {
                    speedpostion = counter;
                } else if (header == "T") {
                    airtempposition = counter;
                } else if (header == "SR") {
                    solarradposition = counter;
                }
            }
        }

        // std::cout << "WAST index position:" << wastpostion << '\n' 
        // << "S index position::" << speedpostion << '\n'
        // << "SR (Solar Radiation) index position: " << solarradposition << '\n'
        // <<  "Air temperature index position: " << airtempposition << std::endl; 

        if (wastpostion == -1 || speedpostion == -1 || airtempposition == -1 || solarradposition == -1) {
            std::cerr << "One of the data types not found in file!" << std::endl;
            exit (-1);
        }

        // next: putting data into wind_data

        std::string line;
        int index = 0;
        while (std::getline(infile, line)) {
            std::string dataline;
            int columncount = 0;
            std::istringstream iss(line);
            Date tempdate;
            Time temptime;
            float tempspeed =0;
            float tempsr = 0;
            float tempairt = 0;
            RecType tempwrt;

            while (std::getline(iss, dataline, ',')) {
                if (dataline == "N/A" || dataline == "") {
                    break;
                }
                if (columncount == wastpostion) {
                    std::istringstream thing(dataline);
                    thing >> tempdate
                    >> temptime;
                } else if (columncount == speedpostion && dataline != "") {
                    tempspeed = stof(dataline);
                } else if (columncount == solarradposition && dataline != "") {
                    tempsr = stof(dataline);
                } else if (columncount == airtempposition && dataline != "") {
                    tempairt = stof(dataline);
                } else  {}
                columncount++;
            }
            if (tempdate.GetDate() == "No Date" || dataline == "N/A") { // checks for blank rows
                continue;
            } else {
                tempwrt.d = tempdate;
                tempwrt.t = temptime;
                tempwrt.speed = tempspeed;
                tempwrt.airtemp = tempairt;
                tempwrt.solarrad = tempsr;
                wind_data.Add(tempwrt);
                index++;
            }     
        }
    
        // for (int i = 0; i < wind_data.Size(); i++)
        // {
        //     std::cout << "Date: " << wind_data.getat(i).d.GetDate() << '\n'
        //     << "Time: " <<wind_data.getat(i).t.GetFullTime() << '\n' 
        //     << "Speed: " <<wind_data.getat(i).speed << '\n'
        //     << "Ambient Air temperature: " << wind_data.getat(i).airtemp << '\n'
        //     << "Solar Radiation: " << wind_data.getat(i).solarrad << '\n' << std::endl;
        // }

        infile.close(); // Close the file after processing
    }

    //next: finding where to get WAST and R

    //DisplaySameasAverage(wind_data,average);

    // Assignment1: Menu options time
    bool choice = true;
    while (choice) {
        menu();
        int option;
        std::cin >> option;
        switch (option) {
            case 1:
                option1(wind_data);
                break;
            case 2:
                option2(wind_data);
                break;
            case 3:
                option3(wind_data);
                break;
            case 4: 
                option4(wind_data); 
                break;
            case 5:
                // exit out
                std::cout << "Ending program..." << std::endl;
                choice = false;
                break;
            default:
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }

    // outfile.close();

    wind_data.Clear();
    std::cout << "Data Cleared." <<std::endl;
}

float CalculateMean(const Vector<float>& array, int size) {
    float sum =0;
    for (int i = 0;i< size ; i++) {
        // add to sum
        sum += array[i];
    }
    sum = sum / size;
    return sum;
}

float CalculateSD(const Vector<float>& array, int size) {

    float mean = CalculateMean(array, size);
    float sd = 0.0;

    for (int i = 0; i < size; i++) {
        sd += pow((array[i] - mean),2);
    }
    
    return sqrt (sd/(size-1));
}

void menu() {
    std::cout << "Enter your desired option [1,2,3,4,5]: " << std::endl;
    std::cout << "1: Average and Standard deviation speed of specified month and year" << std::endl;
    std::cout << "2: Average and Standard deviation ambient air temperature in each month for a specified year" << std::endl;
    std::cout << "3: Total solar radiation of each month of a specified year" << std::endl;
    std::cout << "4: Average wind speed (km/h), average ambient air temperature and total solar radiation in kWh/m2 at a specified year. Output into WindTempSolar.csv." << std::endl;
    std::cout << "5: Exit program" << std::endl;
}

void option1(LogType& inputdata) {
    std::cout << "Enter month and year : ";
    std::string month, year;
    std::cin >> month >> year;

    float average;
    float sd;
    Vector<float> speedarray;
    int elements = 0;
    Date tempdate;

    //check year first

    for (int i = 0; i< inputdata.Size();i++) {
        if (stoul(month) == inputdata[i].d.Getmonth() && stoul(year) == inputdata[i].d.GetYear()) {
            if (inputdata[i].speed != 0) {
                speedarray.Add(inputdata[i].speed);
                elements++;
            }
        }
    }

    if (elements == 0) {    
        std::cout << tempdate.Getmonthname(stoul(month)) << " " << year << ":" << "No data" << std::endl; 
    } else {
        average = CalculateMean(speedarray, elements) *3.6;
        sd = CalculateSD(speedarray, elements);

        std::cout << tempdate.Getmonthname(stoul(month)) << " " << year << ":" << '\n' 
        << "Average speed: " << std::fixed << std::setprecision(1) << average << " km/h" << '\n'
        << "Sample stdev: " << std::fixed << std::setprecision(1) << sd << std::endl;
    }

}

void option2(LogType& inputdata) {
    std::cout << "Enter year :";
    std::string year;
    std::cin >> year;
    Date tempdate;

    std::cout  << " " << year;
    for (unsigned j = 1; j <= 12;j++) {
        float average = 0;
        float sd = 0;
        Vector<float> airtemparray = Vector<float>(31);
        int elements = 0;
        for (int i = 0; i< inputdata.Size();i++) {
            if (stoul(year) == inputdata[i].d.GetYear() && j == inputdata[i].d.Getmonth()) {
                if (inputdata[i].airtemp != 0) {
                    airtemparray.Add(inputdata[i].airtemp);
                    elements++;
                }
            }
        }
        average = CalculateMean(airtemparray, elements);
        sd = CalculateSD(airtemparray, elements);

        std::cout << '\n' 
        << tempdate.Getmonthname(j) << ":";
        if (elements != 0) {
            std::cout << "Average: " << std::fixed << std::setprecision(1) << average << " degrees C, stdev: " << std::fixed << std::setprecision(2) << sd;
        } else {
            std::cout << "No data";
        }
    }
    std::cout << std::endl;
}

void option3(LogType& inputdata) {
    std::cout << "Enter year :";
    std::string year;
    std::cin >> year;
    Date tempdate;

    std::cout  << " " << year;
    for (unsigned j = 1; j <= 12;j++) {
        float total;
        int elements = 0;
        for (int i = 0; i< inputdata.Size();i++) {
            if (stoul(year) == inputdata[i].d.GetYear() && j == inputdata[i].d.Getmonth()) {
                if (inputdata[i].solarrad > 100) {
                    total = total + inputdata[i].solarrad;
                    elements++;
                }
            }
        }
        total = total/6000;
        std::cout << '\n' 
        << tempdate.Getmonthname(j) << ":";
        if (elements != 0) {
            std::cout << std::fixed << std::setprecision(1) << total << "kWh/m^2";
        }
        else {
            std::cout << "No data";
        }
    }
    std::cout << std::endl;
}

void option4(LogType& inputdata) {
    std::cout << "Enter year :";
    std::string year;
    std::cin >> year;
    Date tempdate;
    int outputcounter = 0;

    std::ofstream outfile ("data/WindTempSolar.csv"); 
        if( !outfile ) {
        std::cerr << " Cannot find file!" << std::endl;
        exit(-1);
    }

    outfile << year;
    for (unsigned j = 1; j <= 12;j++) {
        Vector<float> airtemparray = Vector<float>(31);
        Vector<float> speedarray = Vector<float>(31);
        float total;
        int solarelements = 0, speedelements = 0, airtempelements = 0;
        for (int i = 0; i< inputdata.Size();i++) {
            if (stoul(year) == inputdata[i].d.GetYear() && j == inputdata[i].d.Getmonth()) {
                if (inputdata[i].solarrad > 100) {
                    total = total + inputdata[i].solarrad;
                    solarelements++;
                }
                if (inputdata[i].airtemp != 0) {
                    airtemparray.Add(inputdata[i].airtemp);   
                    airtempelements++;                 
                }
                if (inputdata[i].speed != 0) {
                    speedarray.Add(inputdata[i].speed); 
                    speedelements++;                   
                }
            }
        }
        total = total/6000;
        if (speedelements != 0 || airtempelements != 0 || solarelements != 0) {
            outfile << '\n'
            << tempdate.Getmonthname(j) << ",";
            if (speedelements !=0) {
                outfile << std::fixed << std::setprecision(1) << CalculateMean(speedarray,speedelements)*3.6 << "(" << CalculateSD(speedarray,speedelements) << ")";
            }
            outfile <<",";
            if (airtempelements !=0) {
                outfile << std::fixed << std::setprecision(1) << CalculateMean(airtemparray,airtempelements) << "(" << CalculateSD(airtemparray,airtempelements)<< ")";
            }
            outfile <<",";
            if (solarelements != 0 ) {
                outfile << total;
            }
            outputcounter++;
        }
    }
    if (outputcounter ==0) {
        outfile << ":No data";             
    }
    outfile.close();
    std::cout << "Data printed. Check WindTempSolar.csv for details."<< std::endl;
}
