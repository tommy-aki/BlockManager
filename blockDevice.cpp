#include "blockDevice.hpp"

bool blockDevice::create(std::string &filename, uint32_t block_size, uint32_t block_count)
{
    std::fstream newfile = std::fstream(filename, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!newfile) {
        std::cerr << "Error creando el archivo\n";
        return false;
    }
    superBlock sB;
    sB.blockSize = block_size;
    sB.blockCount = block_count;
    newfile.write(reinterpret_cast<char*>(&block_size), sizeof(block_size));
    newfile.write(reinterpret_cast<char*>(&block_count), sizeof(block_count));


    newfile.seekp(block_count * block_size - 1);
    newfile.write("", 1);

    newfile.close();
    std::cout << "Archivo " << filename << " creado con exito.\n"; 
    return true;
}

bool blockDevice::open(std::string &filename)
{
    if(!std::filesystem::exists(filename))
    {
        std::cout << "Error. Archivo inexistente.\n";
        return false;
    }

    file = std::fstream(filename, std::ios::in | std::ios::out | std::ios::binary);  
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        return false;
    }

    file.seekg(0);
    file.read(reinterpret_cast<char*>(&superBloque), sizeof(superBloque));
    //fileName = filename;
    std::cout << "Archivo abierto.\n"
              << "Tamaño de bloques: " << superBloque.blockSize << "\n"
              << "Cantidad de Bloques: " << superBloque.blockCount << "\n";
    return true;
}

bool blockDevice::close()
{
    if(!file.is_open()){
        std::cout << "Error. No hay ningun archivo abierto actualmente. \n";
        return false;
    }
    file.close();
    //fileName = "";
    superBloque = {};
    std::cout << "Archivo cerrado con exito.\n";
    return true;
}

bool blockDevice::writeBlock(std::size_t blockNumber, const std::vector<char>& data)
{
    //file = std::fstream(fileName, std::ios::binary | std::ios::out | std::ios::app);
    if(!file.is_open()){
        std::cout << "Error. No hay ningun archivo abierto actualmente.\n";
        return false;
    }
    if(blockNumber >= superBloque.blockCount){
        std::cout << "Error. El tamaño del archivo es limitado.\n";
        return false;
    }
    if (data.size() > superBloque.blockSize) {
        std::cerr << "Error. Los datos son demasiado grandes para el tamaño del bloque.\n";
        return false;
    }
    file.seekp(blockNumber * superBloque.blockSize);
    uint32_t length = data.size() < superBloque.blockSize - sizeof(uint32_t) ? static_cast<uint32_t>(data.size()) : superBloque.blockSize - sizeof(uint32_t);
    file.write(reinterpret_cast<char*>(&length), sizeof(length));
    file.write(data.data(), length);
    return true;
}

std::vector<char> blockDevice::readBlock(std::size_t blockNumber)
{
    if(!file.is_open()){
        std::cerr << "Error. No hay ningun archivo abierto actualmente.\n";
        return {};
    }
    if(blockNumber >= superBloque.blockCount){
        std::cerr << "Error. El tamaño del archivo es limitado.\n";
        return {};
    }

    file.seekg(blockNumber * superBloque.blockSize);
    uint32_t length;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));

    std::vector<char> v(length);
    file.read(v.data(), length);

    if (!file) {
        std::cerr << "Error al leer los datos.\n";
        return {};
    }
    return v;
}


