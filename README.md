# samples

This is a collection of solutions to some of my favorite programming problems. Here are the descriptions.

## boyGirl.cpp

This is a program that takes as input a string of the form
GGBGBB which represents a seating arrangment of boys and 
girls in row. The program will then calculate the minimum
numbers of swaps necessary to ensure K girls will be seated
together. Note we may only swap adjacent seats.

## candy.cpp

This is a program that takes as input an array of scores
where the ith score corresponds to the ith student sitting
in a row. The teacher wants to give out candy to the students
subject to 2 constraints.

1) Every student gets at least one piece of candy.

2) If a student scored higher than one of their neighbors,
   they must receive more candy than that neighbor.

This program will calculate the minimum amount of candy needed.

## kSub.cpp

This is a program that takes as input an array and a
number K and determines how many subsequences have
sums that are divisible by K.

## pairs.cpp

This is a program that takes as input a string consisting of lower-case and
and capital letters and determines the last position that a "pair" occurs.
A pair is defined to be a capital letter followed immediately by its lower-
case form. Also once two letters pair up, they are removed from further
consideration, similar to how pieces cancel out in Dr. Mario. For example,
ABba would have 2 valid pairs. 

## polish.cpp

This is a simple program that implements a reverse polish calculator.

## querySystem.cpp

This is a program that implements a simple query system.

## robot.cpp

This is a program that if given directions for a robot
that it will repeatedly follow, will determine whether 
the robot will remain in a bounded area for all time.

## selfSimilarity.cpp

This is a program that takes as input a string and determines its self-similarity
or the total number of places in all the beginnings of its substrings that match
the whole string.

## stringPerm.cpp

This is a program that takes as input a string and then a list of positions
we are allowed to swap. It will then return the string with the highest
lexicographical order, we can obtain.
