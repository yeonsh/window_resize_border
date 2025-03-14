import 'package:flutter/material.dart';
import 'package:window_resize_border/window_resize_border.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final _windowResizeBorderPlugin = WindowResizeBorder();
  bool _enlargedBordersEnabled = false;
  int _borderWidth = 8;

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Window Resize Border Example'),
        ),
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                'Enlarged borders are ${_enlargedBordersEnabled ? 'enabled' : 'disabled'}',
                style: const TextStyle(fontSize: 18),
              ),
              const SizedBox(height: 20),
              if (_enlargedBordersEnabled)
                Slider(
                  value: _borderWidth.toDouble(),
                  min: 1,
                  max: 20,
                  divisions: 19,
                  label: _borderWidth.toString(),
                  onChanged: (value) {
                    setState(() {
                      _borderWidth = value.toInt();
                    });
                    _windowResizeBorderPlugin.enableEnlargedBorders(
                      borderWidth: _borderWidth,
                    );
                  },
                ),
              const SizedBox(height: 20),
              ElevatedButton(
                onPressed: () async {
                  bool success;
                  if (_enlargedBordersEnabled) {
                    success = await _windowResizeBorderPlugin.disableEnlargedBorders();
                  } else {
                    success = await _windowResizeBorderPlugin.enableEnlargedBorders(
                      borderWidth: _borderWidth,
                    );
                  }
                  
                  if (success) {
                    setState(() {
                      _enlargedBordersEnabled = !_enlargedBordersEnabled;
                    });
                  }
                },
                child: Text(
                  _enlargedBordersEnabled ? 'Disable Enlarged Borders' : 'Enable Enlarged Borders',
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}