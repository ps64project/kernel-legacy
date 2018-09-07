
// Page Entry :: Attributes 

constexpr DWORD PAGE_FLAGS_P     = 1;
constexpr DWORD PAGE_FLAGS_RW    = 1 << 1;
constexpr DWORD PAGE_FLAGS_US    = 1 << 2;
constexpr DWORD PAGE_FLAGS_PWT   = 1 << 3;
constexpr DWORD PAGE_FLAGS_PCD   = 1 << 4;
constexpr DWORD PAGE_FLAGS_A     = 1 << 5;
constexpr DWORD PAGE_FLAGS_D     = 1 << 6;
constexpr DWORD PAGE_FLAGS_PS    = 1 << 7;
constexpr DWORD PAGE_FLAGS_G     = 1 << 8;
constexpr DWORD PAGE_FLAGS_PAT   = 1 << 11;
constexpr DWORD PAGE_DEFAULT     = PAGE_FLAGS_P | PAGE_FLAGS_RW;