//parte 2
bool blockDevice::format()
{
    if(!file.is_open()){
        std::cout << "Error. No hay ningun archivo abierto actualmente.\n";
        return false;
    }
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&superBloque), sizeof(superBloque));
    double inodosPblock = std::floor(superBloque.blockSize / sizeof(inodo));
    superBloque.InodosPorBloque = inodosPblock;
    double bloquesPTabla = std::ceil(superBloque.blockCount / superBloque.InodosPorBloque);
    superBloque.BloquesParaTabla = bloquesPTabla;
    superBloque.mapaDeBloques = 1; 
    superBloque.tablaDeInodos = 2;
    int firstFreeBlock = superBloque.tablaDeInodos + superBloque.BloquesParaTabla;
    
    file.seekp(0);
    file.write(reinterpret_cast<char*>(&superBloque), sizeof(superBloque));


    //Mapa de bytes
    file.seekp(superBloque.mapaDeBloques * superBloque.blockSize);
    for(int i = 0; i < superBloque.blockCount; i++){
        bool ocupado = i < firstFreeBlock;
        file.write(reinterpret_cast<char*>(&ocupado), sizeof(bool));
    }

    //Tabla de inodos
    inodo emptyInodo = {0, {-1, -1, -1, -1, -1, -1, -1, -1}, "", false};
    for (int i = 0; i < superBloque.BloquesParaTabla; ++i) {
        file.seekp((superBloque.tablaDeInodos + i) * superBloque.blockSize);
        for (int j = 0; j < superBloque.InodosPorBloque; ++j) {
            file.write(reinterpret_cast<char*>(&emptyInodo), sizeof(emptyInodo));
        }
    }
    
    return true;
}

bool blockDevice::list()
{
    if(!file.is_open()){
        std::cout << "Error. No hay ningun archivo abierto actualmente.\n";
        return false;
    }

    inodo Inodo;
    std::cout << "Archivos: \n"
              << "Nombre\t\tTamaño\n";
    for (int i = 0; i < superBloque.BloquesParaTabla; ++i) {
        file.seekg((superBloque.tablaDeInodos + i) * superBloque.blockSize);
        for (int j = 0; j < superBloque.InodosPorBloque; ++j) {
            file.read(reinterpret_cast<char*>(&Inodo), sizeof(Inodo));
            if(Inodo.ocupado){
                std::cout << Inodo.name << "\t\t" << std::dec << Inodo.size << "\n";
            }
        }
    }
    return true;
}

bool blockDevice::writeFile(std::string &filename, std::string &txt)
{
    if(!file.is_open()){
        std::cerr << "Error. No hay ningun archivo abierto actualmente.\n";
        return false;
    }
    if(filename.size() > NAME_SIZE){
        std::cerr << "Error. Nombre del archivo excede el limite.\n";
        return false;
    }
    if(txt.size() > POINTERS_SIZE * superBloque.blockSize){
        std::cerr << "Error. Archivo excede el limite.";
        return false;
    }

    if(bloqueLibre() == -1){
        std::cerr << "Error. Sistema de archivos lleno. Vacie archivos.\n";
        return false;
    }

    int firstFreeInodo = -1;
    int InodoMod = -1;
    inodo Inodo;
    bool found = false;

    for (int i = 0; i < superBloque.BloquesParaTabla; ++i) {
        file.seekg((superBloque.tablaDeInodos + i) * superBloque.blockSize);
        for (int j = 0; j < superBloque.InodosPorBloque; ++j) {
            file.read(reinterpret_cast<char*>(&Inodo), sizeof(Inodo));
            if(!Inodo.ocupado && firstFreeInodo==-1){
                firstFreeInodo = (i+superBloque.tablaDeInodos) * superBloque.blockSize + j * sizeof(inodo);
            }
            if(Inodo.ocupado && strncmp(Inodo.name, filename.c_str(), sizeof(Inodo.name)) == 0){
                InodoMod = (i+superBloque.tablaDeInodos) * superBloque.blockSize + j * sizeof(inodo);
                uint32_t size = Inodo.size;
                Inodo.size = size + txt.size();
                found = true;
                break;
            }
        }
        if(found)
            break;
    }
    if (!found) { 
        if (firstFreeInodo != -1) {
            Inodo.size = txt.size();
            strncpy(Inodo.name, filename.c_str(), sizeof(Inodo.name));
            Inodo.ocupado = true;
            std::fill(Inodo.blockPointers.begin(), Inodo.blockPointers.end(), -1);
            InodoMod = firstFreeInodo;
        } else {
            std::cerr << "Error. No se encontró un inodo disponible.\n"; 
            return false;
        }
    }

    int txtPointer = 0;
    for(int i = 0; i < POINTERS_SIZE; i++){
        std::string block = "";
        if(Inodo.blockPointers.at(i) == -1){
            int freeBlock = bloqueLibre();
            if(freeBlock == -1){
                std::cerr << "Error! No todo el archivo se ha podido escribir. Libera espacio en el disco.\n";
                return false;
            }
            Inodo.blockPointers.at(i) = freeBlock;
            file.seekp(superBloque.mapaDeBloques * superBloque.blockSize + freeBlock * sizeof(bool));
            bool used = true;
            file.write(reinterpret_cast<const char*>(&used), sizeof(bool));

            //block = std::string(superBloque.blockSize, '\0');
        } else {
            block = readBlock(Inodo.blockPointers.at(i)).data();
        }
        
        int bytesEscritos = block.size();
        while (bytesEscritos < superBloque.blockSize - sizeof(uint32_t) && txtPointer < txt.size()) {
            block.push_back(txt.at(txtPointer));
            ++txtPointer;
            ++bytesEscritos;
        }
        block.push_back('\0');
        if (!writeBlock(Inodo.blockPointers[i], std::vector<char>(block.begin(), block.end()))) {
            return false;
        }
        if (txtPointer >= txt.size()) { 
            break;
        }
    }
    
    file.seekp(InodoMod);
    file.write(reinterpret_cast<const char*>(&Inodo), sizeof(Inodo));

    return true;
}

