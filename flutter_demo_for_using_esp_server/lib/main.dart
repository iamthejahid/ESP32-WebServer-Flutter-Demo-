import 'dart:developer';

import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'ESP32 API Call Demo',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key}) : super(key: key);

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  bool _isLoading = false;
  String _response = '';

  Future<void> fetchData() async {
    setState(() {
      _isLoading = true;
    });
    try {
      final response = await http.get(
        Uri.parse('http://192.168.0.5/data'),
      );
      log("this is the response: $response");

      if (response.statusCode == 200) {
        setState(() {
          _response = json.decode(response.body)['message'];
          _isLoading = false;
        });
      } else {
        setState(() {
          _response = 'Failed to fetch data';
          _isLoading = false;
        });
      }
    } catch (e) {
      log("", error: e, name: "error");
      setState(() {
        _response = 'Failed to fetch data';
        _isLoading = false;
      });
    }
    _isLoading = false;
  }

  Future<void> sendMorseRequest(String message) async {
    setState(() {
      _isLoading = true;
    });
    try {
      final response = await http.post(
        Uri.parse('http://192.168.0.5/morse'),
        body: {'message': message},
      );
      log("this is the morse response: $response");

      if (response.statusCode == 200) {
        setState(() {
          _response = 'LED flashed in Morse code';
          _isLoading = false;
        });
      } else {
        setState(() {
          _response = 'Failed to send Morse request';
          _isLoading = false;
        });
      }
    } catch (e) {
      log("", error: e, name: "error");
      setState(() {
        _response = 'Failed to send Morse request';
        _isLoading = false;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('API Call Demo'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            ElevatedButton(
              onPressed: () {
                fetchData();
              },
              child: const Text('Fetch Data'),
            ),
            const SizedBox(height: 20),
            ElevatedButton(
              onPressed: () {
                sendMorseRequest('hello');
              },
              child: const Text('Send Morse Request '),
            ),
            const SizedBox(height: 20),
            if (_isLoading)
              const CircularProgressIndicator()
            else if (_response.isNotEmpty)
              Text(
                'Response: $_response',
                style: const TextStyle(fontSize: 20),
              ),
          ],
        ),
      ),
    );
  }
}
