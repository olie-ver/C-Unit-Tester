Since Assert/Expects tests all draw from the same logic,
creating tests for both Assert/Expects is redundant, as the only
difference in their behavior is that Assert tests terminate testing
for a Test Suite upon failure, whereas Expects tests do not. 
Therefore, in this testing directory, I will be mainly testing Expects
tests for pass/fail behavior. However, Asserts tests will still be created
mainly for the purpose of testing that they terminate testing for a test suite
upon failure.