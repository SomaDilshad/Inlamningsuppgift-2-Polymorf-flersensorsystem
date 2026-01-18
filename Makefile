CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = sensorsystem_inl2
SOURCES = main.cpp sensor.cpp measurement.cpp storage.cpp utils.cpp threshold.cpp systemcontroller.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

uml:
	# Installera mermaid-cli först: npm install -g @mermaid-js/mermaid-cli
	mmdc -i uml_diagram.md -o uml_diagram.png
