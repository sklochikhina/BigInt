#include "BigInt.h"
#include "gtest/gtest.h"

// constructors
TEST(BigIntConstructorsTest, TestDefaultConstructor) {
BigInt object;
EXPECT_EQ(object.checkSize(), 0);
EXPECT_EQ(object.checkIsPositive(), true);
}

TEST(BigIntConstructorsTest, TestPositiveIntConstructor) {
BigInt object(12345);
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 12345);
EXPECT_EQ(object.checkIsPositive(), true);
}

TEST(BigIntConstructorsTest, TestNegativeIntConstructor) {
BigInt object(-12345);
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 12345);
EXPECT_EQ(object.checkIsPositive(), false);
}

TEST(BigIntConstructorsTest, TestIntConstructorBigNum) {
BigInt object(-1123456789123456789);
EXPECT_EQ(object.checkSize(), 3);
EXPECT_EQ(object.checkBigInt(2), 1);
EXPECT_EQ(object.checkBigInt(1), 123456789);
EXPECT_EQ(object.checkBigInt(0), 123456789);
EXPECT_EQ(object.checkIsPositive(), false);
}

TEST(BigIntConstructorsTest, TestPositiveStrConstructor) {
BigInt object("12345123456789");
EXPECT_EQ(object.checkSize(), 2);
EXPECT_EQ(object.checkBigInt(1), 12345);
EXPECT_EQ(object.checkBigInt(0), 123456789);
EXPECT_EQ(object.checkIsPositive(), true);
}

TEST(BigIntConstructorsTest, TestNegativeStrConstructor) {
BigInt object("-12345123456789");
EXPECT_EQ(object.checkSize(), 2);
EXPECT_EQ(object.checkBigInt(1), 12345);
EXPECT_EQ(object.checkBigInt(0), 123456789);
EXPECT_EQ(object.checkIsPositive(), false);
}

TEST(BigIntConstructorsTest, TestStrConstructorExcept) {
EXPECT_ANY_THROW(BigInt object("-12345-12345"));
EXPECT_ANY_THROW(BigInt object("-12345a12345"));
EXPECT_ANY_THROW(BigInt object("a"));
EXPECT_ANY_THROW(BigInt object(""));
}

TEST(BigIntConstructorsTest, TestPositiveBigIntConstructor) {
BigInt object1("12345123456789");
BigInt object2 = object1;
EXPECT_EQ(object2.checkSize(), 2);
EXPECT_EQ(object2.checkBigInt(1), 12345);
EXPECT_EQ(object2.checkBigInt(0), 123456789);
EXPECT_EQ(object2.checkIsPositive(), true);
}

TEST(BigIntConstructorsTest, TestNegativeBigIntConstructor) {
BigInt object1("-1123456789123456789");
BigInt object2 = object1;
EXPECT_EQ(object2.checkSize(), 3);
EXPECT_EQ(object2.checkBigInt(2), 1);
EXPECT_EQ(object2.checkBigInt(1), 123456789);
EXPECT_EQ(object2.checkBigInt(0), 123456789);
EXPECT_EQ(object2.checkIsPositive(), false);
}

TEST(BigIntConstructorsTest, TestBigIntMoveConstructor) {
BigInt object1("4444444444");
BigInt object2 = object1 + object1;
EXPECT_EQ(object2.checkSize(), 2);
EXPECT_EQ(object2.checkBigInt(1), 8);
EXPECT_EQ(object2.checkBigInt(0), 888888888);
EXPECT_EQ(object2.checkIsPositive(), true);
}

// assignment
TEST(AssignmentOperatorsTest, TestPositiveNumAssignment) {
BigInt object1(12345123456789);
BigInt object2(0);
object2 = object1;
EXPECT_EQ(object2.checkSize(), 2);
EXPECT_EQ(object2.checkBigInt(1), 12345);
EXPECT_EQ(object2.checkBigInt(0), 123456789);
EXPECT_EQ(object2.checkIsPositive(), true);
}

TEST(AssignmentOperatorsTest, TestNegativeNumAssignment) {
BigInt object1("-12345123456789");
BigInt object2 = 0;
object2 = object1;
EXPECT_EQ(object2.checkSize(), 2);
EXPECT_EQ(object2.checkBigInt(1), 12345);
EXPECT_EQ(object2.checkBigInt(0), 123456789);
EXPECT_EQ(object2.checkIsPositive(), false);
}

