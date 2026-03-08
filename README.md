# GapBuffer---Implementation
A GapBuffer is a data structure used commonly in text-editors like Emacs. This is my implementation of the data structure in Java and C.

A gapbuffer makes inserting and deleting characters at the cursor very fast and efficient, and is used a lot in text editors.

The data structure is initialized with the gap being as large as the array:
_ _ _ _ _ _ _ _ _ _, for array size 10

when adding characters the gap gets smaller, character by character
H E L L O _ _ _ _ _

when moving the cursor left or right, the characters get moved accordingly to either the start or end of the gap, this way the gap is always where the cursor is,
this makes inserting characters in the middle or beggining of the array much faster and efficient, since we dont have to constantly make a new array with where the gap should be

move cursor left twice: H E L _ _ _ _ _ L O
move cursor right twice: H E L L O _ _ _ _ _

when the gap runs out, the array get reallocated to a new array which is bigger than the previous one, typically double the size, and the gap is put at where the cursor is

H E L L O W O R L _    ==>   H E L L O W O R L D _ _ _ _ _ _ _ _ _ _    or  H _ L L O W O R L D   ==>   H E _ _ _ _ _ _ _ _ _ _ L L O W O R L D

for redability I showed the gaps as underscores '_', but for my implementation, the gap is the empty character '\u0000' in Java or '\0' in C. This is what the elements of 
a new char[] array are initialized too. Also in my code, I made the gaps printied as '_' for showcase purposes, as I made my own show() method to print the buffer.
But in actuallity of course the gap is not printed or shown in real implemntations and usages of the data structure.
