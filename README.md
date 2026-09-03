# Compiler (Not set on any name as of now)

### to do
After some thinking i decided that lexer needs to be rewritten to accomodate for the preprocessor, previously i thought that i'd make the preprocessor and tokenizer 2 different things, but it would harm compiler's efficiency too much. Additionally i'll organize the lexer better and probably i'm gonna create a new function to go over the tokens one by one so that i have more control.

### notes
Compiler:
(Lexer -> Preprocessor) -> Parser -> AST -> LLVM

For an individual file:
Preprocessor ->
    Initialize:
        - BufferList
        - StringList
        - MacroTable
    Add the filename to the StringList in Preprocessor
    Create a buffer and IncludeFrame for filename

    ? Perhaps create a function that takes in a filename and pushes does all 3

    Pass the reference:
        - Error handler
        - Token Streams

    Begin the Preprocessor
        Get the next token, if it's a preprocessor directive, check which is it:
            -   If it's include, then create new buffer, include frame for that file, and move into it while preserving position pointer for the previous file,
                continue, until EOF.
            -   If it's ifdef, check if macro exists in MacroTable if it does, add tokens after it, increment ifdef depth by 1, continue until endif
        Otherwise either push it to token stream, or check if it is an identifier, if it is check if it fits with a previously defined macro.

        At the end i'll probably also add a parameter to only tokenize the source code.