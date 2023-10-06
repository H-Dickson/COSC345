#include "MyApp.h"
#include "calculate.h"
#include "location.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Ultralight/Ultralight.h>
#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 600


using namespace ultralight;

std::vector<Location> locations;

inline std::string ToUTF8(const String& str) {
    String8 utf8 = str.utf8();
    return std::string(utf8.data(), utf8.length());
}

inline const char* Stringify(MessageSource source) {
    switch (source) {
    case kMessageSource_XML: return "XML";
    case kMessageSource_JS: return "JS";
    case kMessageSource_Network: return "Network";
    case kMessageSource_ConsoleAPI: return "ConsoleAPI";
    case kMessageSource_Storage: return "Storage";
    case kMessageSource_AppCache: return "AppCache";
    case kMessageSource_Rendering: return "Rendering";
    case kMessageSource_CSS: return "CSS";
    case kMessageSource_Security: return "Security";
    case kMessageSource_ContentBlocker: return "ContentBlocker";
    case kMessageSource_Other: return "Other";
    default: return "";
    }
}

inline const char* Stringify(MessageLevel level) {
    switch (level) {
    case kMessageLevel_Log: return "Log";
    case kMessageLevel_Warning: return "Warning";
    case kMessageLevel_Error: return "Error";
    case kMessageLevel_Debug: return "Debug";
    case kMessageLevel_Info: return "Info";
    default: return "";
    }
}


MyApp::MyApp() {



    ///
    /// Create our main App instance.
    ///
    app_ = App::Create();


    ///
    /// Create a resizable window by passing by OR'ing our window flags with
    /// kWindowFlags_Resizable.
    /// 
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

JSValueRef MyCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    if (argumentCount == 2) {
        double arg1 = JSValueToNumber(ctx, arguments[0], NULL);
        double arg2 = JSValueToNumber(ctx, arguments[1], NULL);

        // Perform C++ logic with the arguments
        double result = arg1 + arg2;

        // Return a value to JavaScript
        return JSValueMakeNumber(ctx, result);
    }

    // Handle invalid number of arguments or other error cases
    return JSValueMakeUndefined(ctx);
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

void MyApp::loadData() {
    std::cout << "inside Load" << std::endl;
    std::string filename = "./assets/region_data/sorted_file.csv";
    locations = readDataFromFile(filename);

    if (locations.empty()) {
        std::cout << "Error: No data loaded from the CSV file." << std::endl;
        return;
    }

    std::cout << "Location data loaded:" << std::endl;

 
}


JSValue MyApp::GetArea(const JSObject& thisObject, const JSArgs& args) {
    std::cout << "GetArea Called"  << std::endl;
    ultralight::String lat = args[0].ToString();
    std::string lat_t = std::string(lat.utf8().data());
    ultralight::String lon = args[1].ToString();
    std::string lon_t = std::string(lon.utf8().data());
    std::cout << "Latitude: " << lat_t << " Longitude: " << lon_t << std::endl;

    // Call the CalculateArea function from the Calculator class
    MyCalculator calculate;
    std::string area = calculate.CalculateArea(lat_t, lon_t, locations);
    std::cout << "Returned from Calculate" << area << std::endl;
    // Convert the calculated area to a JSValue and return it
    return JSValue(area.c_str());
}





void MyApp::OnDOMReady(ultralight::View* caller,
    uint64_t frame_id,
    bool is_main_frame,
    const String& url) {
    std::cout << "OnDOMReady called" << std::endl;
    std::cout << "Calling load" << std::endl;
    loadData();
    std::cout << "Finished load" << std::endl;
    RefPtr<JSContext> context = caller->LockJSContext();
    SetJSContext(context->ctx());

    JSObject global = JSGlobalObject();
    global["GetArea"] = BindJSCallbackWithRetval(&MyApp::GetArea);
    if (is_main_frame) {
        // Access the view object from the caller
        ultralight::View* view = caller;

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

void MyApp::OnAddConsoleMessage(View* caller,
    MessageSource source,
    MessageLevel level,
    const String& message,
    uint32_t line_number,
    uint32_t column_number,
    const String& source_id) {

    std::cout << "[Console]: [" << Stringify(source) << "] ["
        << Stringify(level) << "] " << ToUTF8(message);

    if (source == kMessageSource_JS) {
        std::cout << " (" << ToUTF8(source_id) << " @ line " << line_number
            << ", col " << column_number << ")";
    }

    std::cout << std::endl;

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
