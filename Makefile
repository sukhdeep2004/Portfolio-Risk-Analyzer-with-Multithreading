# ===============================
# Compiler and flags
# ===============================
CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2
LDFLAGS  := -pthread

# ===============================
# Target
# ===============================
TARGET := risk_analyzer

# ===============================
# Source files
# ===============================
SRCS := main.cpp \
        CsvReader.cpp \
        Returns.cpp \
        Statistics.cpp \
        ParallelCovariance.cpp \
        PortfolioRisk.cpp \
        Annualization.cpp \
        Timer.cpp

OBJS := $(SRCS:.cpp=.o)

# ===============================
# Build rules
# ===============================
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===============================
# Clean
# ===============================
clean:
	del /Q *.o *.exe 2>nul || true
