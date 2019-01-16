#Challenge #1

##Instructions
Given a string, find the length of the longest substring without repeating characters.

##Description
This program recieves a string as an input and finds the longest substring without repeating characters.
We initialize two lists called letterList and words.
Then we iterate over the string and if the character in word[i] is not in letterList then we append it, we repeat this process until we get a letter that is already in letterList, when this happens we join all the characters in the list and append the substring to words and empty letterList.
Once we are done iterating over the string we will have a set of strings in words list, now we just check for the longest string in the list and return it as wll as its length.
