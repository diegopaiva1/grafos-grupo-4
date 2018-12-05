PROJECT_NAME = searching
CPP_FILES := $(shell find . -name "*.cpp")

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(CPP_FILES)
	@ echo 'Building binary using G++ linker: $@'
	@ g++ -std=c++11 -Wall $(CPP_FILES) -o $(PROJECT_NAME)
	@ echo 'Finished building binary: $@'
	@ echo ' '

clean:
	@ echo 'Removed binary: $(PROJECT_NAME)'
	@ rm -rf $(PROJECT_NAME)
	@ echo ' '