std::vector<char> blockDevice::contenido(std::string &filename)
{
    if(!file.is_open()){
        std::cerr << "Error. No hay ningun archivo abierto actualmente.\n";
        return {};
    }

    std::vector<char> vec;
    inodo Inodo;
    for (int i = 0; i < superBloque.BloquesParaTabla; ++i) {
        file.seekg((superBloque.tablaDeInodos + i) * superBloque.blockSize);
        for (int j = 0; j < superBloque.InodosPorBloque; ++j) {
            file.read(reinterpret_cast<char*>(&Inodo), sizeof(Inodo));
            if(Inodo.ocupado && strncmp(Inodo.name, filename.c_str(), sizeof(Inodo.name)) == 0){
                for(int k = 0; k < POINTERS_SIZE; k++){
                    if (Inodo.blockPointers.at(k) > 0) {
                        std::vector<char> txt = readBlock(Inodo.blockPointers.at(k));
                        vec.insert(vec.end(), txt.begin(), txt.end());
                    }   
                }
                return vec;
            }
        }
    }
    std::cerr << "Error. No hay archivo con ese nombre.\n";
    return {};
}

bool blockDevice::copyOut(std::string &simulated, std::string &host)
{
    if(!file.is_open()){
        std::cerr << "Error. No hay ningun archivo abierto actualmente.\n";
        return false;
    }
    
    std::vector <char> txt = contenido(simulated);
    txt.push_back('\0');

    if(!txt.empty()){
        std::ofstream hostFile = std::ofstream(host, std::ios::trunc);
        if (!hostFile.is_open()) {
            std::cerr << "Error al abrir el archivo en el sistema de archivos del host.\n";
            return false;
        }
        hostFile << txt.data(), txt.size();
    } else {
        std::cerr << "Error. No existe el archivo simulado\n";
        return false;
    }
    return true;
}

