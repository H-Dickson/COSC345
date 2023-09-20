#include "MyApp.h"
#include <iostream>
#include <Ultralight/Ultralight.h>

#define WINDOW_WIDTH  700
#define WINDOW_HEIGHT 500

using namespace ultralight;

MyApp::MyApp() {
    ///
    /// Create our main App instance.
    ///
    app_ = App::Create();


    ///
    /// Create a resizable window by passing by OR'ing our window flags with
    /// kWindowFlags_Resizable.
    ///
    window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
        false, kWindowFlags_Titled | kWindowFlags_Resizable);

    ///
    /// Create our HTML overlay-- we don't care about its initial size and
    /// position because it'll be calculated when we call OnResize() below.
    ///
    overlay_ = Overlay::Create(window_, 1, 1, 0, 0);

    ///
    /// Force a call to OnResize to perform size/layout of our overlay.
    ///
    OnResize(window_.get(), window_->width(), window_->height());

    ///
    /// Load a page into our overlay's View
    ///
    overlay_->view()->LoadURL("file:///app.html");

    ///
    /// Register our MyApp instance as an AppListener so we can handle the
    /// App's OnUpdate event below.
    ///
    app_->set_listener(this);

    ///
    /// Register our MyApp instance as a WindowListener so we can handle the
    /// Window's OnResize event below.
    ///
    window_->set_listener(this);

    ///
    /// Register our MyApp instance as a LoadListener so we can handle the
    /// View's OnFinishLoading and OnDOMReady events below.
    ///
    overlay_->view()->set_load_listener(this);

    ///
    /// Register our MyApp instance as a ViewListener so we can handle the
    /// View's OnChangeCursor and OnChangeTitle events below.
    ///
    overlay_->view()->set_view_listener(this);
}

MyApp::~MyApp() {
}

void MyApp::Run() {
    app_->Run();
}

void MyApp::OnUpdate() {
    ///
    /// This is called repeatedly from the application's update loop.
    ///
    /// You should update any app logic here.
    ///
}

void MyApp::OnClose(ultralight::Window* window) {
    app_->Quit();
}

void MyApp::OnResize(ultralight::Window* window, uint32_t width, uint32_t height) {
    ///
    /// This is called whenever the window changes size (values in pixels).
    ///
    /// We resize our overlay here to take up the entire window.
    ///
    overlay_->Resize(width, height);
}

void MyApp::OnFinishLoading(ultralight::View* caller,
    uint64_t frame_id,
    bool is_main_frame,
    const String& url) {
    ///
    /// This is called when a frame finishes loading on the page.
    ///
}

void MyApp::OnDOMReady(ultralight::View* caller,
    uint64_t frame_id,
    bool is_main_frame,
    const String& url) {
    if (is_main_frame) {
        // Access the view object from the caller
        ultralight::View* view = caller;

        // Now you can use 'view' to evaluate JavaScript
        view->EvaluateScript("setupCommunication();"); // Call a JavaScript function to set up communication
    }
}

void MyApp::OnChangeCursor(ultralight::View* caller,
    Cursor cursor) {
    window_->SetCursor(cursor);
}

void MyApp::OnChangeTitle(ultralight::View* caller,
    const String& title) {
    window_->SetTitle(title.utf8().data());
}

// This function will be called from JavaScript
void MyApp::HandleWeatherData(const String& temperature, const String& weatherDescription) {
    // Handle the data received from JavaScript
    std::cout << "Temperature from JavaScript: " << temperature.utf8().data() << std::endl;
    std::cout << "Weather description from JavaScript: " << weatherDescription.utf8().data() << std::endl;
    // Perform C++ logic with the data
}
void MyApp::PassDataToJavaScript(ultralight::View* caller, const String& temperature, const String& weatherDescription)
{
    ultralight::View* view = caller;
    const String& temp = "20.20";
    const String& weather = "Looks good";
    // Call the JavaScript function with the data
    view->EvaluateScript(
        "receiveDataFromCpp('" + temp + "', '" + weather + "');"
    );


}