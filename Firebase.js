const express = require('express');
const app = express();
const firebase = require('firebase');

// Initialize Firebase with your project credentials
const firebaseConfig = {
  apiKey: 'API_KEY',
  authDomain: 'YOUR_AUTH_DOMAIN',
  databaseURL: 'https://air-monitoring-system-7bb90-default-rtdb.europe-west1.firebasedatabase.app/measurements/50003001',
  storageBucket: 'STORAGE_BUCKET',
  messagingSenderId: 'SENDER_ID',
  appId: 'APP_ID',
};


firebase.initializeApp(firebaseConfig);


app.get('/data', (req, res) => {
  // get data from Firebase
  firebase
    .database()
    .ref('/sensor_data')
    .once('value')
    .then((snapshot) => {
      const data = snapshot.val();

      // measurements
      const {
        temperature,
        humidity,
        pm25,
        pm10,
        ozone,
        voc,
        co2,
      } = data;

      // JSON object with the measurements
      const measurements = {
        temperature,
        humidity,
        pm25,
        pm10,
        ozone,
        voc,
        co2,
      };

      res.json(measurements);
    })
    .catch((error) => {
      console.log('Error retrieving data from Firebase:', error);
      res.status(500).json({ error: 'Failed to retrieve data' });
    });
});


app.listen(3000, () => {
  console.log('Backend server started on port 3000');
});
