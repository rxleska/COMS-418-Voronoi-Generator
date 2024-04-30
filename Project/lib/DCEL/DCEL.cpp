#include "headers/DCEL.hpp"
#include "../BeachLine/headers/ParabolaMath.hpp"

#include <limits>

DCEL::DCEL() {
    this->vertices = std::vector<Vertex*>();
    //allocate 20 vertices
    this->xSortedVertices = new Vertex*[20];
    this->xSortedSize = 0;
    this->edges = std::vector<Edge*>();
    this->faces = std::vector<Face*>();
    this->isVoronoi = true;
}

DCEL::DCEL(int n){
    this->vertices = std::vector<Vertex*>();
    //allocate 2n vertices, 3n > 2n - 5 + boundary edges
    this->xSortedVertices = new Vertex*[3*n];
    this->xSortedSize = 0;
    this->edges = std::vector<Edge*>();
    this->faces = std::vector<Face*>();
    this->isVoronoi = true;
}

DCEL::~DCEL() {
    delete[] this->xSortedVertices;
    for (Vertex* vertex : this->vertices) {
        delete vertex;
    }
    for (Edge* edge : this->edges) {
        delete edge;
    }
    for (Face* face : this->faces) {
        delete face;
    }
}

std::vector<Vertex*> DCEL::getVertices() {
    return this->vertices;
}

std::vector<Edge*> DCEL::getEdges() {
    return this->edges;
}

std::vector<Face*> DCEL::getFaces() {
    return this->faces;
}

Vertex** DCEL::getXSortedVertices() {
    return this->xSortedVertices;
}

int DCEL::getXSortedSize() {
    return this->xSortedSize;
}

bool DCEL::getIsVoronoi() {
    return this->isVoronoi;
}

//setters not used in the project
void DCEL::setVertices(std::vector<Vertex*> vertices) {
    this->vertices = vertices;
}

void DCEL::setEdges(std::vector<Edge*> edges) {
    this->edges = edges;
}

void DCEL::setFaces(std::vector<Face*> faces) {
    this->faces = faces;
}

void DCEL::setXSortedVertices(Vertex** xSortedVertices) {
    this->xSortedVertices = xSortedVertices;
}

void DCEL::setXSortedSize(int xSortedSize) {
    this->xSortedSize = xSortedSize;
}

void DCEL::setIsVoronoi(bool isVoronoi) {
    this->isVoronoi = isVoronoi;
}


bool DCEL::compareVertices(Vertex v1, Vertex v2) {
    if(ParabolaMath::areSameDouble(v1.getX(), v2.getX())) {
        return v1.getY() < v2.getY(); //no need to check for equality, as the vertices should be unique
    }
    return v1.getX() < v2.getX();
}

void DCEL::addVertex(Vertex* vertex) {
    this->vertices.push_back(vertex);

    //add to xSortedVertices in the correct position
    int i = 0;
    while (i < this->xSortedSize && this->compareVertices(*this->xSortedVertices[i], *vertex)) {
        i++;
    }
    for (int j = this->xSortedSize; j > i; j--) {
        this->xSortedVertices[j] = this->xSortedVertices[j - 1];
    }
    this->xSortedVertices[i] = vertex;
    this->xSortedSize++;
}

void DCEL::addEdge(Edge *edge) {
    this->edges.push_back(edge);
}

void DCEL::addFace(Face *face) {
    this->faces.push_back(face);
}

