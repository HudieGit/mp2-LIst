#include "List.h"
#include <iostream>
#include <gtest.h>
//конструктор
TEST(List, can_create_list) {
	EXPECT_NO_THROW(List<int> ls(););
}
//ноды
TEST(List, can_create_Node_with_append) {
	List<int> ls;
	EXPECT_NO_THROW(ls.append(10));
}

TEST(List, can_create_Node_with_append_after_head) {
	List<int> ls;
	ls.append(10);
	EXPECT_NO_THROW(ls.append(90));
}

TEST(List, can_create_Node_with_insert) {
	List<int> ls;
	EXPECT_NO_THROW(ls.insert(10));
}

TEST(List, can_create_Node_with_insert_in_place_0) {
	List<int> ls;
	EXPECT_NO_THROW(ls.insert(10,0));
}

TEST(List, can_create_Node_with_insert_negativ_place) {
	List<int> ls;
	EXPECT_ANY_THROW(ls.insert(10, -1));
}

TEST(List, can_create_Node_with_insert_too_large_place) {
	List<int> ls;
	ls.append(5);
	EXPECT_ANY_THROW(ls.insert(10, 2));
}

TEST(List, can_create_Node_with_insert_in_place_between_node) {
	List<int> ls;
	ls.append(5); //0
	ls.append(6); //1 => 2
	EXPECT_NO_THROW(ls.insert(10, 1)); //новый 1
}

TEST(List, can_create_Node_with_insert_in_place_tail) {
	List<int> ls;
	ls.append(5); //0
	ls.append(6); //1
	ls.append(7); //1
	ls.append(5);
	ls.printList();
	ls.insert(10, 4);
	ls.printList();
	EXPECT_NO_THROW(ls.insert(10, 2)); //2
}

TEST(List, check_insert_corret_place) {
	List<int> ls;
	ls.append(5); //0
	ls.append(6); 
	ls.insert(10, 1); //1 , (6) 1 => 2 
	EXPECT_EQ(ls[1], 10); 
}

TEST(List, check_insert_without_place) {
	List<int> ls;
	ls.append(9);
	ls.append(8);
	ls.insert(10);
	EXPECT_EQ(ls[0], 10);
}

TEST(List, check_insert_without_place_in_emty_list) {
	List<int> ls;
	ls.insert(10);
	EXPECT_EQ(ls[0], 10);
}

//Тесты копирования
TEST(List, can_criete_copied_list) {
	List<int> ls;
	ls.append(10);
	EXPECT_NO_THROW(List<int> lst(ls));
}

TEST(List, copied_list_is_equal_to_source_one) {
	List<int> ls;
	ls.append(5);
	ls.append(10);
	List<int> lst(ls);
	EXPECT_EQ(ls, lst);
}
TEST(List, copied_list_has_its_own_memory) {
	List<int> ls0;
	ls0.append(5);
	List<int> ls1(ls0);

	ls0[0] = 100;
	EXPECT_EQ(ls0[0], 100);
	EXPECT_EQ(ls1[0], 5);
}
//оператор скобочки
TEST(List, can_use_operator_square_brackets) {
	List<int> ls;
	ls.insert(10);
	EXPECT_NO_THROW(ls[0]);
}

TEST(List, can_use_operator_square_brackets_with_incorrect_index_null_ptr) {
	List<int> ls;
	ls.insert(10);
	EXPECT_ANY_THROW(ls[1]);
}

TEST(List, can_use_operator_square_brackets_with_incorrect_too_large_index) {
	List<int> ls;
	ls.insert(10);
	EXPECT_ANY_THROW(ls[3]);
}

TEST(List, can_use_operator_square_brackets_with_incorrect_negativ_index) {
	List<int> ls;
	ls.insert(10);
	EXPECT_ANY_THROW(ls[-1]);
}
//оператор равно
TEST(List, can_use_uperator_equal_with_empty_lists) {
	List<int> ls0;
	List<int> ls1;
	EXPECT_NO_THROW(ls0 = ls1);
}

