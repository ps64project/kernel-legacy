/**
 *  MINT64/PS64 ImageMaker
 *  
 *  Originally Written by Seunghoon Han
 *  Rewritten with C++ by 0x00000FF, 2018.
 *
 *  USAGE: imgcreator <bootloader> <kernel32> <kernel64>
 */

#include <iostream>
#include <fstream>

#define  GET_SECTOR_SIZE(stream) (stream.tellg() % 512 ? stream.tellg() / 512 + 1 : (Size32) stream.tellg());

constexpr uint16_t BYTESPERSECTOR { 512 };

using namespace std;

using Int32          = int32_t;
using Size8          = uint8_t;
using Size32         = uint32_t;
using FileDescriptor = int32_t;

void  CopyFile( std::ifstream&, std::ofstream& );
void  WriteKernelInformation ( std::ofstream&, Size8, Size8 );

int main(int argc, char* argv[]) {
    std::ifstream sourceStream;
    std::ofstream targetStream;
    
    Size32 bootloaderSize , sourceSize;
    Size8  kernel32Sectors, kernel64Sectors;

    cout << "PS64 ImageMaker v1.00" << endl
         << "===============" << endl;

    if ( argc != 4 ) {
        cerr << "[ERROR] Insufficient Arguments" << endl
             << "ImageMaker requires all of kernel components as arguments" << endl
             << "USAGE: " << argv[0] << " <Bootloader> <Kernel32> <Kernel64>" << endl ;
        
        return -1;
    }

    cout << "[INFO]  Creating Disk.img Prototype..." << endl;
    targetStream = std::ofstream( "Disk.img", ofstream::out );

    sourceStream = std::ifstream( argv[1] );
    if (!sourceStream.is_open()) {
        cerr << "[ERROR] Bootloader could not be opened, STOPPED" << endl;
        return 1;
    }

    cout << "[INFO]  Copying Bootloader into Disk Image..." << endl;
    CopyFile ( sourceStream, targetStream );

    sourceStream.close();

    sourceStream = std::ifstream( argv[2] );
    if (!sourceStream.is_open()) {
        cerr << "[ERROR] Kernel32 could not be opened, STOPPED" << endl;
        return 2;
    }

    cout << "[INFO]  Copying Kernel32 into Disk Image..." << endl;
    CopyFile ( sourceStream, targetStream );

    kernel32Sectors = GET_SECTOR_SIZE(sourceStream);
    sourceStream.close();

    sourceStream = std::ifstream( argv[3] );
    if (!sourceStream.is_open()) {
        cerr << "[ERROR] Kernel64 could not be opened, STOPPED" << endl;
        return 3;
    }

    cout << "[INFO]  Copying Kernel64 into Disk Image..." << endl;
    CopyFile( sourceStream, targetStream);

    kernel64Sectors = GET_SECTOR_SIZE(sourceStream);
    sourceStream.close();

    cout << "[INFO]  Writing Kernel Information into Disk Image..." << endl;
    WriteKernelInformation( targetStream, kernel32Sectors, kernel64Sectors );

    targetStream.close();

    return 0;
}

void CopyFile( std::ifstream& source, std::ofstream& target ) { 
    target << source.rdbuf();

    auto i = (Size32) 0;
    auto padBytes = static_cast<Size32>(source.tellg()) % BYTESPERSECTOR;

    if (padBytes) {
        for ( i = 0; i < BYTESPERSECTOR - padBytes; ++i) target.put( (char) 0 );
    }

    cout << "[INFO]  Successfully Copied " << static_cast<Size32>(source.tellg()) + i << " Bytes of File" <<
            ( padBytes ? " with Padding." : "." ) << endl;
}

void WriteKernelInformation(ofstream& target, Size8 kernel32Size, Size8 kernel64Size) {
    target.seekp(5);
    target.put(kernel32Size);

    target.seekp(7);
    target.put(kernel32Size + kernel64Size);
}
