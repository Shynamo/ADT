#include "common_tests_utils.h"
#include "../set/set.h"
#include "../common/utils.h"

/*
This test is based on Bordeaux INP's Moodle -> pg 116 -> bigtests.tar.gz
It has been modified to fit with our tests conventions.
*/

////////////////////////////////////////////////////////////////////
///     OPERATORS FUNCTIONS IMPLEMENTATION
////////////////////////////////////////////////////////////////////

void *int__copy(const int *i)
{
    int *copy = safe_malloc(sizeof(*copy));
    *copy = *i;
    return copy;
}

void int__free(int *i)
{
    free(i);
}

int int__cmp(const int *i1, const int *i2)
{
    if (*i1 > *i2)
        return 1;
    if (*i1 < *i2)
        return -1;
    return 0;
}

void int__debug(const int *i)
{
    fflush(stdout);
    printf("%d ", *i);
}

////////////////////////////////////////////////////////////////////
///     SET FUNCTIONS TESTS
////////////////////////////////////////////////////////////////////

int test_set__empty_copy_enabled(void)
{
    printf("%s... ", __func__);

    struct set * st = set__empty_copy_enabled(int__copy, int__free, int__cmp, int__debug);
    int test_result = TEST_SUCCESS;

    if ((st == NULL) || (!set__is_empty(st)))
        test_result = !TEST_SUCCESS;

    set__free(st);
    return test_result;
}

int test_set__is_empty(void)
{
    printf("%s... ", __func__);

    struct set * st = set__empty_copy_enabled(int__copy, int__free, int__cmp, int__debug);
    int test_result = TEST_SUCCESS;

    if ((st == NULL) || (!set__is_empty(st)))
        test_result = !TEST_SUCCESS;

    int v1 = 1;
    if (set__add(st, &v1)) test_result = !TEST_SUCCESS;
    if (set__is_empty(st)) test_result = !TEST_SUCCESS;

    set__free(st);
    return test_result;
}

int test_set__length(void)
{
    printf("%s... ", __func__);

    struct set * st = set__empty_copy_enabled(int__copy, int__free, int__cmp, int__debug);
    int test_result = TEST_SUCCESS;

    if ((st == NULL) || (set__length(st) != 0))
        return !TEST_SUCCESS;

    int v1 = 1, v2 = 5, v3 = 8;
    if (set__add(st, &v1)) test_result = !TEST_SUCCESS;
    if (set__add(st, &v2)) test_result = !TEST_SUCCESS;
    if (set__add(st, &v3)) test_result = !TEST_SUCCESS;
    if (set__length(st) != 3) test_result = !TEST_SUCCESS;

    set__free(st);

    return test_result;
}

int test_set__add(void)
{
    printf("%s... ", __func__);

    struct set * st = set__empty_copy_enabled(int__copy, int__free, int__cmp, int__debug);
    int test_result = TEST_SUCCESS;

    if (st == NULL) test_result = !TEST_SUCCESS;

    int v1 = 3;
    if (set__add(st, &v1)) test_result = !TEST_SUCCESS;
    if (set__length(st) != 1) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v1)) test_result = !TEST_SUCCESS;

    if (!set__add(st, &v1)) test_result = !TEST_SUCCESS;
    if (set__length(st) != 1) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v1)) test_result = !TEST_SUCCESS;

    int v2 = 3;
    if (!set__add(st, &v2)) test_result = !TEST_SUCCESS;
    if (set__length(st) != 1) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v2)) test_result = !TEST_SUCCESS;

    int v3 = 9;
    if (set__add(st, &v3)) test_result = !TEST_SUCCESS;
    if (set__length(st) != 2) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v1)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v3)) test_result = !TEST_SUCCESS;

    int v4 = 5;
    if (set__add(st, &v4)) test_result = !TEST_SUCCESS;
    if (set__length(st) != 3) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v1)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v3)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v4)) test_result = !TEST_SUCCESS;

    int v5 = 1;
    if (set__add(st, &v5)) test_result = !TEST_SUCCESS;
    if (set__length(st) != 4) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v1)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v3)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v4)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v5)) test_result = !TEST_SUCCESS;

    set__free(st);

    return test_result;
}