TEST(List, can_use_uperator_equal_with_equal_size) {
	List<int> ls0;
	ls0.append(5);
	ls0.append(6);
	List<int> ls1;
	ls1.append(1);
	ls1.append(2);

	EXPECT_NO_THROW(ls0 = ls1);
}

TEST(List, can_use_uperator_equal_with_different_size) {
	List<int> ls0;
	ls0.append(5);
	List<int> ls1;
	ls1.append(1);
	ls1.append(2);

	EXPECT_NO_THROW(ls0 = ls1);
}

TEST(List, sheck_correct_use_opetator_equal) {
	List<int> ls0;
	ls0.append(5);
	ls0.append(6);
	List<int> ls1;
	ls1.append(1);
	ls1.append(2);

	ls0 = ls1;
	EXPECT_EQ(ls0[0], ls1[0]);
	EXPECT_EQ(ls0[1], ls1[1]);
}

TEST(List, copied_list_into_yourself) {
	List<int> ls;
	EXPECT_NO_THROW(ls = ls);
}

TEST(List, check_copied_list_has_own_memory) {
	List<int> ls0;
	ls0.append(5);
	List<int> ls1;
	ls1.append(1);

	ls0 = ls1;
	ls0[0] = 100;
	EXPECT_EQ(ls0[0], 100);
	EXPECT_EQ(ls1[0], 1);
}
//другие
TEST(List, can_use_clear) {
	List<int> ls;
	ls.append(10);
	ls.append(5);
	EXPECT_NO_THROW(ls.clear());
}

TEST(List, clear_check_correct_job) {
	List<int> ls;
	ls.append(10);
	ls.append(5);
	ls.clear();
	EXPECT_TRUE(ls.empty() == 1);
}

TEST(List, can_use_printList) {
	List<int> ls;
	ls.append(10);
	ls.append(5);
	ls.append(11);
	EXPECT_NO_THROW(ls.printList());
}
//empty
TEST(List, can_use_empty_true) {
	List<int> ls;
	EXPECT_TRUE(ls.empty());
}

TEST(List, can_use_empty_false) {
	List<int> ls;
	ls.append(11);
	EXPECT_FALSE(ls.empty());
}

//getTail / getHead
TEST(List, can_use_getHead) {
	List<int> ls;
	ls.append(11);
	EXPECT_NO_THROW(ls.getHead());
}

TEST(List, can_use_getTail) {
	List<int> ls;
	ls.append(11);
	EXPECT_NO_THROW(ls.getTail());
}
//search
TEST(List, can_use_search) {
	List<int> ls;
	ls.append(11);
	ls.append(20);
	ls.append(50);
	EXPECT_NO_THROW(ls.search(11));
}

TEST(List, check_correct_operation_search_first_elem) {
	List<int> ls;
	ls.append(11);
	ls.append(20);
	ls.append(50);
	auto search_elem = ls.search(11);
	EXPECT_EQ(search_elem, ls.getHead());
}

TEST(List, check_correct_operation_search_tail_elem) {
	List<int> ls;
	ls.append(11);
	ls.append(20);
	ls.append(50);
	auto search_elem = ls.search(50);
	EXPECT_EQ(search_elem, ls.getTail());
}

//получение размера
TEST(List, can_get_size) {
	List<int> ls;
	ls.append(5);
	size_t size = ls.getSize();
	EXPECT_EQ(1, size);
}
//оператор равноравно
TEST(List, compare_equal_list_expect_true) {
	List<int> ls0;
	List<int> ls1;
	ls0.append(5);
	ls1.append(5);
	EXPECT_TRUE(ls0 == ls1);
}

TEST(List, compare_equal_list_expect_false) {
	List<int> ls0;
	List<int> ls1;
	ls0.append(5);
	ls1.append(4);
	EXPECT_FALSE(ls0 == ls1);
}

TEST(List, compare_equal_list_differense_size_expect_false) {
	List<int> ls0;
	List<int> ls1;
	ls0.append(5);
	ls1.append(5);
	ls1.append(6);
	EXPECT_FALSE(ls0 == ls1);
}

