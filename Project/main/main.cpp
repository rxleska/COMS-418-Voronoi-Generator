#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../lib/headers/Vertex.hpp"
#include "../lib/Beach_Line_RedBlackTree.cpp"

// This is the main file for the project. It will hopefully read in the data from sites.txt, calculate the voronoi diagram, the delaunay triangulation of the voronoi diagram, and then display the results in a window.


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


int main(int argc, char* argv[])
{
    // Read in the data from sites.txt
    //open file for reading
    std::ifstream file("sites.txt");
    if (!file.is_open()){
        std::cerr << "Error: could not open file" << std::endl;
        return 1;
    }
    bool isLeft = true;
    //define linked list of vertices
    std::vector<Vertex> vertices;
    while(!file.eof()){ //while not end of file marker
        //if the next character is a number, read it in 
        if(('0' <= file.peek() && file.peek() <= '9') || file.peek() == '-'){
            std::string num = "";
            while(('0' <= file.peek() && file.peek() <= '9') || file.peek() == '-'){
                num += file.get();
            }
            if(isLeft){
                vertices.push_back(Vertex(stringToInt(num), 0));
                isLeft = false;
            }else{
                vertices[vertices.size() - 1].y = stringToInt(num);
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

    //print out the vertices
    for (int i = 0; i < (int) vertices.size(); i++){
        std::cout << "Vertex " << i << ": (" << vertices[i].x << ", " << vertices[i].y << ")" << std::endl;
    }


    // feed the vertices into the red black tree as leaves for testing
    RBTree tree = RBTree();
    for (int i = 0; i < (int) vertices.size(); i++){
        tree.insert(vertices[i].x, &vertices[i]);            
    }

    tree.printInOrder();
    tree.forest(tree.getRoot());


    // Calculate the voronoi diagram of the sites
    


    // Calculate the delaunay triangulation of the voronoi diagram

    // Display the results in a window (using OpenGL, current idea is to create 2 sides of the window, one for the voronoi diagram and one for the delaunay triangulation)

    return 0;
}