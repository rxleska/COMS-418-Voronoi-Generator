#include "lib/CONST.hpp"
#include "lib/BeachLine/headers/BeachLine.hpp"
#include "lib/BeachLine/headers/EdgeNode.hpp"
#include "lib/BeachLine/headers/Arc.hpp"
#include "lib/DCEL/headers/Vertex.hpp"
#include <fstream>


   
    
//string to int function
int stringToInt(std::string str){
    int result = 0;
    int sign = 1;
    int startIndex = 0;
    if (str[0] == '-') {
        sign = -1;
        startIndex = 1;
    }
    for (int i = startIndex; i < (int) str.length(); i++){
        result *= 10;
        result += str[i] - '0';
    }
    return result * sign;
}

void readSites(std::vector<Vertex> *vertices){
    // Read in the data from sites.txt
    //open file for reading
    std::ifstream file("sites.txt");
    if (!file.is_open()){
        std::cerr << "Error: could not open file" << std::endl;
        throw std::runtime_error("Error: could not open file");
    }
    bool isLeft = true;

    while(!file.eof()){ //while not end of file marker
        //if the next character is a number, read it in 
        if(('0' <= file.peek() && file.peek() <= '9') || file.peek() == '-'){
            std::string num = "";
            while(('0' <= file.peek() && file.peek() <= '9') || file.peek() == '-'){
                num += file.get();
            }
            if(isLeft){
                vertices->push_back(Vertex(stringToInt(num), 0));
                isLeft = false;
            }else{
                (*vertices)[vertices->size() - 1].setY(stringToInt(num));
                isLeft = true;
            }
        }
        //if the next character is not a number, skip it
        else{
            file.get();
        }
    }

    
    // Close the file
    file.close();
}

int main(int argc, char *argv[]) {
    
    //define linked list of vertices
    std::vector<Vertex> vertices;
    
    //read in the sites from the file
    try{
        readSites(&vertices);
    }
    catch(std::runtime_error &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    //print out the vertices
    if(DEBUG){
        std::cout << "Vertices: " << std::endl;
        for(int i = 0; i < (int) vertices.size(); i++){
            std::cout << "Vertex " << i << ": (" << vertices[i].getX() << ", " << vertices[i].getY() << ")" << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
    
    




}