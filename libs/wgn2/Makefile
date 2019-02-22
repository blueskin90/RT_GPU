NAME = wgn2.a

INCLUDES = -I ./includes \
			-I ../glfw/deps \
			-I ../glfw/include \
			-I ../stb_image

SRCS =	./src/Buffers.cpp \
		./src/CommandBuffers.cpp \
		./src/Descriptors.cpp \
		./src/RenderTexture.cpp \
		./src/Shaders.cpp \
		./src/main.cpp \

OBJS =	./Buffers.o \
		./CommandBuffers.o \
		./Descriptors.o \
		./RenderTexture.o \
		./Shaders.o \
		./main.o \

all: $(NAME)

$(NAME):
	@g++ $(INCLUDES) -c $(SRCS)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
clean:
	@rm -f $(OBJS)
	@rm -f $(NAME)
