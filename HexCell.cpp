#include "HexCell.h"
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

HexCell::HexCell(int Q, int R) {
    q = Q;
    r = R;
    for (int i =0;i<6;i++){
        neighbours[i] = nullptr;
        links[i] = nullptr;
    }
    path_dist_from_start = 0;
}

void HexCell::link(HexCell* cell) {
    
    if (cell == nullptr){
        return;
    }

    bool neigh = false;
    if (this->distance(cell)==1){
        neigh = true;
    }
    
    
    if (!neigh){
        return;
    } else{
        int neigh_indx = get_neighbour_side(cell);
        //printf("%d", neigh_indx);
        links[neigh_indx] = cell;
        //printf("%d", links[neigh_indx]->q);
        //printf("%d", links[neigh_indx]->r);
        if (neigh_indx <=2){
            cell->links[neigh_indx+3] = this;
        }
        else if (neigh_indx >=3 ){
            cell->links[neigh_indx-3] = this;
        }
    }
    
    

}


int HexCell::get_neighbour_side(const HexCell* cell) const {
    if (cell != nullptr){
        if ((r - cell->r) == 0){
        if ((q-cell->q) == 1){
            return 5;
        } else if ((q-cell->q) == -1){
            return 2;
        } 

    } else if ((r - cell->r) == 1){
        if ((q-cell->q) == 0){
            return 0;
        } else if ((q-cell->q) == -1){
            return 1;
        } 

    }else if ((r - cell->r) == -1){
        if ((q-cell->q) == 0){
            return 3;
        } else if ((q-cell->q) == 1){
            return 4;
        } 
    }
    }
    return -1;

}

// while (iterate through links)

// if an element in links == cell, return true

// if none of them match, return false



// So since the neighbour cell of an edge cell should be nullptr, 
// the edge cell's link in that direction is also nullptr, 
// so nullptr == nullptr, and your is_linked returns true.
bool HexCell::is_linked(const HexCell* cell) const {
    bool link = false;

    if (cell == nullptr){
        return false;
    }

    for (int i = 0;i<6;i++){
        if (links[i] != nullptr && links[i] == cell){
            return true;
        }
    }
    return false;
}

int HexCell::distance(const HexCell* cell) const {
    int dist = 0;
    
            
    if (cell !=nullptr){
        int dr = r - cell->r;
        int dq = q - cell->q;


        if (((dr) <=0 && (dq) <= 0) || ((dr) >0 && (dq) > 0) ){
            dist = abs(dr + dq);
        }
            
        else{
            dist = fmax(abs(dr), abs(dq)); 
        }
    }
    
    return dist;
}

bool HexCell::is_edge() const {
    
    for (int i = 0;i<6;i++){
        if (neighbours[i] == nullptr){
            return true;

        }
    }
    return false;
}