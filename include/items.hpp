
namespace commands {



struct Command {
  enum RequestType { POST, GET, DELETE };
  enum ResponseType { JSON, TEXT, BINARY };
  const RequestType requestType;
  const char *command_name = "";
  const char *endpoint = "";
};



#define COMMAND(name, endpoint_name, requestType) \
struct name{ \
    const char *endpoint = endpoint_name ;\
    const char *command_name = #name;\
    const Command::RequestType requestType = requestType; \
}\

COMMAND(NewSession, "/session", POST);

COMMAND(DeleteSession, "/session/{sessionId}", DELETE);

COMMAND(Status, "/status", GET);

COMMAND(GetTimeouts, "/session/{sessionId}/timeouts", GET);

COMMAND(SetTimeouts, "/session/{sessionId}/timeouts", POST);

COMMAND(NavigateTo, "/session/{sessionId}/url", POST);

COMMAND(GetCurrentUrl, "/session/{sessionId}/url", GET);

COMMAND(Back, "/session/{sessionId}/back", POST);

COMMAND(Forward, "/session/{sessionId}/forward", POST);

COMMAND(Refresh, "/session/{sessionId}/refresh", POST);

COMMAND(GetTitle, "/session/{sessionId}/title", GET);

COMMAND(GetWindowHandle, "/session/{sessionId}/window", GET);

COMMAND(CloseWindow, "/session/{sessionId}/window", DELETE);

COMMAND(SwitchToWindow, "/session/{sessionId}/window", POST);

COMMAND(GetWindowHandles, "/session/{sessionId}/window/handles", GET);

COMMAND(SwitchToFrame, "/session/{sessionId}/frame", POST);

COMMAND(SwitchToParentFrame, "/session/{sessionId}/frame/parent", POST);

COMMAND(GetWindowRect, "/session/{sessionId}/window/rect", GET);

COMMAND(SetWindowRect, "/session/{sessionId}/window/rect", POST);

COMMAND(MaximizeWindow, "/session/{sessionId}/window/maximize", POST);

COMMAND(MinimizeWindow, "/session/{sessionId}/window/minimize", POST);

COMMAND(FullscreenWindow, "/session/{sessionId}/window/fullscreen", POST);

COMMAND(GetActiveElement, "/session/{sessionId}/element/active", GET);

COMMAND(FindElement, "/session/{sessionId}/element", POST);

COMMAND(FindElements, "/session/{sessionId}/elements", POST);

COMMAND(FindElementFromElement, "/session/{sessionId}/element/{elementId}/element", POST);

COMMAND(FindElementsFromElement, "/session/{sessionId}/element/{elementId}/elements", POST);

COMMAND(IsElementSelected, "/session/{sessionId}/element/{elementId}/selected", GET);

COMMAND(GetElementAttribute, "/session/{sessionId}/element/{elementId}/attribute/{name}", GET);

COMMAND(GetElementProperty, "/session/{sessionId}/element/{elementId}/property/{name}", GET);

COMMAND(GetElementCssValue, "/session/{sessionId}/element/{elementId}/css/{propertyName}", GET);

COMMAND(GetElementText, "/session/{sessionId}/element/{elementId}/text", GET);

COMMAND(GetElementTagName, "/session/{sessionId}/element/{elementId}/name", GET);

COMMAND(GetElementRect, "/session/{sessionId}/element/{elementId}/rect", GET);

COMMAND(IsElementEnabled, "/session/{sessionId}/element/{elementId}/enabled", GET);

COMMAND(ElementClick, "/session/{sessionId}/element/{elementId}/click", POST);

COMMAND(ElementClear, "/session/{sessionId}/element/{elementId}/clear", POST);

COMMAND(ElementSendKeys, "/session/{sessionId}/element/{elementId}/value", POST);

COMMAND(GetPageSource, "/session/{sessionId}/source", GET);

COMMAND(ExecuteScript, "/session/{sessionId}/execute/sync", POST);

COMMAND(ExecuteAsyncScript, "/session/{sessionId}/execute/async", POST);

COMMAND(GetAllCookies, "/session/{sessionId}/cookie", GET);

COMMAND(GetNamedCookie, "/session/{sessionId}/cookie/{name}", GET);

COMMAND(AddCookie, "/session/{sessionId}/cookie", POST);

COMMAND(DeleteCookie, "/session/{sessionId}/cookie/{name}", DELETE);

COMMAND(DeleteAllCookies, "/session/{sessionId}/cookie", DELETE);

COMMAND(PerformActions, "/session/{sessionId}/actions", POST);

COMMAND(ReleaseActions, "/session/{sessionId}/actions", DELETE);

COMMAND(DismissAlert, "/session/{sessionId}/alert/dismiss", POST);

COMMAND(AcceptAlert, "/session/{sessionId}/alert/accept", POST);

COMMAND(GetAlertText, "/session/{sessionId}/alert/text", GET);

COMMAND(SendAlertText, "/session/{sessionId}/alert/text", POST);

COMMAND(TakeScreenshot, "/session/{sessionId}/screenshot", GET);

COMMAND(TakeElementScreenshot, "/session/{sessionId}/element/{elementId}/screenshot", GET);



#undef COMMAND


} // namespace commands