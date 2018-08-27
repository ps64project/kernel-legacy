// PS64 Kernel Start

#include <Types.hpp>

void KernelPrints(const int, const int, const char*);

void KernelStart() {
    KernelPrints(0, 3, "PS64 Kernel Started...");

    while (TRUE) ;
}

void KernelPrints(const int xPos, const int yPos, const char* str) {
   static CHARACTER* screen = (CHARACTER*) 0xB8000;

   screen += (yPos * 80) + xPos;
   for (int i = 0; str[ i ]; ++i )
       screen[ i ].Character = str[ i ];
}
