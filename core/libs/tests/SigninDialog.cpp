#include "prx/libSceSigninDialog/libSceSigninDialog.h"

#include <cstdlib>
#include <cstring>

namespace {

void expect(std::int32_t actual, std::int32_t expected) {
    if (actual != expected) {
        std::abort();
    }
}

}

int main() {
    constexpr auto notInitialized = static_cast<std::int32_t>(0x80B80003u);
    constexpr auto alreadyInitialized = static_cast<std::int32_t>(0x80B80004u);
    constexpr auto notFinished = static_cast<std::int32_t>(0x80B80005u);
    constexpr auto notRunning = static_cast<std::int32_t>(0x80B8000Bu);
    constexpr auto argNull = static_cast<std::int32_t>(0x80B8000Du);
    constexpr std::int32_t userCanceled = 1;
    constexpr std::int32_t statusNone = 0;
    constexpr std::int32_t statusInitialized = 1;
    constexpr std::int32_t statusFinished = 3;
    SceSigninDialogResult result{};
    expect(sceSigninDialogGetResult(&result), notInitialized);
    expect(sceSigninDialogGetStatus(), statusNone);
    expect(sceSigninDialogUpdateStatus(), statusNone);
    expect(sceSigninDialogClose(), notRunning);
    expect(sceSigninDialogTerminate(), notInitialized);
    expect(sceSigninDialogOpen(nullptr), notInitialized);

    expect(sceSigninDialogInitialize(), 0);
    expect(sceSigninDialogInitialize(), alreadyInitialized);
    expect(sceSigninDialogGetStatus(), statusInitialized);
    expect(sceSigninDialogUpdateStatus(), statusInitialized);
    expect(sceSigninDialogClose(), notRunning);
    expect(sceSigninDialogGetResult(nullptr), argNull);
    expect(sceSigninDialogGetResult(&result), notFinished);
    expect(sceSigninDialogOpen(nullptr), argNull);

    std::uint8_t param[0x10]{};
    expect(sceSigninDialogOpen(param), 0);
    expect(sceSigninDialogGetStatus(), statusFinished);
    expect(sceSigninDialogUpdateStatus(), statusFinished);
    expect(sceSigninDialogClose(), notRunning);
    expect(sceSigninDialogGetResult(nullptr), argNull);
    std::memset(&result, 0xFF, sizeof(result));
    expect(sceSigninDialogGetResult(&result), 0);
    expect(result.result, userCanceled);
    for (const std::int32_t word : result.reserved) expect(word, 0);
    expect(sceSigninDialogOpen(param), 0);

    expect(sceSigninDialogTerminate(), 0);
    expect(sceSigninDialogTerminate(), notInitialized);
    expect(sceSigninDialogGetStatus(), statusNone);
    expect(sceSigninDialogGetResult(&result), notInitialized);
    expect(sceSigninDialogClose(), notRunning);
    expect(sceSigninDialogOpen(param), notInitialized);
}
