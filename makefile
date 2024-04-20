OUTPUT_DIR := output
TARGET := $(OUTPUT_DIR)/test
TEST_TARGET := $(OUTPUT_DIR)/test.o
PROTOCOL_STREAM_TARGET := $(OUTPUT_DIR)/protocolstream.o
CXXFLAGS := -g -Wall -O0 -std=c++17

.PHONY: clean

$(TARGET): $(TEST_TARGET) $(PROTOCOL_STREAM_TARGET) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): test.cpp protocolstream.h | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROTOCOL_STREAM_TARGET): protocolstream.cpp protocolstream.h | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTPUT_DIR) :
	mkdir -p $@

clean:
	rm -rf output