#pragma once
#include <AppCore/AppCore.h>
#include <vector>
#include "location.h"

using namespace ultralight;

class MyApp : public AppListener,
              public WindowListener,
              public LoadListener,
              public ViewListener {
public:
  MyApp();



  virtual ~MyApp();

  // Start the run loop.
  virtual void Run();

  // This is called continuously from the app's main loop.
  virtual void OnUpdate() override;

  // This is called when the window is closing.
  virtual void OnClose(ultralight::Window* window) override;

  // This is called whenever the window resizes.
  virtual void OnResize(ultralight::Window* window, uint32_t width, uint32_t height) override;

  // This is called when the page finishes a load in one of its frames.
  virtual void OnFinishLoading(ultralight::View* caller,
                               uint64_t frame_id,
                               bool is_main_frame,
                               const String& url) override;

  // This is called when the DOM has loaded in one of its frames.
  virtual void OnDOMReady(ultralight::View* caller,
                          uint64_t frame_id,
                          bool is_main_frame,
                          const String& url) override;

  void OnAddConsoleMessage(ultralight::View* caller,
      ultralight::MessageSource source,
      ultralight::MessageLevel level,
      const ultralight::String& message,
      uint32_t line_number,
      uint32_t column_number,
      const ultralight::String& source_id);

  JSValue GetArea(const JSObject& thisObject, const JSArgs& args);

  void loadData();

 void HandleWeatherData(const String& temperature, const String& weatherDescription);

 void PassDataToJavaScript(ultralight::View* caller, const String& temperature, const String& weatherDescription);
  // This is called when the page requests to change the Cursor.
  virtual void OnChangeCursor(ultralight::View* caller,
    Cursor cursor) override;

  virtual void OnChangeTitle(ultralight::View* caller,
    const String& title) override;

public:
  RefPtr<App> app_;
  RefPtr<Window> window_;
  RefPtr<Overlay> overlay_;
};