void DCEL::addEdge(Vertex origin, Vertex destination) {
    std::cout << "Adding edge: (" << origin.getX() << ", " << origin.getY() << ") to (" << destination.getX() << ", " << destination.getY() << ")" << std::endl;
    //if DCEL is empty, add the vertices and the edge
    if (this->vertices.size() == 0) {
        std::cout << "DCEL is empty, adding the first edge." << std::endl;
        //create the vertices
        this->addVertex(new Vertex(origin.getX(), origin.getY()));
        this->addVertex(new Vertex(destination.getX(), destination.getY()));
        //create the edges
        Edge *edgeO = new Edge();
        Edge *edgeD = new Edge();
        edgeO->setOrigin(this->vertices[0]);
        this->vertices[0]->setIncidentEdge(edgeO);
        edgeD->setOrigin(this->vertices[1]);
        this->vertices[1]->setIncidentEdge(edgeD);
        edgeO->setTwin(edgeD);
        edgeD->setTwin(edgeO);  
        edgeO->setNext(edgeD);
        edgeD->setNext(edgeO);
        edgeD->setPrev(edgeO);
        edgeO->setPrev(edgeD);
        //create the first face and set the outer component
        Face *face = new Face();
        face->setInnerComponent(edgeO); //this is the only outside face so we use the inner component (since the dcel is complete, there are no holes in the faces)
        edgeO->setIncidentFace(face);
        edgeD->setIncidentFace(face);

        //add the vertices (done at top), edges and face to the DCEL
        this->addEdge(edgeO);
        this->addEdge(edgeD);
        this->addFace(face);
        return;
    }

    
    Vertex * originVertex = this->searchVertex(origin);
    Vertex * destinationVertex = this->searchVertex(destination);
    int NewVertexFlags = 0;

    if(originVertex == nullptr && destinationVertex == nullptr){
        // add the edge with an incident face of 1

        
        throw "Both vertices are null, this should not happen as we are incrementally adding vertices and edges to the DCEL.";
    }
    if(originVertex != nullptr && destinationVertex != nullptr){
        std::vector<Edge *> edges = this->getEdgesFromVertex(originVertex);
        for (Edge *e : edges) {
            if (e->getOrigin() == destinationVertex) {
                return; //edge already exists
            }
        }
        NewVertexFlags += 4;

    }
    Vertex * newVertex;
    if (originVertex == nullptr) {
        newVertex = new Vertex(origin.getX(), origin.getY());
        this->addVertex(newVertex);
        originVertex = newVertex;
        NewVertexFlags += 1;
    }
    if (destinationVertex == nullptr) {
        newVertex = new Vertex(destination.getX(), destination.getY());
        this->addVertex(newVertex);
        destinationVertex = newVertex;
        NewVertexFlags += 2;
    }

    //create the edges
    Edge *edgeO = new Edge();
    Edge *edgeD = new Edge();
    edgeO->setOrigin(originVertex);
    if(NewVertexFlags & 1){ //if origin vertex is new
        originVertex->setIncidentEdge(edgeO);
    }
    edgeD->setOrigin(destinationVertex);
    if(NewVertexFlags & 2){ //if destination vertex is new
        destinationVertex->setIncidentEdge(edgeD);
    }
    edgeO->setTwin(edgeD);
    edgeD->setTwin(edgeO);
    if(NewVertexFlags & 1){ //if origin vertex is new
        edgeO->setPrev(edgeD);
        edgeD->setNext(edgeO);
    }
    else{ //origin vertex is not new
        // find the edge that is the next of the destination vertex
        Edge * dNext = getNextEdgeOnVertices(edgeD);
        edgeD->setNext(dNext);
        dNext->setPrev(edgeD);
        edgeD->setIncidentFace(dNext->getIncidentFace());
        // find the edge that is the prev of the origin vertex
        Edge * oPrev = getPrevEdgeOnVertices(edgeO);
        edgeO->setPrev(oPrev);
        oPrev->setNext(edgeO);
    }
    if(NewVertexFlags & 2){ //if destination vertex is new
        edgeD->setPrev(edgeO);
        edgeO->setNext(edgeD);
    }
    else{
        // find the edge that is the next of the origin vertex
        Edge * oNext = getNextEdgeOnVertices(edgeO);
        edgeO->setNext(oNext);
        oNext->setPrev(edgeO);
        edgeO->setIncidentFace(oNext->getIncidentFace());
        // find the edge that is the prev of the destination vertex
        Edge * dPrev = getPrevEdgeOnVertices(edgeD);
        edgeD->setPrev(dPrev);
        dPrev->setNext(edgeD);
        edgeD->setIncidentFace(dPrev->getIncidentFace());
    }

    //add the edges to the DCEL
    this->addEdge(edgeO);
    this->addEdge(edgeD);


    //if flag 100 is set, create a new face and set the outer component
    if(NewVertexFlags & 4){
        //3 cases, splitting 2 faces, finishing a face using the origin edge, finishing a face using the destination edge
        //splitting into 2 faces (oEdge next is not face 1)
        if(edgeO->getNext()->getIncidentFace() != nullptr && edgeO->getNext()->getIncidentFace()->getId() != 1){
            Face *face = new Face();
            face->setOuterComponent(edgeO);
            //set each edge in the face to the new face
            Edge *edge = edgeO;
            do{
                edge->setIncidentFace(face);
                edge = edge->getNext();
            }while(edge != edgeO);

            if(edgeD->getIncidentFace() == nullptr){
                edgeD->setIncidentFace(this->faces[0]);
            }

        }
        else if(edgeD->getNext()->getIncidentFace() != nullptr && edgeD->getNext()->getIncidentFace()->getId() != 1){
            Face *face = new Face();
            face->setOuterComponent(edgeD);
            //set each edge in the face to the new face
            Edge *edge = edgeD;
            do{
                edge->setIncidentFace(face);
                edge = edge->getNext();
            }while(edge != edgeD);

            if(edgeO->getIncidentFace() == nullptr){
                edgeO->setIncidentFace(this->faces[0]);
            }
        }
        else{
            //if edgeO does not have an incident face set it to face 1
            if(edgeO->getIncidentFace() == nullptr){
                edgeO->setIncidentFace(this->faces[0]);
            }

            //if edgeD does not have an incident face set it to face 1
            if(edgeD->getIncidentFace() == nullptr){
                edgeD->setIncidentFace(this->faces[0]);
            }

            //check which edge is closed 
            if(edgeO->getIsClosed()){
                //create a face 
                Face *face = new Face();
                face->setOuterComponent(edgeO);
                //set each edge in the face to the new face
                Edge *edge = edgeO;
                do{
                    edge->setIncidentFace(face);
                    edge = edge->getNext();
                }while(edge != edgeO);
            }
            else if(edgeD->getIsClosed()){
                //finish using the destination edge
                //create a face
                Face *face = new Face();
                face->setOuterComponent(edgeD);
                //set each edge in the face to the new face
                Edge *edge = edgeD;
                do{
                    edge->setIncidentFace(face);
                    edge = edge->getNext();
                }while(edge != edgeD);
            }
            else{
                //let the edges use their current face
            }
        }

    }
    else{
        if(edgeO->getIncidentFace() == nullptr){
            edgeO->setIncidentFace(this->faces[0]);
        }

        //if edgeD does not have an incident face set it to face 1
        if(edgeD->getIncidentFace() == nullptr){
            edgeD->setIncidentFace(this->faces[0]);
        }
    }

}

