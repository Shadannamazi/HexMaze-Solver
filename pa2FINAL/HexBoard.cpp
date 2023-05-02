#include "HexBoard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

HexBoard::HexBoard(int radius) {
    this->radius = radius;
    longest_path_dist =0;
    longest_path_dist_edge =0;
    start_coord = {0,0};
    end_coord = {0,0};
    cells.clear();
    create_board();
    configure_cells();
}

void HexBoard::create_board() {
    
    for (int r = -radius + 1; r < radius; r++) {
        int r1 = std::max(-radius + 1, -r - radius + 1);
        int r2 = std::min(radius - 1, -r + radius - 1);
        for (int q = r1; q <= r2; q++) {
            HexCell* new_cell = new HexCell(q, r);
            cells[{q,r}] = new_cell;
          
        }
    }
}

void HexBoard::configure_cells() {
    for (auto kv : cells) {
        HexCell* cell = kv.second;
        vector<pair<int, int>> n = get_neigh_coords(kv.first);
        if (cell != nullptr){
            for (int i=0;i<6;i++){
                
                    auto it = cells.find(n[i]);
                    if (it!=cells.end()){
                        cell->neighbours[i] = it->second;
                    }       

            }
            
        }
    }
}


void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob) {
    Stack<pair<int,int>> stack;
    this->start_coord = start_coord;
    stack.push(start_coord);
    map<pair<int,int>,bool> visited;
    visited.insert({start_coord,true});
    //mark as visited?
    while(!stack.isEmpty()){
        HexCell* curr_cell = cells[stack.peek()];
        //printf("curr cell 1: %d \n",curr_cell->path_dist_from_start);

        // pair<int,int> curr_coord = {curr_cell->q,curr_cell->r};
        // visited.insert({curr_coord,true});

        HexCell* neigh_cell = chooseNeighbour(curr_cell,visited,branch_prob);
        //curr_cell->path_dist_from_start = curr_cell->distance(cells[start_coord]);
        if (neigh_cell != nullptr){
            curr_cell->link(neigh_cell);
            //printf("curr cell (%d,%d), linked with:(%d,%d): \n",curr_cell->q,curr_cell->r,neigh_cell->q,neigh_cell->r);

            pair<int,int> neigh_coord = {neigh_cell->q,neigh_cell->r};
            visited.insert({neigh_coord,true});
            
            
            //neigh_cell->path_dist_from_start = neigh_cell->distance(cells[start_coord]);
            //curr_cell->path_dist_from_start = 
            neigh_cell->path_dist_from_start =curr_cell->path_dist_from_start + 1;
            //printf("curr cell (%d,%d): %d \n",curr_cell->q,curr_cell->r,curr_cell->path_dist_from_start);

            //this
            //printf("neigh cell(%d,%d): %d \n",neigh_cell->q,neigh_cell->r,neigh_cell->path_dist_from_start);

            if (neigh_cell->path_dist_from_start >= longest_path_dist){
                longest_path_dist = neigh_cell->path_dist_from_start;
    
            } 
          
            if (neigh_cell->is_edge() && neigh_cell->path_dist_from_start > longest_path_dist_edge){
                longest_path_dist_edge = neigh_cell->path_dist_from_start;
                end_coord = {neigh_cell->q,neigh_cell->r};
            }

            stack.push(neigh_coord);
        } else{
        
            stack.pop();
        }
    }
}

