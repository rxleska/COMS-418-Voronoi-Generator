

#include "headers/BeachLine.hpp"
#include "headers/ParabolaMath.hpp"

//forward declarations
std::vector<CircleEvent *> circleEvents;

BeachLine::BeachLine() {
    this->root = nullptr;
    this->sweepLine = 0;
}

BeachLine::BeachLine(double sweepLine) {
    this->root = nullptr;
    this->sweepLine = sweepLine;
}

//getters and setters
EdgeNode *BeachLine::getRoot() {
    return this->root;
}

void BeachLine::setRoot(EdgeNode *root) {
    this->root = root;
}

double BeachLine::getSweepLine() {
    return this->sweepLine;
}

void BeachLine::setSweepLine(double sweepLine) {
    this->sweepLine = sweepLine;
}

//tree functions

void BeachLine::rightRotate(EdgeNode *node) {
    EdgeNode *y  = node->getLeft();
    node->setLeft(y->getRight());
    if (y->getRight() != nullptr) {
        y->getRight()->setParent(node);
    }
    y->setParent(node->getParent());
    if (node->getParent() == nullptr) {
        this->root = y;
    } else if (node == node->getParent()->getRight()) {
        node->getParent()->setRight(y);
    } else {
        node->getParent()->setLeft(y);
    }
    y->setRight(node);
    node->setParent(y);
}

void BeachLine::leftRotate(EdgeNode *node) {
    EdgeNode *y = node->getRight();
    node->setRight(y->getLeft());
    if (y->getLeft() != nullptr) {
        y->getLeft()->setParent(node);
    }
    y->setParent(node->getParent());
    if (node->getParent() == nullptr) {
        this->root = y;
    } else if (node == node->getParent()->getLeft()) {
        node->getParent()->setLeft(y);
    } else {
        node->getParent()->setRight(y);
    }
    y->setLeft(node);
    node->setParent(y);
}

void BeachLine::splay(EdgeNode *node) {
    while(node->getParent() != nullptr){
        if(node->getParent()->getParent() == nullptr){
            if(node->getParent()->getLeft() == node) rightRotate(node->getParent());
            else leftRotate(node->getParent());
        } else if(node->getParent()->getLeft() == node && node->getParent()->getParent()->getLeft() == node->getParent()){
            rightRotate(node->getParent()->getParent());
            rightRotate(node->getParent());
        } else if(node->getParent()->getRight() == node && node->getParent()->getParent()->getRight() == node->getParent()){
                leftRotate(node->getParent()->getParent());
                leftRotate(node->getParent());
        } else if(node->getParent()->getLeft() == node && node->getParent()->getParent()->getRight() == node->getParent()){
            rightRotate(node->getParent());
            leftRotate(node->getParent());
        } else {
            leftRotate(node->getParent());
            rightRotate(node->getParent());
        }
    }
}


EdgeNode *BeachLine::search(double searchX) {
    // if(VDEBUG) std::cout << "[BeachLine] search" << std::endl;
    //now returns the node that is closest to the searchX
    EdgeNode *current = this->root;
    while (current != nullptr) {
        double value = current->getValue(this->sweepLine);
        if(ParabolaMath::areSameDouble(value, searchX)){
            splay(current);
            return current;
        }
        else if (ParabolaMath::isLessThanDouble(searchX, value)) { //searchX < value
            //if left is null return current
            if(current->getLeft() == nullptr){
                splay(current);
                return current;
            }
            else{
                current = current->getLeft();
            }
        }
        else {
            //if right is null return current
            if(current->getRight() == nullptr){
                splay(current);
                return current;
            }
            else{
                current = current->getRight();
            }
        }
    
    }
    return nullptr;
}

