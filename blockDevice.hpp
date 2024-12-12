#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <array>
#include <optional>
#include <cmath>
#include <cstring>

#define POINTERS_SIZE 8
#define NAME_SIZE 64

struct inodo{
    uint32_t size;
    std::array<int32_t, POINTERS_SIZE> blockPointers;
    char name[NAME_SIZE];
    bool ocupado;
};

struct superBlock{
    uint32_t blockSize;
    uint32_t blockCount;
    uint32_t InodosPorBloque;
    uint32_t BloquesParaTabla;
    uint32_t mapaDeBloques;
    uint32_t tablaDeInodos;
};

class blockDevice
{
private:
    superBlock superBloque;
    std::fstream file;
    //uint32_t blockSize;
    //uint32_t blockCount;
    //std::string fileName = "";

    //parte 2
    //std::vector<bool> byteMap;
public:
    blockDevice() {};
    bool create(std::string &filename, uint32_t block_size, uint32_t block_count);
    bool open(std::string& filename);
    bool close();
    bool writeBlock(std::size_t blockNumber, const std::vector<char>& data);
    std::vector<char>readBlock(std::size_t blockNumber);

    

    uint32_t getBlockSize()
    {return superBloque.blockSize;};
    uint32_t getBlockCount()
    {return superBloque.blockCount;};
    void setPointer(int id)
    {file.seekg(id);};

    //parte 2
    bool format();
    bool list();
    std::vector<char> contenido(std::string& filename);
    bool writeFile(std::string& filename, std::string& txt);
    bool copyOut(std::string& simulated, std::string& host);
    bool copyIn(std::string& host, std::string& simulated);
    bool delFile(std::string& filename);

    int bloqueLibre();
    std::string superBlockDebugPring();
};