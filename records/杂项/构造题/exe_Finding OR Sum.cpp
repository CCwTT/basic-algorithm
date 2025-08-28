//https://codeforces.com/contest/2078/problem/E
//interactive，constructive
/*
There are two hidden non-negative integers x and y (0≤x,y<230). You can ask no more than 2 queries of the following form.
    Pick a non-negative integer n
(0≤n<2^30). The judge will respond with the value of (n|x)+(n|y), where | denotes the bitwise OR operation. 
After this, the judge will give you another non-negative integer m(0≤m<2^30). You must answer the correct value of (m|x)+(m|y).
*/
//We only need to know for each bit how many 1 are there in total.
/*
The queries are …0101 and …1010.
It's easier to look at the case with only two binary digits first.
Let the result of query 01 be q1 and 10 be q2.
Observe that if 
q2=100 then the first (from the right) digit of both x and y is 0.
q2=101 then the first (from the right) digit of one of x or y is 0, and the other one is 1.
q2=110 then the first (from the right) digit of both x and y is 1.
Similarly, if
q1=102 then the second (from the right) digit of both x and y is 0.
q1=100 then the second (from the right) digit of one of x or y is 0, and the other one is 1.
q1=110 then the second (from the right) digit of both x and y is 1.
To generalize to every other digit, apply the same logic to every consecutive pair of digits in x and y. Note that you must account for the carries from the digits before too.
After this, you will know for every digit position whether both x
and y are 0, are 1, or have one 0 and one 1. You can use this information to find (m|x)+(m|y) for any m.
Time complexity: O(logmax(x)) per test case.
*/