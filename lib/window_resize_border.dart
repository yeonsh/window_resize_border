import 'window_resize_border_platform_interface.dart';

class WindowResizeBorder {
  Future<String?> getPlatformVersion() {
    return WindowResizeBorderPlatform.instance.getPlatformVersion();
  }

  /// Enables enlarged resize borders with the specified width in logical pixels.
  /// Returns true if successful, false otherwise.
  Future<bool> enableEnlargedBorders({int borderWidth = 8}) {
    return WindowResizeBorderPlatform.instance.enableEnlargedBorders(
      borderWidth: borderWidth,
    );
  }

  /// Disables enlarged resize borders, returning to system defaults.
  /// Returns true if successful, false otherwise.
  Future<bool> disableEnlargedBorders() {
    return WindowResizeBorderPlatform.instance.disableEnlargedBorders();
  }
}