int test_set__remove(void)
{
    printf("%s... ", __func__);

    struct set * st = set__empty_copy_enabled(int__copy, int__free, int__cmp, int__debug);
    int test_result = TEST_SUCCESS;

    if (st == NULL) test_result = !TEST_SUCCESS;

    int v1 = 1, v2 = 2;
    if (set__add(st, &v1)) test_result = !TEST_SUCCESS;
    if (set__add(st, &v2)) test_result = !TEST_SUCCESS;

    if (set__remove(st, &v1)) test_result = !TEST_SUCCESS;
    if (set__length(st) != 1) test_result = !TEST_SUCCESS;
    if (set__is_in(st, &v1)) test_result = !TEST_SUCCESS;

    if (set__remove(st, &v2)) test_result = !TEST_SUCCESS;
    if (set__is_in(st, &v2)) test_result = !TEST_SUCCESS;
    if (!set__is_empty(st)) test_result = !TEST_SUCCESS;

    int v3 = 1, v4 = 6, v5 = 4;
    if (set__add(st, &v3)) test_result = !TEST_SUCCESS;
    if (set__add(st, &v4)) test_result = !TEST_SUCCESS;
    if (!set__remove(st, &v5)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v3)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v4)) test_result = !TEST_SUCCESS;
    if (set__length(st) != 2) test_result = !TEST_SUCCESS;

    set__free(st);

    return test_result;
}

int test_set__is_in(void)
{
    printf("%s... ", __func__);

    struct set * st = set__empty_copy_enabled(int__copy, int__free, int__cmp, int__debug);
    int test_result = TEST_SUCCESS;

    if (st == NULL) test_result = !TEST_SUCCESS;

    int v1 = 1;
    if (set__is_in(st, &v1)) test_result = !TEST_SUCCESS;

    int v2 = 2;
    if (set__add(st, &v2)) test_result = !TEST_SUCCESS;
    if (set__is_in(st, &v1)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v2)) test_result = !TEST_SUCCESS;

    if (set__add(st, &v1)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v1)) test_result = !TEST_SUCCESS;

    int v3 = 7;
    if (set__add(st, &v3)) test_result = !TEST_SUCCESS;
    if (!set__is_in(st, &v3)) test_result = !TEST_SUCCESS;

    set__free(st);

    return test_result;
}

int test_set__big_set(void)
{
    printf("%s... ", __func__);

    const unsigned int set_size = 00;
    int * t = safe_malloc(set_size * sizeof(*t));
    for (unsigned int i = 0; i < set_size; ++i)
        t[i] = (int) i;

    struct set * st = set__empty_copy_enabled(int__copy, int__free, int__cmp, int__debug);
    int test_result = TEST_SUCCESS;

    if (st == NULL){
        set__free(st);
        free(t);
        return !TEST_SUCCESS;
    }

    for (unsigned int j = 0; j < 3; ++j)
        for (unsigned int i = 0; i < set_size; ++i)
            if (i%3 == j)
                if (set__add(st, t+i)){
                    set__free(st);
                    free(t);
                    return !TEST_SUCCESS;
                }

    if (set__length(st) != set_size){
        set__free(st);
        free(t);
        return !TEST_SUCCESS;
    }

    for (unsigned int j = 0; j < 3; ++j)
        for (unsigned int i = 0; i < set_size; ++i)
            if (i%3 == j)
                if (set__remove(st, t+i)){
                    set__free(st);
                    free(t);
                    return !TEST_SUCCESS;
                }

    if (!set__is_empty(st)){
        set__free(st);
        free(t);
        return !TEST_SUCCESS;
    }


    set__free(st);
    free(t);

    return test_result;
}

int test_set__retrieve()
{
    printf("%s... ", __func__);

    int v0 = 0, v1 = 1, v2 = 2, v3 = 3, v5 = 5, v6 = 6, v7 = 7;

    struct set *set = set__empty_copy_enabled(int__copy, int__free, int__cmp, int__debug);
    int test_result = TEST_SUCCESS;

    if (set__add(set, &v0)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v1)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v2)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v3)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v5)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v6)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v7)) test_result = !TEST_SUCCESS;

    int nope_you_re_not_in_the_set = 101;

    if (set__retrieve(set, &nope_you_re_not_in_the_set) != NULL)
        test_result = !TEST_SUCCESS;

    int *retrieved = set__retrieve(set, &v3);
    *retrieved = 4;
    int v4 = 4;

    if (set__is_in(set, &v3)) test_result = !TEST_SUCCESS;
    if (!set__is_in(set, &v4)) test_result = !TEST_SUCCESS;

    set__free(set);
    return test_result;
}

