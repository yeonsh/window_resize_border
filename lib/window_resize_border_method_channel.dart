import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'window_resize_border_platform_interface.dart';

/// An implementation of [WindowResizeBorderPlatform] that uses method channels.
class MethodChannelWindowResizeBorder extends WindowResizeBorderPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('window_resize_border');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }

  @override
  Future<bool> enableEnlargedBorders({int borderWidth = 8}) async {
    try {
      final result = await methodChannel.invokeMethod<bool>(
        'enableEnlargedBorders',
        {'borderWidth': borderWidth},
      );
      return result ?? false;
    } catch (e) {
      return false;
    }
  }

  @override
  Future<bool> disableEnlargedBorders() async {
    try {
      final result = await methodChannel.invokeMethod<bool>('disableEnlargedBorders');
      return result ?? false;
    } catch (e) {
      return false;
    }
  }
}