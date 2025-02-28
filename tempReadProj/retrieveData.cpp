#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <vector>
#include <thread> 
#include <chrono>
#include <boost/asio.hpp>
#include <stdio.h>
#include <curl/curl.h>

using namespace std;


int main(){
    CURL *curl;
    CURLcode res;

    boost::asio::io_context io;
    boost::asio::serial_port serial(io);
    boost::asio::streambuf buffer;

    string portname = "/dev/tty.usbmodem1101"; 
    unsigned int baudRate = 115200;

    try{
        serial.open(portname);
        serial.set_option(boost::asio::serial_port_base::baud_rate(baudRate));
    } 
    catch(const exception& e) {
//error while trying to open the port
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    while(true){
//error check while reading from the port
        boost::system::error_code ec;
        if(ec){
            cerr << "Error reading from serial port: " << ec.message() << endl;
            break;
        }
        
//read data from serial port into buffer until '\r\n'
        boost::asio::read_until(serial, buffer, "\r\n");
        istream is(&buffer);
        string line;
        getline(is,line);
        cout<< line << endl;
        buffer.consume(buffer.size());

//parsing strings of data into their respective variables one by one, by means of stringstream
        stringstream temporary;
        string temp_str, tempData, door_str1, door_str2, doorStatus;
        temporary << line;
        temporary>>temp_str>>tempData>>door_str1>>door_str2>>doorStatus;
//printing extracted data
        cout<<"------------------------------------------------"<<endl;
        cout<<"Extracted temp: "<<tempData<<"ºC\t";
        cout<<"Extracted door status: "<<doorStatus<<endl;
        cout<<"------------------------------------------------\n\n"<<endl;
        string jsonData = R"({"temperature": )" + tempData + R"(, "door_status": ")" + doorStatus + R"("})";
        curl = curl_easy_init();

        if(curl) {
//initialising curl and HTTP headers
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8000/v1/serial-data");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

            res = curl_easy_perform(curl);

            if(res != CURLE_OK):
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
        }        
    }
    return 0;
}