int test_set__get_umpteenth(void)
{
    printf("%s... ", __func__);

    int v0 = 0, v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6;

    struct set *set = set__empty_copy_enabled(int__copy, int__free, int__cmp, int__debug);
    int test_result = TEST_SUCCESS;

    if (set__add(set, &v0)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v1)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v2)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v3)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v4)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v5)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v6)) test_result = !TEST_SUCCESS;

    int * _v0 = set__get_umpteenth(set, 0);
    int * _v1 = set__get_umpteenth(set, 1);
    int * _v2 = set__get_umpteenth(set, 2);
    int * _v3 = set__get_umpteenth(set, 3);
    int * _v4 = set__get_umpteenth(set, 4);
    int * _v5 = set__get_umpteenth(set, 5);
    int * _v6 = set__get_umpteenth(set, 6);

    if (*_v0 != v0) test_result = !TEST_SUCCESS;
    if (*_v1 != v1) test_result = !TEST_SUCCESS;
    if (*_v2 != v2) test_result = !TEST_SUCCESS;
    if (*_v3 != v3) test_result = !TEST_SUCCESS;
    if (*_v4 != v4) test_result = !TEST_SUCCESS;
    if (*_v5 != v5) test_result = !TEST_SUCCESS;
    if (*_v6 != v6) test_result = !TEST_SUCCESS;

    *_v0 = 69;
    int v69 = 69;
    if (set__is_in(set, &v69)) test_result = !TEST_SUCCESS;

    int__free(_v0);
    int__free(_v1);
    int__free(_v2);
    int__free(_v3);
    int__free(_v4);
    int__free(_v5);
    int__free(_v6);
    set__free(set);
    return test_result;
}

int test_set__debug_data(void)
{
    printf("%s... ", __func__);

    struct set *set = set__empty_copy_enabled(int__copy, int__free, int__cmp, int__debug);
    int test_result = TEST_SUCCESS;

    int v0 = 0,  v3 = 3, v4 = 4, v7 = 7;

    if (set__add(set, &v0)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v3)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v4)) test_result = !TEST_SUCCESS;
    if (set__add(set, &v7)) test_result = !TEST_SUCCESS;

    printf("(expected: 0 3 4 7), Got: ");
    set__debug(set, true);

    set__free(set);

    return test_result;
}


int test_set__map()
{
    printf("%s ", __func__);

    struct set *s = set__empty_copy_enabled(&operator_copy, &operator_delete, &operator_compare, &operator_debug);
    int value1 = 15;
    int value2 = 16;
    int value3 = 69;
    int value4 = 14;

    set__add(s, &value1);
    set__add(s, &value2);
    set__add(s, &value3);
    set__add(s, &value4);

    set__map(s, (applying_func_t) plus_op);

    printf("Expected: (16 17 70 15)... Got: ");
    set__debug(s, true);

    set__free(s);

    return TEST_SUCCESS;
}



int main()
{
    printf("----------- TEST SET -----------\n");

    int nb_success = 0;
    int nb_tests = 0;

    print_test_result(test_set__empty_copy_enabled(), &nb_success, &nb_tests);
    print_test_result(test_set__is_empty(), &nb_success, &nb_tests);
    print_test_result(test_set__length(), &nb_success, &nb_tests);
    print_test_result(test_set__add(), &nb_success, &nb_tests);
    print_test_result(test_set__remove(), &nb_success, &nb_tests);
    print_test_result(test_set__is_in(), &nb_success, &nb_tests);
    print_test_result(test_set__big_set(), &nb_success, &nb_tests);
    print_test_result(test_set__retrieve(), &nb_success, &nb_tests);
    print_test_result(test_set__get_umpteenth(), &nb_success, &nb_tests);
    print_test_result(test_set__debug_data(), &nb_success, &nb_tests);
    print_test_result(test_set__map(), &nb_success, &nb_tests);

    print_test_summary(nb_success, nb_tests);

    return TEST_SUCCESS;
}
