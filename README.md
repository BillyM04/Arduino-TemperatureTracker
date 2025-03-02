# Arduino: Temperature tracker


## Description

The project follows a full-stack architecture to retrieve sensor data from an Arduino via USB. The data is read from a 
specified serial port and uploaded using curl to a FastAPI server, which then stores it in a PostgreSQL database. 
A front-end UI, built with a React app, will fetch data from the FastAPI server and display the ten most recent database entries.

- I wanted to build a project with real-world applications. This project is versatile, applicable in different scenarios,
  and has helped me grow as an engineer by covering multiple topics.
- It can be used for example, as a digital thermometer, where we read and display the temperature data, while also storing it
  so we can track the temperature of a room over a period of time.


## Table of Contents
- [Description](#description)
- [Installation](#installation)
- [Dependencies](#dependencies)
- [Usage](#usage)
- [.env Configuration](#env-configuration)
- [Serial Port Configuration](#serial-port-configuration)
- [Data Model](#data-model)
- [API Endpoints](#api-endpoints)
- [Final Product](#final-product)
- [Credits](#credits)
- [Features](#features)


## Installation

First we need to clone the repository:
### Clone the repository

#### Linux / macOS / Windows
```md
git clone https://github.com/your-username/your-repository.git
```
The 'TempReadProj' directory is to be uploaded to an arduino, so that it can create dummy data, to simulate
temperature readings.

Next, we need to install all dependencies for our project. To do this, download the requirements.txt file 
and execute the following command:
### Dependencies

#### Linux / macOS
```md
  cd /path/to/your/project
  python3 -m ensurepip --upgrade
  pip3 install -r requirements.txt
```

### Windows
```md
  cd C:\path\to\your\project
  python -m ensurepip --upgrade
  pip install -r requirements.txt
```


## Usage

### .env Configuration
You need to create a .env file in your api directory so you can manage your sensitive information,
such as your username, password etc.
You will have a url for your database of the form:
```md
  "postgresql://username:password@host:port/database_name"
```
  This will have your:
  - Username; if you're unsure just use postgres, 
  - Password; password to your database
  - Host; for development use localhost
  - Port; the port your database is running on
  - Database name;

### Serial Port Configuration
Here in line 23 in retrieveData.cpp, we need to alter the portname to the one that our device is using,
in my case it was '/dev/tty.usbmodem11101', as shown below:

<img src="assets/images/port_temperature.png" alt="port" width="500" />

### Data Model
In the 'api' directory, you will follow src/app/models and find models.py, in this file you will find 
a base model for creating an object 'TemperatureData', that will be the template for data 
to be uploaded to the database:

<img src="assets/images/Database_model_temperature.png" alt="model" width="500" />

This specifys that the table is called 'tempdata', but it could be different depending what
you decide to name yours.

### API Endpoints

#### POST 
The POST request is used by the retrieveData.cpp to send data to the fastAPI via curl using the 'serial-data' endpoint.
The incoming data has a format such as:
```md
  {
    "temperature":7.43,
    "door_status":"Open",
  }
```
#### GET 
The GET request is used to display the data on the front end UI. A fetch request is used in the React app to make this happen
The outgoing data is a list, as we want to pull a number of data entries at once, and each object will have a format such as:
```md
  {
    "temperature":7.43,
    "door_status":"Open",
    "id":702,
    "timestamp":"2025-03-02T15:27:23.306887"
  }
```

### Final Product
By the end of these instructions you should have a site that looks like this:

<img src="assets/images/site_temperature.png" alt="front" width="500" />


## Credits

This project was developed with the assistance of tutorials, documentation and AI.
- ChatGPT by OpenAI.
- FastAPI Documentation: https://fastapi.tiangolo.com/#recap
- YouTube tutorial using React app with fastAPI: https://youtu.be/0zb2kohYZIM?si=qw56IG69C4uOqH9X
- Postgres V16 Documentationhttps://www.postgresql.org/docs/16/index.html


## Features  

- Uses Boost.Asio to read serial data from a connected device  
- Sends the data to a FastAPI server using cURL  
- Stores incoming data in a PostgreSQL database  
- Provides a React frontend to display the ten most recent database entries  


