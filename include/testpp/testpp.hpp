#pragma once

#ifndef TESTS_H
#define TESTS_H

#include "internal/Assert.hpp"
#include "internal/Expect.hpp"

#define NOTRUN internal::Core::ExecutionStatus::NotRun
#define COMPLETED internal::Core::ExecutionStatus::Completed
#define CRASHED internal::Core::ExecutionStatus::Crashed
#define TIMEDOUT internal::Core::ExecutionStatus::TimedOut
#define LAUNCHFAIL internal::Core::ExecutionStatus::LaunchFailed
#define COMFAIL internal::Core::ExecutionStatus::CommunicationFailure
#define FRAMEWORKERR internal::Core::ExecutionStatus::InternalFrameworkError
#define SANFAIL internal::Core::ExecutionStatus::SanitizerFailure

#define NOCRASH internal::Core::CrashType::None
#define SEGFAULT internal::Core::CrashType::SegmentationFault
#define ACCESSVIOLATION internal::Core::CrashType::AccessViolation
#define ABORT internal::Core::CrashType::Abort
#define ZERODIV internal::Core::CrashType::DivideByZero
#define ILLINSTR internal::Core::CrashType::IllegalInstruction
#define BUSERR internal::Core::CrashType::BusError
#define FLOATPOINT internal::Core::CrashType::FloatingPointException
#define TRAP internal::Core::CrashType::Trap
#define KILLED internal::Core::CrashType::Killed
#define UNKNOWN internal::Core::CrashType::Unknown

#endif