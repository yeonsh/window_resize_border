#ifndef FLUTTER_PLUGIN_WINDOW_RESIZE_BORDER_PLUGIN_H_
#define FLUTTER_PLUGIN_WINDOW_RESIZE_BORDER_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>
#include <unordered_map>

namespace window_resize_border {

class WindowResizeBorderPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  WindowResizeBorderPlugin();

  virtual ~WindowResizeBorderPlugin();

  // Disallow copy and assign.
  WindowResizeBorderPlugin(const WindowResizeBorderPlugin&) = delete;
  WindowResizeBorderPlugin& operator=(const WindowResizeBorderPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
 
 private:
  // The original window procedure
  static WNDPROC original_window_proc_;
  
  // Flag to determine if enlarged borders are enabled
  static bool enlarged_borders_enabled_;
  
  // Border width in pixels
  static int border_width_;
  
  // Map to store window handle to plugin instance
  static std::unordered_map<HWND, WindowResizeBorderPlugin*> window_to_plugin_;
  
  // The window handle
  HWND window_handle_;
  
  // The window procedure that will handle WM_NCHITTEST
  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
  
  // Set up the custom window procedure
  void SetupWindowInterceptor(flutter::PluginRegistrarWindows* registrar);
  
  // Clean up the window procedure
  void CleanupWindowInterceptor();
  
  // Process WM_NCHITTEST message to enable larger borders
  static LRESULT HandleHitTest(HWND hwnd, WPARAM wparam, LPARAM lparam);
};

}  // namespace window_resize_border

#endif  // FLUTTER_PLUGIN_WINDOW_RESIZE_BORDER_PLUGIN_H_