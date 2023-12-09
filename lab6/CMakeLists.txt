add_executable(lab6.elf main.c bhTester.c fsTester.c vsTester.c globals.c buttonHandler.c simonDisplay.c flashSequence.c verifySequence.c simonControl.c)
target_link_libraries(lab6.elf ${330_LIBS} intervalTimer buttons_switches)
set_target_properties(lab6.elf PROPERTIES LINKER_LANGUAGE CXX)