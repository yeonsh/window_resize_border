#include "include/window_resize_border/window_resize_border_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "window_resize_border_plugin.h"

void WindowResizeBorderPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  window_resize_border::WindowResizeBorderPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