EdgeNode *BeachLine::search(double searchX, double altSweepline) {
    // if(VDEBUG) std::cout << "[BeachLine] search alt " << altSweepline << std::endl;
    //now returns the node that is closest to the searchX
    EdgeNode *current = this->root;
    while (current != nullptr) {
        double value = current->getValue(altSweepline);
        if(ParabolaMath::areSameDouble(value, searchX)){
            splay(current);
            return current;
        }
        else if (ParabolaMath::isLessThanDouble(searchX, value)) { //searchX < value
            //if left is null return current
            if(current->getLeft() == nullptr){
                splay(current);
                return current;
            }
            else{
                current = current->getLeft();
            }
        }
        else {
            //if right is null return current
            if(current->getRight() == nullptr){
                splay(current);
                return current;
            }
            else{
                current = current->getRight();
            }
        }
    
    }
    return nullptr;
}





void BeachLine::insert(EdgeNode *node){
    if(VDEBUG) std::cout << "[BeachLine] insert" << std::endl;
    if(VDEBUG) std::cout << node->getX() << " " << node->getY() << " " << node->getAngle() << std::endl;

    if(this->root == nullptr){
        this->root = node;
        return;
    }
    EdgeNode *current = this->root;
    EdgeNode *parent = nullptr;
    while(current != nullptr){
        parent = current;
        if(ParabolaMath::areSameDouble(node->getValue(this->sweepLine),current->getValue(this->sweepLine))){
            if(node->getLeftArc() != nullptr && current->getRightArc() != nullptr && node->getLeftArc() == current->getRightArc()){
                std::cout << "used right on c:" << current->getX() << " : " << current->getY() <<" : " <<  current->getAngle() << std::endl;
                current = current->getRight();
            }
            else if(node->getRightArc() != nullptr && current->getLeftArc() != nullptr && node->getRightArc() == current->getLeftArc()){
                std::cout << "used left on c:" << current->getX() << " : " << current->getY() <<" : " <<  current->getAngle() << std::endl; 
                current = current->getLeft();
            }
            else{
                //instead of checking the value at the sweep line, check the value at the sweep line + 0.005
                if(node->getValue(this->sweepLine + 0.005) < current->getValue(this->sweepLine + 0.005)){
                    current = current->getLeft();
                } else {
                    current = current->getRight();
                }
            }


            
        }
        else{
            if(node->getValue(this->sweepLine) < current->getValue(this->sweepLine)){
            current = current->getLeft();
            } else {
                current = current->getRight();
            }
        }
    }

    node->setParent(parent);
    if(node->getValue(this->sweepLine) < parent->getValue(this->sweepLine)){
        parent->setLeft(node);
    } else {
        parent->setRight(node);
    }

    splay(node);
}

void BeachLine::remove(EdgeNode *node) {
    if(VDEBUG) std::cout << "[BeachLine] remove" << std::endl;
    if(VDEBUG) std::cout << node->getX() << " " << node->getY() << " " << node->getAngle() << std::endl;
    if (node == nullptr) return;

    // Splay the node to the root
    splay(node);

    // Now 'node' is the root of the splay tree
    if (node->getLeft() != nullptr && node->getRight() != nullptr) {
        // Both children are present
        BeachLine subtree;
        subtree.root = node->getLeft();
        subtree.root->setParent(nullptr);
        
        // Splay the maximum element in the left subtree
        EdgeNode *maxLeft = subtree.root;
        while (maxLeft->getRight() != nullptr) {
            maxLeft = maxLeft->getRight();
        }
        subtree.splay(maxLeft);

        // Attach the right subtree of the original tree to the right of the max element
        maxLeft->setRight(node->getRight());
        node->getRight()->setParent(maxLeft);

        // Set the new root of the main tree
        this->root = subtree.root;
    } else if (node->getLeft() != nullptr) {
        // Only the left child is present
        this->root = node->getLeft();
        this->root->setParent(nullptr);
    } else if (node->getRight() != nullptr) {
        // Only the right child is present
        this->root = node->getRight();
        this->root->setParent(nullptr);
    } else {
        // No child is present
        this->root = nullptr;
    }

    // Clean up
    delete node;
}


