/**
 * @file gtest_main.cpp
 * @author Brendan Bushbaker
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <wx/filefn.h>
#include <wx/image.h>

/**
 * Running all tests via Google tests.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    wxSetWorkingDirectory(L"..");
    wxInitAllImageHandlers();

    return RUN_ALL_TESTS();
}