void HexBoard::solve_maze() {
    Stack<pair<int,int>> s;
    s.push(end_coord);
    map<pair<int,int>,bool> dead;

    map<pair<int,int>,bool> visited;
    visited.insert({end_coord,true});
    bool path_found = false;

    while(!s.isEmpty()){
        pair<int,int> curr_coord = s.peek();
        HexCell* curr_cell = cells[curr_coord];

        visited.insert({curr_coord,true});

        bool neigh_found = false;
        HexCell* neigh_cell;
        pair<int,int> neigh_coord;
        for (int i=0;i<6;i++){
            neigh_cell = curr_cell->links[i];
            

            if (neigh_cell != nullptr && visited.find({neigh_cell->q, neigh_cell->r}) == visited.end()) { //smth wrong with checking if visited or not
                neigh_coord = {neigh_cell->q,neigh_cell->r};

                s.push(neigh_coord);
                visited.insert({neigh_coord,true});
                neigh_found = true;
                break;

                if (dead.find({neigh_cell->q, neigh_cell->r}) != dead.end()){

                    dead.insert({s.pop(),true});
                }

            } 

        }




        if (!neigh_found && curr_coord != start_coord){
            dead.insert({curr_coord,true});
            s.pop();

        }

        if (curr_coord == start_coord){
            while(!s.isEmpty()){
                //pair<int,int> p = ;
                //printf("(%d,%d)\n", p.first, p.second);
                solution.push_back(s.pop());
            }
            
        }

        

        

        


    }
    // Queue<pair<int,int>> q;
    // q.enqueue(end_coord);
    // map<pair<int,int>,bool> dead;

    // map<pair<int,int>,bool> visited;
    // visited.insert({end_coord,true});
    // bool path_found = false;

    // while(!q.isEmpty()){
    //     pair<int,int> curr_coord = q.peek();
    //     HexCell* curr_cell = cells[curr_coord];

    //     visited.insert({curr_coord,true});

    //     bool neigh_found = false;
    //     HexCell* neigh_cell;
    //     pair<int,int> neigh_coord;
    //     for (int i=0;i<6;i++){
    //         neigh_cell = curr_cell->links[i];
            

    //         if (neigh_cell != nullptr && !visited[neigh_coord]) {
    //             neigh_coord = {neigh_cell->q,neigh_cell->r};
    //             q.enqueue(neigh_coord);
    //             visited.insert({neigh_coord,true});
    //             neigh_found = true;

    //             if (dead.find({neigh_cell->q, neigh_cell->r}) != dead.end()){

    //                 dead.insert({q.dequeue(),true});
    //             }

    //         } 
            
    //     }
    //     if (!neigh_found){
    //         dead.insert({neigh_coord,true});
    //         q.dequeue();

    //     }

    //     if (curr_coord == start_coord){
    //         solution.push_back(q.dequeue());
    //     }


    // }
    

    
}



// void HexBoard::solve_maze() {

//     Stack<pair<int,int>> stack;
//     stack.push(end_coord);
//     bool path_found = false;

//     //vector<pair<int,int>> dead_end;
//     map<pair<int,int>,bool> dead_end;
    
//     pair<int,int> tmp = {end_coord};
//     pair<int,int> prev = {end_coord};
//     solution.push_back(end_coord);
//     while (!stack.isEmpty() && !path_found) {

//         pair<int,int> curr_coord = stack.peek();
//         //HexCell* curr_cell = cells[curr_coord];
        
//         //visited.insert({{curr_cell->q,curr_cell->r},true});
//         for (int i =0;i<6;i++){
//             if (cells[tmp]->links[i] != nullptr && cells[tmp]->links[i] != cells[prev]){
//                 if (dead_end.find({cells[tmp]->links[i]->q,cells[tmp]->links[i]->r}) == dead_end.end()){
//                     curr_coord={cells[tmp]->links[i]->q,cells[tmp]->links[i]->r};
//                     stack.push(curr_coord);
//                     solution.push_back(curr_coord);
//                     prev = tmp;
//                     tmp = curr_coord;
//                     break;
//                 }
                
//             } else{
//                 if (tmp!= start_coord){
//                     tmp = stack.pop();
//                 } else{
//                     path_found = true;
//                 }
//                 //pair<int,int> insert_vec = {cells[tmp]->q,cells[tmp]->r};
//                 //dead_end.insert({insert_vec,true});
//                 // if (!contains(dead_end,insert_vec)){
//                 //     //dead_end.push_back(insert_vec);
                    
//                 // }
                
//                 // if (!stack.isEmpty()){
//                 //   tmp = stack.pop();
                     
//                 // }
//                 // if (solution.size() != 0){
//                 //     solution.pop_back(); 
//                 // }
                

//             }
            
//         }
        
//     }
        
// }


