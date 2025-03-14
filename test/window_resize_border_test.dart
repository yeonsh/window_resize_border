import 'package:flutter_test/flutter_test.dart';
import 'package:window_resize_border/window_resize_border.dart';
import 'package:window_resize_border/window_resize_border_platform_interface.dart';
import 'package:window_resize_border/window_resize_border_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockWindowResizeBorderPlatform
    with MockPlatformInterfaceMixin
    implements WindowResizeBorderPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final WindowResizeBorderPlatform initialPlatform = WindowResizeBorderPlatform.instance;

  test('$MethodChannelWindowResizeBorder is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelWindowResizeBorder>());
  });

  test('getPlatformVersion', () async {
    WindowResizeBorder windowResizeBorderPlugin = WindowResizeBorder();
    MockWindowResizeBorderPlatform fakePlatform = MockWindowResizeBorderPlatform();
    WindowResizeBorderPlatform.instance = fakePlatform;

    expect(await windowResizeBorderPlugin.getPlatformVersion(), '42');
  });
}
