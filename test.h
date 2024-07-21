#ifndef TEST_H
#define TEST_H

#include "gtest/gtest.h"
#include "validation.h"

class Test : public ::testing::Test {

protected:
    Validation validator;
    Test(){};
    virtual void SetUp() {};

    virtual void TearDown() {};
};

#endif // TEST_H
