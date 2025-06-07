OBJS := main.o cmd_handle.o cmd_ls.o cmd_cp.o
TARGET := tinyshell

$(TARGET):$(OBJS)
	@gcc $^ -o $@
	@echo "Done."

%.o:%.c
	@gcc -c $< -o $@

clean:
	@rm *.o $(TARGET)
	@echo "Clean."
