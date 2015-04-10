project( UNITTESTPLUSPLUS )
cmake_minimum_required( VERSION 2.8 )

#------ sources ------
set( UNITTEST_SRC
    AssertException.cpp
    AssertException.h
    Checks.cpp
    Checks.h
    DeferredTestReporter.cpp
    DeferredTestReporter.h
    DeferredTestResult.cpp
    DeferredTestResult.h
    MemoryOutStream.cpp
    MemoryOutStream.h
    ReportAssert.cpp
    ReportAssert.h
    Test.cpp
    TestDetails.cpp
    TestDetails.h
    TestList.cpp
    TestReporter.cpp
    TestReporter.h
    TestReporterStdout.cpp
    TestReporterStdout.h
    TestResults.cpp
    TestRunner.cpp
    TestRunner.h
    TestSuite.h
    TimeConstraint.h
    CheckMacros.h
    TimeConstraint.cpp
    Config.h
    Test.h
    TimeHelpers.h
    TestList.h
    UnitTest++.h
    TestMacros.h
    XmlTestReporter.cpp
    TestResults.h
    XmlTestReporter.h
    win32/TimeHelpers.cpp
    win32/TimeHelpers.h
    )

#------ additional includes ------
#include_directories( ${HGE_SOURCE_DIR}/include )

#------ link directories listed ------
#link_directories( ${HGE_SOURCE_DIR}/linklib )

#------ target -----
add_library( unittestpp STATIC ${UNITTEST_SRC} )
