#ifndef CORE_LIBS_PRX_LIBSCESIGNINDIALOG_LIBSCESIGNINDIALOG_H
#define CORE_LIBS_PRX_LIBSCESIGNINDIALOG_LIBSCESIGNINDIALOG_H

#include <cstdint>
#include "SceTypes.hpp"

struct SceSigninDialogResult {
    std::int32_t result;
    std::int32_t reserved[3];
};
static_assert(sizeof(SceSigninDialogResult) == 16);

extern "C" {

std::int32_t APS5_VABI sceSigninDialogInitialize(void);
std::int32_t APS5_VABI sceSigninDialogOpen(const void* param);
std::int32_t APS5_VABI sceSigninDialogUpdateStatus(void);
std::int32_t APS5_VABI sceSigninDialogGetStatus(void);
std::int32_t APS5_VABI sceSigninDialogClose(void);
std::int32_t APS5_VABI sceSigninDialogTerminate(void);
std::int32_t APS5_VABI sceSigninDialogGetResult(SceSigninDialogResult* result);

}

#endif