//beach line specific functions
void BeachLine::checkCircleEvent(EdgeNode *leftedge, EdgeNode *rightedge){
    if(VDEBUG) std::cout << "[BeachLine] checkCircleEvent" << std::endl;

    bool incrementSweepline = false;
    //if any of the arcs are at the sweep line, increment the sweepline by a small amount to avoid division by 0
    if(ParabolaMath::areSameDouble(leftedge->getLeftArc()->getY(), this->sweepLine)){
        this->sweepLine -= 0.001;
        incrementSweepline = true;
    }
    else if(ParabolaMath::areSameDouble(leftedge->getRightArc()->getY(), this->sweepLine)){
        this->sweepLine -= 0.001;
        incrementSweepline = true;
    }
    else if(ParabolaMath::areSameDouble(rightedge->getLeftArc()->getY(), this->sweepLine)){
        this->sweepLine -= 0.001;
        incrementSweepline = true;
    }
    else if(ParabolaMath::areSameDouble(rightedge->getRightArc()->getY(), this->sweepLine)){
        this->sweepLine -= 0.001;
        incrementSweepline = true;
    }

    if(incrementSweepline){
        // std::cout << "incremented sweepline for circle event check" << std::endl;
    }

    EdgeNode *nextLeft = getNextLeftEdge(leftedge);
    EdgeNode *nextRight = getNextRightEdge(rightedge);

    if(incrementSweepline){
        this->sweepLine += 0.001;
    }

    // std::cout << std::endl << std::endl;

    // switching to q p- p+ r method, p- is left edge, p+ is right edge, q is next left edge, r is next right edge
    double p1x;
    double p1y;
    CircleEvent * event;
    if(nextLeft != nullptr && ParabolaMath::doEdgesIntersect(nextLeft, leftedge, &p1x, &p1y)){
        double radius = sqrtf((p1x - leftedge->getRightArc()->getX())*(p1x - leftedge->getRightArc()->getX()) + (p1y - leftedge->getRightArc()->getY())*(p1y - leftedge->getRightArc()->getY()));
        event = new CircleEvent();
        event->setX(p1x);
        event->setY(p1y - radius);
        event->setIntersectionY(p1y);
        event->setLeftEdge(nextLeft);
        event->setRightEdge(leftedge);
        //sanity check that the edges do intersect at that point
        if(ParabolaMath::isLessThanOrEqualDouble(p1y-radius, beachLine->getSweepLine()) && ParabolaMath::doEdgesIntersectAtEvent(nextLeft, leftedge, p1x, p1y)){
            eventQueue->insert(event);
            circleEvents.push_back(event);
            if(DEBUG) std::cout << "inserted circle event: " << p1x << " " << p1y - radius << std::endl;
        }
        else{
            // if(DEBUG) std::cout << ParabolaMath::doEdgesIntersectAtEvent(nextLeft, leftedge, p1x, p1y);
            // log p1y-radius << " " << beachLine->getSweepLine() << std::endl;
            if(DEBUG) std::cout << "did not insert circle event: " << p1y - radius << " " << beachLine->getSweepLine() << std::endl;
            //log desired event location
            if(DEBUG) std::cout << "desired event location: " << p1x << " " << p1y << std::endl;
            delete event;
        }
    }

    // std::cout << std::endl << std::endl;

    double p2x;
    double p2y;
    if(nextRight != nullptr && ParabolaMath::doEdgesIntersect(rightedge, nextRight, &p2x, &p2y)){
        double radius = sqrtf((p2x - rightedge->getLeftArc()->getX())*(p2x - rightedge->getLeftArc()->getX()) + (p2y - rightedge->getLeftArc()->getY())*(p2y - rightedge->getLeftArc()->getY()));
        event = new CircleEvent();
        event->setX(p2x);
        event->setY(p2y - radius);
        event->setIntersectionY(p2y);
        event->setLeftEdge(rightedge);
        event->setRightEdge(nextRight);
        //sanity check that the edges do intersect at that point
        if(ParabolaMath::isLessThanOrEqualDouble(p2y-radius, beachLine->getSweepLine()) && ParabolaMath::doEdgesIntersectAtEvent(rightedge, nextRight, p2x, p2y)){
            eventQueue->insert(event);
            circleEvents.push_back(event);
            if(DEBUG) std::cout << "inserted circle event: " << p2x << " " << p2y - radius << std::endl;
        }
        else{
            // if(DEBUG) std::cout << ParabolaMath::doEdgesIntersectAtEvent(rightedge, nextRight, p2x, p2y);

            if(DEBUG) std::cout << "did not insert circle event: " << p1y - radius << " " << beachLine->getSweepLine() << std::endl;
            if(DEBUG) std::cout << "desired event location: " << p1x << " " << p1y << std::endl;
            delete event;
        }
    }
    else{
        if(DEBUG) std::cout << "did not insert circle event: " // the 3 arcs are
        << rightedge->getLeftArc()->getX() << " " << rightedge->getLeftArc()->getY() << " " << rightedge->getRightArc()->getX() << " " << rightedge->getRightArc()->getY() << std::endl;
        if(DEBUG){
            if(nextRight != nullptr){
                std::cout << "next right edge: " << nextRight->getLeftArc()->getX() << " " << nextRight->getLeftArc()->getY() << " " << nextRight->getRightArc()->getX() << " " << nextRight->getRightArc()->getY() << std::endl;
            }
            else{
                std::cout << "next right edge is null" << std::endl;
            }
        }
        // beachLine->printEdgesInOrder(beachLine->getRoot());
    }

    if(nextLeft != nullptr && nextRight != nullptr){
        //search for circle event with nextLeft and nextRight
        for(CircleEvent * event : circleEvents){
            if(event->getLeftEdge() == nextLeft && event->getRightEdge() == nextRight){
                //remove from circle events
                std::remove(circleEvents.begin(), circleEvents.end(), event);
                eventQueue->remove(event);
                break;
            }
        }
    }


    //old method
    // Arc *a1, *a2, *a3, *a4, *a5;
    // if(nextLeft != nullptr){
    //     a1 = nextLeft->getLeftArc();
    // }
    // a2 = leftedge->getLeftArc(); //same as nextLeft->getRightArc()
    // a3 = leftedge->getRightArc(); //same as rightedge->getLeftArc()
    // a4 = rightedge->getRightArc(); //same as nextRight->getLeftArc()
    // if(nextRight != nullptr){
    //     a5 = nextRight->getRightArc();
    // }

    // //3 checks for circle event (a1,a2,a3) (a2,a3,a4) (a3,a4,a5) 
    // //ignore a check if any of the arcs are the same proceed to next check
    // double evtx, evty, evtr;
    // if(nextLeft != nullptr &&
    //     !(
    //     a1 == a2 ||
    //     a2 == a3 ||
    //     a3 == a1
    // )){ // test 1st circle
    //     if(circleIntersectsBeachLine(Vertex(a1->getX(), a1->getY()), Vertex(a2->getX(), a2->getY()), Vertex(a3->getX(), a3->getY()), &evtx, &evty, &evtr)){
    //         CircleEvent * event = new CircleEvent();
    //         event->setX(evtx);
    //         event->setY(evty- evtr);
    //         event->setIntersectionY(evty);
    //         event->setLeftEdge(nextLeft);
    //         event->setRightEdge(leftedge);
    //         //before inserting sanity check that the edges do intersect eventually 
    //         //could also be due to the fact that I am not removing circle events whoms arcs have been deleted (will check later, this check is easier to implement and makes more sense in my head implementation wise)

    //         if(ParabolaMath::doEdgesIntersectAtEvent(nextLeft, leftedge, evtx, evty)){
    //             eventQueue->insert(event);
    //             if(DEBUG) std::cout << "inserted circle event: " << evtx << " " << evty - evtr << std::endl;
    //         }        
    //     }
    // }

    // if(!(
    //     a2 == a3 ||
    //     a3 == a4 ||
    //     a4 == a2
    // )){ // test 2nd circle
    //     if(circleIntersectsBeachLine(Vertex(a4->getX(), a4->getY()), Vertex(a2->getX(), a2->getY()), Vertex(a3->getX(), a3->getY()), &evtx, &evty, &evtr)){
    //         CircleEvent * event = new CircleEvent();
    //         event->setX(evtx);
    //         event->setY(evty - evtr);
    //         event->setIntersectionY(evty);
    //         event->setLeftEdge(leftedge);
    //         event->setRightEdge(rightedge);
    //         //before inserting sanity check that the edges do intersect eventually 
    //         if(ParabolaMath::doEdgesIntersectAtEvent(leftedge, rightedge, evtx, evty)){
    //             eventQueue->insert(event);
    //             if(DEBUG) std::cout << "inserted circle event: " << evtx << " " << evty - evtr << std::endl;
    //         }
    //     }
    // }

    // if(nextRight != nullptr &&
    //     !(
    //     a3 == a4 ||
    //     a4 == a5 ||
    //     a5 == a3
    // )){ // test 3rd circle
    //     if(circleIntersectsBeachLine(Vertex(a3->getX(), a3->getY()), Vertex(a4->getX(), a4->getY()), Vertex(a5->getX(), a5->getY()), &evtx, &evty, &evtr)){
    //         CircleEvent * event = new CircleEvent();
    //         event->setX(evtx);
    //         event->setY(evty - evtr);
    //         event->setIntersectionY(evty);
    //         event->setLeftEdge(rightedge);
    //         event->setRightEdge(nextRight);
    //         //before inserting sanity check that the edges do intersect eventually 
    //         if(ParabolaMath::doEdgesIntersectAtEvent(rightedge, nextRight, evtx, evty)){
    //             eventQueue->insert(event);
    //             if(DEBUG) std::cout << "inserted circle event: " << evtx << " " << evty - evtr << std::endl;
    //         }
    //     }

    // }

    
}
void BeachLine::checkCircleEvent(EdgeNode *centerEdge){
    EdgeNode *nextLeft = getNextLeftEdge(centerEdge);
    EdgeNode *nextRight = getNextRightEdge(centerEdge);

    Arc *a1, *a2, *a3, *a4;
    if(nextLeft != nullptr){
        a1 = nextLeft->getLeftArc();
    }
    a2 = centerEdge->getLeftArc(); //same as nextLeft->getRightArc()
    a3 = centerEdge->getRightArc(); //same as rightedge->getLeftArc()
    if(nextRight != nullptr){
        a4 = nextRight->getRightArc();
    }

    CircleEvent * event;
    double evtx, evty, evtr;
    if(nextLeft != nullptr &&
        !(
        a1 == a2 ||
        a2 == a3 ||
        a3 == a1
    )){ // test 1st circle
        if(circleIntersectsBeachLine(Vertex(a1->getX(), a1->getY(), -1), Vertex(a2->getX(), a2->getY(), -1), Vertex(a3->getX(), a3->getY(), -1), &evtx, &evty, &evtr)){
            event = new CircleEvent();
            event->setX(evtx);
            event->setY(evty- evtr);
            event->setIntersectionY(evty);
            event->setLeftEdge(nextLeft);
            event->setRightEdge(centerEdge);
            //before inserting sanity check that the edges do intersect eventually 
            //could also be due to the fact that I am not removing circle events whoms arcs have been deleted (will check later, this check is easier to implement and makes more sense in my head implementation wise)

            if(ParabolaMath::doEdgesIntersectAtEvent(nextLeft, centerEdge, evtx, evty)){
                eventQueue->insert(event);
                circleEvents.push_back(event);
                if(DEBUG) std::cout << "inserted circle event: " << evtx << " " << evty - evtr << std::endl;
            }
            else{
                std::cout << "did not insert circle event: " << evtx << " " << evty - evtr << " " << evty << std::endl;
                delete event;
            }        
        }
        else{
            std::cout << "a1: " << a1->getX() << " " << a1->getY() << " a2: " << a2->getX() << " " << a2->getY() << " a3: " << a3->getX() << " " << a3->getY() << std::endl;
            std::cout << "did not insert circle event: " << evtx << " " << evtr << " " << evty << std::endl;
        }
    }

    if(nextRight != nullptr && !(
        a2 == a3 ||
        a3 == a4 ||
        a4 == a2
    )){ // test 2nd circle
        if(circleIntersectsBeachLine(Vertex(a4->getX(), a4->getY(), -1), Vertex(a2->getX(), a2->getY(), -1), Vertex(a3->getX(), a3->getY(), -1), &evtx, &evty, &evtr)){
            event = new CircleEvent();
            event->setX(evtx);
            event->setY(evty - evtr);
            event->setIntersectionY(evty);
            event->setLeftEdge(centerEdge);
            event->setRightEdge(nextRight);
            //before inserting sanity check that the edges do intersect eventually 
            if(ParabolaMath::doEdgesIntersectAtEvent(centerEdge, nextRight, evtx, evty)){
                eventQueue->insert(event);
                circleEvents.push_back(event);
                if(DEBUG) std::cout << "inserted circle event: " << evtx << " " << evty - evtr << std::endl;
            }
            else{
                delete event;
            }
        }
        else{
            std::cout << "a2: " << a2->getX() << " " << a2->getY() << " a3: " << a3->getX() << " " << a3->getY() << " a4: " << a4->getX() << " " << a4->getY() << std::endl;
            std::cout << "did not insert circle event: " << evtx << " " << evtr << " " << evty << std::endl;
        }
    }
}


