CC = cl
CFLAGS = /W4

COMMON_SOURCES = node.c tree.c nodedata.c
COMMON_HEADERS = node.h nodedata.h tree.h

MAIN_SOURCES = main.c $(COMMON_SOURCES)
MAIN_TARGET = tree.exe

TEST_SOURCES = test_tree.c $(COMMON_SOURCES)
TEST_TARGET = test_tree.exe

all: $(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_SOURCES) $(COMMON_HEADERS)
	$(CC) $(CFLAGS) /Fe:$(MAIN_TARGET) $(MAIN_SOURCES)

$(TEST_TARGET): $(TEST_SOURCES) $(COMMON_HEADERS)
	$(CC) $(CFLAGS) /Fe:$(TEST_TARGET) $(TEST_SOURCES)

run: $(MAIN_TARGET)
	$(MAIN_TARGET)

test: $(TEST_TARGET)
	$(TEST_TARGET)

clean:
	del *.exe *.obj