TEST(AssignmentOperatorTest, TestMoveAssignment) {
BigInt object1("4444444444");
BigInt object2 = 0;
object2 = object1 + object1;
EXPECT_EQ(object2.checkSize(), 2);
EXPECT_EQ(object2.checkBigInt(1), 8);
EXPECT_EQ(object2.checkBigInt(0), 888888888);
EXPECT_EQ(object2.checkIsPositive(), true);
}

// increment
TEST(RightIncrementTest, TestSimplePositiveNumIncrement) {
BigInt object("1234567");
object++;
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 1234568);
EXPECT_EQ(object.checkIsPositive(), true);
}

TEST(RightIncrementTest, TestSimpleNegativeNumIncrement) {
BigInt object("-1234567");
object++;
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 1234566);
EXPECT_EQ(object.checkIsPositive(), false);
}

TEST(RightIncrementTest, TestBigPositiveNumIncrement) {
BigInt object("999999999");
object++;
EXPECT_EQ(object.checkSize(), 2);
EXPECT_EQ(object.checkBigInt(1), 1);
EXPECT_EQ(object.checkBigInt(0), 0);
EXPECT_EQ(object.checkIsPositive(), true);
}

TEST(RightIncrementTest, TestBigNegativeNumIncrement) {
BigInt object("-1000000000");
object++;
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 999999999);
EXPECT_EQ(object.checkIsPositive(), false);
}

TEST(LeftIncrementTest, TestSimplePositiveNumIncrement) {
BigInt object("1234567");
++object;
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 1234568);
EXPECT_EQ(object.checkIsPositive(), true);
}

TEST(LeftIncrementTest, TestSimpleNegativeNumIncrement) {
BigInt object("-1234567");
object++;
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 1234566);
EXPECT_EQ(object.checkIsPositive(), false);
}

TEST(LeftIncrementTest, TestBigPositiveNumIncrement) {
BigInt object("999999999");
object++;
EXPECT_EQ(object.checkSize(), 2);
EXPECT_EQ(object.checkBigInt(1), 1);
EXPECT_EQ(object.checkBigInt(0), 0);
EXPECT_EQ(object.checkIsPositive(), true);
}

TEST(LeftIncrementTest, TestBigNegativeNumIncrement) {
BigInt object("-1000000000");
object++;
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 999999999);
EXPECT_EQ(object.checkIsPositive(), false);
}

// decrement
TEST(RightDecrementTest, TestSimplePositiveNumDecrement) {
BigInt object("1234567");
object--;
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 1234566);
EXPECT_EQ(object.checkIsPositive(), true);
}

TEST(RightDecrementTest, TestSimpleNegativeNumDecrement) {
BigInt object("-1234567");
object--;
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 1234568);
EXPECT_EQ(object.checkIsPositive(), false);
}

TEST(RightDecrementTest, TestBigPositiveNumDecrement) {
BigInt object("1000000000");
object--;
EXPECT_EQ(object.checkSize(), 1);
EXPECT_EQ(object.checkBigInt(0), 999999999);
EXPECT_EQ(object.checkIsPositive(), true);
}

TEST(RightDecrementTest, TestBigNegativeNumDecrement) {
BigInt object("-999999999");
object--;
EXPECT_EQ(object.checkSize(), 2);
EXPECT_EQ(object.checkBigInt(1), 1);
EXPECT_EQ(object.checkBigInt(0), 0);
EXPECT_EQ(object.checkIsPositive(), false);
}

// operator +=
TEST(NumbersSumOperatorTest, TestOneOfBigPositiveNum) {
BigInt object1("999999999999999999");
BigInt object2("999999999");
object1 += object2;
EXPECT_EQ(object1.checkSize(), 3);
EXPECT_EQ(object1.checkBigInt(2), 1);
EXPECT_EQ(object1.checkBigInt(1), 0);
EXPECT_EQ(object1.checkBigInt(0), 999999998);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersSumOperatorTest, TestTwoOfBigPositiveNum) {
BigInt object1("999999999999999999");
BigInt object2("-999999999");
object1 += object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 999999999);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersSumOperatorTest, TestThreeOfBigPositiveNum) {
BigInt object1("999999999999999999");
BigInt object2("-999999999999999999");
object1 += object2;
EXPECT_EQ(object1.checkSize(), 1);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersSumOperatorTest, TestFourOfBigPositiveNum1) {
BigInt object1("9999999999");
BigInt object2("-99999999999");
object1 += object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 90);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), false);
}

