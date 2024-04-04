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
}RecType;

class TotalValueHelper {
public:
    static Vector<float> tVspeed;
    static Vector<float> tVairtemp;
    static Vector<float> tVsolarrad;

    static void addValue(RecType& node);
};
Vector<float> TotalValueHelper::tVspeed;
Vector<float> TotalValueHelper::tVairtemp;
Vector<float> TotalValueHelper::tVsolarrad;

typedef Vector<RecType> LogType;
typedef std::map<unsigned, RecType> MAPtype;
typedef BST<RecType> BSTtype;
typedef void (*f)(RecType&);
float CalculateMean(const Vector<float>& array);
float CalculateSD(const Vector<float>& array);
float sPCC(const Vector<float>& vec1, const Vector<float>& vec2);
void runtime();
bool processors();
void option1(MAPtype& inputdata);
void option2(MAPtype& inputdata);
void option3(LogType& inputdata);
void option4(LogType& inputdata);
void printyear(unsigned &value);
void printduplicate();
bool operator>(const RecType &lhs,const RecType &rhs);
bool operator<(const RecType &lhs,const RecType &rhs);
bool operator==(const RecType &lhs,const RecType &rhs);
void menu();

int main() {
    runtime();
    return 0;
}

void runtime() {
    bool checker = true;
    do {
        checker = processors();
    } while (checker == true);
}