bool BeachLine::circleIntersectsBeachLine(Vertex Apt, Vertex Bpt, Vertex Cpt, double *x, double *y, double *r){
    if(VDEBUG) std::cout << "[BeachLine] circleIntersectsBeachLine" << std::endl;
    //find the slope of Apt to Bpt
    double mAB = (Apt.getY() - Bpt.getY()) / (Apt.getX() - Bpt.getX());
    //find the center point of the line between Apt and Bpt
    Vertex midAB = Vertex((Apt.getX() + Bpt.getX()) / 2, (Apt.getY() + Bpt.getY()) / 2, -1);
    double mPerpAB = -1.0 / mAB;
    //find the y intercept of a line perpendicular to AB that goes through midAB
    double bPerpAB = midAB.getY() - mPerpAB * midAB.getX();

    //find the slope of Bpt to Cpt
    double mBC = (Bpt.getY() - Cpt.getY()) / (Bpt.getX() - Cpt.getX());
    //find the center point of the line between Bpt and Cpt
    Vertex midBC = Vertex((Bpt.getX() + Cpt.getX()) / 2, (Bpt.getY() + Cpt.getY()) / 2, -1);
    double mPerpBC = -1.0 / mBC;
    //find the y intercept of a line perpendicular to BC that goes through midBC
    double bPerpBC = midBC.getY() - mPerpBC * midBC.getX();

    //find the slope of Cpt to Apt
    double mCA = (Cpt.getY() - Apt.getY()) / (Cpt.getX() - Apt.getX());
    //find the center point of the line between Cpt and Apt
    Vertex midCA = Vertex((Cpt.getX() + Apt.getX()) / 2, (Cpt.getY() + Apt.getY()) / 2, -1);
    double mPerpCA = -1.0 / mCA;
    //find the y intercept of a line perpendicular to CA that goes through midCA
    double bPerpCA = midCA.getY() - mPerpCA * midCA.getX();

    double circumcenterX;
    double circumcenterY;
    double radius;


    if(ParabolaMath::areSameDouble(Apt.getY(), Bpt.getY())){ //use CA and BC
        //find the intersection of the two lines
        circumcenterX = (bPerpCA - bPerpBC) / (mPerpBC - mPerpCA);
        circumcenterY = mPerpCA * circumcenterX + bPerpCA;

        //find the distance between the circumcenter and any of the points //its the same for all 3 points
        radius = sqrt((Apt.getX() - circumcenterX)*(Apt.getX() - circumcenterX) + (Apt.getY() - circumcenterY)*(Apt.getY() - circumcenterY));

    }
    else if(ParabolaMath::areSameDouble(Bpt.getY(), Cpt.getY())){// use AB and CA
        //find the intersection of the two lines
        circumcenterX = (bPerpAB - bPerpCA) / (mPerpCA - mPerpAB);
        circumcenterY = mPerpAB * circumcenterX + bPerpAB;

        //find the distance between the circumcenter and any of the points //its the same for all 3 points
        radius = sqrt((Apt.getX() - circumcenterX)*(Apt.getX() - circumcenterX) + (Apt.getY() - circumcenterY)*(Apt.getY() - circumcenterY));

    }
    else{// use BC and AB
        //find the intersection of the two lines 
        circumcenterX = (bPerpBC - bPerpAB) / (mPerpAB - mPerpBC);
        circumcenterY = mPerpAB * circumcenterX + bPerpAB;

        //find the distance between the circumcenter and any of the points //its the same for all 3 points
        radius = sqrt((Apt.getX() - circumcenterX)*(Apt.getX() - circumcenterX) + (Apt.getY() - circumcenterY)*(Apt.getY() - circumcenterY));
    }

    

    //check if the circle intersects the sweepline
    if(ParabolaMath::isLessThanOrEqualDouble(circumcenterY - radius, this->sweepLine)){
        *x = circumcenterX;
        *y = circumcenterY;
        *r = radius;
        return true;
    }
    return false;

}


