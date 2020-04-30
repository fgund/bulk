#include <gtest/gtest.h>
#include "bulk.h"
#include "TestLogger.h"

void RunBulk(size_t bulk_size, std::vector<std::string> input, std::shared_ptr<IObserver> test_logger){
    Bulk bulk(bulk_size);
    bulk.AddObserver(test_logger);
    for(auto& cmd : input){
        bulk.Process(std::move(cmd));
    }
}
TEST(bulk, one_simple_bulk)
{
    std::vector<std::string> input{"cmd1","cmd2","cmd3"};
    std::shared_ptr<TestLogger> test_logger = std::make_shared<TestLogger>();
    auto bulk_size{3};
    RunBulk(bulk_size,input,test_logger);
    auto bulks = test_logger->GetBulks();
    ASSERT_EQ(bulks.size(), 1);
    ASSERT_EQ(bulks[0], "bulk: cmd1, cmd2, cmd3");

}
TEST(bulk, not_finished_bulk)
{
    std::vector<std::string> input{"cmd1","cmd2","cmd3","cmd4","cmd5"};
    std::shared_ptr<TestLogger> test_logger = std::make_shared<TestLogger>();
    auto bulk_size{3};
    RunBulk(bulk_size,input,test_logger);
    auto bulks = test_logger->GetBulks();
    ASSERT_EQ(bulks.size(), 2);
    ASSERT_EQ(bulks[0], "bulk: cmd1, cmd2, cmd3");
    ASSERT_EQ(bulks[1], "bulk: cmd4, cmd5");

}
TEST(bulk, nested_bulk)
{
    std::vector<std::string> input{"cmd1","cmd2","cmd3","{","cmd4","cmd5","cmd6","cmd7","}"};
    std::shared_ptr<TestLogger> test_logger = std::make_shared<TestLogger>();
    auto bulk_size{3};
    RunBulk(bulk_size,input,test_logger);
    auto bulks = test_logger->GetBulks();
    ASSERT_EQ(bulks.size(), 2);
    ASSERT_EQ(bulks[0], "bulk: cmd1, cmd2, cmd3");
    ASSERT_EQ(bulks[1], "bulk: cmd4, cmd5, cmd6, cmd7");

}
TEST(bulk, not_finished_nested_bulk)
{
    std::vector<std::string> input{"cmd1","cmd2","cmd3","{","cmd4","cmd5","cmd6","cmd7"};
    std::shared_ptr<TestLogger> test_logger = std::make_shared<TestLogger>();
    auto bulk_size{3};
    RunBulk(bulk_size,input,test_logger);
    auto bulks = test_logger->GetBulks();
    ASSERT_EQ(bulks.size(), 1);
    ASSERT_EQ(bulks[0], "bulk: cmd1, cmd2, cmd3");
}
TEST(bulk, nested_nested_bulk)
{
    std::vector<std::string> input{"{","cmd1","cmd2","{","cmd3","cmd4","}","cmd5","cmd6","}"};
    std::shared_ptr<TestLogger> test_logger = std::make_shared<TestLogger>();
    auto bulk_size{3};
    RunBulk(bulk_size,input,test_logger);
    auto bulks = test_logger->GetBulks();
    ASSERT_EQ(bulks.size(), 1);
    ASSERT_EQ(bulks[0], "bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}