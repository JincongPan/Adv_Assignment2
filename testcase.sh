#!/bin/bash

#make IOTest
#./IOTest
#diff -w test_save_game_file.input test_save_game_file.ouput
./qwirkle < test_replace_node.input 
diff -w test_replace_node_file.output test_replace_node_file.output2 
