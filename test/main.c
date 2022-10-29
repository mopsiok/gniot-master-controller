/**
 * @file main.c
 * @brief Main unit tests file
 * 
 * @author mopsiok
 */

// Includes ========================================
#include <unity.h>

// Private macros and defines ======================

// Private typedefs ================================

// Static variables ================================

// Global and extern variables =====================

// Static function prototypes ======================

// Static functions ================================

// Global functions ================================

void setUp(void) { }

void tearDown(void) { }

void simple_test1(void)
{
    TEST_ASSERT_EQUAL_INT(10, 10);
}

void simple_test2(void)
{
    TEST_ASSERT_EQUAL_INT(10, 11);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(simple_test1);
    RUN_TEST(simple_test2);

    return UNITY_END();
}