TEST(List, compare_equal_large_lists) {
	List<int> ls0;
	List<int> ls1;
	ls0.append(5);
	ls1.append(5);
	ls1.append(6);
	ls0.append(6);
	ls0.append(10);
	ls1.append(10);
	EXPECT_TRUE(ls0 == ls1);
}


//тесты remove
TEST(List, can_use_remove) {
	List<int> ls;
	ls.append(5);
	ls.append(11);
	
	EXPECT_NO_THROW(ls.remove(5));
}

TEST(List, can_use_remove_empty_list) {
	List<int> ls;
	EXPECT_NO_THROW(ls.remove(5));
}

TEST(List, remove_check_correct_job_Head) {
	List<int> ls;
	ls.append(5);
	ls.append(11);
	ls.append(20);
	ls.remove(5);
	EXPECT_EQ(ls[0], 11);
}

TEST(List, remove_check_correct_job_center) {
	List<int> ls;
	ls.append(5);
	ls.append(11);
	ls.append(20);
	ls.remove(11);
	EXPECT_EQ(ls[0], 5);
	EXPECT_EQ(ls[1], 20);
}

TEST(List, remove_check_correct_job_tail) {
	List<int> ls;
	ls.append(5);
	ls.append(11);
	ls.append(20);
	ls.remove(20);
	EXPECT_EQ(ls[0], 5);
	EXPECT_EQ(ls[1], 11);
}

TEST(List, can_use_remove_none_argunents) {
	List<int> ls;
	ls.append(5);
	ls.append(11);

	EXPECT_NO_THROW(ls.remove());
}

TEST(List, check_remove_none_argunents) {
	List<int> ls;
	ls.append(5);
	ls.append(11);
	ls.remove();
	EXPECT_EQ(ls[0], 11);
}

TEST(List, check_remove_none_argunents_last_Node) {
	List<int> ls;
	ls.append(5);
	ls.remove();
	EXPECT_EQ(ls.getSize(), 0);
}

TEST(List, can_use_remove_empty_list_none_argunents) {
	List<int> ls;
	EXPECT_NO_THROW(ls.remove());
}

//move
TEST(List, can_use_move_constructor) {
	List<int> ls;
	ls.append(10);
	EXPECT_NO_THROW(List<int> list(std::move(ls)));
}

TEST(List, check_correct_move_constructor) {
	List<int> ls;
	ls.append(10);
	ls.append(20);

	List<int> list(std::move(ls));
	EXPECT_EQ(list.getHead()->data, 10);
	EXPECT_EQ(list.getHead()->next->data, 20);
	EXPECT_EQ(ls.getHead(), nullptr); // ls должен быть пустым
}

TEST(List, can_use_move_operator) {
	List<int> ls;
	ls.append(10);
	List<int> list;
	EXPECT_NO_THROW(ls = std::move(list));
}

TEST(List, check_correct_move_operator_meow) {
	List<int> ls;
	ls.append(10);
	ls.append(20);

	List<int> list;

	list = (std::move(ls));
	EXPECT_EQ(list.getHead()->data, 10);
	EXPECT_EQ(list.getHead()->next->data, 20);
	EXPECT_EQ(ls.getHead(), nullptr); // ls должен быть пустым
}

//операторы ввода и вывода
/* а как их тестить нормально то? для себя сделал, а вот показать...
TEST(List, can_use_operator_cin) {
	List<int> ls;
	ls.append(10);
	EXPECT_NO_THROW(std::cin >> ls);
}

TEST(List, check_cin) {
	List<int> ls;
	ls.append(10);
	ls.append(1000);
	ls.append(100000);
	std::cin >> ls;
	ls.printList();
	EXPECT_EQ(1, 1); //забыл как пишется затычка
}

TEST(List, can_use_operator_cout) {
	List<int> ls;
	ls.append(10);
	ls.append(100);
	EXPECT_NO_THROW(std::cout << ls);
}
*/