TEST(NumbersSumOperatorTest, TestOneOfBigNegativeNum) {
BigInt object1("-999999999999999999");
BigInt object2("999999999");
object1 += object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 999999999);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), false);
}

TEST(NumbersSumOperatorTest, TestTwoOfBigNegativeNum) {
BigInt object1("-999999999999999999");
BigInt object2("-999999999");
object1 += object2;
EXPECT_EQ(object1.checkSize(), 3);
EXPECT_EQ(object1.checkBigInt(2), 1);
EXPECT_EQ(object1.checkBigInt(1), 0);
EXPECT_EQ(object1.checkBigInt(0), 999999998);
EXPECT_EQ(object1.checkIsPositive(), false);
}

TEST(NumbersSumOperatorTest, TestThreeOfBigNegativeNum) {
BigInt object1("-999999999999999999");
BigInt object2("999999999999999999");
object1 += object2;
EXPECT_EQ(object1.checkSize(), 1);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersSumOperatorTest, TestFourOfBigNegativeNum) {
BigInt object1("-9999999999");
BigInt object2("99999999999");
object1 += object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 90);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), true);
}

// operator -=
TEST(NumbersDifferenceOperatorTest, TestOneOfBigPositiveNum) {
BigInt object1("999999999999999999");
BigInt object2("999999999");
object1 -= object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 999999999);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersDifferenceOperatorTest, TestTwoOfBigPositiveNum) {
BigInt object1("999999999999999999");
BigInt object2("-999999999");
object1 -= object2;
EXPECT_EQ(object1.checkSize(), 3);
EXPECT_EQ(object1.checkBigInt(2), 1);
EXPECT_EQ(object1.checkBigInt(1), 0);
EXPECT_EQ(object1.checkBigInt(0), 999999998);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersDifferenceOperatorTest, TestThreeOfBigPositiveNum) {
BigInt object1("999999999999999999");
BigInt object2("999999999999999999");
object1 -= object2;
EXPECT_EQ(object1.checkSize(), 1);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersDifferenceOperatorTest, TestFourOfBigPositiveNum) {
BigInt object1("9999999999");
BigInt object2("99999999999");
object1 -= object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 90);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), false);
}

TEST(NumbersDifferenceOperatorTest, TestOneOfBigNegativeNum) {
BigInt object1("-999999999999999999");
BigInt object2("999999999");
object1 -= object2;
EXPECT_EQ(object1.checkSize(), 3);
EXPECT_EQ(object1.checkBigInt(2), 1);
EXPECT_EQ(object1.checkBigInt(1), 0);
EXPECT_EQ(object1.checkBigInt(0), 999999998);
EXPECT_EQ(object1.checkIsPositive(), false);
}

TEST(NumbersDifferenceOperatorTest, TestTwoOfBigNegativeNum) {
BigInt object1("-999999999999999999");
BigInt object2("-999999999");
object1 -= object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 999999999);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), false);
}

TEST(NumbersDifferenceOperatorTest, TestThreeOfBigNegativeNum) {
BigInt object1("-999999999999999999");
BigInt object2("-999999999999999999");
object1 -= object2;
EXPECT_EQ(object1.checkSize(), 1);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersDifferenceOperatorTest, TestFourOfBigNegativeNum) {
BigInt object1("-9999999999");
BigInt object2("-99999999999");
object1 -= object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 90);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersDifferenceOperatorTest, SpecialTest) {
    EXPECT_EQ((std::string)(BigInt {"10000000000000000000000000"} - BigInt {1}), "9999999999999999999999999");
}

// operator *=
TEST(NumbersMultiplicationOperatorTest, TestOneOfBigPositiveNum) {
BigInt object1("999999999");
BigInt object2("2");
object1 *= object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 1);
EXPECT_EQ(object1.checkBigInt(0), 999999998);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersMultiplicationOperatorTest, TestTwoOfBigPositiveNum) {
BigInt object1("9999999999");
BigInt object2("-2");
object1 *= object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 19);
EXPECT_EQ(object1.checkBigInt(0), 999999998);
EXPECT_EQ(object1.checkIsPositive(), false);
}

TEST(NumbersMultiplicationOperatorTest, TestThreeOfBigPositiveNum) {
BigInt object1("999999999999999999");
BigInt object2("0");
object1 *= object2;
EXPECT_EQ(object1.checkSize(), 1);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersMultiplicationOperatorTest, TestOneOfBigNegativeNum) {
BigInt object1("-999999999");
BigInt object2("2");
object1 *= object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 1);
EXPECT_EQ(object1.checkBigInt(0), 999999998);
EXPECT_EQ(object1.checkIsPositive(), false);
}

