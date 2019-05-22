#!/bin/bash

#make clean
#make -j4
echo "test_menu_invalid_input"
./qwirkle < test_menu_invalid_input_1.input > test_menu_invalid_input_1.output
diff -w test_menu_invalid_input_1.gameout test_menu_invalid_input_1.output

echo "test_input_player_num_invalid_input"
./qwirkle < test_input_player_num_invalid_input_1.input > test_input_player_num_invalid_input_1.output
diff -w test_input_player_num_invalid_input_1.gameout test_input_player_num_invalid_input_1.output 

echo "test_player_name_upper_invalid_input"
./qwirkle < test_player_name_upper_invalid_input_1.input > test_player_name_upper_invalid_input_1.output
diff -w test_player_name_upper_invalid_input_1.gameout test_player_name_upper_invalid_input_1.output

echo "test_place_illegal_same_tile"
./qwirkle < test_place_illegal_same_tile_1.input > test_place_illegal_same_tile_1.output
diff -w test_place_illegal_same_tile_1.gameout test_place_illegal_same_tile_1.output

echo "test_place_tile_location_error"
./qwirkle < test_place_tile_location_error_1.input  >  test_place_tile_location_error_1.output
diff -w test_place_tile_location_error_1.output test_place_tile_location_error_1.gameout

echo "test_place_tile_tileformat_error"
./qwirkle < test_place_tile_tileformat_error_1.input > test_place_tile_tileformat_error_1.output
diff -w test_place_tile_tileformat_error_1.output test_place_tile_tileformat_error_1.gameout

echo "test_place_tile_notexistin_playerhands_error"
./qwirkle < test_place_tile_notexistin_playerhands_error_1.input > test_place_tile_notexistin_playerhands_error_1.output
diff -w test_place_tile_notexistin_playerhands_error_1.output test_place_tile_notexistin_playerhands_error_1.gameout

echo "test_place_tile_illegal_qwirklerules_error"
./qwirkle < test_place_tile_illegal_qwirklerules_error_1.input > test_place_tile_illegal_qwirklerules_error_1.output
diff -w test_place_tile_illegal_qwirklerules_error_1.output  test_place_tile_illegal_qwirklerules_error_1.gameout

echo "test_replace_tileformat_error"
./qwirkle < test_replace_tileformat_error_1.input > test_replace_tileformat_error_1.output
diff -w test_replace_tileformat_error_1.output test_replace_tileformat_error_1.gameout

echo "test_replace_tile_notexist_inhands_error"
./qwirkle < test_replace_tile_notexist_inhands_error_1.input > test_replace_tile_notexist_inhands_error_1.output
diff -w test_replace_tile_notexist_inhands_error_1.output test_replace_tile_notexist_inhands_error_1.gameout

echo "test_replace_node"
./qwirkle < test_replace_node_1.input  > test_replace_node_1.output
./qwirkle < test_replace_node_1.output  > test_replace_node_1.gameout

echo "test_restart_1"
./qwirkle < test_restart_1.input > test_restart_1.output
diff -w test_restart_1.output test_restart_1.gameout

#./qwirkle < test_invalid_input_2.input > test_invalid_input_2.gameout
#diff -w test_invalid_input_2.gameout test_invalid_input_2.output

echo "test_score_1"
./qwirkle < test_score_1.input > test_score_1.output
diff -w test_score_1.gameout test_score_1.output

echo "test_score"
./qwirkle < test_score.input > test_score.output
./qwirkle < test_score.output > test_score.gameout

echo "test_highscore"
./qwirkle < test_highscore_1.input > test_highscore_1.output 
diff -w test_highscore_1.gameout test_highscore_1.output

echo "test_unicode"
#./qwirkle < test_unicode_1.input  > test_unicode_1.output
#diff -w test_unicode_1.gameout test_unicode_1.output

echo "test_multi_player3"
./qwirkle < test_multi_player3_1.input > test_multi_player3_1.output
diff -w test_multi_player3_1.gameout test_multi_player3_1.output 

#make IOTest
#./IOTest
#diff -w test_load_and_save_game_1.save test_load_and_save_game_1.actualsave
#./qwirkle < test_replace_node.input 
#diff -w test_replace_node_file.output test_replace_node_file.output2 
