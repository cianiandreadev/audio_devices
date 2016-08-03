/***************************************************************************
 *
 * Copyright  2012 Plantronics, Inc. All rights reserved.
 * This code is confidential and proprietary information belonging
 * to Plantronics, Inc. and may not be copied, modified or distributed
 * without the express written consent of Plantronics, Inc.
 *
 * Purpose: HID platform-independent basic types
 * 
 ****************************************************************************/

#pragma once
#if !defined INC_HIDTYPES
#define      INC_HIDTYPES


/** An USB HID usage ID */
typedef uint16_t USAGE;

/** Type of the USB HID report: Input, Output or Feature
*/
enum ReportType
{
    REPORT_TYPE_INPUT,
    REPORT_TYPE_OUTPUT,
    REPORT_TYPE_FEATURE
};

/** Contains information about the capability of a HID control button
    usage (or a set of buttons associated with a usage range).
    HIDAL currently does not support ranged button
    capabilities/usages.  
*/
struct ButtonCap
{
    ButtonCap() {} ///needed for make_shared() (C4345)
    /// Specifies the usage page for a usage or usage range.
    uint16_t UsagePage;
    /// Specifies the report ID of the HID report that contains the
    /// usage or usage range.
    int8_t ReportID;
    /// True if a button has a set of aliased usages. False if the
    /// button has only one usage.
    bool IsAlias;
    /// Contains the data fields (one or two bytes) associated with an
    /// input, output, or feature main item.
    uint16_t BitField;
    /// Specifies the index of the link collection in a top-level
    /// collection's link collection array that contains the usage or
    /// usage range. If LinkCollection is zero, the usage or usage
    /// range is contained in the top-level collection.
    uint16_t LinkCollection;
    /// Specifies the usage page of the link collection that contains
    /// the usage or usage range.  If LinkCollection is zero,
    /// LinkUsagePage specifies the usage page of the top-level
    /// collection.
    uint16_t LinkUsagePage;
    /// Specifies the usage of the link collection that contains the
    /// usage or usage range.  If LinkCollection is zero, LinkUsage
    /// specifies the usage of the top-level collection.
    uint16_t LinkUsage;
    /// True if the structure describes a usage range. False if the
    /// structure describes a single usage.
    bool IsRange;
    /// True if the usage or usage range has a set of string
    /// descriptors. False if the usage or usage range has zero or one
    /// string descriptor.
    bool IsStringRange;
    /// True if the usage or usage range has a set of
    /// designators. False if the usage or usage range has zero or one
    /// designator.
    bool IsDesignatorRange;
    /// Specifies, if TRUE, that the button usage or usage range
    /// provides absolute data. Otherwise, if IsAbsolute is FALSE, the
    /// button data is the change in state from the previous value.
    bool IsAbsolute;
    /// For a single usage, indicates a usage ID
    uint16_t Usage;
    /// For a single usage, specifies the data index specified by Usage.
    uint16_t DataIndex;
};

/** Contains information about a top-level collection's capability.
    HIDAL currently does not support collections other than the
    top-level collection.
*/
struct DeviceCaps
{
    /// Specifies the top-level collection's usage page.
    uint16_t UsagePage;
    /// Specifies a top-level collection's usage ID.
    USAGE Usage;
    /// Specifies the maximum size, in bytes, of all the input reports
    /// (including the report ID, if report IDs are used, which is
    /// prepended to the report data).
    uint16_t InputReportLength;
    /// Specifies the number of input ButtonCaps structures that
    /// hidal_get_button_caps returns.
    uint16_t InputButtonCaps;
    /// Specifies the number of input ValueCaps structures that
    /// hidal_get_value_caps returns.
    uint16_t InputValueCaps;
    /// Specifies the number of data indices assigned to buttons and
    /// values in all input reports.
    uint16_t InputDataIndexes;
    /// Specifies the maximum size, in bytes, of all the output
    /// reports (including the report ID, if report IDs are used,
    /// which is prepended to the report data).
    uint16_t OutputReportLength;
    /// Specifies the number of output ButtonCaps structures that
    /// hidal_get_button_caps returns.
    uint16_t OutputButtonCaps;
    /// Specifies the number of output ValueCaps structures that
    /// hidal_get_value_caps returns.
    uint16_t OutputValueCaps;
    /// Specifies the number of data indices assigned to buttons and
    /// values in all output reports.
    uint16_t OutputDataIndexes;
    /// Specifies the maximum length, in bytes, of all the feature
    /// reports (including the report ID, if report IDs are used,
    /// which is prepended to the report data).
    uint16_t FeatureReportLength;
    /// Specifies the total number of feature ButtonCaps structures
    /// that hidal_get_button_caps returns.
    uint16_t FeatureButtonCaps;
    /// Specifies the total number of feature ValueCaps structures
    /// that hidal_get_value_caps returns.
    uint16_t FeatureValueCaps;
    /// Specifies the number of data indices assigned to buttons and
    /// values in all feature reports.
    uint16_t FeatureDataIndexes;
};

