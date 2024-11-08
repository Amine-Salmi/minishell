#include <stdio.h>
#include <string.h>

// Custom string length function (if needed)
size_t ft_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char *parse_strcpy(char *dst, const char *src, size_t *buffer_index) {
    size_t i = 0;
    size_t src_len = ft_strlen(src);

    // Print the source string for debugging purposes
    printf("src: %s\n", src);

    // Copy characters from src to dst starting from *buffer_index position in buffer
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }

    // Null-terminate the copied string in the buffer
    dst[i] = '\0';

    // Update buffer_index to reflect the number of characters copied
    *buffer_index += src_len;

    // Print the modified destination for debugging purposes
    printf("dst: %s\n", dst);
    return dst;
}

int main() {
    char buffer[100] = {0};  // Assuming a buffer with enough space
    size_t buffer_index = 5;  // Initial buffer index (not starting from 0)
    const char *value = "Hello, world!";

    // Copy the string to buffer starting at index 5
    parse_strcpy(&buffer[buffer_index], value, &buffer_index);

    // Print the buffer and buffer_index after the copy
    printf("Buffer after first copy: %s\n", buffer);
    printf("Buffer index: %zu\n", buffer_index);

    // Now let's append another string starting at the new buffer index
    const char *more_text = " How are you?";
    parse_strcpy(&buffer[buffer_index], more_text, &buffer_index);

    // Print the buffer and buffer_index after the second copy
    printf("Buffer after second copy: %s\n", buffer);
    printf("Buffer index: %zu\n", buffer_index);

    return 0;
}
