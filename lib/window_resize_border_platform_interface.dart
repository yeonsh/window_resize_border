import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'window_resize_border_method_channel.dart';

abstract class WindowResizeBorderPlatform extends PlatformInterface {
  /// Constructs a WindowResizeBorderPlatform.
  WindowResizeBorderPlatform() : super(token: _token);

  static final Object _token = Object();

  static WindowResizeBorderPlatform _instance = MethodChannelWindowResizeBorder();

  /// The default instance of [WindowResizeBorderPlatform] to use.
  ///
  /// Defaults to [MethodChannelWindowResizeBorder].
  static WindowResizeBorderPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [WindowResizeBorderPlatform] when
  /// they register themselves.
  static set instance(WindowResizeBorderPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }

  /// Enables enlarged resize borders with the specified width in logical pixels.
  /// Returns true if successful, false otherwise.
  Future<bool> enableEnlargedBorders({int borderWidth = 8}) {
    throw UnimplementedError('enableEnlargedBorders() has not been implemented.');
  }

  /// Disables enlarged resize borders, returning to system defaults.
  /// Returns true if successful, false otherwise.
  Future<bool> disableEnlargedBorders() {
    throw UnimplementedError('disableEnlargedBorders() has not been implemented.');
  }
}