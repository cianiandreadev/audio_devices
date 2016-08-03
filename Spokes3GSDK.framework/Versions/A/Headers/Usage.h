#pragma once

#ifndef USAGE_H
#define USAGE_H


typedef struct
{
    uint16_t UsagePage;
    uint16_t UsageId;
    wchar_t const* UsageName;
    unsigned long Value;
} Usage;


#endif

