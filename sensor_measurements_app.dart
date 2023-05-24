import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  final DatabaseReference databaseReference = FirebaseDatabase.instance.reference();

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Sensor Measurements',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: SensorMeasurementsScreen(databaseReference: databaseReference),
    );
  }
}

class SensorMeasurementsScreen extends StatefulWidget {
  final DatabaseReference databaseReference;

  SensorMeasurementsScreen({required this.databaseReference});

  @override
  _SensorMeasurementsScreenState createState() =>
      _SensorMeasurementsScreenState();
}

class _SensorMeasurementsScreenState extends State<SensorMeasurementsScreen> {
  Map<String, dynamic> measurements = {};

  @override
  void initState() {
    super.initState();
    _listenToSensorData();
  }

  void _listenToSensorData() {
    widget.databaseReference.child('sensor_data').onValue.listen((event) {
      setState(() {
        measurements = Map<String, dynamic>.from(event.snapshot.value);
      });
    });
  }

  Widget _buildMeasurementRow(String label, dynamic value) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceBetween,
      children: [
        Text(
          label,
          style: TextStyle(fontSize: 18),
        ),
        Text(
          value ?? 'N/A',
          style: TextStyle(fontSize: 18),
        ),
      ],
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Sensor Measurements'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            _buildMeasurementRow('Temperature:', '${measurements['temperature']} °C'),
            SizedBox(height: 12),
            _buildMeasurementRow('Humidity:', '${measurements['humidity']} %'),
            SizedBox(height: 12),
            _buildMeasurementRow('PM2.5:', '${measurements['pm25']} µg/m³'),
            SizedBox(height: 12),
            _buildMeasurementRow('PM10:', '${measurements['pm10']} µg/m³'),
            SizedBox(height: 12),
            _buildMeasurementRow('Ozone:', '${measurements['ozone']}'),
            SizedBox(height: 12),
            _buildMeasurementRow('VOC:', '${measurements['voc']}'),
            SizedBox(height: 12),
            _buildMeasurementRow('CO2:', '${measurements['co2']}'),
          ],
        ),
      ),
    );
  }
}