/** Contains information that describes the capability of a set of HID
    control values (either a single usage or a usage range).  
*/
struct ValueCap
{
    ValueCap() {} //needed for make_shared() (C4345)
    /// Specifies the usage page of the usage or usage range.
    uint16_t UsagePage;
    /// Specifies the report ID of the HID report that contains the usage or usage range.
    int8_t ReportID;
    /// Indicates, if TRUE, that the usage is member of a set of
    /// aliased usages. Otherwise, if IsAlias is FALSE, the value has
    /// only one usage.
    bool IsAlias;
    /// Contains the data fields (one or two bytes) associated with an
    /// input, output, or feature main item.
    uint16_t BitField;
    /// Specifies the index of the link collection in a top-level
    /// collection's link collection array that contains the usage or
    /// usage range.  If LinkCollection is zero, the usage or usage
    /// range is contained in the top-level collection.
    uint16_t LinkCollection;
    /// Specifies the usage page of the link collection that contains
    /// the usage or usage range.  If LinkCollection is zero,
    /// LinkUsagePage specifies the usage page of the top-level
    /// collection.
    uint16_t LinkUsagePage;
    /// Specifies the usage of the link collection that contains the
    /// usage or usage range.  If LinkCollection is zero, LinkUsage
    /// specifies the usage of the top-level collection.
    uint16_t LinkUsage;
    /// True if the structure describes a usage range. False if the
    /// structure describes a single usage.
    bool IsRange;
    /// True if the usage or usage range has a set of string
    /// descriptors. False if the usage or usage range has zero or one
    /// string descriptor.
    bool IsStringRange;
    /// True if the usage or usage range has a set of
    /// designators. False if the usage or usage range has zero or one
    /// designator.
    bool IsDesignatorRange;
    /// True if the usage or usage range provides absolute data. False
    /// if the value is the change in state from the previous value.
    bool IsAbsolute;
    /// True if the usage supports a NULL value, which indicates that
    /// the data is not valid and should be ignored.
    bool HasNull;
    /// Specifies the size, in bits, of a usage's data field in a
    /// report. If ReportCount is greater than one, each usage has a
    /// separate data field of this size.
    uint16_t BitSize;
    /// Specifies the number of usages that this structure describes.
    uint16_t ReportCount;
    /// Specifies the usage's exponent, as described by the USB HID standard.
    uint32_t UnitsExp;
    /// Specifies the usage's units, as described by the USB HID Standard.
    uint32_t Units;
    /// Specifies a usage's signed lower bound.
    int32_t LogicalMin;
    /// Specifies a usage's signed upper bound.
    int32_t LogicalMax;
    /// Specifies a usage's signed lower bound after scaling is
    /// applied to the logical minimum value.
    int32_t PhysicalMin;
    /// Specifies a usage's signed upper bound after scaling is
    /// applied to the logical maximum value.
    int32_t PhysicalMax;
    union {
        /// If IsRange is FALSE, information about a single usage
        struct {
            /// Indicates a usage ID.
            uint16_t Usage;
            /// Indicates a string descriptor ID for the usage specified by NotRange.Usage.
            uint16_t StringIndex;
            /// Indicates a designator ID for the usage specified by NotRange.Usage.
            uint16_t DesignatorIndex;
            /// Indicates the data index of the usage specified by NotRange.Usage.
            uint16_t DataIndex;
        } NotRange;
        /// If IsRange is TRUE, Range contains information about a usage range
        struct {
            /// Indicates the inclusive upper bound of a sequential
            /// range of data indices that correspond, one-to-one and
            /// in the same order, to the usages specified by the
            /// usage range Range.UsageMin to Range.UsageMax.
            uint16_t UsageMin;
            /// Indicates the inclusive lower bound of usage range
            /// whose inclusive upper bound is specified by
            /// Range.UsageMax.
            uint16_t UsageMax;
            /// Indicates the inclusive upper bound of a usage range
            /// whose inclusive lower bound is indicated by
            /// Range.UsageMin.
            uint16_t StringMin;
            /// Indicates the inclusive lower bound of a range of
            /// string descriptors (specified by string minimum and
            /// string maximum items) whose inclusive upper bound is
            /// indicated by Range.StringMax.
            uint16_t StringMax;
            /// Indicates the inclusive upper bound of a range of
            /// string descriptors (specified by string minimum and
            /// string maximum items) whose inclusive lower bound is
            /// indicated by Range.StringMin.
            uint16_t DesignatorMin;
            /// Indicates the inclusive lower bound of a range of
            /// designators (specified by designator minimum and
            /// designator maximum items) whose inclusive lower bound
            /// is indicated by Range.DesignatorMax.
            uint16_t DesignatorMax;
            /// Indicates the inclusive upper bound of a range of
            /// designators (specified by designator minimum and
            /// designator maximum items) whose inclusive lower bound
            /// is indicated by Range.DesignatorMin.
            uint16_t DataIndexMin;
            /// Indicates the inclusive lower bound of a sequential
            /// range of data indices that correspond, one-to-one and
            /// in the same order, to the usages specified by the
            /// usage range Range.UsageMin to Range.UsageMax.
            uint16_t DataIndexMax;
        } Range;
    };
} ;


#endif // define      INC_HIDTYPES
