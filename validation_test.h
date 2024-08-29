// validation_test.h
#ifndef VALIDATION_TEST_H
#define VALIDATION_TEST_H

#include <gtest/gtest.h>
#include "validation.h"

class ValidationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // کد پیکربندی اولیه برای تست‌ها، مانند مقداردهی اولیه validator
    }

    void TearDown() override {
        // کد پاکسازی بعد از تست‌ها
    }

    Validation validator; // شیء validator برای تست‌ها
};

#endif // VALIDATION_TEST_H