std::vector<Edge *> DCEL::getEdgesFromVertex(Vertex *vertex){
    //get all edges that have the vertex as origin
    std::vector<Edge *> edges;
    Edge *edge = vertex->getIncidentEdge();
    do{
        edges.push_back(edge);
        if(edge->getOrigin() == vertex){
            edge = edge->getTwin();
        }
        else{
            edge = edge->getNext();
        }
    }while(edge != vertex->getIncidentEdge());

    return edges;
}


void DCEL::constructDCEL(std::vector<PseudoEdge> pseudoEdges) {    
    std::cout << "Constructing DCEL" << std::endl;
    //construct the DCEL from the pseudo edges
    for (PseudoEdge pseudoEdge : pseudoEdges) {
        //if either vertex is not in the DCEL, add it
        int vmade = 0;
        Vertex *originVertex = this->searchVertex(*pseudoEdge.start);
        if (originVertex == nullptr) {
            originVertex = new Vertex(pseudoEdge.start->getX(), pseudoEdge.start->getY(), pseudoEdge.isBoundary);
            this->addVertex(originVertex);
            vmade+=1; //set 0b01 flag
        }
        Vertex *destinationVertex = this->searchVertex(*pseudoEdge.end);
        if (destinationVertex == nullptr) {
            destinationVertex = new Vertex(pseudoEdge.end->getX(), pseudoEdge.end->getY(), pseudoEdge.isBoundary);
            this->addVertex(destinationVertex);
            vmade+=2; //set 0b10 flag
        }

        //create the edges
        Edge *edgeO = new Edge();
        Edge *edgeD = new Edge();
        edgeO->setOrigin(originVertex);
        originVertex->addOutwardsEdge(edgeO);
        originVertex->addInwardsEdge(edgeD);
        if(vmade & 1) originVertex->setIncidentEdge(edgeO);
        edgeD->setOrigin(destinationVertex);
        destinationVertex->addOutwardsEdge(edgeD);
        destinationVertex->addInwardsEdge(edgeO);
        if(vmade & 2) destinationVertex->setIncidentEdge(edgeD);
        edgeO->setTwin(edgeD);
        edgeD->setTwin(edgeO);

        if(pseudoEdge.isBoundary){
            edgeO->setIsBorder(true);
            edgeD->setIsBorder(true);
        }

        if(pseudoEdge.arc1 != nullptr && pseudoEdge.arc2 != nullptr){
            edgeO->setSite(pseudoEdge.arc1, pseudoEdge.arc2);
            edgeD->setSite(pseudoEdge.arc1, pseudoEdge.arc2);
        }

        //add the edges to the DCEL
        this->addEdge(edgeO);
        this->addEdge(edgeD);
    }


    //for each vertex fix the next and prev pointers
    for (Vertex *vertex : this->vertices) {
        //set the next and prev pointers using the getOutwardsEdges and getInwardsEdges lists of the vertex
        
        //get and sort the outwards edges by angle
        std::vector<Edge *> inwardEdges = vertex->getInwardsEdges();
        //sort the outwards edges by angle
        std::sort(inwardEdges.begin(), inwardEdges.end(), [](Edge *e1, Edge *e2) {
            return e1->getAngle() < e2->getAngle();
        });

        //set the next and prev pointers in order of the sorted list
        for (int i = 0; i < (int) inwardEdges.size(); i++) {
            inwardEdges[i]->setNext(inwardEdges[(i + 1) % inwardEdges.size()]->getTwin());
            inwardEdges[(i + 1) % inwardEdges.size()]->getTwin()->setPrev(inwardEdges[i]);
        }
    }
    
    //for each edge if the edge doesn't have a face create a face and set the outer component, add the edge to the face
    for (Edge *edge : this->edges) {
        if (edge->getIncidentFace() == nullptr) {
            Face *face = new Face();
            face->setOuterComponent(edge);
            bool siteAssigned = false;
            if(edge->getSite() != nullptr){
                face->setSite(edge->getSite());
                siteAssigned = true;
            }
            edge->setIncidentFace(face);
            Edge *e = edge->getNext();
            bool isAllUnbounded = true;
            while (e != edge) {
                e->setIncidentFace(face);
                if(e->getIsBorder()){
                    face->setIsUnbounded(true);
                }
                else{
                    isAllUnbounded = false;
                }
                if(!siteAssigned && edge->getSite() != nullptr){
                    face->setSite(edge->getSite());
                    siteAssigned = true;
                }

                e = e->getNext();
            }
            //if isAllUnbounded is true, set face to use inner component
            if(isAllUnbounded){
                face->setInnerComponent(edge);
                face->setOuterComponent(nullptr);
            }

            this->addFace(face);
        }
    }

}


