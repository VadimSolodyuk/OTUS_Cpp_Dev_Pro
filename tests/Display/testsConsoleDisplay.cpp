#include "../../include/libDisplay.hpp"

#include <gtest/gtest.h>
#include <memory>

struct testsConsoleDisplay : public testing::Test{
  std::shared_ptr<IDisplay> consoleDisplay{nullptr};

  std::shared_ptr<GraphicPrimitive> graphicPrimitive = GraphicPrimitive::create();
  
  void SetUp() override {
    consoleDisplay.reset(new ConsoleDisplay());
  }; 
};

TEST_F(testsConsoleDisplay, drawGraphicPrimitive) {
  consoleDisplay->drawGraphicPrimitive(graphicPrimitive);
}



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
