CC = g++ -std=c++17
INC = include
SRC = src
BUILD = build
INCLUDE = -I ./$(INC)

TARGET = main

OBJECTS = $(BUILD)/main.o

$(TARGET): $(OBJECTS)
	@$(CC) -o $@ $^ $(INCLUDE)

$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(BUILD)
	@$(CC) -o $@ -c $^ $(INCLUDE)

clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD) $(TARGET)