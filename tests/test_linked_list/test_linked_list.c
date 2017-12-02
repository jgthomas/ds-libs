#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <BCUnit/Basic.h>
#include <BCUnit/BCUnit.h>
#include "tests/shared_test.h"
#include "tools/printing.h"
#include "tools/comparison.h"
#include "data_structures/linked_list.h"


enum {NUM_TESTS = 3};


int test_int[] = {15,13,46,10,1};
int answer_int[] = {1,10,46,13,15};

char test_char[] = {'e','a','r','t','b'};
char answer_char[] = {'b','t','r','a','e'};

char *test_string[] = {"zebra",
                       "moose",
                       "elephant",
                       "armadillo",
                       "coyote"};

char *answer_string[] = {"coyote",
                         "armadillo",
                         "elephant",
                         "moose",
                         "zebra"};


TestCase **make_tests(int num_tests)
{        
        TestCase **test_array = init_tests(num_tests);

        TestCase *testint = new_test(test_int, answer_int, sizeof(test_int), sizeof(int), equal_int, less_than_int, print_int);
        TestCase *testchar = new_test(test_char, answer_char, sizeof(test_char), sizeof(char), equal_char, less_than_char, print_char);
        TestCase *teststring = new_test(test_string, answer_string, sizeof(test_string), sizeof(char *), equal_string, less_than_string, print_string);

        test_array[0] = testint;
        test_array[1] = testchar;
        test_array[2] = teststring;

        return test_array;
}


void testLIST_CONTAINS(void)
{
        TestCase **tests = make_tests(NUM_TESTS);


        for (int i = 0; i < NUM_TESTS; i++)
        {
                Node *head = list_init();
                list_add_data(&head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, list_push);
                //list_print_values(head, tests[i]->print);
                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));

                if (i == 0)
                {
                        int n1 = 46;
                        int n2 = 100;
                        void *in_list_int = &n1;
                        void *not_in_list_int = &n2;
                        CU_ASSERT_TRUE(list_contains(head, in_list_int, tests[i]->equal));
                        CU_ASSERT_FALSE(list_contains(head, not_in_list_int, tests[i]->equal));
                }
                else if (i == 1)
                {
                        char c1 = 'r';
                        char c2 = 'n';
                        void *in_list_char = &c1;
                        void *not_in_list_char= &c2;
                        CU_ASSERT_TRUE(list_contains(head, in_list_char, tests[i]->equal));
                        CU_ASSERT_FALSE(list_contains(head, not_in_list_char, tests[i]->equal));
                }
                else if (i == 2)
                {
                        char *s1 = "coyote";
                        char *s2 = "blowfish";
                        void *in_list_string = &s1;
                        void *not_in_list_string = &s2;
                        CU_ASSERT_TRUE(list_contains(head, in_list_string, tests[i]->equal));
                        CU_ASSERT_FALSE(list_contains(head, not_in_list_string , tests[i]->equal));
                }

                list_delete(head);
        }

        clean_tests(tests, NUM_TESTS);
}


void testLIST_PUSH(void)
{
        TestCase **tests = make_tests(NUM_TESTS);

        for (int i = 0; i < NUM_TESTS; i++)
        {
                Node *head = list_init();
                list_add_data(&head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, list_push);
                //list_print_values(head, tests[i]->print);
                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));
                list_delete(head);
        }

        clean_tests(tests, NUM_TESTS);
}


void testLIST_APPEND(void)
{
        TestCase **tests = make_tests(NUM_TESTS);

        for (int i = 0; i < NUM_TESTS; i++)
        {
                Node *head = list_init();
                list_add_data(&head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, list_append);
                //list_print_values(head, tests[i]->print);
                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));
                list_delete(head);
        }

        clean_tests(tests, NUM_TESTS);
}


void testLIST_REVERSE(void)
{
        TestCase **tests = make_tests(NUM_TESTS);

        for (int i = 0; i < NUM_TESTS; i++)
        {
                Node *head = list_init();
                list_add_data(&head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, list_push);
                list_reverse(&head);
                //list_print_values(head, tests[i]->print);
                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));
                list_delete(head);
        }

        clean_tests(tests, NUM_TESTS);
}


