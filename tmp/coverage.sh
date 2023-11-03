set -e

clang++ -fprofile-instr-generate -fcoverage-mapping simple.cpp -o simple
./simple
llvm-profdata merge -sparse default.profraw -o simple.profdata
llvm-cov show ./simple -instr-profile=simple.profdata