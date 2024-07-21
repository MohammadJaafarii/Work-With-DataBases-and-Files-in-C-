#include "validation_test.h"

// Test valid IPv4 addresses
TEST_F(ValidationTest, ValidIP) {
    uint32_t ip = 0xC0A80101; // 192.168.1.1
    EXPECT_TRUE(validator.isValidIP(ip));
    ip = 0x00000000; // 0.0.0.0
    EXPECT_TRUE(validator.isValidIP(ip));
    ip = 0x7F000001; // 127.0.0.1 (localhost)
    EXPECT_TRUE(validator.isValidIP(ip));

}

// Test invalid IPv4 addresses
TEST_F(ValidationTest, InvalidIP) {
    uint32_t ip = 0xFFFFFFFF; // 255.255.255.255
    EXPECT_FALSE(validator.isValidIP(ip));
    ip = 0x0A000001; // 10.0.0.1 (private network)
    EXPECT_FALSE(validator.isValidIP(ip));

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
