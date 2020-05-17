# Libft - @ Codam Coding College
My approach to making some of the Standard C Library functions.

#### How do I use it?
What we should do first is compiling everything and making it a static library. Luckily there is something called a Makefile.
This can automate some processes for you, for example, it can follow a few rules that otherwise I would have to do myself.

So run these commands in order.
```
git clone https://github.com/bdekonin/libft.git
cd libft
make
```
If you include the `libft.h` in your project. You can now compile with the `libft.a` and use my functions

#### Makefile Commands
- `make` - Used to compile everything. this will make object files and create a library out of it.
- `make clean` - This will remove any temporary files, including the objects files.
- `make fclean` - This command will first run `make clean` once finished, it will also remove the `libft.a` file
- `make re` - This will be used to recompile everything. So it will remove any files it would normally have made. Then compile normally with `make`.
- `make bonus` - This will do the same as `make` but will also compile the existing bonus files.

