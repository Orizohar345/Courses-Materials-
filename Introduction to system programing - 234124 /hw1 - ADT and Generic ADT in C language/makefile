CC = gcc
MATAMIKYA_OBJS = matamikya.o matamikya_print.o matamikya_tests.o matamikya_main.o
AMOUNT_SET_STR_OBJS = amount_set_str.o amount_set_str_test.o amount_set_str_main.o
MATAMIKYA_EXEC = matamikya
AMOUNT_SET_STR_EXEC = amount_set_str
DEBUG_FLAG =- = -g -DNDEBUG
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror 
MATAIKYA_FLAGS = -L. -lmtm -lm -las

$(MATAMIKYA_EXEC) : $(MATAMIKYA_OBJS)
	$(CC) $(CFLAGS) $(MATAMIKYA_OBJS) $(MATAIKYA_FLAGS) -o $@
$(AMOUNT_SET_STR_EXEC) : $(AMOUNT_SET_STR_OBJS)
	$(CC) $(CFLAGS) $(AMOUNT_SET_STR_OBJS) -o $@

amount_set_str.o: amount_set_str.c amount_set_str.h
amount_set_str_main.o: amount_set_str_main.c amount_set_str_test.h \
 amount_set_str.h tests/test_utilities.h
amount_set_str_test.o: amount_set_str_test.c amount_set_str.h \
 amount_set_str_test.h tests/test_utilities.h

matamikya.o : matamikya.c amount_set.h matamikya.h set.h matamikya_print.h
matamikya_print.o : matamikya_print.c matamikya_print.h
matamikya_main.o : tests/matamikya_main.c tests/matamikya_tests.h tests/test_utilities.h
matamikya_tests.o : tests/matamikya_tests.c tests/matamikya_tests.h matamikya.h tests/test_utilities.h

clean:
	rm -f $(MATAMIKYA_OBJS) $(AMOUNT_SET_STR_OBJS) $(MATAMIKYA_EXEC) $(AMOUNT_SET_STR_EXEC)