TEST(NumbersMultiplicationOperatorTest, TestTwoOfBigNegativeNum) {
BigInt object1("-9999999999");
BigInt object2("-2");
object1 *= object2;
EXPECT_EQ(object1.checkSize(), 2);
EXPECT_EQ(object1.checkBigInt(1), 19);
EXPECT_EQ(object1.checkBigInt(0), 999999998);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersMultiplicationOperatorTest, TestThreeOfBigNegativeNum) {
BigInt object1("-999999999999999999");
BigInt object2("0");
object1 *= object2;
EXPECT_EQ(object1.checkSize(), 1);
EXPECT_EQ(object1.checkBigInt(0), 0);
EXPECT_EQ(object1.checkIsPositive(), true);
}

TEST(NumbersMultiplicationOperatorTest, ZeroArgumentTest) {
    EXPECT_TRUE(BigInt(0) * BigInt(-1) == BigInt(0));
}

// comparison
TEST(ComparisonOperatorsTest, EqualityOperatorTest) {
BigInt object1("999999999999999999");
BigInt object2("999999999999999999");
BigInt object3("-999999999999999999");
BigInt object4("999999999999999998");
EXPECT_EQ(object1 == object2, true);
EXPECT_EQ(object1 == object3, false);
EXPECT_EQ(object1 == object4, false);
}

TEST(ComparisonOperatorsTest, InequalityOperatorTest) {
BigInt object1("999999999999999999");
BigInt object2("999999999999999999");
BigInt object3("-999999999999999999");
BigInt object4("999999999999999998");
EXPECT_EQ(object1 != object2, false);
EXPECT_EQ(object1 != object3, true);
EXPECT_EQ(object1 != object4, true);
}

TEST(ComparisonOperatorsTest, LessOperatorTest) {
BigInt object1("999999999999999999");
BigInt object2("999999999999999999");
BigInt object3("-999999999999999999");
BigInt object4("999999999999999998");
EXPECT_EQ(object1 < object2, false);
EXPECT_EQ(object1 < object3, false);
EXPECT_EQ(object1 < object4, false);
}

TEST(ComparisonOperatorsTest, MoreOperatorTest) {
BigInt object1("999999999999999999");
BigInt object2("999999999999999999");
BigInt object3("-999999999999999999");
BigInt object4("999999999999999998");
EXPECT_EQ(object1 > object2, false);
EXPECT_EQ(object1 > object3, true);
EXPECT_EQ(object1 > object4, true);
}

TEST(ComparisonOperatorsTest, LessThanOrEqualOperatorTest) {
BigInt object1("999999999999999999");
BigInt object2("999999999999999999");
BigInt object3("-999999999999999999");
BigInt object4("999999999999999998");
EXPECT_EQ(object1 <= object2, true);
EXPECT_EQ(object1 <= object3, false);
EXPECT_EQ(object1 <= object4, false);
}

TEST(ComparisonOperatorsTest, MoreThanOrEqualOperatorTest) {
BigInt object1("999999999999999999");
BigInt object2("999999999999999999");
BigInt object3("-999999999999999999");
BigInt object4("999999999999999998");
EXPECT_EQ(object1 >= object2, true);
EXPECT_EQ(object1 >= object3, true);
EXPECT_EQ(object1 >= object4, true);
}

// converting
TEST(ConvertingBigIntToIntOperatorTest, BigIntConvertingTest) {
BigInt object("999999999999999999");
EXPECT_EQ((int)object, (int)999999999);
}

TEST(ConvertingBigIntToIntOperatorTest, ZeroConvertingTest) {
BigInt object("0");
EXPECT_EQ((int)object, 0);
}

TEST(ConvertingBigIntToStringOperatorTest, PositiveBigIntConvertingTest) {
BigInt object("999999999999999999");
EXPECT_EQ((std::string)object, "999999999999999999");
}

TEST(ConvertingBigIntToStringOperatorTest, ZeroConvertingTest) {
BigInt object("0");
EXPECT_EQ((std::string)object, "0");
}

TEST(ConvertingBigIntToStringOperatorTest, NegativeBigIntConvertingTest) {
BigInt object("-999999999999999999");
EXPECT_EQ((std::string)object, "-999999999999999999");
}