EdgeNode *BeachLine::getNextLeftEdge(EdgeNode *node){
    splay(node);
    if(node->getLeft() == nullptr){
        return nullptr;
    }
    else{
        EdgeNode *current = node->getLeft();
        while(current->getRight() != nullptr){
            current = current->getRight();
        }
        return current;
    }
}

EdgeNode *BeachLine::getNextRightEdge(EdgeNode *node){
    splay(node);
    if(node->getRight() == nullptr){
        return nullptr;
    }
    else{
        EdgeNode *current = node->getRight();
        while(current->getLeft() != nullptr){
            current = current->getLeft();
        }
        return current;
    }
}
    



void BeachLine::printTree(EdgeNode *node){
    if(node == nullptr) return;
    printTree(node->getLeft());
    std::cout << "x: " << node->getX() << " y: " << node->getY() << " r: " << node->getAngle() << " value: " << node->getValue(this->sweepLine) << std::endl  << " left arc x:" << node->getLeftArc()->getX() << " y:" << node->getLeftArc()->getY() << std::endl << " right arc x:" << node->getRightArc()->getX() << " y:" << node->getRightArc()->getY() << std::endl;
    printTree(node->getRight());
}

void BeachLine::printTree(EdgeNode *node, double altSweepline){
    if(node == nullptr) return;
    printTree(node->getLeft(),altSweepline);
    std::cout << "x: " << node->getX() << " y: " << node->getY() << " r: " << node->getAngle() << " value: " << node->getValue(altSweepline) << std::endl  << " left arc x:" << node->getLeftArc()->getX() << " y:" << node->getLeftArc()->getY() << std::endl << " right arc x:" << node->getRightArc()->getX() << " y:" << node->getRightArc()->getY() << std::endl;
    printTree(node->getRight(),altSweepline);
}


void BeachLine::printEdgesInOrder(EdgeNode *node){
    if(node == nullptr) return;
    printEdgesInOrder(node->getLeft());
    std::cout << "x: " << node->getX() << " y: " << node->getY() << " r: " << node->getAngle() << " value: " << node->getValue(this->sweepLine) << std::endl  << " left arc x:" << node->getLeftArc()->getX() << " y:" << node->getLeftArc()->getY() << std::endl << " right arc x:" << node->getRightArc()->getX() << " y:" << node->getRightArc()->getY() << std::endl;
    printEdgesInOrder(node->getRight());
}