Edge * DCEL::getNextEdgeOnVertices(Edge *edge) {
    std::vector<Edge *> edges = this->getEdgesFromVertex(edge->getTwin()->getOrigin());
    double currentAngle = edge->getTwin()->getAngle(); // Angle of the edge from which we are searching
    Edge *nextEdge = nullptr;
    double nextAngle = 4 * PI; // Initialize to a high value that is beyond any valid angle

    for (Edge *e : edges) {
        std::cout << "checking edge: " << e->getEdgeName() << std::endl;
        if (e->getOrigin() == edge->getTwin()->getOrigin() && e != edge->getTwin() && e != edge) {
            double candidateAngle = e->getAngle();
            if (candidateAngle < currentAngle) {
                candidateAngle += 2 * PI; // Adjust angle for cyclic comparison
            }
            if (candidateAngle < nextAngle) {
                nextAngle = candidateAngle;
                nextEdge = e;
                std::cout << "next edge: " << nextEdge->getEdgeName() << std::endl;
            }
        }
    }

    return nextEdge;
}



Edge * DCEL::getPrevEdgeOnVertices(Edge *edge) {
    std::vector<Edge *> edges = this->getEdgesFromVertex(edge->getOrigin());
    double currentAngle = edge->getAngle(); // Use the angle of the edge directly, not its twin
    Edge *prevEdge = nullptr;
    double prevAngle = -4 * PI; // Initialize to a low value beyond any valid angle

    for (Edge *e : edges) {
        if (e->getTwin()->getOrigin() == edge->getOrigin() && e != edge->getTwin() && e != edge) {
            double candidateAngle = e->getAngle();
            if (candidateAngle > currentAngle) {
                candidateAngle -= 2 * PI; // Adjust angle for cyclic comparison
            }
            if (candidateAngle > prevAngle) {
                prevAngle = candidateAngle;
                prevEdge = e;
            }
        }
    }
    return prevEdge;
}