bool blockDevice::copyIn(std::string &host, std::string &simulated)
{
    if(!file.is_open()){
        std::cerr << "Error. No hay ningun archivo abierto actualmente.\n";
        return false;
    }

    std::ifstream hostFile = std::ifstream(host, std::ios::binary | std::ios::ate);
    if (!hostFile.is_open()) {
        std::cerr << "Error al abrir el archivo en el sistema de archivos del host.\n";
        return false;
    
    }

    int fileSize = hostFile.tellg();
    if(fileSize > POINTERS_SIZE * superBloque.blockSize){
        std::cerr << "Error. Archivo muy grande para el dispositivo.\n";
        return false;
    }

    hostFile.seekg(0, std::ios::beg);
    std::vector<char> buffer(fileSize);
    if(!hostFile.read(buffer.data(), fileSize)){
        std::cerr << "Error al leer el archivo del host.\n";
        return false;
    }
    
    buffer.push_back('\0');
    std::string txt = buffer.data();
    return writeFile(simulated, txt);
}

bool blockDevice::delFile(std::string &filename)
{
    if(!file.is_open()){
        std::cerr << "Error. No hay ningun archivo abierto actualmente.\n";
        return false;
    }

    int InodoMod = -1;
    inodo Inodo;
    for (int i = 0; i < superBloque.BloquesParaTabla; ++i) {
        file.seekg((superBloque.tablaDeInodos + i) * superBloque.blockSize);
        for (int j = 0; j < superBloque.InodosPorBloque; ++j) {
            file.read(reinterpret_cast<char*>(&Inodo), sizeof(Inodo));
            if(Inodo.ocupado && strncmp(Inodo.name, filename.c_str(), sizeof(Inodo.name)) == 0){
                InodoMod = (i+superBloque.tablaDeInodos) * superBloque.blockSize + j * sizeof(inodo);
                for (int k = 0; k < POINTERS_SIZE; ++k) {
                    if (Inodo.blockPointers[k] != -1) {
                        file.seekp(superBloque.mapaDeBloques * superBloque.blockSize + Inodo.blockPointers[k] * sizeof(bool));
                        bool used = false;
                        file.write(reinterpret_cast<const char*>(&used), sizeof(bool));
                        Inodo.blockPointers[k] = -1;
                    }
                }
                Inodo.ocupado = false;
                break;
            }
        }
    }

    // Si el archivo no fue encontrado
    if (InodoMod == -1) {
        std::cerr << "Error. No se encontró el archivo.\n";
        return false;
    }

    file.seekp(InodoMod);
    file.write(reinterpret_cast<const char*>(&Inodo), sizeof(Inodo));
    return true;
}

int blockDevice::bloqueLibre()
{
    int bloqueLibre = -1;
    file.seekg(superBloque.mapaDeBloques * superBloque.blockSize);
    for(int i = 0; i < superBloque.blockCount; i++){
        bool used;
        
        file.read(reinterpret_cast<char*>(&used), sizeof(bool));
        if(!used){
            bloqueLibre = i;
            break;
        }
    }
    return bloqueLibre;
}

std::string blockDevice::superBlockDebugPring()
{
    if(!file.is_open()){
        std::cerr << "Error. No hay ningun archivo abierto actualmente.\n";
        return "";
    }
    
    std::string superBlock;
    superBlock.append("Bloques: ");
    superBlock.append(std::to_string(superBloque.blockCount));
    superBlock.append("\nTamaño de Bloques: ");
    superBlock.append(std::to_string(superBloque.blockSize));
    superBlock.append("\nInodos por Bloque: ");
    superBlock.append(std::to_string(superBloque.InodosPorBloque));
    superBlock.append("\nBloques para Tabla: ");
    superBlock.append(std::to_string(superBloque.BloquesParaTabla));
    superBlock.append("\nMapa de Bytes: ");
    file.seekg(superBloque.mapaDeBloques * superBloque.blockSize);
    for(int i = 0; i < superBloque.blockCount; i++){
        bool used = false;
        int insert;
        file.read(reinterpret_cast<char*>(&used), sizeof(bool));
        insert = used ? 1 : 0;
        superBlock.append(std::to_string(insert));
    }
    superBlock.append("\n");
    return superBlock;
}
