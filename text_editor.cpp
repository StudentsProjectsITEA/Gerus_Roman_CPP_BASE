#include <iostream>

// main text editor comand
const char* PRINT_CMD = "PRINT";
const char* SELECT_CMD = "SELECT";
const char* COPY_CMD = "COPY";
const char* PASTE_CMD = "PASTE";
const char* MOVE_CMD = "MOVE";
const char* CUT_CMD = "CUT";
const char* SHOW_CMD = "SHOW";
const char* HELP_CMD = "HELP";

// promt when user select help command
const char* HELP_PROMT = R"(There are 8 commands available including this command: 
  print: 'some_text';
  select: '[start position end position] in current buffer';
  copy: copying selected text;
  paste: pasting copied text into current buffer; 
  move: 'direction[left/right] length';
  cut: cutting selected text;
  show: displays your buffer.
But remember, if you want to use copy or cut, you need to select some range of text!
Have a nice experience in using text editor!)";

const uint32_t SIZE_FOR_ARRAYS = 300;
enum EnumTest{
  PRINT = 1,
  SELECT,
  COPY,
  PASTE,
  MOVE,
  CUT,
  SHOW,
  HELP,
  UNDEFINED
};

size_t arr_len (const char* temp) {
  size_t count = 0;
  if (temp != nullptr) {
    while (*temp++) {
      ++count;
    }
  }
  return count;
}

int strcmp (const char* str1, const char* str2) {
  if (str1 != nullptr && str2 != nullptr) {
    while (*str1 && *str1 == *str2) {
      ++str1;
      ++str2;
    }
  }
  return (*str1 - *str2);
}

EnumTest check (const char *str ) {
  if (str != nullptr) {
    if (strcmp(str, PRINT_CMD) == 0) {
      return PRINT;
    } else if (strcmp(str, SELECT_CMD) == 0) {
      return SELECT;
    } else if (strcmp(str, COPY_CMD) == 0) {
      return COPY;
    } else if (strcmp(str, PASTE_CMD) == 0) {
      return PASTE;
    } else if (strcmp(str, MOVE_CMD) == 0) {
      return MOVE;
    } else if (strcmp(str, CUT_CMD) == 0) {
      return CUT;
    } else if (strcmp(str, SHOW_CMD) == 0) {
      return SHOW;
    } else if (strcmp(str, HELP_CMD) == 0) {
      return HELP;
    }
  }
  return UNDEFINED;
}

char* copy(char* dst, char* src, const char* const end_of_src) {
  if ((dst != nullptr && src != nullptr && end_of_src != nullptr)) {
    while (src != end_of_src) { 
      *dst++ = *src++;
    }
  }
  return dst;
}

char* print (char *start, const char * const end) {
  if (start != nullptr && end != nullptr && start != end) {
    char arr[SIZE_FOR_ARRAYS] {};
    std::cin >> arr;
    char *begin_arr = arr;
    const char * const end_arr = arr + arr_len(begin_arr);
    if (*begin_arr != '\0' && *start == '\0') {
      while (begin_arr != end_arr) {
        *start++ = *begin_arr++;
      }
    }
    if (*begin_arr != '\0' && *start != '\0') {
      char temp_print_arr [SIZE_FOR_ARRAYS] {};
      char *first_of_temp = temp_print_arr;
      const char * const last_of_temp = temp_print_arr + arr_len(start);
      copy(first_of_temp, start, end);
      while (begin_arr != end_arr) {
        *start++ = *begin_arr++;
      }
      copy(start, first_of_temp, last_of_temp);
    }
  }
  return start;
}

char *move (char *start, const char * const end, const char * const start_of_buff) {
  if (start != nullptr && end != nullptr) {
    char way[SIZE_FOR_ARRAYS] {};
    uint32_t num;
    std::cin >> way >> num;
    if ((start - num) < start_of_buff && strcmp(way, "left") == 0) {
      std::cout << "Out of range!" << std::endl;
      return start;
    } else if ((start + num) > end && strcmp(way, "right") == 0) {
      std::cout << "Out of range!" << std::endl;
      return start;
    }
    if (strcmp(way, "left") == 0) {
      start -= num;
    } else if (strcmp(way, "right") == 0) {
      start += num;
    }
  }
  return start; 
}

char* cut (char *start, char * const end) {
  if (start != nullptr && end != nullptr) {
    char *end_for_cut = end;
    const char * const new_end = start + arr_len(start);
    while (start != new_end) {
      *start++ = *end_for_cut++;
    }
    return (end - 1);
  }
  return start;
}

void clear (char *start) {
  if (start != nullptr) {
    while (*start != '\0') {
      *start++ = '\0';
    }
  }
}

void to_upper (char *start) {
  const char TO_UPPER = 'A' - 'a';
  const char * const end = start + arr_len(start);
  while (start != end && *start != '\0') {
    char& ch = *start++;
    if (ch >= 'a' && ch <= 'z') {
      ch += TO_UPPER;
    }
  } 
}

int main () {
  char user_arr[SIZE_FOR_ARRAYS] {};
  char *begin = user_arr;
  const char * const end = user_arr + SIZE_FOR_ARRAYS;
  char temp_arr [SIZE_FOR_ARRAYS] {};
  uint32_t start_position;
  uint32_t end_position;

  std::cout << "Hello, it's text editor, here you " 
  "can do different operations with text, for more info enter 'help'\n";

  while (true) {
    std::cout << "Enter you command and text: ";
    char command[SIZE_FOR_ARRAYS] {};
    std::cin >> command;
    to_upper(command);
    size_t type = check(command);

    switch (type) {
      case PRINT: {
        start_position = 0;
        end_position = 0;
        begin = print(begin, end);
        break;
      }
      case SELECT: {
        std::cin >> start_position >> end_position;
        if (start_position >= SIZE_FOR_ARRAYS || end_position >= SIZE_FOR_ARRAYS) {
          std::cout << "Your position is out of range!\n";
          start_position = 0;
          end_position = 0;
        }
        break;
      }
      case COPY: {
        if (end_position != 0 && *(user_arr + start_position) != '\0') {
          copy(temp_arr, user_arr + start_position, user_arr + start_position + end_position);
        } else {
          std::cout << "You didn`t select any word!" << std::endl;
        }
        break;
      }
      case PASTE: {
        if (arr_len(temp_arr) != 0) {
          start_position = 0;
          end_position = 0;
          copy(begin, temp_arr, temp_arr + arr_len(temp_arr));
          begin += arr_len(begin);
        } else {
          std::cout << "You didn`t copy any word, unable to paste." << std::endl;
        }
        clear(temp_arr);
        break;
      }
      case MOVE: {
        start_position = 0;
        end_position = 0;
        begin = move(begin, end, user_arr);
        break;
      } 
      case CUT: {
        begin = cut(user_arr + start_position, user_arr + start_position + end_position);
        break;
      } 
      case SHOW: {
        std::cout << user_arr << std::endl;
        break;
      }
      case HELP: {
        std::cout << HELP_PROMT << std::endl;
        break;
      } 
      default: {
        std::cout << "You entered wrong command";
        return 0;
      }
    }
  }
}