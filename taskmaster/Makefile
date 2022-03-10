CC := g++
CFLAGS := -g -std=c++1z -Wall -Werror
TFLAGS := -I $GTEST_INC -L $GTEST_LIB -lgtest -lgtest_main -lpthread

SRC_PATH := .
OBJ_PATH := obj
BIN_PATH := bin


# separating source and test files
TESTS := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,_test.cpp)))
ALLCPP := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.cpp)))
SRC := $(filter-out $(TESTS), $(ALLCPP))

# separating obj files and the lib which can be linked to the test targets
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
LIB := $(filter-out $(OBJ_PATH)/main.o, $(OBJ))


TARGET_MAIN := $(BIN_PATH)/main
TARGET_TESTS := $(addprefix $(BIN_PATH)/, $(notdir $(basename $(TESTS))))


default: main


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET_MAIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(BIN_PATH)/%: %.cpp $(LIB)
	$(CC) $< $(TFLAGS) $(CFLAGS) -o $@ $(LIB)


.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH)

.PHONY: all
all: makedir $(TARGET_MAIN) $(TARGET_TESTS)

.PHONY: main
main: makedir $(TARGET_MAIN)

.PHONY: tests
tests: makedir $(TARGET_TESTS)

.PHONY: run_tests
run_tests: $(TARGET_TESTS)
	@echo $^ > $(BIN_PATH)/run_tests.sh
	@sed -i "s/ /; /g" $(BIN_PATH)/run_tests.sh
	@chmod u+x bin/run_tests.sh
	@eval $(BIN_PATH)/run_tests.sh
	@rm $(BIN_PATH)/run_tests.sh

.PHONY: clean
clean:
	$(RM) $(TARGET_MAIN) $(TARGET_TESTS)

.PHONY: distclean
distclean: clean
	$(RM) $(OBJ)

.PHONY: superclean
superclean:
	$(RM) -r $(OBJ_PATH) $(BIN_PATH)	