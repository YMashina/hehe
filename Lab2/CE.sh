#!/bin/bash
g++ ./Source/Main.cpp ./Source/l_impl.cpp -o Lab2
echo -e 'Test 1:\n'
echo 'Input sequence:'
cat ./Tests/Test1.txt
./Lab2 < ./Tests/Test1.txt
echo -e '\nTest 2:\n'
echo 'Input sequence:'
cat ./Tests/Test2.txt
./Lab2 < ./Tests/Test2.txt
echo -e '\nTest 3:\n'
echo 'Input sequence:'
cat ./Tests/Test3.txt
./Lab2 < ./Tests/Test3.txt
echo -e '\nTest 4:\n'
echo 'Input sequence:'
cat ./Tests/Test4.txt
./Lab2 < ./Tests/Test4.txt
echo -e '\nTest 5:\n'
echo 'Input sequence:'
cat ./Tests/Test5.txt
./Lab2 < ./Tests/Test5.txt