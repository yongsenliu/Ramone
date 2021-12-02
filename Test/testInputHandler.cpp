#include "InputHandler.hpp"
#include <gtest/gtest.h>
#include <curses.h>
#include "NcKeyBindings.hpp"

class UserInputTest : public ::testing::Test
{
  protected:

  virtual void SetUp()
  {      
    MyUserInput.PrintSensorValues();
  }

  virtual void TearDown()
  {
    MyUserInput.PrintSensorValues();
  }

   UserInput MyUserInput;
};

// UserInput MyUserInput;

TEST_F(UserInputTest, GearTest)
{
  MyUserInput.Sensing(NC::D_KEY);
  EXPECT_EQ((int) MyUserInput.ValuesToCan().gearLeverPos, 1);
    MyUserInput.Sensing(NC::N_KEY);
  EXPECT_EQ((int) MyUserInput.ValuesToCan().gearLeverPos, 2);
    MyUserInput.Sensing(NC::R_KEY);
  EXPECT_EQ((int) MyUserInput.ValuesToCan().gearLeverPos, 3);
    MyUserInput.Sensing(NC::P_KEY);
  EXPECT_EQ((int) MyUserInput.ValuesToCan().gearLeverPos, 0);
      MyUserInput.Sensing(NC::D_KEY);
  EXPECT_EQ((int) MyUserInput.ValuesToCan().gearLeverPos, 1);
}