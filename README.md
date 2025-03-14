# Window Resize Border

A Flutter plugin that enhances window resizing experience on Windows by enlarging the resize border area, making it easier for users to grab and resize windows.

[![Pub Version](https://img.shields.io/pub/v/window_resize_border.svg)](https://pub.dev/packages/window_resize_border)

## Features

- Enlarge window resize borders beyond Windows default size
- Customizable border width
- Easy to enable/disable at runtime
- Works on Windows 7, 8, 10, and 11

## Platform Support

| Windows | macOS | Linux | Web | Android | iOS |
|:-------:|:-----:|:-----:|:---:|:-------:|:---:|
| ✅      | ❌    | ❌    | ❌  | ❌      | ❌  |

## Installation

Add this to your package's `pubspec.yaml` file:

```yaml
dependencies:
  window_resize_border: ^0.1.0
```

Then run:

```
flutter pub get
```

## Usage

Import the package:

```dart
import 'package:window_resize_border/window_resize_border.dart';
```

Create an instance of the plugin:

```dart
final windowResizeBorder = WindowResizeBorder();
```

### Enable Enlarged Borders

Enable the enlarged borders with the default width (8 pixels):

```dart
await windowResizeBorder.enableEnlargedBorders();
```

Or specify a custom border width:

```dart
await windowResizeBorder.enableEnlargedBorders(borderWidth: 12);
```

### Disable Enlarged Borders

Return to system default border size:

```dart
await windowResizeBorder.disableEnlargedBorders();
```

### Complete Example

```dart
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
```

## How It Works

This plugin uses Windows API to intercept the `WM_NCHITTEST` message and modify the hit-testing behavior of window borders. By extending the hit-test area beyond the visible border, it makes it easier for users to grab and resize the window.

## Troubleshooting

### Plugin not working

Make sure you're running your Flutter app on a Windows system. This plugin only works on Windows and will have no effect on other platforms.

### Borders not expanding

If enabling the enlarged borders doesn't seem to have an effect, check:

1. You're running on Windows OS
2. Your app has a resizable window
3. Your Flutter app is using the Windows embedding correctly

## Limitations

- Only works on Windows platforms
- Requires Flutter desktop support to be enabled
- Window appearance doesn't change, only the interactive area increases

## Contributing

Contributions are welcome! If you have a bug fix or feature addition, please create a pull request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.