#include <gtest/gtest.h>
#include "../../include/Process/Context/ProcessContext.h"
#include "../../include/Process/Observer/ProcessObserver.h"

TEST(ProcessContext, CreationAndMetadata) 
{
    EXPECT_NO_THROW(ProcessContext());
    EXPECT_NO_THROW(std::make_shared<ProcessObserver>());
}

TEST(ProcessContext, FullTest) 
{
    auto pContext = ProcessContext();
    auto pObserver = std::make_shared<ProcessObserver>();
    EXPECT_NO_THROW(pContext.attach(pObserver));
    EXPECT_NO_THROW(pContext.markCurrProcesses());
    EXPECT_NO_THROW(pContext.notify());
    EXPECT_NO_THROW(pContext.detach(pObserver));
}