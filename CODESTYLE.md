# Code Style Guidelines

This guidelines is for C code. Mainly derived from [Linux kernel coding style](https://github.com/torvalds/linux/blob/master/Documentation/process/coding-style.rst).

**TL;DR - 4 spaces, small code, useful comments**

## Don't get things too large

- Try to keep **lines under 80 characters**. It's okay if it goes over by a few, but 100 character lines or larger are definitely unacceptable.
- **Don't** let files get too large (over 1500 lines of code).

## Spaces

- Use **4 spaces** to indent.
- Try to stay under 8 levels of indentation.
- Add spaces between operators so they line up when appropiate.
- Separate functions by a newline for readability.
- Use a space after ```if```, ```else```, ```for```, ```do```, ```while```, ```switch```, ```case```, ```try```, ```catch```, etc. but not with ```sizeof```.
- When breaking conditionals, indent following lines of the conditional with 8 spaces and the statement body with 4 spaces.

Example:
```c
height = get_width()
width  = get_height()

if (THIS_LONG_VARIABLE_NAME_ONE_TWO == ANOTHER_LONG_VARIABLE_NAME_THREE ||
        THIS_LONG_VARIABLE_NAME_FOUR_FIVE == ANOTHER_LONG_VARIABLE_NAME_SIX)
{
    printk("LOL");
}

bool okay_to_do =
        one_okay   && two_okay   && three_okay &&
        four_okay  && five_okay  && six_okay   &&
        seven_okay && eight_okay && nine_okay;
```

## Function declarations

In case your function parameters don't fit within the defined line length use following style. Indention for follow up lines is exactly four spaces.

Try to lowen the amount of parameters, except for constructor.

Example:
```c
int function_with_many_args(int LONG_PARAMETERS_NAME_ONE_TWO, int LONG_PARAMETERS_NAME_THREE_FOUR,
    int LONG_PARAMETERS_NAME_FIVE_SIX, int LONG_PARAMETERS_NAME_SEVEN_EIGHT)
{
    return 1;
}
```

## Bracing and indentation

### If statements

Do **not** unnecessarily use braces where a single statement will do.
```c
if (condition)
    action();
```
and
```c
if (condition)
    do_this();
else
    do_that();
```

This does not apply if only one branch of a conditional statement is a single statement; in the latter case use braces in both branches:
```c
if (condition) {
    do_this();
    do_that();
} else {
    otherwise();
}
```

## Commenting

Generally, you want your comments to tell **what** your code does, **not how**.

- **Don't** make it like this:
```c
// Draw "Loading" screen
draw_load_screen(L"Loading...", driver, font);
```

- For comments with text, be sure to add a space between the text and the comment tokens:
```c
DoThingHere(); // This does thing
```

## Addendum

This rule is _still_ being applied to this repo. You can help to fix wrong style in code or watch PRs for wrong code style.

_This rule may change to fit our coding pattern._