void testLIST_DELETE_FIRST_ELEMENT(void)
{
        TestCase **tests = make_tests(NUM_TESTS);

        int new_answer_int[] = {10,46,13,15};
        char new_answer_char[] = {'t','r','a','e'};
        char *new_answer_string[] = {"armadillo",
                                     "elephant",
                                     "moose",
                                     "zebra"};

        for (int i = 0; i < NUM_TESTS; i++)
        {
                Node *head = list_init();
                list_add_data(&head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, list_push);

                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));

                list_delete_index(&head, 0);

                if (i == 0)
                {
                        tests[i]->answer = new_answer_int;
                        tests[i]->data_size = sizeof(new_answer_int);
                }
                else if (i == 1)
                {
                        tests[i]->answer = new_answer_char;
                        tests[i]->data_size = sizeof(new_answer_char);
                }
                else if (i == 2)
                {
                        tests[i]->answer = new_answer_string;
                        tests[i]->data_size = sizeof(new_answer_string);
                }

                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));
                list_delete(head);
        }

        clean_tests(tests, NUM_TESTS);
}


void testLIST_DELETE_MIDDLE_ELEMENT(void)
{
        TestCase **tests = make_tests(NUM_TESTS);

        int new_answer_int[] = {1,10,13,15};
        char new_answer_char[] = {'b','t','a','e'};
        char *new_answer_string[] = {"coyote",
                                     "armadillo",
                                     "moose",
                                     "zebra"};

        for (int i = 0; i < NUM_TESTS; i++)
        {
                Node *head = list_init();
                list_add_data(&head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, list_push);

                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));

                list_delete_index(&head, 2);

                if (i == 0)
                {
                        tests[i]->answer = new_answer_int;
                        tests[i]->data_size = sizeof(new_answer_int);
                }
                else if (i == 1)
                {
                        tests[i]->answer = new_answer_char;
                        tests[i]->data_size = sizeof(new_answer_char);
                }
                else if (i == 2)
                {
                        tests[i]->answer = new_answer_string;
                        tests[i]->data_size = sizeof(new_answer_string);
                }

                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));

                list_delete(head);
        }

        clean_tests(tests, NUM_TESTS);
}


void testLIST_DELETE_LAST_ELEMENT(void)
{
        TestCase **tests = make_tests(NUM_TESTS);

        int new_answer_int[] = {1,10,46,13};
        char new_answer_char[] = {'b','t','r','a'};
        char *new_answer_string[] = {"coyote",
                                     "armadillo",
                                     "elephant",
                                     "moose"};

        for (int i = 0; i < NUM_TESTS; i++)
        {
                Node *head = list_init();
                list_add_data(&head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, list_push);

                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));

                list_delete_index(&head, 4);

                if (i == 0)
                {
                        tests[i]->answer = new_answer_int;
                        tests[i]->data_size = sizeof(new_answer_int);
                }
                else if (i == 1)
                {
                        tests[i]->answer = new_answer_char;
                        tests[i]->data_size = sizeof(new_answer_char);
                }
                else if (i == 2)
                {
                        tests[i]->answer = new_answer_string;
                        tests[i]->data_size = sizeof(new_answer_string);
                }

                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));
                list_delete(head);
        }

        clean_tests(tests, NUM_TESTS);

}


void testLIST_DELETE_VALUE(void)
{
        TestCase **tests = make_tests(NUM_TESTS);

        int new_answer_int[] = {10,46,13,15};
        char new_answer_char[] = {'b','t','a','e'};
        char *new_answer_string[] = {"coyote",
                                     "armadillo",
                                     "elephant",
                                     "moose"};

        for (int i = 0; i < NUM_TESTS; i++)
        {
                Node *head = list_init();
                list_add_data(&head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, list_push);

                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));

                if (i == 0)
                {
                        int n = 1;
                        void *to_del_int = &n;
                        list_delete_value(&head, to_del_int, tests[i]->equal);
                        tests[i]->answer = new_answer_int;
                        tests[i]->data_size = sizeof(new_answer_int);
                }
                else if (i == 1)
                {
                        char c = 'r';
                        void *to_del_char = &c;
                        list_delete_value(&head, to_del_char, tests[i]->equal);
                        tests[i]->answer = new_answer_char;
                        tests[i]->data_size = sizeof(new_answer_char);
                }
                else if (i == 2)
                {
                        char *s = "zebra";
                        void *to_del_string = &s;
                        list_delete_value(&head, to_del_string, tests[i]->equal);
                        tests[i]->answer = new_answer_string;
                        tests[i]->data_size = sizeof(new_answer_string);
                }

                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));

                list_delete(head);
        }

        clean_tests(tests, NUM_TESTS);
}


