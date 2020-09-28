# Code Style Guide

All of the code in the project should follow a single, consistent style. Below are best practices and example(s). Before complaining, please note that this project will ideally remain accessible to relatively new programmers. Not all brilliant minds are coders, everyone has potential to contribute to a game.

Before complaining about how slow a routine is, or how bulky a type is, remember this is a text-parsing RPG with no real-time components. We will be just fine.

## Code Guidelines

The following is rather not-negotiable within this project:

0. Indentation should use tabs instead of spaces. Every editor can display tabs to the individual coder's preference.
1. No using declarations for namespaces. Keep the global namespace tidy.
2. No usage of 'auto', it is not helpful to people learning the game's code.
3. Avoid lambdas and macros. This game does not need to be blazingly fast, and the preference is nicely documented, easy-to-understand functions.
4. Prefer basic types 'int' over 'int32'.
			If you absolutely need more that 32 bits, use int64_t.
5. Avoid unsigned integers.
6. Avoid floats unless absolutely necessary.

## Code Example

Here's an example that illustrates the most common points of style:

````c++
int foo( int arg1, int *arg2 )
{
	if( arg1 < 5 ) {
		switch( *arg2 ) {
			case 0:
					return arg1 + 5;
					break;
			case 1:
					return arg1 + 7;
					break;
			default:
					return 0;
					break;
		}
	} else if( arg1 > 17 ) {
		int i = 0;
		while( i < arg1 ) {
			printf( _( "Really long message that's pointless except for the number %d and for its "
								 "length as it's illustrative of how to break strings properly.\n" ), i );
		}
	}
	
	return 0;
}
````
