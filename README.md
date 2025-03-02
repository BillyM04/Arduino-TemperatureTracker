# Arduino: Temperature tracker

## Description

The project follows a full-stack architecture to retrieve sensor data from an Arduino via USB. The data is read from a 
specified serial port and uploaded using curl to a FastAPI server, which then stores it in a PostgreSQL database. 
A front-end UI, built with a React app, will fetch data from the FastAPI server and display the ten most recent database entries.

- I wanted to build a project that has real world applications, and this project could be used in various scenarios
and teaches about a number of topics, which helped me further my development as an engineer.
- It can be used for example, as a digital thermometer, where we read and display the temperature data, while also storing it
so we can track the temperature of a room over a period of time.


## Table of Contents

If your README is long, add a table of contents to make it easy for users to find what they need.

- [Installation](#installation)
- [Usage](#usage)
- [Credits](#credits)
- [Features](#features)

## Installation

- First we need to clone the repository:
### Clone the repository

#### Linux / macOS / Windows
```md
git clone https://github.com/your-username/your-repository.git
```
- The 'TempReadProj' directory is to be uploaded to an arduino, so that it can create dummy data, to simulate
temperature readings.

- Next we need to install the all the dependencies for our project, to do this we'll download the requirements.txt file
and we will execute the following command;
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
- You need to create a .env file in your api directory so you can manage your sensitive information,
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



Here in line 23 in retrieveData.cpp, we need to alter the portname to the one that our device is using,
in my case it was '/dev/tty.usbmodem11101', as shown below:
```md
![alt text](assets/images/portname_temperature.png)
```

In the 'api' directory, you will follow src/app/models and find models.py, in this file you will find 
a base model for creating an object 'TemperatureData', that will be the template for data 
to be uploaded to the database:

```md
![alt text](assets/images/database_model_temperature.png)
```

This specifys that the table is called 'tempdata', but it could be different depending what
you decide to name yours.



By the end of these instructions you should have a site that looks like this:
```md
![alt text](assets/images/final_product_temperature.png)
```



## Credits

This project was developed with the assistance of tutorials, documentation and AI.
- ChatGPT by OpenAI.
- https://fastapi.tiangolo.com/#recap
- https://youtu.be/0zb2kohYZIM?si=qw56IG69C4uOqH9X
- https://www.postgresql.org/docs/16/index.html


## Features  

- Uses Boost.Asio to read serial data from a connected device  
- Sends the data to a FastAPI server using cURL  
- Stores incoming data in a PostgreSQL database  
- Provides a React frontend to display the ten most recent database entries  


