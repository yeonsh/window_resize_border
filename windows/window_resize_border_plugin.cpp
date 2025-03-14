#include "window_resize_border_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>
#include <windowsx.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace window_resize_border {

// Static variable initialization
WNDPROC WindowResizeBorderPlugin::original_window_proc_ = nullptr;
bool WindowResizeBorderPlugin::enlarged_borders_enabled_ = false;
int WindowResizeBorderPlugin::border_width_ = 8;
std::unordered_map<HWND, WindowResizeBorderPlugin*> WindowResizeBorderPlugin::window_to_plugin_;

// static
void WindowResizeBorderPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "window_resize_border",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<WindowResizeBorderPlugin>();
  plugin->SetupWindowInterceptor(registrar);

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

WindowResizeBorderPlugin::WindowResizeBorderPlugin() : window_handle_(nullptr) {}

WindowResizeBorderPlugin::~WindowResizeBorderPlugin() {
  CleanupWindowInterceptor();
}

void WindowResizeBorderPlugin::SetupWindowInterceptor(flutter::PluginRegistrarWindows* registrar) {
  // Get the window handle from the registrar
  window_handle_ = registrar->GetView()->GetNativeWindow();
  
  // Store this plugin instance in the map
  window_to_plugin_[window_handle_] = this;
  
  // Replace the window procedure with our custom one
  original_window_proc_ = reinterpret_cast<WNDPROC>(
      SetWindowLongPtr(window_handle_, GWLP_WNDPROC, 
                      reinterpret_cast<LONG_PTR>(WindowProc)));
}

void WindowResizeBorderPlugin::CleanupWindowInterceptor() {
  // Restore the original window procedure if it exists
  if (window_handle_ && original_window_proc_) {
    SetWindowLongPtr(window_handle_, GWLP_WNDPROC, 
                     reinterpret_cast<LONG_PTR>(original_window_proc_));
    
    // Remove this instance from the map
    window_to_plugin_.erase(window_handle_);
  }
}

LRESULT CALLBACK WindowResizeBorderPlugin::WindowProc(HWND hwnd, UINT message, 
                                                    WPARAM wparam, LPARAM lparam) {
  // If WM_NCHITTEST and enlarged borders are enabled, process it
  if (message == WM_NCHITTEST && enlarged_borders_enabled_) {
    LRESULT result = HandleHitTest(hwnd, wparam, lparam);
    if (result != 0) {
      return result;
    }
  }
  
  // Otherwise, pass to the original window procedure
  return CallWindowProc(original_window_proc_, hwnd, message, wparam, lparam);
}

LRESULT WindowResizeBorderPlugin::HandleHitTest(HWND hwnd, WPARAM wparam, LPARAM lparam) {
  // Get the window rectangle
  RECT window_rect;
  GetWindowRect(hwnd, &window_rect);
  
  // Get the cursor position (x, y)
  int x = GET_X_LPARAM(lparam);
  int y = GET_Y_LPARAM(lparam);
  
  // Check if cursor is in the border area
  bool in_left = x >= window_rect.left && x < window_rect.left + border_width_;
  bool in_right = x < window_rect.right && x >= window_rect.right - border_width_;
  bool in_top = y >= window_rect.top && y < window_rect.top + border_width_;
  bool in_bottom = y < window_rect.bottom && y >= window_rect.bottom - border_width_;
  
  // Determine the hit test result based on cursor position
  if (in_left && in_top) {
    return HTTOPLEFT;
  } else if (in_right && in_top) {
    return HTTOPRIGHT;
  } else if (in_left && in_bottom) {
    return HTBOTTOMLEFT;
  } else if (in_right && in_bottom) {
    return HTBOTTOMRIGHT;
  } else if (in_left) {
    return HTLEFT;
  } else if (in_right) {
    return HTRIGHT;
  } else if (in_top) {
    return HTTOP;
  } else if (in_bottom) {
    return HTBOTTOM;
  }
  
  // Not in the border area
  return 0;
}

void WindowResizeBorderPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";
    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    result->Success(flutter::EncodableValue(version_stream.str()));
  } else if (method_call.method_name().compare("enableEnlargedBorders") == 0) {
    // Get the border width from the arguments
    const auto* arguments = std::get_if<flutter::EncodableMap>(method_call.arguments());
    if (arguments) {
      auto border_width_it = arguments->find(flutter::EncodableValue("borderWidth"));
      if (border_width_it != arguments->end()) {
        border_width_ = std::get<int>(border_width_it->second);
      }
    }
    
    // Enable enlarged borders
    enlarged_borders_enabled_ = true;
    
    // Return success
    result->Success(flutter::EncodableValue(true));
  } else if (method_call.method_name().compare("disableEnlargedBorders") == 0) {
    // Disable enlarged borders
    enlarged_borders_enabled_ = false;
    
    // Return success
    result->Success(flutter::EncodableValue(true));
  } else {
    result->NotImplemented();
  }
}

}  // namespace window_resize_border