#define GDT_TYPE_CODE   0x0A
#define GDT_TYPE_DATA   0x02
#define GDT_TYPE_TSS    0x09

#define GDT_FLAGS_LOWER_S       0x10
#define GDT_FLAGS_LOWER_DPL(x)  (0x20 * x)
#define GDT_FLAGS_LOWER_P       0x80
#define GDT_FLAGS_UPPER_L       0x20
#define GDT_FLAGS_UPPER_DB      0x40
#define GDT_FLAGS_UPPER_G       0x80

#define GDT_FLAGS_LOWER_KERNELCODE ( GDT_TYPE_CODE | GDT_FLAGS_LOWER_S | \
                                     GDT_FLAGS_LOWER_DPL(0) | GDT_FLAGS_LOWER_P )
#define GDT_FLAGS_LOWER_KERNELDATA ( GDT_TYPE_DATA | GDT_FLAGS_LOWER_S | \
                                     GDT_FLAGS_LOWER_DPL(0) | GDT_FLAGS_LOWER_P )
#define GDT_FLAGS_LOWER_TSS        ( GDT_FLAGS_LOWER_DPL(0) | GDT_FLAGS_LOWER_P )
#define GDT_FLAGS_LOWER_USERCODE   ( GDT_TYPE_CODE | GDT_FLAGS_LOWER_S | \
                                     GDT_FLAGS_LOWER_DPL(3) | GDT_FLAGS_LOWER_P )
#define GDT_FLAGS_LOWER_USERDATA   ( GDT_TYPE_DATA | GDT_FLAGS_LOWER_S | \
                                     GDT_FLAGS_LOWER_DPL(3) | GDT_FLAGS_LOWER_P )

#pragma pack( push, 1 )

typedef struct kGDTRStruct {
    WORD   limit;
    QWORD  baseAddress;
    WORD   padding16;
    DWORD  padding32;
} GDTR, IDTR;

typedef struct kGDTEntry8Struct {
    WORD   lowerLimit;
    WORD   lowerBaseAddress;
    BYTE   upperBaseAddress1;
    BYTE   typeAndLowerFlag;
    BYTE   upperLimitAndUpperFlag;
    BYTE   upperBaseAddress2;
} GDTENTRY8;

typedef struct kGDTEntry16Struct {
    WORD   lowerLimit;
    WORD   lowerBaseAddress;
    BYTE   middleBaseAddress1;
    BYTE   typeAndLowerFlag;
    BYTE   upperLimitAndUpperFlag;
    BYTE   middleBaseAddress2;
    DWORD  upperBaseAddress;
    DWORD  reserved;
} GDTENTRY16;

typedef struct kTSSDataStruct {
    DWORD  reserved1;
    QWORD  rsp[ 3 ];
    QWORD  reserved2;
    QWORD  ist[ 7 ];
    QWORD  reserved3;
    WORD   reserved;
    WORD   ioMapBaseAddress;
} TSSSEGMENT;

#pragma pack( pop )
