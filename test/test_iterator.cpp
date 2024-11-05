#include "List.h"
#include <iostream>
#include <gtest.h>

TEST(Iterator, can_make_iterator_is_not_empty) {
	List<int> ls;
	ls.append(50);
	EXPECT_NO_THROW(Iterator<int> it(ls.getHead()));
}

TEST(Iterator, can_make_iterator_is_empty) {
	List<int> ls;
	EXPECT_NO_THROW(Iterator<int> it(ls.getHead()));
}

TEST(Iterator, check_correct_iterator_in_head) {
	List<int> ls;
	ls.append(10);
	ls.append(50);
	ls.append(1);
	Iterator<int> it(ls.getHead());
	EXPECT_EQ(it, ls.getHead());
}

TEST(Iterator, check_correct_iterator_in_center) {
	List<int> ls;
	ls.append(10);
	ls.append(50);
	ls.append(1);
	Iterator<int> it(ls.getHead()->next);
	EXPECT_EQ(it, ls.getHead()->next);
}

TEST(Iterator, check_correct_iterator_in_tail) {
	List<int> ls;
	ls.append(10);
	ls.append(50);
	ls.append(1);
	Iterator<int> it(ls.getTail());
	EXPECT_EQ(it, ls.getTail());
}

TEST(Iterator, can_use_operator_get_data) {
	List<int> ls;
	ls.append(10);
	ls.append(50);
	ls.append(1);
	Iterator<int> it(ls.getHead());
	EXPECT_NO_THROW(*it);
}

TEST(Iterator,	check_correct_operator_get_data) {
	List<int> ls;
	ls.append(10);
	ls.append(50);
	ls.append(1);
	Iterator<int> it(ls.getHead());
	EXPECT_EQ(*it, 10);
}

TEST(Iterator, can_use_operator_next) {
	List<int> ls;
	ls.append(10);
	ls.append(50);
	ls.append(1);
	Iterator<int> it(ls.getHead());
	EXPECT_NO_THROW(++it);
}

TEST(Iterator, check_correct_operator_next) {
	List<int> ls;
	ls.append(10);
	ls.append(50);
	ls.append(1);
	Iterator<int> it(ls.getHead());
	EXPECT_EQ(++it, ls.getHead()->next);
}

TEST(Iterator, check_correct_operator_next_in_empty) {
	List<int> ls;
	Iterator<int> it(ls.getTail());
	EXPECT_NO_THROW(++it);
}

TEST(Iterator, check_correct_operator_compare_false) {
	List<int> ls;
	ls.append(4);
	ls.append(2);
	ls.append(1);
	Iterator<int> it(ls.getTail());
	Iterator<int> itl(ls.getHead());
	EXPECT_FALSE(it == itl);
}

TEST(Iterator, check_correct_operator_compare_true) {
	List<int> ls;
	ls.append(4);
	ls.append(2);
	Iterator<int> it(ls.getTail());
	Iterator<int> itl(ls.getHead());
	EXPECT_TRUE(it == ++itl);
}