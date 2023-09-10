#include "stdio.h"
#include "stdlib.h"

#include "getoutinfo.h"
#include "sorter.h"

int main()
{
    // Why is this required? It's not obvious if you don't know the
    // implementation of ReadFile
    char* text = (char* ) calloc(text_len, sizeof(char));

    int line_amount = 1;

    // It's generally a bad idea to have condition with side effects
    // You can rewrite this as follows:
    //
    // // Read file contents
    // bool success = ReadFile(text, &line_amount)
    // // If failed to read
    // if (!success)
    // {
    //     // Return error
    //     return 1;
    // }
    //
    if (!ReadFile(text, &line_amount))
        return 1;

    // Why is this required? It's not obvious if you don't know the
    // implementation of CreatePtrArray.
    char** lines_pointers = (char** ) calloc(line_amount, sizeof(char*));
    lines_pointers[0] = text;

    // It looks like this function does not create ptr array. You create it
    // yourself on line 32. Consider renaming function.
    CreatePtrArray(lines_pointers, text);

    // Std sort? What comparator does it use? Consider renaming function.
    StdSort(lines_pointers, line_amount);

    // Print text? What text? You are passing `lines_pointers` to it, not `text`
    PrintText(lines_pointers, line_amount);

    free(lines_pointers);
    free(text);
}
