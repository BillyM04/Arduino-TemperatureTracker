import React, { useState, useEffect } from 'react';
import api from './api';

const App = () => {
  const [temperature, setTemp] = useState([]);
  useEffect(() => {
    api.get('/temp-data')
    .then(response => {
      const data = response.data;

      console.log('Temp data: ', data);

      if(Array.isArray(data)){
        setTemp(data);
      } 
      else{
        console.error("Data is not array: ", data);
      }
    })
    .catch(error => console.error("Error fetching data: ", error));
  }, []);  
  
  return (
    <div>
      <nav className="navbar navbar-dark bg-primary">
        <div className="container-fluid">
          <a className="navbar-brand" href="#">
            TempData
          </a>
        </div>
      </nav>

      <div className="container mt-4">
        <h3>Temperature Data</h3>
        <ul>
          {temperature.length > 0 ? (
            temperature.map((item) => (
              <li key={item.id}>
                {item.temperature}°C - {item.door_status} ({item.timestamp})
              </li>
            ))
          ) : (
            <p>No data available</p>
          )}
        </ul>
      </div>
    </div>
  );
};

export default App;