Vertex* DCEL::searchVertex(Vertex vertex) {
    //binary search for the vertex (log n time complexity)
    int left = 0;
    int right = this->xSortedSize - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (ParabolaMath::areSameDouble(this->xSortedVertices[mid]->getX(), vertex.getX())) {
            if (ParabolaMath::areSameDouble(this->xSortedVertices[mid]->getY(), vertex.getY())) {
                return this->xSortedVertices[mid];
            }
            else if (this->xSortedVertices[mid]->getY() < vertex.getY()) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        else if (this->xSortedVertices[mid]->getX() < vertex.getX()) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return nullptr;
}

void DCEL::printDCEL() {
    std::cout << "DCEL" << std::endl;
    for (Vertex* vertex : this->vertices) {
        std::cout << vertex->vertexToString(isVoronoi) << std::endl;
    }
    std::cout << std::endl;
    for (Face* face : this->faces) {
        std::cout << face->faceToString(isVoronoi) << std::endl;
    }
    std::cout << std::endl;
    // std::cout << "edge og twin next prev fc" << std::endl;
    for (Edge* edge : this->edges) {
        std::cout << edge->edgeToString(isVoronoi) << std::endl;
    }
}

std::string DCEL::dcelToString(){
    std::string dcelString = "";
    for(Vertex * vertex : this->vertices){
        dcelString += vertex->vertexToString(isVoronoi) + "\n";
    }
    dcelString += "\n";
    for(Face * face : this->faces){
        dcelString += face->faceToString(isVoronoi) + "\n";
    }
    dcelString += "\n";
    for(Edge * edge : this->edges){
        dcelString += edge->edgeToString(isVoronoi) + "\n";
    }
    return dcelString;
}



//converts DCEL of voronoi diagram to delaunay triangulation DCEL
DCEL * DCEL::toDelaunayTriangulation(){
    //create a new DCEL
    DCEL * delaunay = new DCEL(this->faces.size());
    delaunay->setIsVoronoi(false);
    
    //CONVERT FACES TO VERTICES
    for(Face * face : this->faces){
        if(face->getOuterComponent() != nullptr){
            Vertex * vertex = new Vertex(face->getSite()->getX(), face->getSite()->getY(), face->getId());
            delaunay->addVertex(vertex);
        }
    }

    //CONVERT EDGES (Vvertex to Vvertex) TO EDGES (site to site)
    for(Edge * edge : this->edges){
        if(!edge->getConverted()){
            if(edge->getSite() != nullptr && edge->getTwin()->getSite() != nullptr){
                //mark the edges as converted
                edge->setConverted(true);
                edge->getTwin()->setConverted(true);
                Edge * newEdge = new Edge(edge->getId());
                Edge * newEdgeTwin = new Edge(edge->getTwin()->getId());
                //set twin pointers
                newEdge->setTwin(newEdgeTwin);
                newEdgeTwin->setTwin(newEdge);
                Vertex * origin = delaunay->searchVertex(*edge->getSite());
                Vertex * destination = delaunay->searchVertex(*edge->getTwin()->getSite());
                if(origin != nullptr && destination != nullptr){
                    newEdge->setOrigin(origin);
                    newEdgeTwin->setOrigin(destination);
                    //set next and prev pointers (prematurely will be fixed later)
                    newEdge->setNext(newEdgeTwin);
                    newEdgeTwin->setPrev(newEdge);
                    newEdgeTwin->setNext(newEdge);
                    newEdge->setPrev(newEdgeTwin);

                    //add the edges to the DCEL
                    delaunay->addEdge(newEdge);
                    origin->addOutwardsEdge(newEdge);
                    origin->addInwardsEdge(newEdgeTwin);
                    delaunay->addEdge(newEdgeTwin);
                    destination->addOutwardsEdge(newEdgeTwin);
                    destination->addInwardsEdge(newEdge);

                    if(origin->getIncidentEdge() == nullptr){
                        origin->setIncidentEdge(newEdge);
                    }
                    if(destination->getIncidentEdge() == nullptr){
                        destination->setIncidentEdge(newEdgeTwin);
                    }
                }
                else{
                    delete newEdge;
                    delete newEdgeTwin;
                }
            }
        }
    }

    //fix the next and prev pointers of the edges
    delaunay->fixEdges();

    //find the faces of the DCEL
    delaunay->findFaces();

    return delaunay;
}


//fixes the edges of the DCEL
void DCEL::fixEdges(){
    //for each vertex fix the next and prev pointers
    for (Vertex *vertex : this->vertices) {
        //set the next and prev pointers using the getOutwardsEdges and getInwardsEdges lists of the vertex
        
        //get and sort the outwards edges by angle
        std::vector<Edge *> inwardEdges = vertex->getInwardsEdges();
        //sort the outwards edges by angle
        std::sort(inwardEdges.begin(), inwardEdges.end(), [](Edge *e1, Edge *e2) {
            return e1->getAngle() < e2->getAngle();
        });

        //set the next and prev pointers in order of the sorted list
        for (int i = 0; i < (int) inwardEdges.size(); i++) {
            inwardEdges[i]->setNext(inwardEdges[(i + 1) % inwardEdges.size()]->getTwin());
            inwardEdges[(i + 1) % inwardEdges.size()]->getTwin()->setPrev(inwardEdges[i]);
        }
    }
}

//finds the faces of the DCEL
void DCEL::findFaces(){
    int MostEdges = 0;
    Face * MostEdgesFace = nullptr;
    Edge * MostEdgesEdge = nullptr;
    int i = 1;
    for (Edge *edge : this->edges) {
        if (edge->getIncidentFace() == nullptr) {
            Face *face = new Face(i);
            i++;
            face->setOuterComponent(edge);
            bool siteAssigned = false;
            if(edge->getSite() != nullptr){
                face->setSite(edge->getSite());
                siteAssigned = true;
            }
            int countOfEdges = 1;
            edge->setIncidentFace(face);
            Edge *e = edge->getNext();
            bool isAllUnbounded = true;
            while (e != edge) {
                e->setIncidentFace(face);
                if(e->getIsBorder()){
                    face->setIsUnbounded(true);
                }
                else{
                    isAllUnbounded = false;
                }
                if(!siteAssigned && edge->getSite() != nullptr){
                    face->setSite(edge->getSite());
                    siteAssigned = true;
                }
                countOfEdges++;
                e = e->getNext();
            }
            //if isAllUnbounded is true, set face to use inner component
            if(isAllUnbounded){
                face->setInnerComponent(edge);
                face->setOuterComponent(nullptr);
            }
            if((countOfEdges > 3 && !(this->getIsVoronoi()))){
                if(countOfEdges > MostEdges){
                    MostEdges = countOfEdges;
                    MostEdgesFace = face;
                    MostEdgesEdge = edge;
                }
            }
            this->addFace(face);
        }
    }

    if(MostEdgesFace != nullptr){
        MostEdgesFace->setIsUnbounded(true);
        MostEdgesFace->setInnerComponent(MostEdgesEdge);
        MostEdgesFace->setOuterComponent(nullptr);
    }
}