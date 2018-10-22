# About this test suite

This test suite was designed and used for my bachelor thesis "Evaluating the performance of open source static analysis tools".

This test suite was inspired by, and used in conjunction with the test suite presented in "Test-driving static analysis tools in search of c code vulnerabilities" by George Chatzieleftheriou and Panagiotis Katsaros.

## How to use this test suite

The .c files included in this test suite need to be preprocessed before use. The shellscript ```preprocess_files.sh``` can be used to accomplish this.

- ```preprocess_files.sh``` needs a unix like environment with gpp installed to work. 
- Usage: ```preprocess_files.sh [directory to process]```, for example ```preprocess_files.sh ./integers/overflow/```.
This should generate the sub directories ```test_correct``` (safe calls to unsafe functions), ```test_incorrect``` (unsafe calls to unsafe functions), ```test_lib_correct``` (safe functions, no entry point), ```test_lib_incorrect``` (unsafe functions, no entry point) and ```test_correct_catch_bad``` (safe calls to safe functions).