bool processors() {
    std::string filename;
    LogType wind_data;
    MAPtype MAPdata;
    std::ifstream inputFile("data/data_source.txt");

    while (std::getline(inputFile, filename)) {
        filename = "data/" + filename;
        std::ifstream infile(filename);
        // std::cout << filename << std::endl;
        if (!infile) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            continue; // Move to the next file
        }

        // std::cout << "Processing file: " << filename << std::endl;
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
                    tempspeed = stof(dataline)*3.6;
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

    wind_data.Shuffle();
    for (int i = 0; i < wind_data.Size(); i++) {
        int key = wind_data[i].d.GetYear()*100000000 + wind_data[i].d.Getmonth()*1000000 + wind_data[i].d.Getday()*10000 + wind_data[i].t.Gethour()*100 + wind_data[i].t.Getminute();
        MAPdata[key] = wind_data[i];
    }

    // std::cout  << MAPdata.size() << std::endl;

    // Assignment1: Menu options time
    bool choice = true;
    bool option5 = false;
    while (choice) {
        menu();
        int option;
        std::cin >> option;
        switch (option) {
            case 1:
                option1(MAPdata);
                break;
            case 2:
                option2(MAPdata);
                break;
            case 3:
                option3(wind_data);
                break;
            case 4: 
                option4(wind_data); 
                break;
            case 5:
                option5 = true;
                std::cout << "Restarting program..." << std::endl;
                choice = false;
                break;
            case 6:
                std::cout << "Ending program..." << std::endl;
                choice = false;
                option5 = false;
                break;
            default:
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }
    MAPdata.clear();
    wind_data.Clear();
    // outfile.close();
    std::cout << "Data Cleared." <<std::endl;
    return option5;
}

float CalculateMean(const Vector<float>& array) {
    float sum = 0.0 ;
    for (int i = 0; i< array.Size() ; i++) {
        // add to sum
        sum += array[i];
    }
    return sum / array.Size();
}

float CalculateSD(const Vector<float>& array) {

    float mean = CalculateMean(array);
    float sd = 0.0;

    for (int i = 0; i < array.Size(); i++) {
        sd += ((array[i] - mean) * (array[i] - mean));
    }

    sd = sd/ (array.Size()-1);
    
    return std::sqrt(sd);
}

void menu() {
    std::cout << "Enter your desired option [1,2,3,4,5]: " << std::endl;
    std::cout << "1: Average and Standard deviation speed of specified month and year" << std::endl;
    std::cout << "2: Average and Standard deviation ambient air temperature in each month for a specified year" << std::endl;
    std::cout << "3: Pearson Correlation coefficient options" << std::endl;
    std::cout << "4: Average wind speed (km/h), average ambient air temperature and total solar radiation in kWh/m2 at a specified year. Output into WindTempSolar.csv." << std::endl;
    std::cout << "5: UNFINISHED OPTION DO NOT USE" << std::endl;
    std::cout << "6: Exit" << std::endl;
}

void option1(MAPtype& inputdata) {
    std::cout << "Enter month and year : ";
    std::string month, year;
    std::cin >> month >> year;

    float average;
    float sd;
    Vector<float> speedarray;
    int elements = 0;
    Date tempdate;
    
    for (auto itr = inputdata.begin(); itr != inputdata.end();itr++) {
        if (stoul(month) == itr->second.d.Getmonth() && stoul(year) == itr->second.d.GetYear()) {
            if (itr->first != 0) {
                speedarray.Add(itr->second.speed);
                elements++;
            }
        }
    }

    // std::cout << speedarray.Size() << std::endl;

    if (elements == 0) {    
        std::cout << tempdate.Getmonthname(stoul(month)) << " " << year << ":" << "No data" << std::endl; 
    } else {
        average = CalculateMean(speedarray);
        sd = CalculateSD(speedarray);

        std::cout << tempdate.Getmonthname(stoul(month)) << " " << year << ":" << '\n' 
        << "Average speed: " << std::fixed << std::setprecision(1) << average << " km/h" << '\n'
        << "Sample stdev: " << std::fixed << std::setprecision(1) << sd << std::endl;
    }

}

void option2(MAPtype& inputdata) {
    std::cout << "Enter year :";
    std::string year;
    std::cin >> year;
    Date tempdate;

    std::cout  << " " << year;
    for (unsigned j = 1; j <= 12;j++) {
        float average = 0;
        float sd = 0;
        Vector<float> airtemparray;
        int elements = 0;

        for (auto itr = inputdata.begin(); itr != inputdata.end() ;itr++) {
            if (stoul(year) == itr->second.d.GetYear() && j == itr->second.d.Getmonth()) {
                if (itr->first != 0) {
                    airtemparray.Add(itr->second.airtemp);
                    elements++;
                }
            }
        }
        average = CalculateMean(airtemparray);
        sd = CalculateSD(airtemparray);

        std::cout << '\n' 
        << tempdate.Getmonthname(j) << ":";
        if (elements != 0) {
            std::cout << "Average: " << std::fixed << std::setprecision(1) << average;
            std::cout << " degrees C, stdev: " << std::fixed << std::setprecision(2) << sd;
        } else {
            std::cout << "No data";
        }
    }
    std::cout << std::endl;
}

void option3(LogType& inputdata) { //sPRR thing calculation
    std::cout << "Enter month:";
    unsigned month;
    std::cin >> month;
    BSTtype bstlog;

    if (month < 1 || month > 12) { //check for valid month
        std::cout << "Invalid month!" << std::endl;
        return;
    }

    for (int i =0; i< inputdata.Size();i++) {
        if (inputdata[i].d.Getmonth() == month) {
            bstlog.insert(inputdata[i],printduplicate);
        }
    }

    if (bstlog.size() == 0) { //check for any data in specified month
        std::cout << "No data found on selected month" << std::endl;
        return;
    }

    // std::cout << newlog.size() <<std::endl;

    TotalValueHelper tvh;
    //output sPRR for each 3 of the results.
    //calls the inordertraversal to store data into the helper class.
    bstlog.inorderTraversal(TotalValueHelper::addValue);
    std::cout << "S_T: " << std::fixed << std::setprecision(2)<< sPCC(tvh.tVspeed, tvh.tVairtemp) <<std::endl;
    std::cout << "S_R: " << std::fixed << std::setprecision(2)<< sPCC(tvh.tVspeed, tvh.tVsolarrad) <<std::endl;
    std::cout << "T_R: " << std::fixed << std::setprecision(2)<< sPCC(tvh.tVsolarrad, tvh.tVairtemp) <<std::endl;

    bstlog.destroyTree();
}

float sPCC(const Vector<float>& vec1, const Vector<float>& vec2) {
    float meanX = CalculateMean(vec1);
    float meanY = CalculateMean(vec2);
    // std::cout << meanX <<std::endl;
    // std::cout << meanY <<std::endl;

    // Calculate standard deviations
    float sdX = CalculateSD(vec1);
    float sdY = CalculateSD(vec2);

    // std::cout << sdX <<std::endl;
    // std::cout << sdY <<std::endl;

    float cov = 0;
    for (int i = 0;i < vec1.Size(); ++i) {
        cov += (vec1[i] - meanX) * (vec2[i] - meanY);
    }
    cov /= vec1.Size();

    float correlation = cov / (sdX * sdY);
    return correlation;
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
                outfile << std::fixed << std::setprecision(1) << CalculateMean(speedarray)*3.6 << "(" << CalculateSD(speedarray) << ")";
            }
            outfile <<",";
            if (airtempelements !=0) {
                outfile << std::fixed << std::setprecision(1) << CalculateMean(airtemparray) << "(" << CalculateSD(airtemparray)<< ")";
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

void printyear(unsigned &value) {
    std::cout << value << std::endl;
}

void printduplicate() {
    std::cout << "Duplicate data found. This will be removed." << std::endl;
}

bool operator>(const RecType &lhs,const RecType &rhs) {
    if (lhs.d > rhs.d)
        return true;
    else if (lhs.d < rhs.d)
        return false;
    else {
        if (lhs.t > rhs.t) {
            return true;            
        } else {
            return lhs.t > rhs.t;
        }
    }
}

bool operator<(const RecType &lhs,const RecType &rhs) {
    return !(lhs > rhs) && !(lhs == rhs);
}

bool operator==(const RecType &lhs,const RecType &rhs) {
    return lhs.d == rhs.d && lhs.t == rhs.t;
}

void TotalValueHelper::addValue(RecType& node) {
    tVspeed.Add(node.speed);
    tVairtemp.Add(node.airtemp);
    tVsolarrad.Add(node.solarrad);
}