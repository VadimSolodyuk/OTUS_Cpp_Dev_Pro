#include "../../include/libGraphicElement.hpp"
#include "../../include/libDisplay.hpp"

#include <gtest/gtest.h>
#include <memory>


struct testsGraphicPrimitive : public testing::Test{
  std::shared_ptr<GraphicPrimitive> graphicPrimitive = GraphicPrimitive::create();
  std::shared_ptr<IDisplay> display = std::make_shared<ConsoleDisplay>();
  
  std::string name{"gp-1"};
  std::string name_1{"gp"};
};

TEST_F(testsGraphicPrimitive, constructDefaultAndGetName){
  ASSERT_TRUE(graphicPrimitive->getName() == name);
}

TEST_F(testsGraphicPrimitive, constructWithName){
  graphicPrimitive = GraphicPrimitive::create(name_1.data());
  ASSERT_TRUE(graphicPrimitive->getName() == name_1);
}

TEST_F(testsGraphicPrimitive, setName){
  graphicPrimitive->setName(name_1.data());
  ASSERT_TRUE(graphicPrimitive->getName() == name_1);
}

TEST_F(testsGraphicPrimitive, draw){
    graphicPrimitive->draw(display);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
