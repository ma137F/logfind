# logfind
This program is an attempt at a solution of project logfind from LCTHW book,
## Summary 
This binary acts as a very basic form of 'grep' that prints out the filenames which contain the strings passed to it, 
## Compilation 
<code>$ gcc logfind.c -o logfind.out</code>
## Example usage
Single string:
<br><code>$ ./logfind.out one
one.txt
one_two.txt
one_two_three.txt
</br></code>

Multiple strings:
<br><code>$ ./logfind.out -o one two three
one.txt
one_two.txt
one_two.txt
one_two_three.txt
one_two_three.txt
one_two_three.txt</br></code>

Note:<br>
<code>The filenames are printed for every 'hit' of the provided string.</code></br>
