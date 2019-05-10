
#include "LinkedList.h"

#include <iostream>
char colour[] = {'R', 'O', 'Y', 'G', 'B', 'P'};
int shape[] = {1, 2, 3, 4, 5, 6};

int main(void) {
   LinkedList* list = new LinkedList();

   for (int i = 0; i < 6; ++i) {
      for (int j = 0; j < 6; ++j) {
         // std::cout << i << " " << j << std::endl;
         Tile* t1 = new Tile(colour[i], shape[j]);
         list->InsertNodeToTail(t1);
      }
   }

   std::cout << list->GetTiles() << std::endl;
   // list->PrintTiles();
   list->Shuffle();
   std::cout << list->GetTiles() << std::endl;
   // list->PrintTiles();
   Node* tn = nullptr;
   
   LinkedList* hand = new LinkedList();
   for (size_t k = 0; k < 6; ++k) {
      tn = list->Pop();
      hand->InsertNodeToTail(tn);
   }
   std::cout << "Before Delete B5, hand's" << hand->GetTiles() << std::endl;
   std::cout << "Before Delete B5, bags's" << list->GetTiles() << std::endl;
   std::cout << "Delete B5" << std::endl;

   // delete B5
   tn = hand->DeleteTile(new Tile('P', 6));
   list->InsertNodeToTail(tn);
   tn = list->Pop();
   hand->InsertNodeToTail(tn);
   std::cout << "After Delete B5, hand's" << hand->GetTiles() << std::endl;
   std::cout << "After Delete B5, bag's" << list->GetTiles() << std::endl;

   // hand->PrintTiles();
   return 0;
}