void testLIST_FIND_AND_MOVE(void)
{
        TestCase **tests = make_tests(NUM_TESTS);

        int new_answer_int[] = {1,10,46,13,15};
        char new_answer_char[] = {'r','b','t','a','e'};
        char *new_answer_string[] = {"zebra",
                                     "coyote",
                                     "armadillo",
                                     "elephant",
                                     "moose"};

        for (int i = 0; i < NUM_TESTS; i++)
        {
                Node *head = list_init();
                list_add_data(&head, tests[i]->test, tests[i]->data_size, tests[i]->elem_size, list_push);
                CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));

                if (i == 0)
                {
                        int n1 = 1;
                        int n2 = 100;
                        void *in_list_int = &n1;
                        void *not_in_list_int = &n2;
                        tests[i]->answer = new_answer_int;
                        CU_ASSERT_FALSE(list_find_and_move(&head, not_in_list_int, tests[i]->equal));
                        CU_ASSERT_TRUE(list_find_and_move(&head, in_list_int, tests[i]->equal));
                        CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));

                }
                else if (i == 1)
                {
                        char c1 = 'r';
                        char c2 = 'n';
                        void *in_list_char = &c1;
                        void *not_in_list_char = &c2;
                        tests[i]->answer = new_answer_char;
                        CU_ASSERT_FALSE(list_find_and_move(&head, not_in_list_char, tests[i]->equal));
                        CU_ASSERT_TRUE(list_find_and_move(&head, in_list_char, tests[i]->equal));
                        CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));
                }
                else if (i == 2)
                {
                        char *s1 = "zebra";
                        char *s2 = "blowfish";
                        void *in_list_string = &s1;
                        void *not_in_list_string = &s2;
                        tests[i]->answer = new_answer_string;
                        CU_ASSERT_FALSE(list_find_and_move(&head, not_in_list_string, tests[i]->equal));
                        CU_ASSERT_TRUE(list_find_and_move(&head, in_list_string, tests[i]->equal));
                        CU_ASSERT_TRUE(ll_array_match(head, tests[i]->answer, tests[i]->data_size, tests[i]->elem_size, tests[i]->equal));
                }

                list_delete(head);
        }

        clean_tests(tests, NUM_TESTS);
}


int main(void)
{
        // test suite
        CU_pSuite suite = NULL;

        // initialize registry
        if (CUE_SUCCESS != CU_initialize_registry())
        {
                return CU_get_error();
        }

        // add suite
        suite = CU_add_suite("Binary heap", 0, 0);
        if (NULL == suite)
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

        // add tests
        if (NULL == CU_add_test(suite, "Pushing to list", testLIST_PUSH)||
            NULL == CU_add_test(suite, "Appending to list", testLIST_APPEND) ||
            NULL == CU_add_test(suite, "Reverse the list", testLIST_REVERSE) ||
            NULL == CU_add_test(suite, "Delete first element", testLIST_DELETE_FIRST_ELEMENT) ||
            NULL == CU_add_test(suite, "Delete mid-list element", testLIST_DELETE_MIDDLE_ELEMENT) ||
            NULL == CU_add_test(suite, "Delete last element", testLIST_DELETE_LAST_ELEMENT) ||
            NULL == CU_add_test(suite, "Delete value start, middle, end", testLIST_DELETE_VALUE) ||
            NULL == CU_add_test(suite, "Find elements in list", testLIST_CONTAINS) ||
            NULL == CU_add_test(suite, "Find element and move to front", testLIST_FIND_AND_MOVE))
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

        // run tests
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
        CU_cleanup_registry();
        return CU_get_error();
}