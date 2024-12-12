#include "blockDevice.hpp"
#include <sstream>
#include <queue>
#include <fstream>

int main()
{
    blockDevice bd;
    std::string in;
    std::cout << "Manejo de bloques.\n"
              << "Usa 'help' para ver los comandos.\n";

    std::string argumento;
    /*
    help - ver comandos
    create [string] [int] [int] - crear archivo con tamaño y cantidad de bloques especificos
    create [string] - crear archivo con tamaño y cantidad de bloques por defecto
    open [string] - abrir archivo especificado
    close - cerrar archivo actualmente abierto
    write(old)
    info - información del archivo
    read [int] [int] [int] - leer bloque
    format - formatea el archivo
    ls - lista los archivos
    cat [string] - mostrar contenido
    write [string][string] - agregar texto a un archivo existente o nuevo
    hexdump [string] - mostrar contenido en hexadecimal
    copy out [string] [string] - copiar de simulado a host
    copy in [string] [sring] - copiar de host a simulado
    rm [string] - eliminar archivo
    exit - cerrar el manejo de bloques
    */

    do{
        std::cout << "> ";
        std::getline(std::cin, in);

        std::istringstream iss(in);
        std::queue<std::string> commandLine;
        while(iss >> argumento)
            commandLine.push(argumento);
        
        if (commandLine.empty()) continue;

        argumento = commandLine.front();
        commandLine.pop();
        if(argumento == "create"){

            if(commandLine.size() == 1){
                std::string filename = commandLine.front();
                commandLine.pop();
                bd.create(filename, 1024, 256);
            } else if (commandLine.size() == 3){
                std::string filename = commandLine.front();
                commandLine.pop();
                try {
                    int b_size = std::stoi(commandLine.front());
                    commandLine.pop();
                    if(b_size > sizeof(inodo)){
                        int b_count = std::stoi(commandLine.front());
                        commandLine.pop();

                        bd.create(filename, b_size, b_count);
                    } else {
                        std::cout << "Error: el tamaño del archivo es menor al limite\n";
                    }
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: el tamaño y la cantidad de bloques deben ser enteros.\n";
                }
            } else 
            {
                std::cout << "Uso de comando inadecuado.\n"
                          << "create [filename] [block_size] [block_count]\n"
                          << "create [filename]\n";
            }

        } else if(argumento == "open"){

            if(commandLine.size() == 1){
                std::string filename = commandLine.front();
                commandLine.pop();
                bd.open(filename);
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                          << "open [filename]\n";
            }

        } else if(argumento == "close"){

            if(commandLine.size() == 0){
                bd.close();
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                          << "close\n";
            }
        } else if(argumento == "info"){

            if(commandLine.size() == 0){
                std::cout << bd.superBlockDebugPring();
            }
        } 
        /*else if(argumento == "write"){

            if(commandLine.size() >= 2){
                int id = 0;
                try {
                    id = std::stoi(commandLine.front());
                    commandLine.pop();
                } catch (const std::invalid_argument& e){
                    std::cerr << "Error: el id del bloque debe ser entero.\n";
                }
                std::string data;
                while (!commandLine.empty()) {
                    data.append(commandLine.front());
                    commandLine.pop();
                    
                    // Agregar un espacio solo si hay más elementos en la cola
                    if (!commandLine.empty()) {
                        data.append(" ");
                    }
                }
                std::vector<char> dataVec(data.begin(), data.end());

                if(bd.writeBlock(id, dataVec)){
                    std::cout << "Escrito con exito.\n";
                };
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                          << "write [id] [texto]\n";
            }
        */
          else if(argumento == "read"){

            if (commandLine.size() == 3){
                int id = 0, start = 0, end = 0;
                try{
                    id = std::stoi(commandLine.front());
                    commandLine.pop();
                    start = std::stoi(commandLine.front());
                    commandLine.pop();
                    end = std::stoi(commandLine.front());
                    commandLine.pop();
                } catch (const std::invalid_argument& e){
                    std::cerr << "Error: el id, inicio y fin del bloque debe ser entero.\n";
                }

                if(start < end){

                    std::vector<char> block = bd.readBlock(id),
                                    txt;
                    //if(!block.empty())
                    //{

                    if(start < block.size()){
                        for(int i = start; i < block.size() && i <= end; i++){
                            txt.push_back(block.at(i));
                        };

                        //txt.push_back('\0');
                        for (unsigned char c : txt) {
                            std::cout << std::hex << std::uppercase << (int)c << " ";
                        }
                        std::cout << "\n";
                    }else {
                        std::cout << "No hay datos desde el inicio.\n";
                    }
                    
                    //} 
                } else {
                    std::cout << "Uso de comando inadecuado, start debe ser menor que finish\n";
                }
            } else 
            {
                std::cout << "Uso de comando inadecuado.\n"
                          << "read [id] [start] [finish]\n";
            }
        
        } else if(argumento == "format"){
            if(commandLine.size() == 0){
                if(bd.format()){
                    std::cout << "Archivo formateado correctamente\n";
                };
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                          << "format\n";
            }
        } else if(argumento == "ls") { 
            if(commandLine.size() == 0){
                if(bd.list()){
                    //std::cout << "Fin\n";
                };
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                          << "ls\n";
            } 
        } else if(argumento == "cat") {
            if(commandLine.size() == 1){
                std::string filename = commandLine.front();
                commandLine.pop();
                std::vector<char> cat = bd.contenido(filename);
                if(!cat.empty()){
                    std::cout << cat.data() << "\n";
                } 
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                          << "cat [filename] [txt]\n";
            } 
        } else if(argumento == "write") {
            if(commandLine.size() >= 2){
                std::string filename = commandLine.front();
                commandLine.pop();
                std::string data;
                while (!commandLine.empty()) {
                    data.append(commandLine.front());
                    commandLine.pop();
                    
                    // Agregar un espacio solo si hay más elementos en la cola
                    if (!commandLine.empty()) {
                        data.append(" ");
                    }
                }
                if(bd.writeFile(filename, data)){
                    std::cout << "Escrito con éxito.\n";
                }
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                          << "write [filename] [data]\n";
            }
            
        } else if(argumento == "hexdump") {
            if(commandLine.size() == 1){
                std::string filename = commandLine.front();
                commandLine.pop();
                std::vector<char> cat = bd.contenido(filename);
                if(!cat.empty()){
                    for (unsigned char c : cat) {
                        std::cout << std::hex << std::uppercase << (int)c << " ";
                    }
                    std::cout << "\n";
                } 
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                          << "cat [filename] [txt]\n";
            } 
        } else if(argumento == "copy") {
            if(commandLine.size() == 3){
                std::string stream = commandLine.front();
                commandLine.pop();
                if(stream == "out"){
                    std::string simulated = commandLine.front();
                    commandLine.pop();
                    std::string host = commandLine.front();
                    commandLine.pop();
                    if(bd.copyOut(simulated, host)){
                        std::cout << "Exportado con éxito.\n";
                    }
                } else if(stream == "in"){
                    std::string host = commandLine.front();
                    commandLine.pop();
                    std::string simulated = commandLine.front();
                    commandLine.pop();
                    if(bd.copyIn(host, simulated)){
                        std::cout << "Importado con éxito.\n";
                    }
                } else {
                    std::cout << "Uso de comando inadecuado.\n"
                          << "copy in [archivo_simulado] [archivo_host]\n"
                          << "copy out [archivo_host] [archivo_simulado]\n";
                }
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                          << "copy in [archivo_simulado] [archivo_host]\n"
                          << "copy out [archivo_host] [archivo_simulado]\n";
            }
            
        } else if(argumento == "rm") {
            if(commandLine.size() == 1){
                std::string filename = commandLine.front();
                commandLine.pop();
                if(bd.delFile(filename)){
                    std::cout << "Archivo borrado con éxito" << "\n";
                } 
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                          << "rm [filename]\n";
            } 
        } else if(argumento == "help"){
            if(commandLine.size() == 0){
                std::cout << "help - ver comandos\n"
                            << "create [filename] [block_size] [block_count] - crear archivo con tamaño y cantidad de bloques especificos\n"
                            << "create [filename] - crear archivo con tamaño y cantidad de bloques por defecto\n"
                            << "open [filename] - abrir archivo especificado\n"
                            << "close - cerrar archivo actualmente abierto\n"
                            << "info - información del archivo\n"
                            //<< "write [id] [texto] - escribir en un bloque dentro del archivo abierto\n"
                            //<< "read [id] [start] [finish] - leer bloque desde el primer valor hasta el segundo\n"
                            << "format - formatear el archivo\n"
                            << "exit - cerrar el manejo de bloques\n"
                            << "format - formatea el archivo\n"
                            << "ls - lista los archivos\n"
                            << "cat [filename] - mostrar contenido\n"
                            << "write [filename] [texto] - agregar texto a un archivo existente o nuevo\n"
                            << "hexdump [filename] - mostrar contenido en hexadecimal\n"
                            << "copy out [archivo_simulado] [archivo_host] - copiar de simulado a host\n"
                            << "copy in [archivo_host] [archivo_simulado] - copiar de host a simulado\n"
                            << "rm [filename] - eliminar archivo\n";
            } else {
                std::cout << "Uso de comando inadecuado.\n"
                            << "help\n";
            }
        } else if(argumento == "exit"){

            if(commandLine.size() == 0){
                std::cout << "Saliendo...\n";
            } else 
            {
                std::cout << "Uso de comando inadecuado.\n"
                          << "exit\n";
            }
        } else {
            std::cout << "Comando desconocido. Usar help para ver la lista de comandos\n";
        }
    } while (argumento != "exit");
   
}