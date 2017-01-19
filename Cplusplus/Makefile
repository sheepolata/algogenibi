PROGRAM = algogen

BIN_DIR = bin
OBJ_DIR = obj
INCLUDE_DIR = -I/usr/include/ -I./inc


SRC_DIR = src
# PACKAGES= opencv glibmm-2.4 glib-2.0 gtkmm-3.0 gtk+-3.0 gdkmm-3.0


#*******

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(addprefix $(OBJ_DIR)/,$(notdir $(SRCS:.cpp=.o)))

#*******

CPPFLAGS = -g -Wall -std=c++14

LIB_DIR = -L/usr/include/
LIBS = -L/usr/local/lib 

# GTK_LDFLAGS = $(shell pkg-config --libs $(PACKAGES))

#*************************

#*******  FLAGS  *********

#*************************

LDFLAGS  = $(LIB_DIR) $(LIBS) 
# CFLAGS  = `pkg-config --cflags $(PACKAGES)`

#****************************

#******     REGLES     ******

#****************************

$(BIN_DIR)/$(PROGRAM): $(OBJ)

	g++ $(CPPFLAGS) $+ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp

	g++ $(CPPFLAGS) -c $(INCLUDE_DIR) $< -o $@

	

###############################

default: $(BIN_DIR)/$(PROGRAM)

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(PROGRAM)

run : $(BIN_DIR)/$(PROGRAM)

	./$(BIN_DIR)/$(PROGRAM)
